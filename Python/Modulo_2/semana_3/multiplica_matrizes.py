def multiplica_matrizes(A, B):
    num_linhas_A, num_colunas_A = len(A), len(A[0])
    num_linhas_B, num_colunas_B = len(B), len(B[0])
    assert num_colunas_A == num_linhas_B

    C = []
    for linha in range(num_linhas_A):
        C.append([])
        for coluna in range(num_colunas_B):
            C[linha].append(0)
            for k in range(num_colunas_A):
                C[linha][coluna] += A[linha][k] * B[k][coluna]

    return C

print(multiplica_matrizes([[1,2,3],[4,5,6]], [[1,2],[3,4],[5,6]]))

