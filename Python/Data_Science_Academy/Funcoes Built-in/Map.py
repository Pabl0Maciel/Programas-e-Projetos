def potencia(x):
    return x**2

numeros = [1, 2, 3, 4, 5]
numeros_ao_quadrado = list(map(potencia,numeros))
print(numeros_ao_quadrado)

def fahrenheit(T):
    return ((float(9)/5) * T + 32)

def celsius(T):
    return (float(5)/9) * (T-32)

temperaturas = [0, 22.5, 40, 100]
print(list(map(fahrenheit, temperaturas)))

for temp in map(fahrenheit, temperaturas):
    print(temp)

print(list(map(celsius, temperaturas)))

print(list(map(lambda x: (5.0/9)*(x - 32), temperaturas)))

a = [1, 2, 3, 4]
b = [5, 6, 7, 8]
c = [9, 10, 11, 12]
print(list(map(lambda x, y: x+y, a, b)))
print(list(map(lambda x, y, z: x + y + z, a,b,c)))



