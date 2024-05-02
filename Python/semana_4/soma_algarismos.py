x=input("Digite um número inteiro: ")
tamanho=len(x)
x=int(x)
i=0
soma_alg=0
while i<tamanho:
    ai=x%10
    soma_alg=soma_alg+ai
    x=x//10
    i=i+1

print(soma_alg)