def insertion_sort(lista):

    for i in range(1, len(lista)):

        aux = lista[i]

        j = i-1
        while j >= 0 and aux < lista[j] :
                lista[j + 1] = lista[j]
                j -= 1
        lista[j + 1] = aux
    return lista