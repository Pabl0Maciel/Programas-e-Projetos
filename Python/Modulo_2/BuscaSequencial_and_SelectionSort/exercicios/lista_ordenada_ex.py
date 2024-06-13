def ordenada(lista):
    if len(lista) == 1:
            return True
    for i in range(len(lista)-1):
        if lista[i] < lista[i+1]:
            return True
        return False

