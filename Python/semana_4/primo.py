x=int(input("Digite um número inteiro: "))
divisores=0
i=1
while i<=x:
    if x%i==0:
        divisores=divisores+1
    i=i+1

if divisores==2:
    print("primo")
else:
    print("não primo")