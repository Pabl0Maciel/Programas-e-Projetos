produtos = ['apple tv', 'mac', 'iphone x', 'ipad', 'apple watch', 'mac book', 'airpods']
print(produtos)

# adicionar
produtos.append('iphone 11')
print(produtos)

# remover

## maneira 1:
try:
    produtos.remove('iphone x')
except:
    print('Item nao existe na lista')

# maneira 2:
item_removido = produtos.pop(1)
print('Item removido: {}'.format(item_removido))
print(produtos)