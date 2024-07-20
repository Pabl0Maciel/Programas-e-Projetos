try:                                 # deste modo
    8 + 's'                          # o programa
except TypeError:                    # nao e
    print('Operacao nao permitida')  # interrompido


try:
    f = open('arquivos/testandoerros.txt', 'w')
    f.write('Gravando no arquivo')
except IOError:
    print('Erro: arquivo nao encontrado ou nao pode ser salvo')
else:
    print('Conteudo gravado com sucesso!')
    f.close()


try:
    f = open('arquivos/testandoerros', 'r')
except IOError:
    print('Erro: arquivo nao encontrado ou nao pode ser salvo')
else:
    print('Conteudo gravado com sucesso!')
f.close()


try:
    f = open('arquivos/testandoerros.txt', 'w')
    f.write('Gravando no arquivo')
except IOError:
    print('Erro: arquivo nao encontrado ou nao pode ser salvo')
else:
    print('Conteudo gravado com sucesso!')
    f.close()
finally:
    print('Comandos no bloco finally sao sempre executados!')
