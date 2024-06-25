# numpy
import numpy
print(dir(numpy))
print(numpy.sqrt(25))

from numpy import sqrt
print(sqrt(9))

# random
import random
print(random.choice(['Abacate','Banana', 'Laranja']))

print(random.sample(range(100),10))

# statistics
import statistics
dados = [2.75, 1.75, 1.25, 0.25, 0.5, 1.25, 3.5]
print(statistics.mean(dados)) # media
print(statistics.median(dados)) # mediana

# os
import os
print(os.getcwd())

# importando modulo do pacote
import urllib.request # importa um modulo que traz urls para o ambiente Python
resposta = urllib.request.urlopen('http://python.org')
print(resposta)

html = resposta.read()
print(html)