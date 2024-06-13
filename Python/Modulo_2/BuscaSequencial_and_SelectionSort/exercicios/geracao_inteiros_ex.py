import random

def lista_grande(n):
    lista = []
    for i in range(n):
        lista.append(random.randint(-1000, 1000))
    return lista
