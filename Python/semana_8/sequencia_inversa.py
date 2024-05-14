lista=[]
x=1
while x!=0:
    x=int(input("Digite um numero inteiro: "))
    if x==0:
        break
    lista.append(x)

i=len(lista)-1

while i>=0:
    print(lista[i])
    i-=1