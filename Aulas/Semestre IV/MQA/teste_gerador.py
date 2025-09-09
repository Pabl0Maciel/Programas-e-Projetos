#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep  8 16:42:14 2025

@author: pablo
"""

import os
import random
from collections import Counter

keywords_file = "keywords.txt"

if not os.path.exists(keywords_file):
    raise FileNotFoundError(f"❌ O arquivo {keywords_file} não existe. Gere ele primeiro.")

# Carregar keywords + idioma
keywords = []
idiomas = []

with open(keywords_file, "r", encoding="utf-8") as f:
    for line in f:
        if ";" in line:
            palavra, lang = line.strip().split(";")
            keywords.append(palavra)
            idiomas.append(lang)
        else:
            keywords.append(line.strip())
            idiomas.append("desconhecido")

print(f"📖 Total de palavras carregadas: {len(keywords)}")

# Mostrar amostras
print("\n🔹 Primeiras 20 palavras:")
for k, lang in list(zip(keywords, idiomas))[:20]:
    print(f"{k} ({lang})")

print("\n🔹 20 palavras aleatórias:")
sample = random.sample(list(zip(keywords, idiomas)), 20)
for k, lang in sample:
    print(f"{k} ({lang})")

# Checar duplicados
duplicates = len(keywords) - len(set(keywords))
print(f"\n🔍 Duplicados encontrados: {duplicates}")

# Contagem por idioma
contagem = Counter(idiomas)
print("\n🌍 Distribuição por idioma:")
for lang, qtd in contagem.most_common():
    print(f"{lang}: {qtd}")
