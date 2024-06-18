x, y = 10, 20 #atribuicao simultanea
print(x,',',y)

def peso_altura(): #retorno de valores para variaveis
    return 77, 1.83

peso, altura = peso_altura() 
print(peso,',',altura)

x, y = y, x #troca de valores
print(x,',',y)

def pagamento_semanal(valor_por_hora, numero_de_horas = 40): #faz com que a variavel 'numero_de_horas' assuma valor 40 caso o nao seja fornecido o parametro
    assert valor_por_hora >=0 and numero_de_horas >0 #verifica a condicao e exibe uma mensagem de erro caso seja False
    return valor_por_hora*numero_de_horas

print(pagamento_semanal(100, 20))
print(pagamento_semanal(100))
print(pagamento_semanal(100, 10))




