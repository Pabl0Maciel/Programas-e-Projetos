'''
Problema de Negocio:
Considerando dados historicos de clientes que realizaram compras em nossa empresa, agrupe-os por similaridade e caracteristicas em 3 grupos e envie o relatorio
'''

# importacoes
import pandas as pd
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler

# carregando os dados
df = pd.read_csv('Programas-e-Projetos/Projetos/Segmentacao de Clientes/dados_clientes.csv')
print(df.head())

# descricao das colunas
print(df[['idade', 'renda_anual', 'pontuacao_gastos']].describe())

# cria o padronizador dos dados
padronizador = StandardScaler()

# padroniza os dados
dados_padronizados = padronizador.fit_transform(df[['idade', 'renda_anual', 'pontuacao_gastos']])
print(dados_padronizados)

# definindo o numero de clusters (k)
k = 3

# criando o modelo K-Means
kmeans = KMeans(n_clusters = k)

# treinando o modelo
kmeans.fit(dados_padronizados)

# criando a coluna cluster com os clientes segmentados
df['cluster'] = kmeans.labels_

print(df.head(10))

# salvando o arquivo
df.to_csv('Programas-e-Projetos/Projetos/Segmentacao de Clientes/clientes_segmentados.csv', index = False)