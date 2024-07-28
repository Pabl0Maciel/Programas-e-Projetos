tupla1 = ('Geografia', 23, 'Elefantes', 9.8, 'Python') # imutaveis
# nao suportam .append(), del de um elemento e alteracoes

print(len(tupla1))
print(tupla1[0])
print(tupla1[1:])
print(tupla1.index('Elefantes'))

lista1 = list(tupla1)     # converte uma tupla para lista,
lista1.append('Chocolate')# adiciona um item e depois converte para tupla denovo
tupla1 = tuple(lista1)    #
print(tupla1)