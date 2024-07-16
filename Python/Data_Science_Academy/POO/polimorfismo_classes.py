class Veiculo():
    
    def __init__(self, marca, modelo):
        self.marca = marca
        self.modelo = modelo

    def acelerar(self):
        pass

    def frear(self):
        pass

class Carro(Veiculo):

    def acelerar(self):
        print("O carro esta acelerando")

    def frear(self):
        print("O carro esta freando")

class Moto(Veiculo):

    def acelerar(self):
        print("A moto esta acelerando")

    def frear(self):
        print("A moto esta freando")

class Aviao(Veiculo):
    
    def acelerar(self):
        print("O aviao esta acelerando")
    
    def frear(self):
        print("O aviao esta freando")

    def decolar(self):
        print("O aviao esta decolando")

lista_veiculos = [Carro("Porsche", "911 Turbo"), Moto("Honda", "CB 1000R Black Edition"), Aviao("Boeing", "757")]

for item in lista_veiculos:

    item.acelerar()

    item.frear()

    if isinstance(item, Aviao): # verifica de o item e do tipo aviao e execute caso true
        item.decolar()
    
    print("---")