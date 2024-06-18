#exemplo 1
def fatorial(n):
    if n < 1:
        return 1
    else:
        return n*fatorial(n-1) # chamada recursiva

for i in range(6):
    print(fatorial(i))
print("")

#exemplo 2
def fibonacci(n):
    if n < 2:
        return n
    else:
        return fibonacci(n-1) + fibonacci(n-2) #chamada recursiva
    

for i in range(6):
    print(fibonacci(i))
print("")

#exemplo 3
def busca_binaria(lista, elemento, min = 0, max = None):
    if max == None:
        max = len(lista)-1

    if max < min:
        return False
    else:
        meio = min + (max - min)//2

    if lista[meio] > elemento:
        return busca_binaria(lista, elemento, min, meio-1)
    
    elif lista[meio] < elemento:
        return busca_binaria(lista, elemento, meio+1, max)
    else:
        return meio

for i in range(10, 80, 10):
    print(busca_binaria([10, 20, 30, 40, 50, 60], i))