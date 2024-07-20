import re

musica = '''
Todos os dias quando acordo
Não tenho mais
O tempo que passou
Mas tenho muito tempo
Temos todo o tempo do mundo
Todos os dias
Antes de dormir
Lembro e esqueço
Como foi o dia
Sempre em frente
Não temos tempo a perder
Nosso suor sagrado
É bem mais belo
Que esse sangue amargo
E tão sério
E selvagem! Selvagem!
Selvagem!
Veja o sol
Dessa manhã tão cinza
A tempestade que chega
É da cor dos teus olhos
Castanhos
Então me abraça forte
E diz mais uma vez
Que já estamos
Distantes de tudo
Temos nosso próprio tempo
Temos nosso próprio tempo
Temos nosso próprio tempo
Não tenho medo do escuro
Mas deixe as luzes
Acesas agora
O que foi escondido
É o que se escondeu
E o que foi prometido
Ninguém prometeu
Nem foi tempo perdido
Somos tão jovens
Tão jovens! Tão jovens!
'''

print(musica)

# 1- Crie um REGEX para contar quantas vezes o caracter "a" aparece em todo o texto da música.
# 2- Crie um REGEX em Python para contar quantas vezes a palavra tempo aparece na música.
# 3- Crie um REGEX em Python para extrair as palavras seguidas por exclamação.
# 4- Crie um REGEX que extrai qualquer palavra cujo antecessor seja a palavra "esse" e o sucessor seja a palavra "amargo" em um texto.
# 5- Crie um REGEX que retorne as palavras com acento, mas somente os caracteres na palavra que são anteriores ao caracter com acento.

# Solucao:

# 1-
ocorrencias = re.findall(r'a', musica, re.IGNORECASE)

numero_de_a = len(ocorrencias)

print(f"O caractere 'a' aparece {numero_de_a} vezes na musica.")

# 2-
ocorrencias = re.findall(r'\btempo\b', musica, re.IGNORECASE)

numero_de_tempos = len(ocorrencias)

print(f"A palavra 'tempo' aparece {numero_de_tempos} vezes no texto.")

# 3-
ocorrencias = re.findall(r'\w+(?=!)', musica)

print(f"Palavras seguidas por exclamação: {ocorrencias}")

# 4-
padrao = r'(?<=esse\s)\w+(?=\s+amargo)'

ocorrencias = re.findall(padrao, musica, re.IGNORECASE)

print(f"Palavras encontradas: {ocorrencias}")

# 5-
padrao = r'\b(\w+)[áéíóúâêîôûãõàç]\w*\b'

ocorrencias = re.findall(padrao, musica, re.IGNORECASE)

print(f"Partes das palavras antes dos acentos: {ocorrencias}")