"""
Scraper de imóveis do QuintoAndar com suporte a segmentação.

Este módulo implementa toda a lógica de coleta de dados via API, incluindo:
- Construção de payloads dinâmicos com filtros
- Requisições HTTP com retry e controle de rate limit
- Paginação e deduplicação de resultados
- Segmentação por critérios (ex: preço, quartos, etc.)
- Parsing e normalização dos dados retornados
- Exportação final para DataFrame e CSV

O fluxo principal é orquestrado pela função `scrape`, que coordena a coleta
por segmentos e consolida os dados em um único dataset.
"""

#################################################################################################################
###                                                BIBLIOTECAS                                                ###
#################################################################################################################
import requests
import logging
import time
import pandas as pd
import random
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional, List

#################################################################################################################
###                                            CLASSE DE SEGMENTO                                             ###
#################################################################################################################
@dataclass
class Segment:
    """
    Define um segmento de busca com filtros específicos para a coleta.

    Permite segmentar a extração de dados por critérios como faixa de preço,
    número de quartos e filtros adicionais customizados.
    """

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
    """
    Constrói o payload da requisição para a API do QuintoAndar.

    Args:
        fields (List[str]): Lista de campos a serem retornados pela API.
        offset (int): Offset da paginação.
        page_size (int): Quantidade de registros por página.
        segment (Optional[Segment]): Segmento com filtros aplicáveis.

    Returns:
        dict: Payload completo formatado para envio na requisição POST.
    """

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
    fields: List[str],
    offset: int,
    page_size: int,
    max_retries: int,
    retry_wait: int,
    log: logging.Logger,
    segment: Optional[Segment] = None
) -> Optional[dict]:
    """
    Realiza uma requisição HTTP para obter uma página de resultados.

    Implementa tratamento de erros, retry automático e controle de rate limit.

    Args:
        base_url (str): URL da API.
        session (requests.Session): Sessão HTTP reutilizável.
        fields (List[str]): Campos a serem solicitados.
        offset (int): Offset da paginação.
        page_size (int): Tamanho da página.
        max_retries (int): Número máximo de tentativas.
        retry_wait (int): Tempo de espera entre tentativas.
        log (logging.Logger): Logger para registro de eventos.
        segment (Optional[Segment]): Segmento de filtros aplicado.

    Returns:
        Optional[dict]: JSON da resposta ou None em caso de falha.
    """
    
    
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
    base_url: str,
    session: requests.Session,
    fields: List[str],
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
    """
    Executa a coleta de dados para um segmento específico.

    Controla paginação, deduplicação de registros, delays entre requisições
    e logging detalhado do progresso.

    Args:
        base_url (str): URL da API.
        session (requests.Session): Sessão HTTP ativa.
        fields (List[str]): Campos a serem coletados.
        segment (Optional[Segment]): Segmento de busca.
        max_pages (int): Número máximo de páginas a coletar.
        page_size (int): Tamanho de cada página.
        delay_min (float): Delay mínimo entre requisições.
        delay_max (float): Delay máximo entre requisições.
        max_retries (int): Número máximo de tentativas por request.
        retry_wait (int): Tempo de espera entre retries.
        segment_break_warning (int): Parâmetro de controle (uso futuro/log).
        seen_ids (set): Conjunto de IDs já coletados (deduplicação).
        log (logging.Logger): Logger da aplicação.

    Returns:
        list[dict]: Lista de registros coletados e normalizados.
    """
    
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
        log.info(f"📄 Página {page_num + 1} | offset={offset} | acumulado={len(segment_listings)}")

        # Repassa com precisão os parâmetros exigidos pelo base_url e payload
        data = fetch_page(base_url, session, fields, offset, page_size, max_retries, retry_wait, log, segment)
        if data is None:
            log.info(f"Encerrando segmento '{label}' por resposta nula/fim.")
            break

        if not total_estimated_logged:
            total_estimated = extract_total_from_response(data)
            log.info(f"📊 Total estimado do segmento '{label}': {total_estimated or 'Desconhecido'}")

            if total_estimated is not None and total_estimated >= 1000:
                log.warning(
                    f"⚠️ Segmento '{label}' parece saturado (estimativa={total_estimated}). "
                    f"Considere subdividir os filtros."
                )
            total_estimated_logged = True

        listings_raw = extract_listings_from_response(data)
        if not listings_raw:
            log.info(f"✅ Fim da lista de imóveis no segmento '{label}'.")
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

        if new_count == 0: 
            log.info(f"✅ Resposta repetida/sem novidades no segmento '{label}' — fim da paginação.")
            break

        if len(segment_listings) >= segment_break_warning:
            log.warning(
                f"⚠️ Segmento '{label}' já acumulou {len(segment_listings)} imóveis. "
                "Está perto do limite de paginação da API (offset alto)."
            )

        offset += page_size
        page_num += 1

        delay = random.uniform(delay_min, delay_max)
        log.info(f"   ⏳ Aguardando {delay:.1f}s...")
        time.sleep(delay)

    log.info(f"🏁 Segmento '{label}' finalizado com {len(segment_listings)} imóveis únicos.")
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
    """
    Orquestra o processo completo de scraping.

    Executa a coleta por segmentos (ou de forma única), consolida os dados,
    realiza pós-processamento e salva o resultado em CSV.

    Args:
        url (str): Endpoint da API.
        headers (dict): Headers HTTP da requisição.
        fields (list): Campos a serem coletados.
        segments (List[Segment]): Lista de segmentos de busca.
        log (logging.Logger): Logger da aplicação.
        log_file (Path): Caminho do arquivo de log.
        output_file (Path): Caminho do CSV de saída.
        max_pages (int): Limite de páginas por segmento.
        page_size (int): Tamanho de cada página.
        delay_min (float): Delay mínimo entre requests.
        delay_max (float): Delay máximo entre requests.
        max_retries (int): Número máximo de tentativas.
        retry_wait (int): Tempo entre retries.
        segment_break_warning (int): Parâmetro de controle (uso futuro/log).
        use_segments (bool): Define se usa segmentação ou não.

    Returns:
        pd.DataFrame: DataFrame final com os dados coletados.
    """
    
    session = requests.Session()
    session.headers.update(headers)
    all_listings = []
    seen_ids = set()

    log.info("=" * 60)
    log.info("QuintoAndar Scraper — Coleta iniciada")
    log.info(f"Modo segmentado: {use_segments}")
    log.info(f"Total de segmentos: {len(segments) if use_segments else 1}")
    log.info("=" * 60)

    target_segments = segments if use_segments else [None]

    for idx, segment in enumerate(target_segments, start=1):
        label = segment.label if segment else "sem_segmento"
        log.info(f"\n[{idx}/{len(target_segments)}] Iniciando segmento '{label}'")

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
        log.info(f"📦 Acumulado global: {len(all_listings)} imóveis únicos")

        if idx < len(target_segments):
            delay = random.uniform(5, 10)
            log.info(f"😴 Pausa entre segmentos: {delay:.1f}s...")
            time.sleep(delay)

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
    else:
        log.warning("⚠️ Nenhum dado coletado.")
        return df 

    before = len(df)
    df = df.drop_duplicates(subset=["id"], keep="first").reset_index(drop=True)
    removed = before - len(df)

    if removed > 0:
        log.info(f"🧹 Duplicatas removidas no final: {removed}")
    
    df.to_csv(output_file, index=False, encoding="utf-8-sig")

    log.info("")
    log.info("=" * 60)
    log.info("✅ Coleta concluída com sucesso!")
    log.info(f"Total de imóveis : {len(df):,}")
    log.info(f"Arquivo CSV      : {output_file}")
    log.info("=" * 60)

    return df

