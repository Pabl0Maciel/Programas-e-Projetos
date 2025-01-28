precos = 'Jan: 25, Fev: 27, Mar: 29'

# primeiro caractere eh inclusivo e o segundo eh exclusivo
preco_jan = precos[0:7]
print(preco_jan)

preco_mar = precos[-7:]
print(preco_mar)

# slice com step (passo)
codigo = '1.2.3.4,5,1,2.3.4,7.9'

pedaco_cod = codigo[::2]
pedaco_cod_reverso = codigo[::-2]
print(pedaco_cod)
print(pedaco_cod_reverso)

