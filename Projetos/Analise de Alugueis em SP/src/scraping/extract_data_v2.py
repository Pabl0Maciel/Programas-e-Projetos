#!/usr/bin/env python3
"""
extract_data.py
===============
Scraper completo para QuintoAndar — Análise de Aluguéis em SP
Estratégia: segmentação por número de quartos + faixa de preço para contornar
            o limite de ~1000 imóveis por sessão de paginação.

Uso:
    python src/scraping/extract_data.py
    python src/scraping/extract_data.py --pages 50
    python src/scraping/extract_data.py --output custom.csv
    python src/scraping/extract_data.py --no-segment     # comportamento antigo
"""

import requests
import pandas as pd
import time
import json
import logging
import argparse
import random
from pathlib import Path
from datetime import datetime
from dataclasses import dataclass, field
from typing import Optional

# ─────────────────────────────────────────────
#  CONFIGURAÇÕES
# ─────────────────────────────────────────────
BASE_URL  = "https://apigw.prod.quintoandar.com.br/house-listing-search/v2/search/list"

PAGE_SIZE   = 36
MAX_PAGES   = 100       # por segmento
DELAY_MIN   = 1.2
DELAY_MAX   = 3.0
MAX_RETRIES = 3
RETRY_WAIT  = 10

OUTPUT_DIR = Path(__file__).resolve().parents[2] / "data" / "raw"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# ─────────────────────────────────────────────
#  SEGMENTOS DE BUSCA
#  Cada segmento define um conjunto de filtros independente.
#  A API retorna no máximo ~1000 imóveis por combinação de filtros,
#  então dividimos por quartos e, se necessário, por faixa de preço.
# ─────────────────────────────────────────────
@dataclass
class Segment:
    label: str
    bedrooms_min: Optional[int] = None
    bedrooms_max: Optional[int] = None
    price_min: Optional[float] = None
    price_max: Optional[float] = None
    extra_filters: dict = field(default_factory=dict)


# Segmentos principais: 0, 1, 2, 3, 4+ quartos
# Caso algum ainda estoure ~1000, subdivida por faixa de preço
SEGMENTS: list[Segment] = [
    Segment(label="studio",    bedrooms_min=0, bedrooms_max=0),
    Segment(label="1q",        bedrooms_min=1, bedrooms_max=1),
    Segment(label="2q_ate2k",  bedrooms_min=2, bedrooms_max=2, price_max=2000),
    Segment(label="2q_2k_4k",  bedrooms_min=2, bedrooms_max=2, price_min=2000, price_max=4000),
    Segment(label="2q_4kplus", bedrooms_min=2, bedrooms_max=2, price_min=4000),
    Segment(label="3q_ate4k",  bedrooms_min=3, bedrooms_max=3, price_max=4000),
    Segment(label="3q_4k_7k",  bedrooms_min=3, bedrooms_max=3, price_min=4000, price_max=7000),
    Segment(label="3q_7kplus", bedrooms_min=3, bedrooms_max=3, price_min=7000),
    Segment(label="4qplus",    bedrooms_min=4, bedrooms_max=None),
]

# ─────────────────────────────────────────────
#  LOGGING
# ─────────────────────────────────────────────
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger("quintoandar_scraper")

# ─────────────────────────────────────────────
#  HEADERS
# ─────────────────────────────────────────────
HEADERS = {
    "Accept":          "application/json",
    "Accept-Language": "en-US,en;q=0.9",
    "Content-Type":    "application/json",
    "Origin":          "https://www.quintoandar.com.br",
    "Referer":         "https://www.quintoandar.com.br/",
    "Sec-Fetch-Dest":  "empty",
    "Sec-Fetch-Mode":  "cors",
    "Sec-Fetch-Site":  "same-site",
    "User-Agent": (
        "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:149.0) "
        "Gecko/20100101 Firefox/149.0"
    ),
    "X-AB-Test": (
        "ab_beakman_search_services_open_search_find:1,"
        "ab_beakman_search_services_open_search_migration:true,"
        "ab_beakman_search_services_location_embedding_on_cg_experiment:1,"
        "ab_beakman_search_services_demand_concentration_v1_map_and_ssr_rent_experiment_v2:1"
    ),
}

# ─────────────────────────────────────────────
#  FIELDS
# ─────────────────────────────────────────────
FIELDS = [
    "id", "coverImage", "rent", "totalCost", "salePrice",
    "iptuPlusCondominium", "area", "imageList", "imageCaptionList",
    "address", "regionName", "city", "visitStatus",
    "activeSpecialConditions", "type", "forRent", "forSale",
    "isPrimaryMarket", "bedrooms", "parkingSpaces", "suites",
    "listingTags", "yield", "yieldStrategy", "neighbourhood",
    "categories", "bathrooms", "isFurnished", "installations",
    "amenities", "shortRentDescription", "shortSaleDescription",
]

