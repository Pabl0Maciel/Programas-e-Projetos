n=int(input("Digite um numero inteiro positivo: "))
while n>=0:
    fatorial=1
    if fatorial==0:
        fatorial=1
    else:
        while n>1:
            fatorial=fatorial*n
            n=n-1
        print(fatorial)
        n=int(input("Digite um numero inteiro positivo: "))