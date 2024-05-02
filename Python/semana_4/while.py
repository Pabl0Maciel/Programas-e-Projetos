#exemplo 1
i=0
while i<=10:
    print(2**i)
    i=i+1


#exemplo 2
print("Digite uma sequencia de valores terminada por 0")
soma=0
valor=1
while valor!=0:
    valor=int(input("digite um valor a ser somado: "))
    soma=soma+valor

print("o resultado da soma e:", soma)

#exemplo 3
x=input("digite seu numero: ")
tamanho=len(x)
x=int(x)
i=0
soma_alg=0
while i<tamanho:
    ai=x%10
    soma_alg=soma_alg+ai
    x=x//10
    i=i+1

print("soma dos algarismos:",soma_alg)

#exemplo 4
descrescente=True
anterior=int(input("digite o primeiro numero da sequencia: "))
valor=1
while valor!=0 and descrescente:
    valor=int(input("Digite o proximo numero da sequencia: "))
    if valor>anterior:
        descrescente=False
    anterior=valor
if descrescente:
    print("ordem decrescente")
else:
    print("ordem crescente")

#exemplo 5
meucartao=int(input("digite o numero do seu cartao de credito: "))

cartaolido=1

encontreimeucartao=False

while cartaolido!=0 and not encontreimeucartao:
    cartaolido=int(input("digite o numero do proximo cartao de credito:"))
    if cartaolido==meucartao:
        encontreimeucartao=True

if encontreimeucartao:
    print("encontrei meu cartao")
else:
    print("nao encontrei meu cartao")

