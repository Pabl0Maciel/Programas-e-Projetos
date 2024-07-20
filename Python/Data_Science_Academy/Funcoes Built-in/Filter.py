def verificaPar(num):
    if num % 2 == 0:
        return True
    else:
        return False
    
lista = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18]
print(filter(verificaPar, lista)) # retorna um objeto iteravel com o filtro aplicado
print(list(filter(verificaPar, lista)))

print(list(filter(lambda num: num % 2 == 0, lista)))
print(list(filter(lambda num: num > 8, lista)))
