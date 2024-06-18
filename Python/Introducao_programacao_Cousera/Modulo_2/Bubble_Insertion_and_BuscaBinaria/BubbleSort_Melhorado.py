def BubbleSort(lista):
    fim = len(lista)

    trocou = False
    for i in range(fim-1, 0, -1):
        for j in range(i):
            if lista[j] > lista[j+1]:
                lista[j], lista[j+1] = lista[j+1], lista[j]
                trocou = True

        if not trocou: #se nao trocou nenhuma vez e pq ja esta ordenado
            return lista
    return lista

print(BubbleSort([6,7,8,3,10,19,4,1,0,61,30,16,17,82,29,34,43,21,11,39,56,67,12]))