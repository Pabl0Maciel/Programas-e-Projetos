import matplotlib.pyplot as plt

# grafico de dispersao
plt.figure()
x = [1, 2, 3, 4, 5, 6, 7, 8]
y = [5, 2, 4, 5, 6, 8, 4, 8]
plt.scatter(x, y, label = 'Pontos', color = 'black', marker = 'o') # cria um grafico de dispersao com o formato de bolinhas (marker = 'o', pode usar '*')
plt.legend()

# grafico de area empilhada
plt.figure()
dias = [1, 2, 3, 4, 5]
dormir = [7, 8, 6, 77, 7]
comer = [2, 3, 4, 5, 3]
trabalhar = [7, 8, 7, 2, 2]
passear = [8, 5, 7, 8, 13]

plt.stackplot(dias, dormir, comer, trabalhar, passear, colors = ['m', 'c', 'r', 'k', 'b'], labels=['Dormir', 'Comer', 'Trabalhar', 'Passear']) # cria um 
                                                                                                                                                # grafico de
                                                                                                                                                # area emp.
                                                                                                                                                # com as 
                                                                                                                                                # legendas e 
                                                                                                                                                # cores
plt.legend(loc = 'upper left') # adiciona a legenda no canto superior esquerdo

# grafico de setores
plt.figure()
setores = [7, 2, 2, 13]
atividades = ['dormir', 'comer', 'passear', 'trabalhar']
cores = ['olive', 'lime', 'violet', 'royalblue']

plt.pie(setores, colors = cores, startangle = 90, shadow = True, explode = (0, 0.2, 0, 0), autopct='%1.1f%%', pctdistance=0.5) # cria o grafico de setores  
                                                                                                                               # com setor destacado 
                                                                                                                               # (explode(1 setor, 2 
                                                                                                                               # setor,...)), divididos em % 
                                                                                                                               # (autopct='%1.1f%%) e 
                                                                                                                               # distantes do centro 
                                                                                                                               # (pctdistance)
plt.legend(atividades, loc = 'best') 

plt.show()