import pandas as pd, numpy as np, matplotlib.pyplot as plt, seaborn as sns, datetime as dt

dados = pd.read_csv('arquivos/dataset3.csv')
df = pd.DataFrame(dados)
print(df.head())


# Pergunta 1
### calculo
cat_p1 = df[(df.Categoria == 'Office Supplies')]
cids_p1 = cat_p1.groupby('Cidade')['Valor_Venda'].sum()
cidade_maior_venda = cids_p1.idxmax()
print("A cidade com maior valor de vendas para categoria 'Office Supplies' foi", cidade_maior_venda)

# Pergunta 2
### calculo
df['Data_Pedido'] = pd.to_datetime(df['Data_Pedido'], format='%d/%m/%Y')
valores_datas = df.groupby('Data_Pedido')['Valor_Venda'].sum()
valores_datas = valores_datas.sort_index()
print(valores_datas)

### grafico
plt.figure(figsize = (20,6))
valores_datas.plot.bar(x = 'Data_Pedido', y = 'Valor_Venda', color = 'g')
plt.title('Total de Vendas Por Data do Pedido')

# Pergunta 3
### calculo
vendas_estado = df.groupby('Estado')['Valor_Venda'].sum().reset_index()
print(vendas_estado)

### grafico
plt.figure(figsize = (16,10))
sns.barplot(data = vendas_estado,
            y = 'Valor_Venda',
            x = 'Estado').set_title('Vendas Por Estado')
plt.xticks(rotation = 70)

# Pergunta 4
### calculo
cidades_vendas = df.groupby('Cidade')['Valor_Venda'].sum().reset_index().sort_values(by = 'Valor_Venda', ascending = False).head(10)
print(cidades_vendas)

### grafico
plt.figure(figsize = (16,10))
sns.set_palette('coolwarm')
sns.barplot(data = cidades_vendas,
            x = 'Cidade',
            y = 'Valor_Venda').set_title('Top 10 Cidades com Maior Total de Venda')
plt.tight_layout(pad = 3.0)

# Pergunta 5
### calculo
segmentos_vendas = df.groupby('Segmento')['Valor_Venda'].sum().reset_index()
print(segmentos_vendas)

def autopct_format(values):
    def my_format(pct):
        total = sum(values)
        val = int(round(pct * total / 100.0))
        return ' $ {v:d}'.format(v = val)
    return my_format

### grafico
plt.figure(figsize = (16,6))
cores = sns.color_palette('coolwarm', len(segmentos_vendas))
plt.pie(segmentos_vendas['Valor_Venda'], colors = cores, labels = segmentos_vendas['Segmento'], startangle = 90, autopct = autopct_format(segmentos_vendas['Valor_Venda']))

centre_circle = plt.Circle((0, 0), 0.82, fc = 'white')
fig = plt.gcf()
fig.gca().add_artist(centre_circle)

plt.annotate(text = 'Total de Vendas: ' + '$ ' + str(int(sum(segmentos_vendas['Valor_Venda']))), xy = (-0.25, 0))
plt.title('Valor Total das Vendas por Segmento')
plt.show()






