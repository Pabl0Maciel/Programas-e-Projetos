x=input("Digite um número inteiro: ")
adjacente=False

i=0
while i<len(x)-1:
    if x[i]==x[i+1]:
        adjacente=True
        break
    i+=1

if adjacente:
    print("sim")
else:
    print("não")
