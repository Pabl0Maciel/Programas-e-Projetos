import os, numpy as npy

filename = os.path.join('arquivos/dataset.csv')

arr = npy.loadtxt(filename, delimiter = ',', usecols = (0,1,2,3), skiprows = 1) # delimeter = separa os dados em ,
                                                                                # usecols = use colunas (possue uma coluna de palavras que nao pode ser usada)
                                                                                # skiprows = pule linhas
print(arr)

var1, var2 = npy.loadtxt(filename, delimiter = ',', usecols = (0,1), skiprows = 1, unpack = True)

import matplotlib.pyplot as plt
plt.plot(var1, var2, 'o', markersize = 6, color = 'red')
plt.show()