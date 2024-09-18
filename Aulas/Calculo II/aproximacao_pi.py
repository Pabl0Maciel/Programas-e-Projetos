from mpmath import mp

# calcula as 2100 casas decimais
mp.dps = 2100

# formula de K . Takano
pi_takano = 4 * (12 * mp . atan (1 / 49) + 32 * mp . atan (1 / 57) - 5 * mp . atan (1 / 239) + 12 * mp . atan (1 / 110443) )

# formula de F . C . M . Stormer
pi_stormer = 4 * (44 * mp . atan (1 / 57) + 7 * mp . atan (1 / 239) - 12 * mp . atan (1 / 682) + 24 * mp . atan (1 / 12943) )

print(" Valor de pi usando K . Takano : \n", pi_takano )
print('-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------')
print(" Valor de pi usando F . C . M . Stormer : ", pi_stormer)