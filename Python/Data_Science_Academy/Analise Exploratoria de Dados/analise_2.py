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

plt.show()
