import numpy as np

arr = np.arange(1, 10)
print(arr)

print(np.sum(arr)) # soma
print(np.prod(arr)) # produto
print(np.cumsum(arr)) # soma acumulada
print(np.cumprod(arr)) # produto acumulado

# soma de arrays
arr2 = np.array([3,2,1])
arr3 = np.array([1,2,3])

arr4 = np.add(arr2, arr3) # soma cada elemento de uma lista com o outro
print(arr4)

# multiplicacao de matrizes
arr5 = np.array([[1,2], [3,4]])
arr6 = np.array([[5,6], [0,7]])

print(arr5.shape)
print(arr6.shape)

print(np.dot(arr5, arr6)) # multiplica as matrizes
print(arr5 @ arr6) # tambem multiplica as matrizes


