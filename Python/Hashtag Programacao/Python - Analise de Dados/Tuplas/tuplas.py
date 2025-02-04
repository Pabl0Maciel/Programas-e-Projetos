vendas = ('lira', '25/08/2020', '15/02/1994', 2000, 'Estagiario')

# nome = vendas[0]
# data_contratacao = vendas[1]
# data_nascimento = vendas[2]
# salario = vendas[3]
# cargo = vendas[4]

nome, data_contratacao, data_nascimento, salario, cargo = vendas

print(f'{nome}, {data_contratacao}, {data_nascimento}, {salario}, {cargo}')

vendas = [
    ('20/08/2020', 'iphone x', 'azul', '128gb', 350, 4000),
    ('20/08/2020', 'iphone x', 'prata', '128gb', 1500, 4000),
    ('20/08/2020', 'ipad', 'prata', '256gb', 127, 6000),
    ('20/08/2020', 'ipad', 'prata', '128gb', 981, 5000),
    ('21/08/2020', 'iphone x', 'azul', '128gb', 397, 4000),
    ('21/08/2020', 'iphone x', 'prata', '128gb', 1017, 4000),
    ('21/08/2020', 'ipad', 'prata', '256gb', 50, 6000),
    ('21/08/2020', 'ipad', 'prata', '128gb', 4000, 5000),
]

faturamento = 0
for item in vendas:
    data, produto, cor, capacidade, unidades, valor_unitario = item

    if produto == 'iphone x' and data == '20/08/2020':
        faturamento += unidades * valor_unitario

print(f'O faturamento de Iphone X no dia 20/08/2020 foi de {faturamento}')


produto_mais_vendido = ''
qntd_produto_mais_vendido = 0
for item in vendas:
    data, produto, cor, capacidade, unidades, valor_unitario = item

    if data == '21/08/2020':

        if qntd_produto_mais_vendido < unidades:
            qntd_produto_mais_vendido = unidades
            produto_mais_vendido = produto

print(f'O produto mais vendido no dia 21/08/2020 foi {produto_mais_vendido}, com {qntd_produto_mais_vendido} unidades vendidas')
    



