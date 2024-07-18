import pandas as pd
from pandas import DataFrame

df = pd.read_csv("arquivos/dataset2.csv") 
moda = df['Quantidade'].value_counts().index[0] 
df['Quantidade'].fillna(value = moda, inplace = True) 

# filtrando DataFrames
print(df[df.Segmento.str.startswith('Con')].head()) # filtra as linhas da coluna segmentos que possuem strings que comecam com 'Con'
print(df[df.Segmento.str.endswith('mer')].head()) # filtra as linhas da coluna segmentos que possuem strings que terminam com 'mer'

# split de strings
print(df['ID_Pedido'].head()) # a coluna e composta por 'pais-ano-pedido', separados por '-'
print(df['ID_Pedido'].str.split('-')) # retorna cada linha como uma lista com os elementos separados
print(df['ID_Pedido'].str.split('-').str[1].head()) # retorna somente os elementos de indice 1 (ano) das listas geradas pelo split

df["Ano"] = df['ID_Pedido'].str.split('-').str[1] # cria a coluna 'Ano'
df['Pedido'] = df['ID_Pedido'].str.split('-').str[2] # cria a coluna 'Pedido'
df['Sigla'] = df['ID_Pedido'].str.split('-').str[0] # cria a coluna 'Sigla

new_order = ['Sigla', 'Ano', 'Pedido', 'ID_Pedido', 'Data_Pedido', 'ID_Cliente', 'Segmento', 'Regiao', 'ID_Produto', 'Categoria', 'Nome_Produto', 'Valor_Venda', 'Quantidade'] #defina uma nova ordem das colunas

df = df[new_order] # implementa a nova ordem

print(df.drop(columns = 'ID_Pedido').head()) # exclui a coluna (como o 'inplace = True' nao foi escrito, a mudanca nao sera no arquivo original)

# removendo caracteres
print(df['Data_Pedido'].head())
print(df['Data_Pedido'].str.lstrip('20').head()) # remove os caracteres '20' a partir do lado esquerdo

# substituicao de strings
print(df['ID_Cliente'].head())
df['ID_Cliente'] = df['ID_Cliente'].str.replace('CG', 'AX') # substitui na coluna id_cliente as strings 'CG' por 'AX'
print(df['ID_Cliente'].head())

# concatenacao de strings
df['Pedido_Segmento'] = df['ID_Pedido'].str.cat(df['Segmento'], sep = '-') # combina as colunas em uma nova: 'Pedido_Segmento'
print(df.head())