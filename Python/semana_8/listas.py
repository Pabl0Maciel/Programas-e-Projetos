playlist=["musica 1", "musica 2", "musica 3"]

print(playlist)

playlist.append("musica 4")

print(playlist)

lista=[]
x=1
while x!=0:
    x=int(input("Digite um numero inteiro: "))
    lista.append(x)

i=len(lista)-1

while i>=0:
    print(lista[i])
    i-=1
