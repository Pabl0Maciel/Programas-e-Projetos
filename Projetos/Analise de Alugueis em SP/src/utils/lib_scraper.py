#################################################################################################################
###                                                BIBLIOTECAS                                                ###
#################################################################################################################
import json
import requests
import logging
import time
import pandas as pd
import random
from datetime import datetime
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional, List, Dict, Any

#################################################################################################################
###                                            CLASSES E ESTRUTURAS                                           ###
#################################################################################################################
@dataclass
class Segment:
    label: str
    bedrooms_min: Optional[int] = None
    bedrooms_max: Optional[int] = None
    price_min: Optional[float] = None
    price_max: Optional[float] = None
    extra_filters: dict = field(default_factory=dict)

#################################################################################################################
###                                                PAYLOAD                                                    ###
#################################################################################################################
def build_payload(
        fields: List[str], 
        offset: int, 
        page_size: int, 
        segment: Optional[Segment] = None
) -> dict:

    payload = {
        "slug": "sao-paulo-sp-brasil",
        "topics": [],
        "fields": fields,
        "sorting": {"criteria": "RELEVANCE", "order": "DESC"},
        "pagination": {"pageSize": page_size, "offset": offset},
        "context": {"listShowing": True, "mapShowing": False, "numPhotos": 1, "isSSR": False},
        "filters": {
            "enableFlexibleSearch": True,
            "businessContext": "RENT",
            "availability": "ANY",
            "occupancy": "ANY",
            "location": {
                "coordinate": {"lat": -23.55052, "lng": -46.633309},
                "viewport": {
                    "east":  -46.506107919677724, "north": -23.453390975915813,
                    "south": -23.647577310278265, "west":  -46.760510080322256,
                },
                "neighborhoods": [], "countryCode": "BR",
            },
            "priceRange": [], "partnerIds": [], "specialConditions": [],
            "excludedSpecialConditions": [], "blocklist": [], "selectedHouses": [], "categories": [],
            "houseSpecs": {
                "area": {"range": {}}, "houseTypes": [], "amenities": [], "installations": [],
                "bathrooms": {"range": {}}, "bedrooms": {"range": {}}, 
                "parkingSpace": {"range": {}}, "suites": {"range": {}},
            },
        },
        "locationDescriptions": [{"description": "sao-paulo-sp-brasil"}],
    }

    if segment is None:
        return payload

    bedroom_range = {}
    if segment.bedrooms_min is not None: bedroom_range["min"] = segment.bedrooms_min
    if segment.bedrooms_max is not None: bedroom_range["max"] = segment.bedrooms_max
    if bedroom_range:
        payload["filters"]["houseSpecs"]["bedrooms"]["range"] = bedroom_range

    if segment.price_min is not None or segment.price_max is not None:
        price_range = {}
        if segment.price_min is not None: price_range["min"] = segment.price_min
        if segment.price_max is not None: price_range["max"] = segment.price_max
        payload["filters"]["priceRange"] = [price_range]

    for key, value in segment.extra_filters.items():
        if key == "houseTypes":
            payload["filters"]["houseSpecs"]["houseTypes"] = value
        else:
            payload["filters"][key] = value

    return payload

#################################################################################################################
###                                                     REQUEST                                               ###
#################################################################################################################
def fetch_page(
    base_url: str,
    session: requests.Session,
    fields: List[str],        # ← Adicionado para fluir até o payload
    offset: int,
    page_size: int,
    max_retries: int,
    retry_wait: int,
    log: logging.Logger,
    segment: Optional[Segment] = None
) -> Optional[dict]:
    
    # Repassando os parâmetros corretamente para a montagem
    payload = build_payload(fields, offset, page_size, segment)

    for attempt in range(1, max_retries + 1):
        try:
            resp = session.post(base_url, json=payload, timeout=30)
            if resp.status_code == 200:
                return resp.json()
            elif resp.status_code == 429:
                wait = retry_wait * attempt
                log.warning(f"Rate limit (429) — aguardando {wait}s...")
                time.sleep(wait)
            elif resp.status_code == 400:
                log.warning(f"HTTP 400 no offset {offset} — limite/fim da paginação.")
                return None
            elif resp.status_code in (401, 403):
                log.error(f"Acesso negado ({resp.status_code}).")
                return None
            else:
                log.warning(f"HTTP {resp.status_code} na tentativa {attempt}/{max_retries}")
                time.sleep(retry_wait)
        except requests.exceptions.RequestException as e:
            log.warning(f"Erro de conexão/timeout: {e}")
            time.sleep(retry_wait)
        except Exception as e:
            log.error(f"Erro inesperado no request: {e}")
            return None

    log.error(f"Falhou após {max_retries} tentativas no offset {offset}")
    return None

