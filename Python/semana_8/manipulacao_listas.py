primos=[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

#fatia de lista
print(primos[2:7])
print(primos[:12])
print(primos[12:])

#clone de lista
lista1=["vermelho","verde","azul"]

lista2=lista1[:]
lista2[0]="preto"

print(lista1[0])
print(lista2[0])

#pertinencia a uma lista
if "preto" in lista1:
    print("esta")
else:
    print("nao esta")

#concatenacao de listas
lista3=lista1+lista2

print(lista3)

#repeticao de listas
lista1_repetida_3x=lista1*3
print(lista1_repetida_3x)

#remocao em listas
lista4=[1,2,3,4,5]
del lista4[4]
print(lista4)
lista5=['a','b','c','d','e','f']
del lista5[0:3]
print(lista5)