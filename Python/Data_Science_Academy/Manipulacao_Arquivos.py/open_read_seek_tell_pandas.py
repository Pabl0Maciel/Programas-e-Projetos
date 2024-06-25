arq1 = open("arquivos/arquivo1.txt", "r") # r = read
print(arq1.read()) # le o arquivo

print(arq1.tell()) # conta caracteres

print(arq1.seek(0,0)) # volta para o inicio

print(arq1.read(23)) # lendo os 23 primeiros caracteres

print(arq1.read()) # lendo o restante

# Gravando arquivos

arq2 = open("arquivos/arquivo2.txt", "w") # w = write # como nao existe este arquivo, vai ser criado um novo
#print(arq2.read()) # como abriu somente para escrita, nao e possivel ler

arq2.write("Aprendendo a programar em Python.") # grava uma frase

arq2.close() # fecha o arquivo

arq2 = open("arquivos/arquivo2.txt", "r") # abre no modo leitura
print(arq2.read())
arq2.close()

arq2 = open("arquivos/arquivo2.txt", "a") # a = append
arq2.write(" E a metodologia de ensino da Data Science Academy facilita o aprendizado.")
arq2.close()

arq2 = open("arquivos/arquivo2.txt", "r")
print(arq2.read())
arq2.seek(0,0)
print(arq2.read())

# Abrindo Dataset em linha unica

f = open('arquivos/salarios.csv', 'r')
data = f.read()
rows = data.split('\n')
print(rows)

# Dividindo um arquivo em colunas

f = open('arquivos/salarios.csv', 'r')
data = f.read()
rows = data.split('\n')
full_data = []

for row in rows:
    split_row = row.split(',')
    full_data.append(split_row)
print(full_data)

# Contando as linhas

f = open('arquivos/salarios.csv', 'r')
data = f.read()
rows = data.split('\n')
full_data = []

for row in rows:
    split_row = row.split(',')
    full_data.append(split_row)

count = 0 
for row in full_data:
    count += 1
print(count)

# Contando as colunas

f = open('arquivos/salarios.csv', 'r')
data = f.read()
rows = data.split('\n')
full_data = []

for row in rows:
    split_row = row.split(',')
    full_data.append(split_row)
    first_row = full_data[0]

count = 0
for column in first_row:
    count += 1
print(count)

# Importando um Dataset com Pandas

import pandas as pd

print(pd.__version__)

arquivo = 'arquivos/salarios.csv'

df = pd.read_csv(arquivo)
df.head()

print(df)



