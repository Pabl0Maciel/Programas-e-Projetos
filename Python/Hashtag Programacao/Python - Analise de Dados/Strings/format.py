faturamento = 1000
custo = 500
lucro = faturamento - custo

# usando str() para transformar em string
print('O faturamento da loja foi de: ' + str(faturamento)) 

# usando o format
print('O faturamento da loja foi de {0}. O custo foi de {1} e o Lucro foi de {2}'.format(faturamento, custo, lucro)) 

# usando %s e %d
print('O faturamento foi de: %d, o custo foi de %d e o lucro foi de %d' % (faturamento, custo, lucro))

'''
Cola de formatacoes:

:< - alinha o texto para a esquerda
:> - alinha para direita
:^ - alinha para o meio

:+ - coloca sinal na frente do numero
:, - coloca virgula para separar o milhar
:_ - coloca _ para separar o milhar

:e - formato cientifico
:f - define quantidade de casas decimais
:x - HEX minuscula
:X - HEX maiscula
:% - percentual
'''

# aumenta a caixa de texto para 30 caracteres e centraliza ao meio
email = 'lira@gmail.com'
print('O meu email nao eh {:^30}'.format(email))

custo = 5000
faturamento = 2700
lucro = faturamento - custo

# coloca o sina negativo e separa por virgula
print('O faturamento foi de {:+,} e o lucro de {:+,}'.format(faturamento, lucro))

# formata para duas casas decimais
print('O faturamento foi de {:.2f} e o lucro de {:.2f}'.format(faturamento, lucro))

custo = 500
faturamento = 1300
lucro = faturamento - custo
margem = lucro / faturamento

# coloca em porcentagem
print('Margem de Lucro foi de {:.2%}'.format(margem))

custo = 5000
faturamento = 27000
lucro = faturamento - custo

# formato de moeda
print('Faturamento foi de R${:,.2f} e lucro de {:,.2f}'.format(faturamento, lucro))

# arredondando
imposto = 0.15758
preco = 100
valor_imposto = round(preco * imposto, 1)
print('imposto sobre o preco eh de {}'.format(valor_imposto))
