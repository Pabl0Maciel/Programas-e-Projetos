import numpy as np

# selecionando elementos
arr = np.diag(np.arange(3))
print(arr)

print(arr[:,2]) # qualquer linha, porem coluna 2

arr2 = np.arange(10)
print(arr2)

print(arr2[2:9:3]) # start:end:step

# comparacao
a = np.array([1,2,3,4])
b = np.array([4,2,2,4])

print(a == b) # comparacao item a item

print(np.array_equal(arr, arr2)) # comparacao global

# operacoes
print(arr2.min()) # minimo
print(arr2.max()) # maximo

print(np.array([1,2,3]) + 1.5) # soma um valor a cada item

arr3 = np.array([1.2, 1.5, 1.6, 2.5, 3.5, 4.5])
print(arr3)
print(np.around(arr3)) # arredonda os itens

# achatamento
arr4 = np.array([[1,2,3,4], [5,6,7,8]])
print(arr4)

print(arr4.flatten()) # 'achata' a matriz

# repetindo elementos
print(np.repeat(arr2, 2)) # repete cada elemento do arr2 duas vezes

print(np.tile(arr2, 2)) # repete o arr2 duas vezes

# criando copia
arr5 = np.copy(arr2)
print(arr5)




