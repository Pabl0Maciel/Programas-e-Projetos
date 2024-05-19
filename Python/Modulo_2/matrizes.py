A = [[1,2,3],
     [4,5,6],
     [7,8,9]]

print(A)

def cria_matriz(num_linhas, num_colunas, valor):
    matriz = []
    for i in range(num_linhas):
        linha = []
         
        for j in range(num_colunas):
            linha.append(valor)

        matriz.append(linha)
    
    return matriz

print(cria_matriz(3, 3, 1))