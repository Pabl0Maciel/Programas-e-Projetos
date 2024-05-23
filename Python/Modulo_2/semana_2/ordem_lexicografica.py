def primeiro_lex(lista):
    primeira_string = lista[0]
    for elemento in lista:
        if elemento < primeira_string:
            primeira_string = elemento
    return primeira_string


