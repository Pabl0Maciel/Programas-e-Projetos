l=int(input("Digite a largura: "))
h=int(input("Digite a altura: "))
j=1
vazio=l-4
while j<=h:
    if j==1 or j==h:
        print(l*"#")
    else:
        i=1
        while i<l:
            if i==1 or i==l:
                print("#",vazio*" ","#")
            i+=1
    j+=1