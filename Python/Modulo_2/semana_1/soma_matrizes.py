def soma_matrizes(m1, m2):
    linhas_1 = len(m1)
    colunas_1 = len(m1[0])

    linhas_2 = len(m2)
    colunas_2 = len(m2[0])

    if linhas_1 != linhas_2 or colunas_1 != colunas_2:
        return False

    nova_matriz = []
    for i in range(linhas_1):
        nova_linha = []
        for j in range(colunas_1):
            nova_linha.append(m1[i][j] + m2[i][j])
        nova_matriz.append(nova_linha)
    
    return nova_matriz

