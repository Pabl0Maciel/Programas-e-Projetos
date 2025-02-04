vendas_tecnologia = {
    'iphone': 15000, 
    'samsung galaxy': 12000, 
    'tv samsung': 10000, 
    'ps5': 14300, 
    'tablet': 1720, 
    'ipad': 1000, 
    'tv philco': 2500, 
    'notebook hp': 1000, 
    'notebook dell': 17000, 
    'notebook asus': 2450
}

# items()
#itens_dicionario = vendas_tecnologia.items()
#print(itens_dicionario)

for produto, qntd in vendas_tecnologia.items():
    print('{}: {}'.format(produto, qntd))

for chave in vendas_tecnologia:

    if vendas_tecnologia[chave] > 5000:
        print('{}: {}'.format(chave, vendas_tecnologia[chave]))

# keys() e values()
chaves = vendas_tecnologia.keys()
valores = vendas_tecnologia.values()

print(chaves)
print(valores)

# list
lista_chaves = list(chaves)
lista_chaves.sort()

for chave in lista_chaves:
    print('{}: {}'.format(chave, vendas_tecnologia[chave]))