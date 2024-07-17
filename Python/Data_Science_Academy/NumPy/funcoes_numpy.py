import numpy as npy

arr2 = npy.array([1, 2, 3, 4, 5])
print(arr2)
print(type(arr2))

print(arr2.cumsum()) # accumulated sum
print(arr2.cumprod()) # accumulated product

arr3 = npy.arange(0, 50, 5) # semelhante a funcao range
print(arr3)
print(arr3.shape)
print(arr3.dtype) # tipo do array (inteiros, string...)

arr4 = npy.zeros(10) # cria um array de tamanho 10 preenchido com 0
print(arr4)

arr5 = npy.eye(3) # cria uma matriz identidade de ordem 3
print(arr5)

arr6 = npy.diag(npy.array([1, 2, 3, 4])) # cria uma matriz diagonal com os elementos passados
print(arr6)

arr7 = npy.array([True, False, False, True]) # cria um array de valores booleanos
print(arr7)

arr8 = npy.array(['Linguagem Python', 'Linguagem R', 'Linguagem Julia'])
print(arr8)

print(npy.linspace(0, 10)) # gera uma sequencia de numeros igualmente espacados (quando nao preenchido o terceiro espaco da sintaxe, o valor assumido e 50)
print(npy.linspace(0, 10, 15)) # gera 15 numeros espacados igualmente

print(npy.logspace(0, 5, 10)) # gera 10 numeros espacados logaritmicamente (o primeiro e 10^0 e o ultimo 10^100)


