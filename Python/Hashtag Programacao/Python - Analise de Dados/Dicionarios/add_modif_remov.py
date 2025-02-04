lucro_1tri = {
    'janeiro' : 100000,
    'fevereiro' : 120000,
    'marco' : 90000
}

lucro_2tri = {
    'abril' : 88000,
    'maio' : 89000,
    'junho' : 120000
}

print(lucro_1tri)
# adicionando

#lucro_1tri['abril'] = 88000

lucro_1tri.update(lucro_2tri)
print(lucro_1tri)

# removendo

#del lucro_1tri['junho']
lucro_jun = lucro_1tri.pop('junho')
print(lucro_1tri)

