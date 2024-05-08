n=0
while n<=1:
    n=int(input("Digite um numero inteiro maior que 1 para ser decomposto em numeros primos: "))

fator=2
multiplicidade=0
while n>1:
    while n%fator==0:
        multiplicidade+=1
        n=n/fator
        if multiplicidade>0:
            print("fator",fator,"de multiplicidade =",multiplicidade)
    fator+=1
    multiplicidade=0

    