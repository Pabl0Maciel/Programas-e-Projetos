# transforma a primeira letra em maiuscula
texto = 'lira'
print(texto.capitalize())

# transforma a primeira letra em minuscula
texto = 'Lira'
print(texto.casefold())

# conta quantas vezes aparece na string
texto = 'lira@yahoo.com.br'
print(texto.count('.'))

# verifica se termina com algo
texto = 'lira@gmail.com'
print(texto.endswith('gmail.com'))

# encontra a posicao de algo
texto = 'lira@gmail.com'
print(texto.find('@'))

# formata para string
faturamento = 1000
print('O faturamento foi de {} reais'.format(faturamento))

# verifica de somente tem letras e numeros, # e outras coisas sao False
texto = 'Joao123'
print(texto.isalnum())

# verifica se somente tem letras
texto = 'Joao'
print(texto.isalpha())

# verifica se somente tem numeros
texto = '123'
print(texto.isalnum())

# substitui um texto por outro
texto = '1000.00'
print(texto.replace('.', ','))

# separa uma string
texto = 'lira@gmail.com'
print(texto.split('@'))

# separa um texto de acordo com os enters
texto = '''Ola, bom dia
Venho por meio desse email lhe informar o faturamento da loja no dia de hoje
Faturamento = 2500 reais
'''
print(texto.splitlines())

# verifica se comeca com algo
texto = 'BEB123453'
print(texto.startswith('BEB'))

# coloca a primeira letra de cada palavra como maiuscula
texto = 'joao paulo lira'
print(texto.title())

# coloca o texto todo em maiuscula
texto = 'beb12343'
print(texto.upper())

