#!/usr/bin/env python3
"""
extract_data.py
===============
Scraper completo para QuintoAndar — Análise de Aluguéis em SP
Estrutura: src/scraping/extract_data.py

Uso:
    python src/scraping/extract_data.py                     # roda com defaults
    python src/scraping/extract_data.py --pages 50          # limita páginas
    python src/scraping/extract_data.py --output custom.csv # nome do arquivo de saída
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

# ─────────────────────────────────────────────
#  CONFIGURAÇÕES
# ─────────────────────────────────────────────
BASE_URL = "https://apigw.prod.quintoandar.com.br/house-listing-search/v2/search/list"

PAGE_SIZE     = 36       # máximo aceito pela API
MAX_PAGES     = 100      # teto de segurança (~3 600 imóveis)
DELAY_MIN     = 1.2      # delay mínimo entre requests (s)
DELAY_MAX     = 3.0      # delay máximo entre requests (s)
MAX_RETRIES   = 3        # tentativas por página em caso de erro
RETRY_WAIT    = 10       # espera entre retentativas (s)

# Salva na pasta data/raw/ na raiz do projeto
OUTPUT_DIR  = Path(__file__).resolve().parents[2] / "data" / "raw"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

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
    "Accept":           "application/json",
    "Accept-Language":  "en-US,en;q=0.9",
    "Content-Type":     "application/json",
    "Origin":           "https://www.quintoandar.com.br",
    "Referer":          "https://www.quintoandar.com.br/",
    "Sec-Fetch-Dest":   "empty",
    "Sec-Fetch-Mode":   "cors",
    "Sec-Fetch-Site":   "same-site",
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
#  CAMPOS SOLICITADOS À API
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
#  PAYLOAD BASE
# ─────────────────────────────────────────────
def build_payload(offset: int, page_size: int) -> dict:
    return {
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
                "area":         {"range": {}},
                "houseTypes":   [],
                "amenities":    [],
                "installations":[],
                "bathrooms":    {"range": {}},
                "bedrooms":     {"range": {}},
                "parkingSpace": {"range": {}},
                "suites":       {"range": {}},
            },
        },
        "locationDescriptions": [{"description": "sao-paulo-sp-brasil"}],
    }

# ─────────────────────────────────────────────
#  FLATTEN DE UM IMÓVEL
# ─────────────────────────────────────────────
def flatten_listing(item: dict) -> dict:
    """Converte um objeto da API em linha plana para DataFrame."""
    return {
        "id":                    item.get("id"),
        "type":                  item.get("type"),
        "address":               item.get("address"),
        "neighbourhood":         item.get("neighbourhood"),
        "regionName":            item.get("regionName"),
        "city":                  item.get("city"),

        "rent":                  item.get("rent"),
        "totalCost":             item.get("totalCost"),
        "iptuPlusCondominium":   item.get("iptuPlusCondominium"),
        "salePrice":             item.get("salePrice"),

        "area":                  item.get("area"),
        "bedrooms":              item.get("bedrooms"),
        "bathrooms":             item.get("bathrooms"),
        "suites":                item.get("suites"),
        "parkingSpaces":         item.get("parkingSpaces"),
        "isFurnished":           item.get("isFurnished"),

        "forRent":               item.get("forRent"),
        "forSale":               item.get("forSale"),
        "isPrimaryMarket":       item.get("isPrimaryMarket"),
        "visitStatus":           item.get("visitStatus"),

        "listingTags":           json.dumps(item.get("listingTags", []),  ensure_ascii=False),
        "activeSpecialConditions": json.dumps(item.get("activeSpecialConditions", []), ensure_ascii=False),
        "amenities":             json.dumps(item.get("amenities", []),    ensure_ascii=False),
        "installations":         json.dumps(item.get("installations", []),ensure_ascii=False),
        "categories":            json.dumps(item.get("categories", []),   ensure_ascii=False),
        "shortRentDescription":  item.get("shortRentDescription"),
        "coverImage":            item.get("coverImage"),
    }

# ─────────────────────────────────────────────
#  FUNÇÃO DE REQUEST COM RETRY
# ─────────────────────────────────────────────
def fetch_page(session: requests.Session, offset: int, page_size: int) -> dict | None:
    payload = build_payload(offset, page_size)

    for attempt in range(1, MAX_RETRIES + 1):
        try:
            resp = session.post(BASE_URL, json=payload, timeout=30)

            if resp.status_code == 200:
                return resp.json()

            elif resp.status_code == 429:
                wait = RETRY_WAIT * attempt
                log.warning(f"Rate limit (429) — aguardando {wait}s...")
                time.sleep(wait)

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
#  SCRAPER PRINCIPAL
# ─────────────────────────────────────────────
def scrape(max_pages: int = MAX_PAGES, output_file: str | None = None) -> pd.DataFrame:
    session = requests.Session()
    session.headers.update(HEADERS)

    all_listings = []
    seen_ids     = set()
    offset       = 0
    page_num     = 0

    log.info("=" * 55)
    log.info("  QuintoAndar Scraper — Aluguéis em São Paulo")
    log.info("=" * 55)

    while page_num < max_pages:
        log.info(f"📄 Página {page_num + 1} | offset={offset} | coletados={len(all_listings)}")

        data = fetch_page(session, offset, PAGE_SIZE)
        if data is None:
            log.error("Resposta inválida ou vazia — abortando coleta.")
            break

        listings_raw = []

        # ── EXTRATOR INTELIGENTE DE RESPOSTAS JSON ────────────
        # 1. Tenta formato padrão / Elasticsearch (hits -> hits)
        if isinstance(data.get("hits"), dict) and isinstance(data["hits"].get("hits"), list):
            for hit in data["hits"]["hits"]:
                if isinstance(hit, dict) and "_source" in hit:
                    listings_raw.append(hit["_source"]) 
                elif isinstance(hit, dict):
                    listings_raw.append(hit)
        
        # 2. Tenta formato antigo de lista direta
        elif isinstance(data.get("hits"), list):
            listings_raw = data["hits"]
        elif isinstance(data.get("listings"), list):
            listings_raw = data["listings"]
        elif isinstance(data.get("results"), list):
            listings_raw = data["results"]
        elif isinstance(data.get("data", {}).get("search", {}).get("listings"), list):
            listings_raw = data["data"]["search"]["listings"]
            
        # 3. Fallback: Procura qualquer lista de dicionários dentro da resposta
        if not listings_raw and isinstance(data, dict):
            for k, v in data.items():
                if isinstance(v, list) and len(v) > 0 and isinstance(v[0], dict):
                    listings_raw = v
                    break

        # Bloco de segurança estrito: deve ser lista
        if not isinstance(listings_raw, list):
            log.warning("Formato estranho retornado pela API. Pulando página.")
            log.debug(f"Preview (primeiros 300 chars): {str(data)[:300]}")
            break

        if not listings_raw:
            log.info("✅ Fim da lista de imóveis.")
            break

        # ── PROCESSAMENTO E AVALIAÇÃO DE ITENS INDIVIDUAIS ────
        new_count = 0
        for item in listings_raw:
            
            # Garantia 100% que item é um dicionário e não uma string/inteiro!
            if not isinstance(item, dict):
                continue

            item_id = item.get("id")
            if item_id and item_id not in seen_ids:
                seen_ids.add(item_id)
                all_listings.append(flatten_listing(item))
                new_count += 1

        log.info(f"   → {new_count} novos imóveis adicionados")

        if new_count == 0:
            log.info("✅ Resposta repetida ou vazia — fim da paginação.")
            break

        offset += PAGE_SIZE
        page_num += 1

        # Delay humano entre requests (ESSENCIAL PARA NÃO TOMAR BAN)
        delay = random.uniform(DELAY_MIN, DELAY_MAX)
        log.info(f"   ⏳ Aguardando {delay:.1f}s...")
        time.sleep(delay)

    # ── MONTANDO O ARQUIVO FINAL ─────────────────────────────
    df = pd.DataFrame(all_listings)

    if df.empty:
        log.warning("⚠️ Nenhum dado coletado neste run.")
        return df

    numeric_cols = ["rent", "totalCost", "iptuPlusCondominium",
                    "salePrice", "area", "bedrooms", "bathrooms",
                    "suites", "parkingSpaces"]
    for col in numeric_cols:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")

    # Tratamento para não dar divisão por zero se area = 0
    df["rentPerSqm"] = df.apply(lambda row: round(row["rent"] / row["area"], 2) if pd.notnull(row["rent"]) and pd.notnull(row["area"]) and row["area"] > 0 else None, axis=1)
    df["scraped_at"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Salva o arquivo CSV
    if output_file is None:
        ts = datetime.now().strftime("%Y%m%d_%H%M%S")
        output_file = OUTPUT_DIR / f"quintoandar_sp_{ts}.csv"
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
    parser.add_argument("--pages",  type=int, default=MAX_PAGES,
                        help=f"Máximo de páginas (default: {MAX_PAGES})")
    parser.add_argument("--output", type=str, default=None,
                        help="Nome do arquivo CSV de saída (salvo em data/raw/)")
    args = parser.parse_args()

    df = scrape(max_pages=args.pages, output_file=args.output)
