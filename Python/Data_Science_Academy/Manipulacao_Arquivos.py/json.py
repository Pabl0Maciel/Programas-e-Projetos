dict_guido = {'nome': 'Guido van Rossim',
              'linguagem':'Python',
              'similar': ['c', 'Modula-3', 'lisp'],
              'users': 1000000}

for k,v in dict_guido.items():
    print(k,v)

import json

json.dumps(dict_guido) # converte para o formato json

with open('arquivos/dados.json', 'w') as arquivo:
    arquivo.write(json.dumps(dict_guido))

with open('arquivos/dados.json', 'r') as arquivo:
    texto = arquivo.read()
    dados = json.loads(texto)

print(dados)

print(dados['nome'])

# Extracao de arquivos da Web

from urllib.request import urlopen

response = urlopen("http://vimeo.com/api/v2/video/57733101.json").read().decode('utf8')
dados = json.loads(response)[0]

print(dados)

print("Titulo: ", dados['title'])
print("URL: ", dados['url'])
print("Duracao: ", dados['duration'])
print("Numero de visualizacoes: ", dados['stats_number_of_plays'])

# Copiando o conteudo de um arquivo para outro

arquivo_fonte = 'arquivos/dados.json'
arquivo_destino = 'arquivos/dados.txt'

    # metodo 1
#with open(arquivo_fonte, 'r') as infile:
    #text = infile.read()
    #with open(arquivo_destino, 'w') as outfile:
        #outfile.write(text)

    # metodo 2
open(arquivo_destino, 'w').write(open(arquivo_fonte, 'r').read())

with open('arquivos/dados.txt', 'r') as arquivo:
    texto = arquivo.read()
    #dados = json.loads(texto)

print(texto)