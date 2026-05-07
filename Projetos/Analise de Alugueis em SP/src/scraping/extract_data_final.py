#################################################################################################################
###                                                BIBLIOTECAS                                                ###
#################################################################################################################
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import argparse
from datetime import datetime
from utils.lib_scraper import scrape, Segment

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
OUTPUT_FILE = OUTPUT_DIR / f"quintoandar_sp_{RUN_TS}_teste.csv"

#################################################################################################################
###                                                LOGGING                                                   ###
#################################################################################################################
# Configuração de logging para registrar o progresso e eventuais erros durante a coleta.
from utils.logger_config import setup_logger
log = setup_logger(LOG_FILE)

#################################################################################################################
###                                                SEGMENTOS                                                  ###
#################################################################################################################
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

    df_imoveis = scrape(
        url=BASE_URL,
        headers=HEADERS,
        fields=FIELDS,
        segments=SEGMENTS,
        log=log,
        output_file=OUTPUT_FILE,
        max_pages=MAX_PAGES,
        page_size=PAGE_SIZE,
        delay_min=DELAY_MIN,
        delay_max=DELAY_MAX,
        max_retries=MAX_RETRIES,
        retry_wait=RETRY_WAIT,
        segment_break_warning=SEGMENT_BREAK_WARNING,
        use_segments=True
    )
