# Problema de Negocio: construir um robo baseado em IA que aprenda a operar na bolsa de valores a partir de experimentos de compra e venda de acoes. Dado um 
# saldo inicial, o modelo deve apresentar o resultado (lucro) a ser obtido depois da execucao.

import plotly.graph_objects as go, pandas as pd, numpy as np, random
from datetime import datetime

df = pd.read_csv('arquivos/dataset7.csv')
print(df.head())

# cria o grafico
fig = go.Figure(data = [go.Candlestick(x = df['Date'],
                open = df['AAPL.Open'],
                high = df['AAPL.High'],
                low = df['AAPL.Low'],
                close = df['AAPL.Close'])])
fig.show()

precos = df['AAPL.Close'].values # cotacao de fechamento da acao
print(type(precos))

# algoritimo Q-Learning

print('\nDefinindo os Hiperparametros do Q-Learning...')
num_episodios = 1000 # numero de vezes que rodara
alfa = 0.1 # taxa de aprendizado
gama = 0.99 # valorizacao da recompensa
epsilon = 0.1 # politica de exploracao

# configurando o ambiente de negociacao
print('\nDefinindo o Ambiente de Negociacao...')
acoes = ['comprar', 'vender', 'manter']
saldo_inicial = 1000
num_acoes_inicial = 0

# funcao para execucar os passos do robo
def executar_acao(estado, acao, saldo, num_acoes, preco):
    
    # comprar
    if acao == 0:
        if saldo >= preco:
            num_acoes += 1
            saldo -= preco
    
    # vender
    elif acao == 1:
        if num_acoes > 0:
            num_acoes -= 1
            saldo += preco
    
    # lucro
    lucro = saldo + num_acoes * preco - saldo_inicial

    return(saldo, num_acoes, lucro)

# treinamento do robo
print('\nInicializando a Tabela Q...')
q_tabela = np.zeros((len(precos), len(acoes)))

print('\nInicializando o Treinamento...')
for _ in range(num_episodios):
    
    saldo = saldo_inicial

    num_acoes = num_acoes_inicial

    for i, preco in enumerate(precos[:-1]):

        estado = i

        if np.random.random() < epsilon:
            acao = random.choice(range(len(acoes)))
        else:
            acao = np.argmax(q_tabela[estado])
        
        saldo, num_acoes, lucro = executar_acao(estado, acao, saldo, num_acoes, preco)
        prox_estado = i + 1

        q_tabela[estado][acao] += alfa * (lucro + gama * np.max(q_tabela[prox_estado]) - q_tabela[estado][acao])

print('\nTreinamento Concluido!')

# executando o robo e prevendo o lucro
saldo = saldo_inicial
num_acoes = num_acoes_inicial

print('\nExecutando o Agente...')

for i, preco in enumerate(precos[:-1]):
    estado = i
    acao = np.argmax(q_tabela[estado])
    saldo, num_acoes, _ = executar_acao(estado, acao, saldo, num_acoes, preco)

print('\nExecucao Concluida!')

# vendendo todas as acoes no ultimo preco
saldo += num_acoes * precos[-1]
lucro = saldo - saldo_inicial
lucro_final = round(lucro, 2)

print(f"\nComecamos a Negociacao com Saldo Inicial de 1000 e Tivemos Lucro de: {lucro_final}")

    

