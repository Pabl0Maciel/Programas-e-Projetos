class Circulo():
    pi = 3.14

    def __init__(self, raio = 5):
        self.raio = raio

    def area(self):
        return (self.raio * self.raio) * Circulo.pi
    
    def setRaio(self, novo_raio):
        self.raio = novo_raio
    
    def getRaio(self):
        return self.raio
    
circ = Circulo()
print(circ.getRaio())

circ1 = Circulo(7)
print(circ1.getRaio())

print("A area e igual a", circ.area())
circ.setRaio(3)
print("Novo raio e", circ.getRaio())