# ─────────────────────────────────────────────
#  PAYLOAD
# ─────────────────────────────────────────────
def build_payload(offset: int, page_size: int, segment: Optional[Segment] = None) -> dict:
    """
    Monta o payload base e aplica os filtros do segmento atual.
    Filtros de quartos e preço são injetados nos campos corretos da API.
    """
    payload = {
        "slug": "sao-paulo-sp-brasil",
        "topics": [],
        "fields": FIELDS,
        "sorting": {"criteria": "RELEVANCE", "order": "DESC"},
        "pagination": {"pageSize": page_size, "offset": offset},
        "context": {
            "listShowing": True,
            "mapShowing":  False,
            "numPhotos":   1,
            "isSSR":       False,
        },
        "filters": {
            "enableFlexibleSearch": True,
            "businessContext": "RENT",
            "availability": "ANY",
            "occupancy": "ANY",
            "location": {
                "coordinate":    {"lat": -23.55052, "lng": -46.633309},
                "viewport": {
                    "east":  -46.506107919677724,
                    "north": -23.453390975915813,
                    "south": -23.647577310278265,
                    "west":  -46.760510080322256,
                },
                "neighborhoods": [],
                "countryCode": "BR",
            },
            "priceRange": [],
            "partnerIds": [],
            "specialConditions": [],
            "excludedSpecialConditions": [],
            "blocklist": [],
            "selectedHouses": [],
            "categories": [],
            "houseSpecs": {
                "area":          {"range": {}},
                "houseTypes":    [],
                "amenities":     [],
                "installations": [],
                "bathrooms":     {"range": {}},
                "bedrooms":      {"range": {}},
                "parkingSpace":  {"range": {}},
                "suites":        {"range": {}},
            },
        },
        "locationDescriptions": [{"description": "sao-paulo-sp-brasil"}],
    }

    if segment is None:
        return payload

    specs = payload["filters"]["houseSpecs"]

    # ── Filtro de quartos ──────────────────────────────────────
    bedroom_range: dict = {}
    if segment.bedrooms_min is not None:
        bedroom_range["min"] = segment.bedrooms_min
    if segment.bedrooms_max is not None:
        bedroom_range["max"] = segment.bedrooms_max
    if bedroom_range:
        specs["bedrooms"]["range"] = bedroom_range

    # ── Filtro de preço (rent) ─────────────────────────────────
    # A API aceita priceRange como lista de objetos {min, max}
    # ou como campo dentro de houseSpecs dependendo da versão.
    # Testamos ambos os formatos para garantir compatibilidade.
    if segment.price_min is not None or segment.price_max is not None:
        price_range: dict = {}
        if segment.price_min is not None:
            price_range["min"] = segment.price_min
        if segment.price_max is not None:
            price_range["max"] = segment.price_max

        # Formato 1: campo priceRange (lista de ranges)
        payload["filters"]["priceRange"] = [price_range]

        # Formato 2: dentro de houseSpecs (alguns endpoints aceitam assim)
        payload["filters"]["houseSpecs"]["rentRange"] = {"range": price_range}

    # ── Filtros extras opcionais (ex: tipo de imóvel) ──────────
    for key, value in segment.extra_filters.items():
        payload["filters"][key] = value

    return payload


# ─────────────────────────────────────────────
#  FLATTEN
# ─────────────────────────────────────────────
def flatten_listing(item: dict) -> dict:
    return {
        "id":                      item.get("id"),
        "type":                    item.get("type"),
        "address":                 item.get("address"),
        "neighbourhood":           item.get("neighbourhood"),
        "regionName":              item.get("regionName"),
        "city":                    item.get("city"),
        "rent":                    item.get("rent"),
        "totalCost":               item.get("totalCost"),
        "iptuPlusCondominium":     item.get("iptuPlusCondominium"),
        "salePrice":               item.get("salePrice"),
        "area":                    item.get("area"),
        "bedrooms":                item.get("bedrooms"),
        "bathrooms":               item.get("bathrooms"),
        "suites":                  item.get("suites"),
        "parkingSpaces":           item.get("parkingSpaces"),
        "isFurnished":             item.get("isFurnished"),
        "forRent":                 item.get("forRent"),
        "forSale":                 item.get("forSale"),
        "isPrimaryMarket":         item.get("isPrimaryMarket"),
        "visitStatus":             item.get("visitStatus"),
        "listingTags":             json.dumps(item.get("listingTags", []),           ensure_ascii=False),
        "activeSpecialConditions": json.dumps(item.get("activeSpecialConditions", []),ensure_ascii=False),
        "amenities":               json.dumps(item.get("amenities", []),             ensure_ascii=False),
        "installations":           json.dumps(item.get("installations", []),         ensure_ascii=False),
        "categories":              json.dumps(item.get("categories", []),            ensure_ascii=False),
        "shortRentDescription":    item.get("shortRentDescription"),
        "coverImage":              item.get("coverImage"),
    }


