mais_vendidos = {
    'tecnologia': 'iphone', 
    'refrigeracao': 'ar consul 12000 btu', 
    'livros': 'o alquimista', 
    'eletrodoméstico': 'geladeira', 
    'lazer': 'prancha surf'
}

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

total_notebooks = 0
for chave in vendas_tecnologia:
    print('{}: {} unidades'.format(chave, vendas_tecnologia[chave]))
    if 'notebook' in chave:
        total_notebooks += vendas_tecnologia[chave]

print(total_notebooks)

qntd_iphone = vendas_tecnologia['iphone']
print(f'Quantidade de iphone vendida foi de {qntd_iphone}')

print('Quantidade de iphone vendida foi de {}'.format(vendas_tecnologia.get('iphone')))

if vendas_tecnologia.get('copo') == None:
    print('Item nao esta dentro da lista')
else:
    print(vendas_tecnologia.get('copo'))
