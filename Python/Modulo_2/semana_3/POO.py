class Carro:
    pass #vazia
meu_carro = Carro()
carro_do_ime = Carro()

meu_carro.ano = 1968
meu_carro.modelo = 'Fusca'
meu_carro.cor = 'Azul'

carro_do_ime.ano = 1981
carro_do_ime.modelo = 'Brasilia'
carro_do_ime.cor = 'Amarelo'

class carro:
    def __init__(self, modelo, ano, cor):
        self.modelo = modelo
        self.ano = ano
        self.cor = cor

carro_do_meu_avo = carro('Ferrari', 1980, 'vermelha')


