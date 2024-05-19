def remove_repetidos(lista):
    nova_lista=[]
    for i in lista:
        if i not in nova_lista:
            nova_lista.append(i)
        nova_lista.sort()
    return nova_lista
