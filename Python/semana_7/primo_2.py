def ePrimo(n):
    divisores=0
    i=1
    while i<=n:
        if n%i==0:
            divisores=divisores+1
        i=i+1

    if divisores==2:
        return True
    else:
        return False

n=int(input("Digite um numero inteiro positivo: "))

while n>0:
    if ePrimo(n):
        print(n,"e primo!")
    else:
        print(n,"nao e primo!")
    n=int(input("Digite um numero inteiro positivo: "))