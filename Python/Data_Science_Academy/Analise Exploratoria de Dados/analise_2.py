import pandas as pd, numpy as np, matplotlib.pyplot as plt, seaborn as sns, datetime as dt

dados = pd.read_csv('arquivos/dataset3.csv')
df = pd.DataFrame(dados)

# Pergunta 6
### calculo
#df['Ano'] = df['Data_Pedido'].str.split('/').str[2] # outro modo valido
df['Data_Pedido'] = pd.to_datetime(df['Data_Pedido'], dayfirst = True)
df['Ano'] = df['Data_Pedido'].dt.year

vendas_por_segmento_por_ano = df.groupby(['Segmento', 'Ano'])['Valor_Venda'].sum().reset_index()
print(vendas_por_segmento_por_ano)

### grafico
plt.figure(figsize = (12,8))
sns.barplot(data = vendas_por_segmento_por_ano,
            y = 'Valor_Venda',
            x = 'Ano',
            hue = 'Segmento',
            palette = 'viridis')

plt.title('Vendas por Segmento e Ano')
plt.xlabel('Ano')
plt.ylabel('Valor das Vendas')
plt.legend(title = 'Segmento')
plt.xticks(rotation = 45) 
plt.tight_layout()

# Pergunta 7
### calculo
df['Desconto'] = np.where(df['Valor_Venda'] > 1000, 0.15, 0.10) 
print(df['Desconto'].value_counts())

### outra alternativa ###
#count = 0
#coluna_valor = df['Valor_Venda']
#for venda in  range(len(coluna_valor)):
#    if coluna_valor[venda] > 1000:
#        count += 1
#        coluna_valor[venda] = coluna_valor[venda] * 0.85
#    else:
#        coluna_valor[venda] = coluna_valor[venda] * 0.9
#print("o numero total de vendas que receberam 15% de desconto e", count)
### /////////////////////////////////////////////////////////////////// ###
  
# Pergunta 8
### calculo
df['Valor_Venda_Desconto'] = df['Valor_Venda'] - (df['Valor_Venda'] * df['Desconto'])
vendas_antes = df.loc[df['Desconto'] == 0.15, 'Valor_Venda']
vendas_depois = df.loc[df['Desconto'] == 0.15, 'Valor_Venda_Desconto']
media_antes = vendas_antes.mean()
media_depois = vendas_depois.mean()

### resposta
print("Media das vendas antes do desconto de 15%:", round(media_antes, 2))
print("Media das vendas depois do desconto de 15%:", round(media_depois, 2))

# Pergunta 9
### calculo
df['Mes'] = df['Data_Pedido'].dt.month
media_segmento_ano_mes = df.groupby(['Segmento', 'Ano','Mes'])['Valor_Venda'].agg([np.sum, np.mean, np.median])
#print(media_segmento_ano_mes)

anos = media_segmento_ano_mes.index.get_level_values(1)
meses = media_segmento_ano_mes.index.get_level_values(2)
segmentos = media_segmento_ano_mes.index.get_level_values(0)

### grafico

fig1 = sns.relplot(kind = 'line',
                   data = media_segmento_ano_mes,
                   y = 'mean',
                   x = meses,
                   hue = segmentos,
                   col = anos,
                   col_wrap = 4)

# Pergunta 10
### calculo
cat_subcat_top12 = df.groupby(['Categoria', 'SubCategoria']).sum(numeric_only = True).sort_values('Valor_Venda', ascending = False).head(12)
cat_subcat_top12 = cat_subcat_top12[['Valor_Venda']].astype(int).sort_values(by = 'Categoria').reset_index()
#print(cat_subcat_top12)
cat_vendas = cat_subcat_top12.groupby('Categoria').sum(numeric_only = True).reset_index()
#print(cat_vendas)

def autopct_format(values):
    def my_format(pct):
        total = sum(values)
        val = int(round(pct * total / 100.0))
        return ' $ {v:d}'.format(v = val)
    return my_format

### grafico
cores_cat = ['#5d00de', '#0ee84f', '#e80e27']
cores_subcat = ['#aa8cd4', '#aa8cd5', '#aa8cd6', '#aa8cd7', '#26c957', '#26c958', '#26c959', '#26c960', '#e65e65', '#e65e66', '#e65e67', '#e65e68']

fig, ax = plt.subplots(figsize = (18,12))

p1 = ax.pie(cat_vendas['Valor_Venda'],
            radius = 1,
            labels = cat_vendas['Categoria'],
            wedgeprops = dict(edgecolor = 'white'),
            colors = cores_cat)

p2 = ax.pie(cat_subcat_top12['Valor_Venda'],
            radius = 0.9,
            labels = cat_subcat_top12['SubCategoria'],
            autopct = autopct_format(cat_subcat_top12['Valor_Venda']),
            colors = cores_subcat,
            labeldistance = 0.67,
            wedgeprops = dict(edgecolor = 'white'),
            pctdistance = 0.53,
            rotatelabels = True)

centre_circle = plt.Circle((0,0), 0.6, fc = 'white')

fig = plt.gcf()
fig.gca().add_artist(centre_circle)
plt.annotate(text = 'Total de Vendas: ' + '$ ' + str(int(sum(cat_subcat_top12['Valor_Venda']))), xy = (-0.2, 0))
plt.title('Total de Vendas por Categoria e Top 12 SubCategorias')

plt.show()