#################################################################################################################
###                                                 SCRAPE DE SEGMENTO                                        ###
#################################################################################################################
def scrape_segment(
    base_url: str,            # ← Recebe URL da configuração superior
    session: requests.Session,
    fields: List[str],        # ← Recebe a lista de colunas para puxar
    segment: Optional[Segment],
    max_pages: int,
    page_size: int,
    delay_min: float,
    delay_max: float,
    max_retries: int,
    retry_wait: int,
    segment_break_warning: int,
    seen_ids: set,
    log: logging.Logger
) -> list[dict]:
    
    label = segment.label if segment else "sem_segmento"
    segment_listings = []
    offset = 0
    page_num = 0
    total_estimated_logged = False

    log.info("─" * 60)
    log.info(f"Segmento: {label}")
    log.info("─" * 60)

    while page_num < max_pages:
        log.info(f"📄 Página {page_num + 1} | offset={offset} | acumulado={len(segment_listings)}")

        # Repassa com precisão os parâmetros exigidos pelo base_url e payload
        data = fetch_page(base_url, session, fields, offset, page_size, max_retries, retry_wait, log, segment)
        if data is None:
            break

        if not total_estimated_logged:
            total_estimated = extract_total_from_response(data)
            log.info(f"📊 Total estimado do segmento '{label}': {total_estimated or 'Desconhecido'}")
            total_estimated_logged = True

        listings_raw = extract_listings_from_response(data)
        if not listings_raw:
            break

        new_count, duplicate_count = 0, 0
        for item in listings_raw:
            if not isinstance(item, dict): continue
            item_id = item.get("id")
            
            if item_id and item_id not in seen_ids:
                seen_ids.add(item_id)
                flat_item = flatten_listing(item)
                flat_item["segment"] = label
                segment_listings.append(flat_item)
                new_count += 1
            else:
                duplicate_count += 1

        log.info(f"   → {new_count} novos | {duplicate_count} duplicados")

        if new_count == 0: break

        offset += page_size
        page_num += 1

        delay = random.uniform(delay_min, delay_max)
        time.sleep(delay)

    return segment_listings

#################################################################################################################
###                                                 SCRAPER PRINCIPAL                                         ###
#################################################################################################################
def scrape(
    url: str,
    headers: dict,
    fields: list,
    segments: List[Segment],
    log: logging.Logger,
    log_file: Path,
    output_file: Path,
    max_pages: int,
    page_size: int,
    delay_min: float,
    delay_max: float,
    max_retries: int,
    retry_wait: int,
    segment_break_warning: int,
    use_segments: bool = True
) -> pd.DataFrame:
    
    session = requests.Session()
    session.headers.update(headers)
    all_listings = []
    seen_ids = set()

    log.info("=" * 60)
    log.info("QuintoAndar Scraper — Iniciando...")
    log.info("=" * 60)

    target_segments = segments if use_segments else [None]

    for idx, segment in enumerate(target_segments, start=1):
        # Chama passando todos os argumentos herdados do bloco de configuração
        segment_rows = scrape_segment(
            base_url=url,
            session=session,
            fields=fields,
            segment=segment,
            max_pages=max_pages,
            page_size=page_size,
            delay_min=delay_min,
            delay_max=delay_max,
            max_retries=max_retries,
            retry_wait=retry_wait,
            segment_break_warning=segment_break_warning,
            seen_ids=seen_ids,
            log=log
        )
        
        all_listings.extend(segment_rows)
        if idx < len(target_segments):
            time.sleep(random.uniform(5, 10))

    df = pd.DataFrame(all_listings)

    if not df.empty:
        numeric_cols = ["rent", "totalCost", "area", "bedrooms", "bathrooms"]
        for col in numeric_cols:
            if col in df.columns:
                df[col] = pd.to_numeric(df[col], errors="coerce")

        if "rent" in df.columns and "area" in df.columns:
            df["rentPerSqm"] = df.apply(
                lambda row: round(row["rent"] / row["area"], 2) if row.get("rent") and row.get("area") else None,
                axis=1
            )
        
        df = df.drop_duplicates(subset=["id"], keep="first").reset_index(drop=True)
        df.to_csv(output_file, index=False, encoding="utf-8-sig")

    log.info(f"✅ Coleta concluída! Salvo em: {output_file}")
    return df

#################################################################################################################
###                                            FUNÇÕES DE PARSING PURO                                        ###
#################################################################################################################
def flatten_listing(item: dict) -> dict:
    return {
        "id": item.get("id"), "type": item.get("type"), "address": item.get("address"),
        "neighbourhood": item.get("neighbourhood"), "rent": item.get("rent"),
        "totalCost": item.get("totalCost"), "area": item.get("area"),
        "bedrooms": item.get("bedrooms"), "bathrooms": item.get("bathrooms"),
        "parkingSpaces": item.get("parkingSpaces"), "isFurnished": item.get("isFurnished")
        # Mantive a versão resumida do flatten, adicione o resto dos campos base se precisar
    }

def extract_listings_from_response(data: dict) -> list:
    if isinstance(data.get("hits"), dict) and isinstance(data["hits"].get("hits"), list):
        return [h["_source"] if "_source" in h else h for h in data["hits"]["hits"]]
    return data.get("hits", data.get("listings", data.get("results", [])))

def extract_total_from_response(data: dict) -> Optional[int]:
    if isinstance(data.get("total"), int): return data["total"]
    if isinstance(data.get("hits", {}).get("total"), int): return data["hits"]["total"]
    return None