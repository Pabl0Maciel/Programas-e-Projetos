def askint():
    try:
        val = int(input('Digite um numero: '))
    except:
        print('Voce nao digitou um numero!')
        askint()
    return 'Obrigado!'

print(askint())

