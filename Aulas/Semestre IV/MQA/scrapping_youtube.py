import random
import yt_dlp
import pandas as pd
import time
import os
from tqdm import tqdm
from yt_dlp.utils import DownloadError

################################################ Funcao auxiliar ####################################################

def to_int_or_none(value):
    """Converte para inteiro ou retorna None se não for possível."""
    try:
        return int(value)
    except (TypeError, ValueError):
        return None
################################################ Funcao auxiliar ####################################################

def safe_str(value):
    """Converte listas em string única separada por ';'."""
    if isinstance(value, list):
        return ";".join(map(str, value))
    return value
################################################ Funcao Principal ####################################################

def coletar_videos(keywords_file="keywords.txt", output_file="videos.csv",
                   videos_target=20000, videos_per_search=10, batch_size=100,
                   delay_per_video=1.0, delay_per_keyword=2.0,
                   usar_cookies=False, navegador="chrome", debug=False):
    """
    Coleta metadados de vídeos do YouTube de forma incremental usando yt-dlp.

    Recursos principais:
    - Evita vídeos duplicados (controle por ID).
    - Evita repetir keywords já usadas (inclusive em retomadas).
    - Converte métricas para numéricas e listas para strings seguras.
    - Salva em batches no CSV, permitindo retomada em caso de falha.
    - Adiciona delays configuráveis para evitar bloqueio por excesso de requisições.
    - Pode usar cookies do navegador para acessar vídeos com restrição de idade.

    Parâmetros
    ----------
    keywords_file : str
        Arquivo contendo as palavras-chave no formato "palavra;idioma".
    output_file : str
        Nome do CSV de saída.
    videos_target : int
        Número total de vídeos a coletar.
    videos_per_search : int
        Quantidade de vídeos por busca (ytsearchN).
    batch_size : int
        Número de vídeos processados antes de salvar no CSV.
    delay_per_video : float
        Pausa (em segundos) entre cada vídeo processado. (default=1.0)
    delay_per_keyword : float
        Pausa (em segundos) entre cada keyword processada. (default=2.0)
    usar_cookies : bool
        Se True, usa cookies do navegador para coletar vídeos com restrição.
    navegador : str
        Navegador para leitura dos cookies (chrome, firefox, edge, safari).
    debug : bool
        Se True, imprime logs detalhados (keywords e vídeos coletados).
    """
    # Carregar keywords
    if not os.path.exists(keywords_file):
        raise FileNotFoundError(f"Arquivo {keywords_file} não encontrado.")

    with open(keywords_file, "r", encoding="utf-8") as f:
        keywords = [line.strip().split(";")[0] for line in f if line.strip()]

    print(f"{len(keywords)} palavras-chave carregadas de {keywords_file}")

    results = []

    # Retomar progresso
    if os.path.exists(output_file):
        df_existente = pd.read_csv(output_file)
        collected_ids = set(df_existente["id"].tolist())
        used_keywords = set(df_existente["keyword"].dropna().unique())
        total_coletados = len(df_existente)
        print(f"Retomando coleta: {total_coletados} vídeos já salvos.")
        print(f"{len(used_keywords)} keywords já foram usadas.")
    else:
        collected_ids = set()
        used_keywords = set()
        total_coletados = 0

    ydl_opts = {
        'quiet': True,
        'default_search': f'ytsearch{videos_per_search}'
    }

    if usar_cookies:
        ydl_opts["cookiesfrombrowser"] = (navegador,)
        print(f"Usando cookies do navegador: {navegador}")

    # Rotação sem repetição
    keywords_pool = [kw for kw in keywords if kw not in used_keywords]
    if not keywords_pool:
        keywords_pool = keywords[:]
        used_keywords.clear()
    keywords_pool = random.sample(keywords_pool, len(keywords_pool))
    i = 0

    with tqdm(total=videos_target, initial=total_coletados, desc="Coletando vídeos") as pbar:
        while total_coletados < videos_target:
            if i >= len(keywords_pool):
                keywords_pool = [kw for kw in keywords if kw not in used_keywords]
                if not keywords_pool:
                    keywords_pool = keywords[:]
                    used_keywords.clear()
                keywords_pool = random.sample(keywords_pool, len(keywords_pool))
                i = 0

            query = keywords_pool[i]
            i += 1
            used_keywords.add(query)

            try:
                with yt_dlp.YoutubeDL(ydl_opts) as ydl:
                    info = ydl.extract_info(query, download=False)
                    entries = info.get("entries", [])
            except Exception as e:
                print(f"Erro na busca com keyword '{query}': {e}")
                time.sleep(delay_per_keyword)
                continue

            if debug:
                print(f"\nKeyword '{query}' retornou {len(entries)} resultados")

            for video in entries:
                try:
                    vid_id = video.get("id")
                    if vid_id in collected_ids:
                        continue

                    results.append({
                        "id": vid_id,
                        "title": video.get("title"),
                        "upload_date": video.get("upload_date"),
                        "view_count": to_int_or_none(video.get("view_count")),
                        "like_count": to_int_or_none(video.get("like_count")),
                        "comment_count": to_int_or_none(video.get("comment_count")),
                        "duration": to_int_or_none(video.get("duration")),
                        "categories": safe_str(video.get("categories")),
                        "tags": safe_str(video.get("tags")),
                        "fps": to_int_or_none(video.get("fps")),
                        "width": to_int_or_none(video.get("width")),
                        "height": to_int_or_none(video.get("height")),
                        "tbr": to_int_or_none(video.get("tbr")),
                        "description": video.get("description"),
                        "keyword": query
                    })

                    collected_ids.add(vid_id)
                    pbar.update(1)

                    if debug:
                        print(f" - Coletado: {vid_id} - {video.get('title')}")

                    # Salvar em batch
                    if len(results) >= batch_size:
                        df_new = pd.DataFrame(results)
                        mode = "a" if os.path.exists(output_file) else "w"
                        header = not os.path.exists(output_file)
                        df_new.to_csv(output_file, index=False, encoding="utf-8-sig",
                                      mode=mode, header=header)
                        total_coletados += len(results)
                        results = []

                except DownloadError as e:
                    print(f"Vídeo ignorado (restrição ou indisponível): {e}")
                    continue
                except Exception as e:
                    print(f"Erro inesperado em um vídeo: {e}")
                    continue

                # Delay entre vídeos
                time.sleep(delay_per_video)
                pbar.refresh()

            # Delay entre keywords
            time.sleep(delay_per_keyword)

    print(f"\nColeta finalizada com {total_coletados} vídeos no {output_file}")
#################################################################################################################    
# Teste
# coletar_videos("keywords.txt", "videos_teste.csv",
#                videos_target=20, videos_per_search=5,
#                batch_size=5, debug=True)

coletar_videos(
    keywords_file="keywords.txt",
    output_file="videos.csv",
    videos_target=20000,
    videos_per_search=5,
    batch_size=100,
    usar_cookies=True,        
    navegador="firefox",
    debug=True
)