# ─────────────────────────────────────────────
#  REQUEST COM RETRY
# ─────────────────────────────────────────────
def fetch_page(
    session: requests.Session,
    offset: int,
    page_size: int,
    segment: Optional[Segment] = None,
) -> Optional[dict]:
    payload = build_payload(offset, page_size, segment)

    for attempt in range(1, MAX_RETRIES + 1):
        try:
            resp = session.post(BASE_URL, json=payload, timeout=30)

            if resp.status_code == 200:
                return resp.json()

            elif resp.status_code == 429:
                wait = RETRY_WAIT * attempt
                log.warning(f"Rate limit (429) — aguardando {wait}s...")
                time.sleep(wait)

            elif resp.status_code == 400:
                # 400 normalmente indica que a paginação chegou ao fim
                # ou offset inválido — encerra silenciosamente
                log.info(f"HTTP 400 no offset {offset} — fim da paginação deste segmento.")
                return None

            elif resp.status_code in (401, 403):
                log.error(f"Acesso negado ({resp.status_code}).")
                return None

            else:
                log.warning(f"HTTP {resp.status_code} na tentativa {attempt}/{MAX_RETRIES}")
                time.sleep(RETRY_WAIT)

        except requests.exceptions.RequestException as e:
            log.warning(f"Erro de conexão/timeout na tentativa {attempt}: {e}")
            time.sleep(RETRY_WAIT)
        except Exception as e:
            log.error(f"Erro inesperado no request: {e}")
            return None

    log.error(f"Falhou após {MAX_RETRIES} tentativas no offset {offset}")
    return None


# ─────────────────────────────────────────────
#  SCRAPE DE UM SEGMENTO
# ─────────────────────────────────────────────
def scrape_segment(
    session: requests.Session,
    segment: Optional[Segment],
    max_pages: int,
    seen_ids: set,
) -> list[dict]:
    """
    Coleta todos os imóveis de um único segmento.
    Usa seen_ids para deduplicação global entre segmentos.
    Retorna apenas os registros novos deste segmento.
    """
    label = segment.label if segment else "sem_segmento"
    log.info(f"\n{'─'*55}")
    log.info(f"  Segmento: {label}")
    log.info(f"{'─'*55}")

    segment_listings: list[dict] = []
    offset   = 0
    page_num = 0

    while page_num < max_pages:
        log.info(f"  📄 Pág {page_num + 1} | offset={offset} | novos neste segmento={len(segment_listings)}")

        data = fetch_page(session, offset, PAGE_SIZE, segment)
        if data is None:
            break

        listings_raw = extract_listings_from_response(data)

        if listings_raw is None:
            log.warning("  Formato estranho — pulando página.")
            break
        if not listings_raw:
            log.info("  ✅ Fim da lista neste segmento.")
            break

        new_count = 0
        for item in listings_raw:
            if not isinstance(item, dict):
                continue
            item_id = item.get("id")
            if item_id and item_id not in seen_ids:
                seen_ids.add(item_id)
                segment_listings.append(flatten_listing(item))
                new_count += 1

        log.info(f"     → {new_count} novos (total duplicatas ignoradas: {len(listings_raw) - new_count})")

        if new_count == 0:
            log.info("  ✅ Apenas duplicatas — fim da paginação.")
            break

        # Aviso preventivo se estiver próximo do limite de ~1000
        if len(segment_listings) >= 900:
            log.warning(
                f"  ⚠️  Segmento '{label}' com {len(segment_listings)} imóveis — "
                "próximo do limite. Considere subdividir este segmento."
            )

        offset   += PAGE_SIZE
        page_num += 1
        delay = random.uniform(DELAY_MIN, DELAY_MAX)
        log.info(f"     ⏳ Aguardando {delay:.1f}s...")
        time.sleep(delay)

    log.info(f"  Segmento '{label}' finalizado: {len(segment_listings)} imóveis únicos coletados.")
    return segment_listings


