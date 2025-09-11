from wordfreq import top_n_list
import random

def gerar_keywords_globais(arquivo_saida="keywords.txt"):
    """
    Gera uma lista global de palavras-chave em múltiplos idiomas para coleta de vídeos no YouTube.

    A lista é construída a partir das palavras mais comuns em diferentes idiomas,
    utilizando a biblioteca `wordfreq`. São incluídas também letras isoladas,
    números e combinações aleatórias de letras, para aumentar a diversidade.

    A saída é salva em um arquivo `.txt`, no formato:
        palavra;idioma
    Exemplo:
        music;en
        música;pt
        juego;es
        film;fr
        auto;de
        42;extra
        abc;extra

    Parâmetros
    ----------
    arquivo_saida : str, opcional (default="keywords.txt")
        Nome do arquivo de saída onde as keywords serão salvas.
        O arquivo conterá uma palavra por linha, seguida de um sufixo que indica o idioma ou "extra".

    Idiomas incluídos
    -----------------
    - en : Inglês (500 palavras)
    - pt : Português (300 palavras)
    - es : Espanhol (300 palavras)
    - fr : Francês (200 palavras)
    - de : Alemão (200 palavras)
    - it : Italiano (150 palavras)
    - ru : Russo (150 palavras)
    - ja : Japonês (100 palavras)
    - zh : Chinês (100 palavras)
    - ar : Árabe (100 palavras)
    - hi : Hindi (100 palavras)
    - extra : letras (a-z), números (1-100) e 50 trigramas aleatórios

    Saída
    -----
    - Arquivo `keywords.txt` com aproximadamente 2300 entradas (podem existir duplicadas).
    - Cada linha contém "palavra;idioma".

    Observações
    -----------
    - Palavras duplicadas podem aparecer, já que alguns termos são comuns em múltiplos idiomas.
    - Para evitar duplicados, pode-se aplicar pós-processamento (deduplicação).
    - A lista gerada pode ser usada em scripts de coleta com `yt-dlp`, sorteando palavras aleatórias.

    Exemplo de uso
    --------------
    >>> gerar_keywords_globais("keywords.txt")
    ✅ Geradas 2376 keywords globais com idiomas e salvas em keywords.txt
    """

    distribuicao = {
    "en": 2000,   # Inglês
    "pt": 1000,   # Português
    "es": 1000,   # Espanhol
    "fr": 800,    # Francês
    "de": 800,    # Alemão
    "it": 600,    # Italiano
    "ru": 600,    # Russo
    "ja": 500,    # Japonês
    "zh": 500,    # Chinês
    "ar": 500,    # Árabe
    "hi": 500     # Hindi
    }

    keywords = []

    for lang, n in distribuicao.items():
        try:
            palavras = top_n_list(lang, n)
            keywords.extend([f"{p};{lang}" for p in palavras])
        except Exception as e:
            print(f"⚠️ Não consegui gerar palavras para {lang}: {e}")

    # Extras: letras, números e combinações aleatórias
    letras = [chr(i) for i in range(97, 123)]  # a-z
    numeros = [str(i) for i in range(1, 101)]  # 1-100
    combos = ["".join(random.choices(letras, k=3)) for _ in range(50)]

    keywords.extend([f"{l};extra" for l in letras])
    keywords.extend([f"{n};extra" for n in numeros])
    keywords.extend([f"{c};extra" for c in combos])

    random.shuffle(keywords)

    with open(arquivo_saida, "w", encoding="utf-8") as f:
        for kw in keywords:
            f.write(kw + "\n")

    print(f"✅ Geradas {len(keywords)} keywords globais com idiomas e salvas em {arquivo_saida}")


# chamada da função
gerar_keywords_globais()