#################################################################################################################
###                                            FUNÇÕES DE PARSING PURO                                        ###
#################################################################################################################
########################################### Achatamento de Lista Simples ########################################
def flatten_listing(item: dict) -> dict:
    """
    Normaliza um item bruto da API em um dicionário plano.

    Args:
        item (dict): Registro original retornado pela API.

    Returns:
        dict: Dicionário com campos simplificados e padronizados.
    """

    return {
        "id": item.get("id"), "type": item.get("type"), "address": item.get("address"),
        "neighbourhood": item.get("neighbourhood"), "rent": item.get("rent"),
        "totalCost": item.get("totalCost"), "area": item.get("area"),
        "bedrooms": item.get("bedrooms"), "bathrooms": item.get("bathrooms"),
        "parkingSpaces": item.get("parkingSpaces"), "isFurnished": item.get("isFurnished")
        # Mantive a versão resumida do flatten, adicione o resto dos campos base se precisar
    }
########################################### Extração de Dados da Resposta ########################################
def extract_listings_from_response(data: dict) -> list:
    """
    Extrai a lista de imóveis da resposta da API.

    Suporta diferentes estruturas de resposta possíveis.

    Args:
        data (dict): JSON retornado pela API.

    Returns:
        list: Lista de registros de imóveis.
    """

    if isinstance(data.get("hits"), dict) and isinstance(data["hits"].get("hits"), list):
        return [h["_source"] if "_source" in h else h for h in data["hits"]["hits"]]
    return data.get("hits", data.get("listings", data.get("results", [])))

########################################### Extração de Total de Resultados ########################################
def extract_total_from_response(data: dict) -> Optional[int]:
    """
    Extrai o total estimado de resultados da resposta da API.

    Args:
        data (dict): JSON retornado pela API.

    Returns:
        Optional[int]: Total de registros ou None se não disponível.
    """

    if isinstance(data.get("total"), int): return data["total"]
    if isinstance(data.get("hits", {}).get("total"), int): return data["hits"]["total"]
    return None
#################################################################################################################