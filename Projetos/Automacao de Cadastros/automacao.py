'''
Este codigo automatiza um processo de cadastro de produtos em um sistema. Tanto o site quanto os dados sao ficticios e visam somente o aprendizado.
'''

# modulos usados
import pyautogui as pag
import pandas as pd
import time


# define o tempo de pausa entre cada acao como 1 segundo
pag.PAUSE = 1

# abrindo o navegador
pag.press('win') # clica na tecla windows
pag.write('firefox') # escreve 'firefox'
pag.press('enter') # pressiona enter

pag.sleep(3) # espera 3 segundos

# entra no site
pag.write("https://dlp.hashtagtreinamentos.com/python/intensivao/login", interval=0.005)
pag.press('enter')
pag.sleep(3)

# preenche o email e a senha
pag.click(x=879, y=401) # clica no campo de email
pag.write('pythonimpressionador@gmail.com', interval=0.005)
pag.click(x=849, y=496) # clica no campo da senha
pag.write('sua senha', interval=0.005)
pag.press('enter')
pag.sleep(2)

# importacao dos dados
dados = pd.read_csv('Projetos/Automacao de Cadastros/produtos.csv') # caminho do arquivo (certifique-se de colocar o caminho correspondente no seu caso)

# verificando se esta tudo certo
#print(dados.head())
#print(dados.shape)

linhas = len(dados)
## preechendo dados dos produtos

for linha in range(linhas):

    # codigo do produto
    codigo = dados.loc[linha, "codigo"] # pega o codigo
    pag.click(x=1050, y=291) # clica no campo de codigo do produto
    pag.write(str(codigo), interval=0.005) # digita o codigo
    pag.press('tab') # aperta tab para passar para o proximo campo

    # marca
    marca = dados.loc[linha, "marca"]
    pag.write(str(marca), interval=0.005) # digita a marca
    pag.press('tab') # aperta tab para passar para o proximo campo

    # tipo
    tipo = dados.loc[linha, "tipo"]
    pag.write(str(tipo), interval=0.005) # digita o tipo
    pag.press('tab') # aperta tab para passar para o proximo campo

    # categoria
    categoria = dados.loc[linha, "categoria"]
    pag.write(str(categoria), interval=0.005) # digita a categoria
    pag.press('tab') # aperta tab para passar para o proximo campo

    # preco unitario
    preco = dados.loc[linha, "preco_unitario"]
    pag.write(str(preco), interval=0.005) # digita o preco un.
    pag.press('tab') # aperta tab para passar para o proximo campo

    # custo
    custo = dados.loc[linha, "custo"]
    pag.write(str(custo), interval=0.005) # digita o custo
    pag.press('tab') # aperta tab para passar para o proximo campo

    # obs
    obs = dados.loc[linha, "obs"]
    if not pd.isna(obs):
        pag.write(str(obs), interval=0.005) # digita a obs
    pag.press('tab') # aperta tab para passar para o proximo campo

    pag.press('enter') # envia o cadastro

    pag.scroll(5000) # volta o scroll para cima













