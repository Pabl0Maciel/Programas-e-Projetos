import sqlite3 as sql, pandas as pd

### exemplo 1
con = sql.connect('arquivos/cap12_dsa.db') # conecta ao banco de dados
cursor = con.cursor() # cria um cursor para percorrer o banco de dados

sql_query = """SELECT name FROM sqlite_master WHERE type = 'table';""" # prepara a busca no banco de dados (maisculo = comandos SQL) 
                                                                       # (minusculo = nomes no banco de dados)

cursor.execute(sql_query) # executa a busca
print(cursor.fetchall()) # retorna a tabela da query

### exemplo 2
query1 = 'SELECT * FROM tb_vendas_dsa' # seleciona tudo da tabela
cursor.execute(query1) # executa

nomes_colunas = [description[0] for description in cursor.description] # list comprehension para retornar os nomes das colunas
print(nomes_colunas)

dados = cursor.fetchall() # retorna os dados da consulta
print(dados)

### exemplo 3
query2 = 'SELECT AVG(Unidades_Vendidas) FROM tb_vendas_dsa' # cria uma consulta para calcular a media das unidades vendidas78
cursor.execute(query2)

print(cursor.fetchall())

### exemplo 4
query3 = 'SELECT Nome_Produto, AVG(Unidades_Vendidas) FROM tb_vendas_dsa GROUP BY Nome_Produto' # calcula a media de unidades vendidas por cada produto
cursor.execute(query3)

print(cursor.fetchall())

### exemplo 5
# calcula a media de unidades vendidas por cada produto em que o valor unitario e maior de 199
query4 = """SELECT Nome_Produto, AVG(Unidades_Vendidas)
            FROM tb_vendas_dsa
            WHERE Valor_Unitario > 199
            GROUP BY Nome_Produto"""

cursor.execute(query4)
print(cursor.fetchall())

### exemplo 6
# a media so e executada apos o group by, por isso deve ser usado um having avg() caso queria passar mais de uma condicao na busca
query5 = """SELECT Nome_Produto, AVG(Unidades_Vendidas) 
            FROM tb_vendas_dsa
            WHERE Valor_Unitario > 199
            GROUP BY Nome_Produto
            HAVING AVG(Unidades_Vendidas) > 10"""

cursor.execute(query5)
print(cursor.fetchall())

cursor.close() # fecha o cursor
con.close() # fecha a conexao com o banco de dados


