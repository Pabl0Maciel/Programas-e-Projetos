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
    plt.title('Estimativa de PI com Mil Pontos', y = 1.05)
    plt.text(0.5, 1.06, f'Valor estimado de PI: {pi:.6f}', ha='center', fontsize=12)
    plt.legend(loc = 'lower left')
    plt.show()

grafico(1000)