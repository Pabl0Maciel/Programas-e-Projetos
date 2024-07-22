import sqlite3 as sql, pandas as pd

con = sql.connect('arquivos/cap12_dsa.db')
cursor = con.cursor()

query = 'SELECT * FROM tb_vendas_dsa'
cursor.execute(query)

dados = cursor.fetchall()
print(dados)

df = pd.DataFrame(dados, columns = ['ID_Pedido', 'ID_Cliente', 'Nome_Produto', 'Valor_Unitario', 'Unidades_Vendidas', 'Custo']) # importa a tabela para o 
                                                                                                                                # pandas
#print(df.head())

cursor.close()
con.close()

# usando pandas
media_unidades_vendidas = df['Unidades_Vendidas'].mean()
print(type(media_unidades_vendidas))
print(media_unidades_vendidas)

media_unidades_vendidas_por_produto = df.groupby('Nome_Produto')['Unidades_Vendidas'].mean()
print(media_unidades_vendidas_por_produto.head(10))

print(df[df['Valor_Unitario'] > 199].groupby('Nome_Produto')['Unidades_Vendidas'].mean())

print(df[df['Valor_Unitario'] > 199].groupby('Nome_Produto').filter(lambda x: x['Unidades_Vendidas'].mean() > 10))



