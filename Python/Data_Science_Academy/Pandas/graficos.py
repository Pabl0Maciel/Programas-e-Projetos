import sklearn, pandas as pd, matplotlib.pyplot as plt  
from sklearn.datasets import load_iris

data = load_iris()

df = pd.DataFrame(data['data'], columns = data['feature_names']) # cria o dataframe
df['species'] = data['target']
print(df.head())

df.plot() # cria um grafico de linhas com todas as variaveis

df.plot.scatter(x = 'sepal length (cm)', y = 'sepal width (cm)') # cria um grafico de bolinhas


columns = ['sepal length (cm)', 'petal length (cm)', 'petal width (cm)', 'sepal width (cm)']
df[columns].plot.area() # cria um grafico de area

df.groupby('species').mean().plot.bar() # cria um grafico de barras

df.groupby('species').count().plot.pie(y = 'sepal length (cm)') # cria um grafico de setores

df.plot.kde(subplots = True, figsize = (8,8)) # cria um grafico de densidade

df[columns].plot.box(figsize = (8,8)) # cria um boxplot

plt.show()

