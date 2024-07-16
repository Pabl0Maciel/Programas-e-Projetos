class Livro():

    def __init__(self, titulo, isbn):
        self.titulo = titulo
        self.isbn = isbn
        print("Construtor chamado para criar um objeto desta classe")

    def imprime(self, titulo, isbn):
        print("Este e o livro %s e ISBN %d" % (titulo, isbn))

Livro2 = Livro("O Poder do Habito", 77886611)

print(Livro2.titulo)
print(Livro2.imprime("O Poder do Habito", 77886611))

class Algoritmo():
    def __init__(self, tipo_algo):
        self.tipo = tipo_algo
        print("Construtor chamado para criar um objeto desta classe")

algo1 = Algoritmo(tipo_algo = 'Deep Learning')
print(algo1.tipo)

algo2 = Algoritmo(tipo_algo = 'Random Forest')
print(algo2.tipo)