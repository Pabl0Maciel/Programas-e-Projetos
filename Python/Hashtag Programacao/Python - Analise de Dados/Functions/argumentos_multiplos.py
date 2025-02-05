# quando colocado '*' antes de um argumento, isso quer dizer que se pode colocar quantos argumentos quiser (tupla)
def minha_soma(*numeros):
    soma = 0

    for numero in numeros:
        soma += numero
    
    return soma

print(minha_soma(10, 2, 5, 0, 560, 32, 7))

## quando colocado '**' antes de um argumento, isso quer dizer que se pode colocar quantos argumentos quiser desde que tenham uma palavra chave e um valor associado a ela (dicionario)
def preco_final(preco, **adicionais):
    if 'desconto' in adicionais:
        preco *= (1 - adicionais['desconto'])
    if 'garantia_extra' in adicionais:
        preco += adicionais['garantia_extra']
    if 'imposto' in adicionais:
        preco *= (1 + adicionais['imposto'])
    
    return preco

print(preco_final(1000, desconto = 0.1, garantia_extra = 100, imposto = 0.3))