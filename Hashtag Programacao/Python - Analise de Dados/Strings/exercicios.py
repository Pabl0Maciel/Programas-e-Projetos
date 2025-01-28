# Exercicio 1: Cadastro de CPF
cpf = input('Insira seu CPF:')
cpf_valido = False

while cpf_valido == False:
    ## tirar espacos no comeco e final
    cpf_tratado = cpf.strip()

    ## tirar os pontos(.)
    cpf_tratado = cpf_tratado.replace('.', '')

    ## tirar os tracos (-)
    cpf_tratado = cpf_tratado.replace('-', '')

    if len(cpf_tratado) == 11 and cpf_tratado.isnumeric():
        print (cpf)
        cpf_valido = True
    else:
        print('Digite seu CPF corretamente!')
        cpf = input('Insira seu CPF:')

# Exercicio 2: Cadastro de Email
nome = input('Digite seu nome: ')
email = input('digite seu email: ')
cadastro = False

dominios_existentes = [
    'gmail.com',
    'hotmail.com',
    'yahoo.com',
    'outlook.com',
    'usp.br',
    'uol.com.br',
    'icloud.com',
    'bol.com.br',
    'live.com',
    'aol.com',
    'protonmail.com',
    'yandex.com',
    'zoho.com',
    'terra.com.br',
    'mail.com',
    'msn.com',
    'gmx.com',
    'me.com',
    'edu.br'
]

while cadastro == False:
    if nome and email:
        pos_arroba = (email.find('@')) + 1

        dominio = email[pos_arroba:]

        if dominio in dominios_existentes:
            print('Cadastro concluido!')
            cadastro = True
            
        else:
            print('Preencha o nome e o email corretamente!')
            nome = input('Digite seu nome: ')
            email = input('digite seu email: ')