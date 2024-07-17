import numpy as npy

arr1 = npy.array([[1,2,3], [4,5,6]])
print(arr1)
print(type(arr1))
print(arr1.shape)

arr2 = npy.ones((2,3)) # cria uma matriz 2x3 preenchida com 1
print(arr2)

lista = [[3,81,22], [0,34,59], [21,48,94]]
arr3 = npy.matrix(lista) # cria uma matriz a partir de uma lista de listas
print(arr3)
print(arr3.size)

# usar o metodo array para armazenar dados
# usar o metodo matrix para realizar calculos

# indexacao em mais dimensoes
print(arr3[2, 1])
print(arr3[0:2, 2]) # retorna os elementos de indice 2 nas linhas 0 e 1
print(arr3[1, ]) # retorna a linha 1

# alteracao de elementos
arr3[1, 0] = 100
print(arr3)

# tipos de dados
x = npy.array([1, 2]) # numpy decide o tipo do dado
y = npy.array([1.0, 2.0]) # numpy decide o tipo do dado
z = npy.array([1, 2], dtype = npy.float64) # forcando um tipo de dado

print(x.dtype, y.dtype, z.dtype)

arr4 = npy.array([[24, 76, 92, 14], [47, 35, 89, 2]], dtype = float) # cria uma matriz do tipo float mesmo que os numeros sejam int
print(arr4)

# tamanho em bytes
print(arr4.itemsize) # tamanho de cada elemento em bytes
print(arr4.nbytes) # tamanho total do array em bytes
print(arr4.ndim) # numero de dimensoes

# matrizes de 3 e 4 dimensoes
arr_3d = npy.array([
    [
        [1,2,3,4],
        [5,6,7,8],
        [9,10,11,12]
    ],
    [
        [13,14,15,16],
        [17,18,19,20],
        [21,22,23,24]
    ]
])

print(arr_3d)
print(arr_3d.ndim)
print(arr_3d.shape)
print(arr_3d[0, 2, 1])

arr_4d = npy.random.rand(2, 3, 4, 5)
print(arr_4d)
print(arr_4d.ndim)
print(arr_4d.shape)
print(arr_4d[0, 2, 1])
print(arr_4d[0, 2, 1, 4])
