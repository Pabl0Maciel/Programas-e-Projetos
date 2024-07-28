import numpy as npy

arr1 = npy.array([10, 21, 32, 43, 48, 15, 76, 57, 89])
print(arr1)
print(type(arr1)) # ndarray = array de n dimensoes
print(arr1.shape) # mostra as dimensoes 

print(arr1[4])
print(arr1[1:4])
print(arr1[1:4+1])

indices = [1, 2, 5, 6]
print(arr1[indices]) # retorna os valores do arr1 que possuem os numeros da lista 'indices' como indices

mask = (arr1 % 2 == 0) # verifica os numeros pares
print(mask) # retorna true se e par e false se e impar
print(arr1[mask]) # retorna os numeros pares do arr1

arr1[0] = 100
print(arr1)

# nao e possivel alterar/incluir elementos de outro tipo
try:
    arr1[0] = 'Novo elemento'
except:
    print("Operacao nao permitida")