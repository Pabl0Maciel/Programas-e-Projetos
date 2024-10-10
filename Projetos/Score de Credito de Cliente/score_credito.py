'''
Você foi contratado por um banco para conseguir definir o score de crédito dos clientes. Você precisa analisar todos os clientes do banco e, com base nessa análise, criar um modelo que consiga ler as informações do cliente e dizer automaticamente o score de crédito dele: Ruim, Ok, Bom
'''

# modulos
import pandas as pd
from sklearn.preprocessing import LabelEncoder 
from sklearn.model_selection import train_test_split # responsavel pela divisao dos dados de treino e teste
from sklearn.ensemble import RandomForestClassifier # modelo de arvore de decisao
from sklearn.neighbors import KNeighborsClassifier # modelo dos vizinhos proximos
from sklearn.metrics import accuracy_score

# importacao da base de dados
dados = pd.read_csv('Projetos/Score de Credito de Cliente/clientes.csv')
print(dados) # imprime a tabela
print(dados.info()) # mostra os tipos dos dados

## usa o Label Encoder para alterar o tipo da coluna de texto para inteiro. Ex: a profissao 'cientista' vira o numero '1'.
# o uso de tres codificadores se da na necessidade de armazenar a codificacao usada para cada coluna em especifico
codificador = LabelEncoder()
dados['profissao'] = codificador.fit_transform(dados['profissao'])

codificador2 = LabelEncoder()
dados['mix_credito'] = codificador2.fit_transform(dados['mix_credito'])

codificador3 = LabelEncoder()
dados['comportamento_pagamento'] = codificador3.fit_transform(dados['comportamento_pagamento'])

print(dados.info())

# criando quem se quer prever (y) e quem sera usado para a previsao (x)
y = dados['score_credito']
x = dados.drop(columns=['score_credito', 'id_cliente']) # usa todas as colunas para a previsao, exceto a de id_cliente e a de score, que sera prevista

# separando as amostras de teste e de treino
x_treino, x_teste, y_treino, y_teste = train_test_split(x, y, test_size=0.3, random_state=1)

# criando a IA
modelo_ArvoreDecisao = RandomForestClassifier()
modelo_KNN = KNeighborsClassifier()

# treinando a IA
modelo_ArvoreDecisao.fit(x_treino, y_treino)
modelo_KNN.fit(x_treino, y_treino)

# calculando a previsao
previsao_ArvoreDecisao = modelo_ArvoreDecisao.predict(x_teste)
previsao_KNN = modelo_KNN.predict(x_teste)

# verificando a acuracia
print(accuracy_score(y_teste, previsao_ArvoreDecisao))
print(accuracy_score(y_teste, previsao_KNN))

# importando novos dados para previsao
novos_dados = pd.read_csv('Projetos/Score de Credito de Cliente/novos_clientes.csv')

# usando o Label Encoder novamente
novos_dados['profissao'] = codificador.fit_transform(novos_dados['profissao'])
novos_dados['mix_credito'] = codificador2.fit_transform(novos_dados['mix_credito'])
novos_dados['comportamento_pagamento'] = codificador3.fit_transform(novos_dados['comportamento_pagamento'])

# gerando a previsao
previsao = modelo_ArvoreDecisao.predict(novos_dados)
print(previsao)
