from decimal import Decimal, getcontext

# Ajusta a precisao para 2110 casas decimais
getcontext().prec = 100 

# Calculo de arctan usando a Serie de Taylor
def arctan(x, terms):
    result = Decimal(0)
    for n in range(terms):
        term = ((-1) ** n) * (x ** (2 * n + 1)) / Decimal(2 * n + 1)
        result += term
    return result

# Formula de Machin
def pi_machin(terms):
    term1 = 4 * arctan(Decimal(1) / 5, terms)
    term2 = arctan(Decimal(1) / 239, terms)
    pi_over_4 = term1 - term2
    return 4 * pi_over_4

# Formula de K. Takano
def pi_k_takano(terms):
    term1 = Decimal(12) * arctan(Decimal(1) / 49, terms)
    term2 = Decimal(32) * arctan(Decimal(1) / 57, terms)
    term3 = Decimal(-5) * arctan(Decimal(1) / 239, terms)
    term4 = Decimal(12) * arctan(Decimal(1) / 110443, terms)
    pi_over_4 = term1 + term2 + term3 + term4
    return 4 * pi_over_4

# Formula de Stormer
def pi_f_stormer(terms):
    term1 = Decimal(44) * arctan(Decimal(1) / 57, terms)
    term2 = Decimal(7) * arctan(Decimal(1) / 239, terms)
    term3 = Decimal(-12) * arctan(Decimal(1) / 682, terms)
    term4 = Decimal(24) * arctan(Decimal(1) / 12943, terms)
    pi_over_4 = term1 + term2 + term3 + term4
    return 4 * pi_over_4

# Cálculo de pi 
terms = 1000  # numero de termos usados na Serie de Taylor (quanto mais, maior a precisao)

pi_Machin = pi_machin(terms)

#pi_takano = pi_k_takano(terms)
#pi_stormer = pi_f_stormer(terms)

# Mostra o Resultado
print("Pi calculado com a fórmula de Machin:")
print(str(pi_Machin))


#print("Pi calculado com a fórmula de K. Takano:")
#print(str(pi_takano))

#print("\nPi calculado com a fórmula de F.C.M. Størmer:")
#print(str(pi_stormer))
