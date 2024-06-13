def ordena(lista):
    fim = len(lista)
    for i in range(fim-1):
        pos_menor = i
        for j in range(i+1, fim):
            if lista[j] < lista[pos_menor]:
                pos_menor = j   
        lista[i], lista[pos_menor] = lista[pos_menor], lista[i]
    return lista