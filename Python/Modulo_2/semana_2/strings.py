time = "Corinthians"
print(time)

print(time.upper()) #coloca tudo em maiusculo

print(time.lower()) #coloca tudo em minusculo

print(time.capitalize()) #coloca a primeira letra em maiusculo

email = "   pablocaballero07@gmail.com   "

print(email.strip()) #remove os espacos em branco no comeco e no final

print(email.count("a")) #conta quantos "a" existem na string

print(email.replace("@gmail.com", "@usp.br")) #substitui um pedaco da string

print(time.upper().center(150)) #centraliza a string conforme o parametro

print(email.find("@")) #encontra a posicao do que foi pedido (retorna "-1" se nao esta presente na string)

print(len(time))

print(time[1:])

print(time[4:8])

print(ord("a"))
print(ord("A"))