print([x for x in range(10)])

lista_numeros = [x for x in range(10) if x < 5]
print(lista_numeros)

lista_frutas = ['banana', 'abacate', 'melancia', 'cereja', 'manga']
nova_lista = [x for x in lista_frutas if 'm' in x]
print(nova_lista)

dict_alunos = {'Bob':68, 'Michel':84, 'Zico':57, 'Ana':93}
dict_alunos_status = {k:v for (k,v) in dict_alunos.items()}
print(dict_alunos_status)

dict_alunos_status2 = {k: ('Aprovado' if v > 70 else 'Reprovado') for (k,v) in dict_alunos.items()}
print(dict_alunos_status2)