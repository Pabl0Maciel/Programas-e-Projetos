import math

a=float(input("digite o valor de a: "))
b=float(input("digite o valor de b: "))
c=float(input("digite o valor de c: "))

delta=b**2-4*a*c

if delta==0:
    raiz1=(-b+math.sqrt(delta))/(2*a)
    print("a unica raiz e:",raiz1)
else:
    if delta<0:
       print("nao existem raizes reais")
    else:
        raiz1=(-b+math.sqrt(delta))/(2*a)
        raiz2=(-b-math.sqrt(delta))/(2*a)
        print("a primeira raiz e:", raiz1)
        print("a segunda raiz e:", raiz2)

