A = [[1,2,3],
     [4,5,6],
     [7,8,9]]

print(A)

def cria_matriz(num_linhas, num_colunas):
    matriz = []
    for i in range(num_linhas):
        linha = []         
        for j in range(num_colunas):
            valor = int(input("Digite o elemento[" + str(i) + "][" + str(j) + "]:"))
            linha.append(valor)
        matriz.append(linha)

    for linha in matriz:
        print(linha)

    return "\0"

def le_matriz():
    lin = int(input("Digite o numero de linhas da matriz:"))
    col = int(input("Digite o numero de colunas da matriz:"))
    cria_matriz(lin, col)
    return "\0"

print(le_matriz())