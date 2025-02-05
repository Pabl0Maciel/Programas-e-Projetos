def minha_soma(num1, num2, num3):
    return num1 + num2 + num3

def padronizar_texto(texto):
    texto = texto.casefold()
    texto = texto.replace('  ', ' ')
    texto = texto.strip()
    
    return texto

def bateu_meta(vendas, meta):
    if vendas >= meta:
        return True
    else: 
        return False
    
def filtrar_lista_texto(lista, pedaco_texto):
    lista_filtrada = []
    
    for item in lista:
        if pedaco_texto in item:
            lista_filtrada.append(item)
    
    return lista_filtrada

lista_texto = ['lira@gmail.com', 'zezinho@hotmail.com', 'joao@gmail.com', 'alon@gmailcom']

lista = filtrar_lista_texto(lista_texto, 'gmail')
print(lista)

# return com mais valores

def operacoes_basicas (num1, num2):
    soma = num1 + num2
    diferenca = num1 - num2
    mult = num1 * num2
    divisao = num1 / num2

    return(soma, diferenca, mult, divisao)

print(operacoes_basicas(10, 5))