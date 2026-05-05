#################################################################################################################
###                                                BIBLIOTECAS                                                ###
#################################################################################################################
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

#################################################################################################################
###                                                CONFIGURAÇÕES                                              ###
#################################################################################################################
BASE_URL = "https://apigw.prod.quintoandar.com.br/house-listing-search/v2/search/list" # endpoint de busca

PAGE_SIZE     = 36 # número de resultados por página (36 é o máximo conhecido, pode variar)
MAX_PAGES     = 100 # limite de páginas por segmento, mas costuma parar antes por limitacao da API
DELAY_MIN     = 1.2 # delay mínimo entre requests
DELAY_MAX     = 3.0 # delay máximo entre requests
MAX_RETRIES   = 3 # número máximo de tentativas para cada request em caso de falha 
RETRY_WAIT    = 10 # tempo de espera base para retry (multiplicado pelo número da tentativa)
SEGMENT_BREAK_WARNING = 900  # alerta para subdividir segmento (perto de 1000 imóveis)

# Caminhos de saída para dados e logs
BASE_DIR   = Path(__file__).resolve().parents[2]
OUTPUT_DIR = BASE_DIR / "data" / "raw"
LOG_DIR    = BASE_DIR / "data" / "logs"

# Cria os diretórios de saída e logs, se não existirem
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
LOG_DIR.mkdir(parents=True, exist_ok=True)

# Timestamp para nomear arquivos de saída
RUN_TS = datetime.now().strftime("%Y%m%d_%H%M%S")
LOG_FILE = LOG_DIR / f"logging_{RUN_TS}.txt"

#################################################################################################################
###                                                SEGMENTOS                                                  ###
#################################################################################################################
# Criação de segmentos para tentar evitar o limite de 1000 imóveis por busca.
@dataclass
class Segment:
    label: str
    bedrooms_min: Optional[int] = None
    bedrooms_max: Optional[int] = None
    price_min: Optional[float] = None
    price_max: Optional[float] = None
    extra_filters: dict = field(default_factory=dict)


# Dicionario para mapear tipos de imóvel conforme a API do QuintoAndar
HOUSE_TYPES = {
    "apartamento": "APARTMENT",
    "casa": "HOME",
    "casa_condominio": "HOUSE_CONDO",
    "kitnet_studio": "STUDIO",
}

