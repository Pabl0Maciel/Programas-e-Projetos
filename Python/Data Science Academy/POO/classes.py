class Livro():
    def __init__(self):
        self.titulo = 'Sapiens - Uma Breve Historia da Humanidade'
        self.isbn = 9988888
        print("Construtor chamado para criar um objeto desta classe")

    def imprime(self):
        print("Foi o criado o livro %s com ISBN %d" % (self.titulo, self.isbn))

Livro1 = Livro()
print(Livro1)
print(type(Livro1))

print(Livro1.titulo)
print(Livro1.imprime())
