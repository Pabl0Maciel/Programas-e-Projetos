def fatorial(n):
    fat=1
    if n==0:
        return 1
    else:
        while(n>1):
            fat=fat*n
            n=n-1
        return fat
    
def numero_binomial(n,k):
    return fatorial(n)//(fatorial(k)*fatorial(n-k))

print(numero_binomial(5,3))
print(numero_binomial(20,3))

