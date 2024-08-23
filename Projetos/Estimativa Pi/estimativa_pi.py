# Este programa gera pontos(x,y) aleatorios e os insere dentro de um quadrado de lado 1. 
# Dentro do quadrado eh tracada um quarto de circunferencia de raio 1, de forma a posicionar os pontos dentro ou fora dela
# Estima o valor de PI da seguinte forma: PI = (4 * Pontos dentro) / Pontos totais
# Quanto mais pontos gerados maior a precisao da estimativa

import random, matplotlib.pyplot as plt

def grafico (n):
    dentro_x = []
    dentro_y = []
    fora_x = []
    fora_y = []

    # calcula n pontos aleatorios
    for i in range(n):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)

        dist = abs(x*x + y*y)

        # verifica se esta dentro ou fora da circunferencia
        if dist <= 1:
            dentro_x.append(x)
            dentro_y.append(y)
        else:
            fora_x.append(x)
            fora_y.append(y) 
    
    # calcula pi
    pi = (4 * len(dentro_x)) / (len(dentro_x) + len (fora_x))
    print(pi)

    # criando o grafico
    plt.figure()
    plt.scatter(dentro_x, dentro_y, label = 'Pontos Dentro da Circunferencia')
    plt.scatter(fora_x, fora_y, label = 'Pontos fora da Circunferencia')
    plt.xlim = 1
    plt.ylim = 1
    plt.title('Estimativa de PI com 10 Milhões de Pontos')
    plt.legend(loc = 'lower left')
    plt.show()

grafico(10000000)