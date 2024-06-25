x = [1, 2, 3]
y = [4, 5, 6]

print(list(zip(x,y))) # juncao dos elementos em pares

print(list(zip('ABCD', 'xy'))) # junta somente os pares que consegue, descarta o resto

a = [1, 2, 3]
b = [4, 5, 6, 7, 8]

print(list(zip(a,b)))

d1 = {'a': 1, 'b': 2}
d2 = {'c': 4, 'd': 5}

print(list(zip(d1,d2))) # une as chaves
print(list(zip(d1,d2.values()))) # passa os valores do d2 para as keys do d1

def trocaValores(d1, d2):
    dicTemp = {}

    for d1Key, d2Val in zip(d1,d2.values()):
        dicTemp[d1Key] = d2Val
    
    return dicTemp

print(trocaValores(d1,d2))

