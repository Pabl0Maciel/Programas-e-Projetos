texto = "Cientista de Dados pode ser uma excelente alternativa de carreira.\n"
texto = texto + "Esses profissionais precisam saber como programar em Python.\n"
texto += "E, claro, devem ser proficientes em Data Science."

print(texto)

import os

arquivo = open(os.path.join('arquivos/cientista.txt'), 'w')

for palavra in texto.split():
    arquivo.write(palavra + ' ')
arquivo.close()

arquivo = open("arquivos/cientista.txt", "r")
print(arquivo.read())
arquivo.close()

# Expressao 'with'

with open('arquivos/cientista.txt', 'r') as arquivo:
    conteudo = arquivo.read()

print(len(conteudo))
print(conteudo)

with open('arquivos/cientista.txt', 'w') as arquivo:
    arquivo.write(texto[:19])
    arquivo.write('\n')
    arquivo.write(texto[28:66])

arquivo = open('arquivos/cientista.txt', 'r')
print(arquivo.read())
arquivo.close()