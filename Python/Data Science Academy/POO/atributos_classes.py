class Funcionarios:
    def __init__(self, nome, salario, cargo):
        self.nome = nome
        self.salario = salario
        self.cargo = cargo

    def listFunc(self):
        print("Funcionario(a) " + self.nome + " tem salario de R$" + str(self.salario) + " e o cargo e " + self.cargo)

Func1 = Funcionarios("Mary", 2000, "Cientista de Dados")
print(Func1.listFunc())

print(hasattr(Func1, "nome")) # has attribute

print(getattr(Func1, "salario")) # get attribute

setattr(Func1, "salario", 4500) # set attribute

print(getattr(Func1, "salario")) 

delattr(Func1, "salario") # delete attribute

print(hasattr(Func1, "salario"))
