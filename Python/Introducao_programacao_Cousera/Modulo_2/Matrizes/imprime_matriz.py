def imprime_matriz(matriz):
    linha = len(matriz)

    for linha in matriz:
        print(" ".join(map(str,linha)))


matriz = [[1,2,3], [4,5,6], [7,8,9]]
print(imprime_matriz(matriz))