# ─────────────────────────────────────────────
#  EXTRATOR GENÉRICO DE RESPOSTA JSON
# ─────────────────────────────────────────────
def extract_listings_from_response(data: dict) -> Optional[list]:
    """
    Tenta extrair a lista de imóveis de diferentes formatos de resposta.
    Retorna None se o formato for irreconhecível, lista vazia se não houver itens.
    """
    # Formato Elasticsearch: hits.hits[*]._source
    if isinstance(data.get("hits"), dict) and isinstance(data["hits"].get("hits"), list):
        result = []
        for hit in data["hits"]["hits"]:
            if isinstance(hit, dict):
                result.append(hit.get("_source", hit))
        return result

    # Formato lista direta
    for key in ("hits", "listings", "results"):
        if isinstance(data.get(key), list):
            return data[key]

    # Formato aninhado
    try:
        nested = data["data"]["search"]["listings"]
        if isinstance(nested, list):
            return nested
    except (KeyError, TypeError):
        pass

    # Fallback: primeira lista de dicts encontrada
    for v in data.values():
        if isinstance(v, list) and v and isinstance(v[0], dict):
            return v

    return None


# ─────────────────────────────────────────────
#  SCRAPER PRINCIPAL
# ─────────────────────────────────────────────
def scrape(
    max_pages: int = MAX_PAGES,
    output_file: Optional[str] = None,
    use_segments: bool = True,
) -> pd.DataFrame:

    session = requests.Session()
    session.headers.update(HEADERS)

    all_listings: list[dict] = []
    seen_ids:     set        = set()

    log.info("=" * 55)
    log.info("  QuintoAndar Scraper — Aluguéis em São Paulo")
    log.info(f"  Modo: {'segmentado' if use_segments else 'único'}")
    log.info("=" * 55)

    if use_segments:
        # ── Coleta segmentada ──────────────────────────────────
        for i, segment in enumerate(SEGMENTS, 1):
            log.info(f"\n[{i}/{len(SEGMENTS)}] Iniciando segmento '{segment.label}'...")
            new_listings = scrape_segment(session, segment, max_pages, seen_ids)
            all_listings.extend(new_listings)
            log.info(f"  Acumulado total: {len(all_listings):,} imóveis únicos")

            # Pausa maior entre segmentos para evitar bloqueio
            if i < len(SEGMENTS):
                pause = random.uniform(5, 10)
                log.info(f"\n  💤 Pausa entre segmentos: {pause:.1f}s...")
                time.sleep(pause)
    else:
        # ── Coleta simples (comportamento original) ────────────
        all_listings = scrape_segment(session, None, max_pages, seen_ids)

    # ── Montar DataFrame ───────────────────────────────────────
    df = pd.DataFrame(all_listings)

    if df.empty:
        log.warning("⚠️  Nenhum dado coletado.")
        return df

    numeric_cols = [
        "rent", "totalCost", "iptuPlusCondominium",
        "salePrice", "area", "bedrooms", "bathrooms",
        "suites", "parkingSpaces",
    ]
    for col in numeric_cols:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")

    df["rentPerSqm"] = df.apply(
        lambda r: round(r["rent"] / r["area"], 2)
        if pd.notnull(r.get("rent")) and pd.notnull(r.get("area")) and r["area"] > 0
        else None,
        axis=1,
    )
    df["scraped_at"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Remove duplicatas residuais (caso a API retorne o mesmo id em segmentos diferentes)
    before = len(df)
    df = df.drop_duplicates(subset="id", keep="first").reset_index(drop=True)
    if len(df) < before:
        log.info(f"  🧹 {before - len(df)} duplicatas residuais removidas no DataFrame final.")

    # ── Salvar CSV ─────────────────────────────────────────────
    if output_file is None:
        ts = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_file = OUTPUT_DIR / f"quintoandar_sp_{ts}_v2.csv"
    else:
        output_file = OUTPUT_DIR / output_file

    df.to_csv(output_file, index=False, encoding="utf-8-sig")

    log.info("")
    log.info("=" * 55)
    log.info("✅ Coleta concluída com sucesso!")
    log.info(f"   Total de imóveis : {len(df):,}")
    log.info(f"   Arquivo gerado   : {output_file}")
    log.info("=" * 55)

    return df


# ─────────────────────────────────────────────
#  ENTRY POINT
# ─────────────────────────────────────────────
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Scraper QuintoAndar — Aluguéis SP")
    parser.add_argument("--pages",      type=int,            default=MAX_PAGES)
    parser.add_argument("--output",     type=str,            default=None)
    parser.add_argument("--no-segment", action="store_true", help="Desativa segmentação (comportamento original)")
    args = parser.parse_args()

    scrape(
        max_pages=args.pages,
        output_file=args.output,
        use_segments=not args.no_segment,
    )
