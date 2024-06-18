estudantes = ['Pedro', 24, 'Ana', 22, 'Ronaldo', 26, 'Janaina', 25]
print(type(estudantes))
print(len(estudantes))

estudantes_dict = {'Pedro':24, 'Ana':22, 'Ronaldo':26, 'Janaina':25} # dicionario (associacoes de valores a chaves)
print(type(estudantes_dict))
print(len(estudantes_dict))
print(estudantes_dict['Pedro'])

estudantes_dict['Marcelo'] = 23
print(estudantes_dict['Marcelo'])

estudantes_dict.clear() # limpa o dicionario
print(estudantes_dict)

del estudantes_dict # deleta o dicionario

estudantes_dict_1 = {'Pedro':24, 'Ana':22, 'Ronaldo':26, 'Janaina':25}
print(estudantes_dict_1.keys()) # retorna as chaves
print(estudantes_dict_1.values()) # retorna os valores
print(estudantes_dict_1.items()) # retorna os itens

estudantes_dict_2 = {'Camila':27, 'Adriana':28, 'Roberta':26}

estudantes_dict_1.update(estudantes_dict_2)
print(estudantes_dict_1)

dict_3 = {'chave1':1230, 'chave2':[22, 453, 73.4], 'chave3':['picanha', 'fraldinha', 'alcatra']} # pode atribuir uma lista a uma chave
print(dict_3)
print(dict_3['chave2'])

print(dict_3['chave3'][0].upper()) # acesso a elementos da lista da chave

dict_3['chave2'][0] -= 2
print(dict_3)

dict_aninhado = {'key1':{'key2_aninhada':{'key3_aninhada':'dict aninhado em Python'}}}
print(dict_aninhado)

print(dict_aninhado['key1']['key2_aninhada']['key3_aninhada'])



