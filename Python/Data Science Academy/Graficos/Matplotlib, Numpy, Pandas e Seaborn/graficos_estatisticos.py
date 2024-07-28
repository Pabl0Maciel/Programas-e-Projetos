import matplotlib.pyplot as plt, numpy as np, seaborn as sea, pandas as pd

# valores randomicos
np.random.seed(42)
n = 1000
pct_smokers = 0.2

# varaiaveis
flag_fumante = np.random.rand(n) < pct_smokers
idade = np.random.normal(40, 10, n)
altura = np.random.normal(170, 10, n)
peso = np.random.normal(70, 10, n)

# dataframe
df = pd.DataFrame({'altura': altura, 'peso': peso, 'flag_fumante': flag_fumante})

df['flag_fumante'] = df['flag_fumante'].map({True: 'Fumante', False: 'Nao Fumante'})

print(df.shape)
print(df.head())

# style
sea.set(style = 'ticks')

# lmplot
sea.lmplot(x = 'altura',
           y = 'peso',
           data = df,
           hue = 'flag_fumante',
           palette = ['tab:blue', 'tab:orange'],
           height = 7)

# labels e titulo
plt.xlabel('Altura (cm)')
plt.ylabel('Peso (kg)')
plt.title('Relacao entre altura e peso de fumantes e nao fumantes')

# remove as bordas
sea.despine()

plt.show()