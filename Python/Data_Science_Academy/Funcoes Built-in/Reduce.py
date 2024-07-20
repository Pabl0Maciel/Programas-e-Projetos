from functools import reduce

lista = [47, 11, 42, 13]

def soma (a,b):
    x = a + b
    return x

print(reduce(soma, lista))

lst = [47, 11, 42, 13]
reduce(lambda x,y: x+y, lst)

max_find2 = lambda a,b: a if (a>b) else b
print(type(max_find2))
print(reduce(max_find2, lst))