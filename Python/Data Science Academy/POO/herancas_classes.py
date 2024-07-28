class Animal():

    def __init__(self):
        print("Animal criado")
    
    def imprimir(self):
        print("Este e um animal")
    
    def comer(self):
        print("Hora de comer")
    
    def emitir_som(self):
        pass

class Cachorro(Animal):

    def __init__(self):
        Animal.__init__(self)
        print("Objeto Cachorro criado")
    
    def emitir_som(self):
        print("Au au!")

class Gato(Animal):

    def __init__(self):
        Animal.__init__(self)
        print("Objeto Gato criado")
    
    def emitir_som(self):
        print("Miau!")

Kiko = Cachorro()

Mochi = Gato()

Kiko.emitir_som()
Mochi.emitir_som()
Kiko.imprimir()
Kiko.comer()
Mochi.comer()