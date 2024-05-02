n=int(input("Digite o valor de n: "))
i=n-1
fatorial=n
zero=False
while (i>0 or n==0) and (not zero):
    if n==0:
        fatorial=1 
        zero=True
    else:
        fatorial=fatorial*i
    i=i-1
    
print(fatorial)
    