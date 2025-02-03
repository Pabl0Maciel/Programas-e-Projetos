produtos = ['apple tv', 'mac', 'iphone x', 'ipad', 'apple watch', 'mac book', 'airpods', 'iphone 11']
novos_produtos = ['iphone 12', 'ioculos']

print(produtos)

# juntar listas

## maneira 1:
produtos.extend(novos_produtos)
print(produtos)

## maneira 2:
nova_lista = produtos + novos_produtos
print(nova_lista)

# ordenar
vendas = [1000, 1500, 15000, 20000, 270, 900, 100, 1200]

vendas.sort(reverse=True)
print(vendas)