# Lista de segmentos definidos para a coleta, combinando número de quartos e tipo de imóvel
SEGMENTS: list[Segment] = [
    # Studio/Kitnet (0 quartos)
    Segment(label="studio_0q", bedrooms_min=0, bedrooms_max=0,
            extra_filters={"houseTypes": [HOUSE_TYPES["kitnet_studio"]]}),

    Segment(label="studio_1q", bedrooms_min=1, bedrooms_max=1,
            extra_filters={"houseTypes": [HOUSE_TYPES["kitnet_studio"]]}),

    # 1 quarto
    Segment(label="1q_apto", bedrooms_min=1, bedrooms_max=1,
            extra_filters={"houseTypes": [HOUSE_TYPES["apartamento"]]}),
    Segment(label="1q_casa", bedrooms_min=1, bedrooms_max=1,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa"]]}),
    Segment(label="1q_condo", bedrooms_min=1, bedrooms_max=1,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa_condominio"]]}),

    # 2 quartos
    Segment(label="2q_apto", bedrooms_min=2, bedrooms_max=2,
            extra_filters={"houseTypes": [HOUSE_TYPES["apartamento"]]}),
    Segment(label="2q_casa", bedrooms_min=2, bedrooms_max=2,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa"]]}),
    Segment(label="2q_condo", bedrooms_min=2, bedrooms_max=2,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa_condominio"]]}),

    # 3 quartos
    Segment(label="3q_apto", bedrooms_min=3, bedrooms_max=3,
            extra_filters={"houseTypes": [HOUSE_TYPES["apartamento"]]}),
    Segment(label="3q_casa", bedrooms_min=3, bedrooms_max=3,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa"]]}),
    Segment(label="3q_condo", bedrooms_min=3, bedrooms_max=3,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa_condominio"]]}),

    # 4+ quartos
    Segment(label="4qplus_apto", bedrooms_min=4, bedrooms_max=None,
            extra_filters={"houseTypes": [HOUSE_TYPES["apartamento"]]}),
    Segment(label="4qplus_casa", bedrooms_min=4, bedrooms_max=None,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa"]]}),
    Segment(label="4qplus_condo", bedrooms_min=4, bedrooms_max=None,
            extra_filters={"houseTypes": [HOUSE_TYPES["casa_condominio"]]}),
]

#################################################################################################################
###                                                LOGGING                                                   ###
#################################################################################################################
# Configuração de logging para registrar o progresso e eventuais erros durante a coleta.
def setup_logger() -> logging.Logger:
    logger = logging.getLogger("quintoandar_scraper")
    logger.setLevel(logging.INFO)
    logger.handlers.clear()

    formatter = logging.Formatter(
        fmt="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S"
    )

    # Configuração do handler de console
    console_handler = logging.StreamHandler()
    console_handler.setLevel(logging.INFO)
    console_handler.setFormatter(formatter)

    # Configuração do handler de arquivo
    file_handler = logging.FileHandler(LOG_FILE, encoding="utf-8")
    file_handler.setLevel(logging.INFO)
    file_handler.setFormatter(formatter)

    # Adiciona os handlers ao logger
    logger.addHandler(console_handler)
    logger.addHandler(file_handler)
    logger.propagate = False
    return logger


log = setup_logger()

#################################################################################################################
###                                                HEADERS                                                    ###
#################################################################################################################
# Cabeçalhos HTTP para simular um navegador real e evitar bloqueios básicos da API.
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

#################################################################################################################
###                                                FIELDS                                                     ###
#################################################################################################################
# Lista de campos solicitados na API para cada imóvel. Pode ser ajustada conforme necessidade.
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

#################################################################################################################
###                                                PAYLOAD                                                    ###
#################################################################################################################
# Função para construir o payload da requisição POST, adaptando os filtros conforme o segmento definido.
def build_payload(offset: int, page_size: int, segment: Optional[Segment] = None) -> dict:
    payload = {
        "slug": "sao-paulo-sp-brasil",
        "topics": [],
        "fields": FIELDS,
        "sorting": {"criteria": "RELEVANCE", "order": "DESC"},
        "pagination": {"pageSize": page_size, "offset": offset},
        "context": {
            "listShowing": True,
            "mapShowing": False,
            "numPhotos": 1,
            "isSSR": False,
        },
        "filters": {
            "enableFlexibleSearch": True,
            "businessContext": "RENT",
            "availability": "ANY",
            "occupancy": "ANY",
            "location": {
                "coordinate": {"lat": -23.55052, "lng": -46.633309},
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
                "area": {"range": {}},
                "houseTypes": [],
                "amenities": [],
                "installations": [],
                "bathrooms": {"range": {}},
                "bedrooms": {"range": {}},
                "parkingSpace": {"range": {}},
                "suites": {"range": {}},
            },
        },
        "locationDescriptions": [{"description": "sao-paulo-sp-brasil"}],
    }

    if segment is None:
        return payload

    # Quantidade de quartos
    bedroom_range = {}
    if segment.bedrooms_min is not None:
        bedroom_range["min"] = segment.bedrooms_min
    if segment.bedrooms_max is not None:
        bedroom_range["max"] = segment.bedrooms_max
    if bedroom_range:
        payload["filters"]["houseSpecs"]["bedrooms"]["range"] = bedroom_range

    # Faixa de preço
    if segment.price_min is not None or segment.price_max is not None:
        price_range = {}
        if segment.price_min is not None:
            price_range["min"] = segment.price_min
        if segment.price_max is not None:
            price_range["max"] = segment.price_max
        payload["filters"]["priceRange"] = [price_range]

    # Filtros extras (ex.: tipo de imóvel)
    for key, value in segment.extra_filters.items():
        if key == "houseTypes":
            payload["filters"]["houseSpecs"]["houseTypes"] = value
        else:
            payload["filters"][key] = value

    return payload

#################################################################################################################
###                                                PAYLOAD                                                    ###
#################################################################################################################
# Função para "achatar" a estrutura de um imóvel, extraindo apenas os campos principais e convertendo listas em JSON strings.
def flatten_listing(item: dict) -> dict:
    return {
        "id": item.get("id"),
        "type": item.get("type"),
        "address": item.get("address"),
        "neighbourhood": item.get("neighbourhood"),
        "regionName": item.get("regionName"),
        "city": item.get("city"),

        "rent": item.get("rent"),
        "totalCost": item.get("totalCost"),
        "iptuPlusCondominium": item.get("iptuPlusCondominium"),
        "salePrice": item.get("salePrice"),

        "area": item.get("area"),
        "bedrooms": item.get("bedrooms"),
        "bathrooms": item.get("bathrooms"),
        "suites": item.get("suites"),
        "parkingSpaces": item.get("parkingSpaces"),
        "isFurnished": item.get("isFurnished"),

        "forRent": item.get("forRent"),
        "forSale": item.get("forSale"),
        "isPrimaryMarket": item.get("isPrimaryMarket"),
        "visitStatus": item.get("visitStatus"),

        "listingTags": json.dumps(item.get("listingTags", []), ensure_ascii=False),
        "activeSpecialConditions": json.dumps(item.get("activeSpecialConditions", []), ensure_ascii=False),
        "amenities": json.dumps(item.get("amenities", []), ensure_ascii=False),
        "installations": json.dumps(item.get("installations", []), ensure_ascii=False),
        "categories": json.dumps(item.get("categories", []), ensure_ascii=False),
        "shortRentDescription": item.get("shortRentDescription"),
        "coverImage": item.get("coverImage"),
    }

#################################################################################################################
###                                                EXTRAÇÃO DE LISTAGENS                                      ###
#################################################################################################################
# Função para extrair a lista de imóveis da resposta da API, tentando lidar com diferentes estruturas possíveis.
def extract_listings_from_response(data: dict) -> list:
    listings_raw = []

    if isinstance(data.get("hits"), dict) and isinstance(data["hits"].get("hits"), list):
        for hit in data["hits"]["hits"]:
            if isinstance(hit, dict) and "_source" in hit:
                listings_raw.append(hit["_source"])
            elif isinstance(hit, dict):
                listings_raw.append(hit)

    elif isinstance(data.get("hits"), list):
        listings_raw = data["hits"]
    elif isinstance(data.get("listings"), list):
        listings_raw = data["listings"]
    elif isinstance(data.get("results"), list):
        listings_raw = data["results"]
    elif isinstance(data.get("data", {}).get("search", {}).get("listings"), list):
        listings_raw = data["data"]["search"]["listings"]

    if not listings_raw and isinstance(data, dict):
        for _, v in data.items():
            if isinstance(v, list) and len(v) > 0 and isinstance(v[0], dict):
                listings_raw = v
                break

    return listings_raw if isinstance(listings_raw, list) else []

#################################################################################################################
###                                           EXTRAÇÃO DO TOTAL ESTIMADO                                      ###
#################################################################################################################
# Função para tentar extrair o total estimado de imóveis da resposta, procurando em vários campos comuns e estruturas aninhadas.
def extract_total_from_response(data: dict) -> Optional[int]:
    candidates = [
        data.get("total"),
        data.get("count"),
        data.get("totalCount"),
        data.get("totalResults"),
        data.get("pagination", {}).get("total"),
        data.get("pageInfo", {}).get("total"),
        data.get("hits", {}).get("total"),
    ]

    for candidate in candidates:
        if isinstance(candidate, int):
            return candidate
        if isinstance(candidate, dict):
            # ex.: {"value": 1234, "relation": "eq"}
            if isinstance(candidate.get("value"), int):
                return candidate["value"]

    try:
        nested = data["data"]["search"]["total"]
        if isinstance(nested, int):
            return nested
    except (KeyError, TypeError):
        pass

    return None

#################################################################################################################
###                                                     REQUEST                                               ###
#################################################################################################################
# Função para realizar a requisição POST à API, com tratamento de erros, retries e logging detalhado.
def fetch_page(
    session: requests.Session,
    offset: int,
    page_size: int,
    segment: Optional[Segment] = None
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
                log.warning(f"HTTP 400 no offset {offset} — provável limite/fim da paginação deste segmento.")
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

#################################################################################################################
###                                                 SCRAPE DE SEGMENTO                                        ###
#################################################################################################################
# Função para realizar a coleta de um segmento específico, iterando pelas páginas e acumulando os imóveis únicos encontrados.
def scrape_segment(
    session: requests.Session,
    segment: Optional[Segment],
    max_pages: int,
    seen_ids: set
) -> list[dict]:
    label = segment.label if segment else "sem_segmento"
    segment_listings = []
    offset = 0
    page_num = 0
    total_estimated_logged = False

    log.info("─" * 60)
    log.info(f"Segmento: {label}")
    if segment:
        log.info(
            f"Detalhes: bedrooms_min={segment.bedrooms_min}, "
            f"bedrooms_max={segment.bedrooms_max}, "
            f"extra_filters={segment.extra_filters}"
        )
    log.info("─" * 60)

    while page_num < max_pages:
        log.info(f"📄 Página {page_num + 1} | offset={offset} | acumulado_segmento={len(segment_listings)}")

        data = fetch_page(session, offset, PAGE_SIZE, segment)
        if data is None:
            log.info(f"Encerrando segmento '{label}' por resposta nula/fim.")
            break

        if not total_estimated_logged:
            total_estimated = extract_total_from_response(data)
            if total_estimated is not None:
                log.info(f"📊 Total estimado do segmento '{label}': {total_estimated}")
                if total_estimated >= 1000:
                    log.warning(
                        f"⚠️ Segmento '{label}' parece saturado "
                        f"(total estimado={total_estimated}). "
                        f"Considere subdividir por preço futuramente."
                    )
            else:
                log.info(f"📊 Total estimado do segmento '{label}': não encontrado na resposta")
            total_estimated_logged = True

        listings_raw = extract_listings_from_response(data)

        if not listings_raw:
            log.info(f"✅ Fim da lista de imóveis no segmento '{label}'.")
            break

        new_count = 0
        duplicate_count = 0

        for item in listings_raw:
            if not isinstance(item, dict):
                continue

            item_id = item.get("id")
            if item_id and item_id not in seen_ids:
                seen_ids.add(item_id)
                flat_item = flatten_listing(item)
                flat_item["segment"] = label
                segment_listings.append(flat_item)
                new_count += 1
            else:
                duplicate_count += 1

        log.info(f"   → {new_count} novos imóveis adicionados | duplicados ignorados={duplicate_count}")

        if new_count == 0:
            log.info(f"✅ Resposta repetida/sem novidades no segmento '{label}' — fim da paginação.")
            break

        if len(segment_listings) >= SEGMENT_BREAK_WARNING:
            log.warning(
                f"⚠️ Segmento '{label}' já acumulou {len(segment_listings)} imóveis. "
                "Está perto do limite e pode precisar de subdivisão adicional."
            )

        offset += PAGE_SIZE
        page_num += 1

        delay = random.uniform(DELAY_MIN, DELAY_MAX)
        log.info(f"   ⏳ Aguardando {delay:.1f}s...")
        time.sleep(delay)

    log.info(f"🏁 Segmento '{label}' finalizado com {len(segment_listings)} imóveis únicos.")
    return segment_listings

#################################################################################################################
###                                                 SCRAPER PRINCIPAL                                         ###
#################################################################################################################
# Função principal para orquestrar a coleta, iterando pelos segmentos definidos, acumulando os imóveis únicos e salvando o resultado final em CSV.
def scrape(max_pages: int = MAX_PAGES, output_file: str | None = None, use_segments: bool = True) -> pd.DataFrame:
    session = requests.Session()
    session.headers.update(HEADERS)

    all_listings = []
    seen_ids = set()

    log.info("=" * 60)
    log.info("QuintoAndar Scraper — Aluguéis em São Paulo")
    log.info(f"Modo segmentado: {use_segments}")
    log.info(f"Arquivo de log: {LOG_FILE}")
    log.info("=" * 60)

    if use_segments:
        for idx, segment in enumerate(SEGMENTS, start=1):
            log.info(f"\n[{idx}/{len(SEGMENTS)}] Iniciando segmento '{segment.label}'")
            segment_rows = scrape_segment(session, segment, max_pages, seen_ids)
            all_listings.extend(segment_rows)

            log.info(f"📦 Acumulado global até agora: {len(all_listings)} imóveis únicos")

            if idx < len(SEGMENTS):
                segment_pause = random.uniform(5, 10)
                log.info(f"😴 Pausa entre segmentos: {segment_pause:.1f}s...")
                time.sleep(segment_pause)
    else:
        all_listings = scrape_segment(session, None, max_pages, seen_ids)

    df = pd.DataFrame(all_listings)

    if df.empty:
        log.warning("⚠️ Nenhum dado coletado neste run.")
        return df

    numeric_cols = [
        "rent", "totalCost", "iptuPlusCondominium",
        "salePrice", "area", "bedrooms", "bathrooms",
        "suites", "parkingSpaces"
    ]
    for col in numeric_cols:
        if col in df.columns:
            df[col] = pd.to_numeric(df[col], errors="coerce")

    df["rentPerSqm"] = df.apply(
        lambda row: round(row["rent"] / row["area"], 2)
        if pd.notnull(row["rent"]) and pd.notnull(row["area"]) and row["area"] > 0
        else None,
        axis=1
    )
    df["scraped_at"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    before_drop = len(df)
    df = df.drop_duplicates(subset=["id"], keep="first").reset_index(drop=True)
    removed = before_drop - len(df)
    if removed > 0:
        log.info(f"🧹 Duplicatas residuais removidas no DataFrame final: {removed}")

    if output_file is None:
        output_file = OUTPUT_DIR / f"quintoandar_sp_{RUN_TS}_v3.csv"
    else:
        output_file = OUTPUT_DIR / output_file

    df.to_csv(output_file, index=False, encoding="utf-8-sig")

    log.info("")
    log.info("=" * 60)
    log.info("✅ Coleta concluída com sucesso!")
    log.info(f"Total de imóveis : {len(df):,}")
    log.info(f"Arquivo CSV      : {output_file}")
    log.info(f"Arquivo de log   : {LOG_FILE}")
    log.info("=" * 60)

    return df

#################################################################################################################
###                                                        MAIN                                               ###
#################################################################################################################
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Scraper QuintoAndar — Aluguéis SP")
    parser.add_argument("--pages", type=int, default=MAX_PAGES,
                        help=f"Máximo de páginas por segmento (default: {MAX_PAGES})")
    parser.add_argument("--output", type=str, default=None,
                        help="Nome do arquivo CSV de saída (salvo em data/raw/)")
    parser.add_argument("--no-segment", action="store_true",
                        help="Desativa a segmentação e usa busca única")
    args = parser.parse_args()

    df = scrape(
        max_pages=args.pages,
        output_file=args.output,
        use_segments=not args.no_segment
    )
