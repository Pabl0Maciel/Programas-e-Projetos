def encontra_impares(lista):
    if not lista:
        return []

    if (lista[0] % 2) != 0:
        return [lista[0]] + encontra_impares(lista[1:])
    else:
        return encontra_impares(lista[1:]) 
      
