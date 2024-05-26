class Triangulo:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    
    def perimetro(self):
        return self.a + self.b + self.c
    
    def tipo_lado(self):
        if (self.a == self.b or self.b == self.c or self.a == self.c) and (self.a != self.b or self.b != self.c):
            return 'isósceles'
        elif self.a == self.b and self.b == self.c:
            return 'equilátero'
        else:
            return 'escaleno'
        
    def retangulo(self):
        if (self.a)**2 + (self.b)**2 == (self.c)**2:
            return True
        else:
            return False
        
    def semelhantes(self, triangulo):
        triangulo_1 = sorted([self.a, self.b, self.c])
        triangulo_2 = sorted([triangulo.a, triangulo.b, triangulo.c])

        if triangulo_1[0]/triangulo_2[0] == triangulo_1[1]/triangulo_2[1] == triangulo_1[1]/triangulo_2[1] == triangulo_1[2]/triangulo_2[2]:
            return True
        else:
            return False
        
t1 = Triangulo(2,3,5)
t2 = Triangulo (4,6,10)

print(t1.semelhantes(t2))


    
