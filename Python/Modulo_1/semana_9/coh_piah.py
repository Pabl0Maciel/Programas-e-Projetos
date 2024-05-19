import re

def le_assinatura():
    '''A funcao le os valores dos tracos linguisticos do modelo e devolve uma assinatura a ser comparada com os textos fornecidos'''
    print("Bem-vindo ao detector automático de COH-PIAH.")
    print("Informe a assinatura típica de um aluno infectado:")

    wal = float(input("Entre o tamanho médio de palavra:"))
    ttr = float(input("Entre a relação Type-Token:"))
    hlr = float(input("Entre a Razão Hapax Legomana:"))
    sal = float(input("Entre o tamanho médio de sentença:"))
    sac = float(input("Entre a complexidade média da sentença:"))
    pal = float(input("Entre o tamanho medio de frase:"))

    return [wal, ttr, hlr, sal, sac, pal]

def le_textos():
    '''A funcao le todos os textos a serem comparados e devolve uma lista contendo cada texto como um elemento'''
    i = 1
    textos = []
    texto = input("Digite o texto " + str(i) +" (aperte enter para sair):")
    while texto:
        textos.append(texto)
        i += 1
        texto = input("Digite o texto " + str(i) +" (aperte enter para sair):")

    return textos

def separa_sentencas(texto):
    '''A funcao recebe um texto e devolve uma lista das sentencas dentro do texto'''
    sentencas = re.split(r'[.!?]+', texto)
    if sentencas[-1] == '':
        del sentencas[-1]
    return sentencas

def separa_frases(sentenca):
    '''A funcao recebe uma sentenca e devolve uma lista das frases dentro da sentenca'''
    return re.split(r'[,:;]+', sentenca)

def separa_palavras(frase):
    '''A funcao recebe uma frase e devolve uma lista das palavras dentro da frase'''
    return frase.split()

def n_palavras_unicas(lista_palavras):
    '''Essa funcao recebe uma lista de palavras e devolve o numero de palavras que aparecem uma unica vez'''
    freq = dict()
    unicas = 0
    for palavra in lista_palavras:
        p = palavra.lower()
        if p in freq:
            if freq[p] == 1:
                unicas -= 1
            freq[p] += 1
        else:
            freq[p] = 1
            unicas += 1

    return unicas

def n_palavras_diferentes(lista_palavras):
    '''Essa funcao recebe uma lista de palavras e devolve o numero de palavras diferentes utilizadas'''
    freq = dict()
    for palavra in lista_palavras:
        p = palavra.lower()
        if p in freq:
            freq[p] += 1
        else:
            freq[p] = 1

    return len(freq)

def compara_assinatura(as_a, as_b):
    i = 0
    similaridade = 0
    while i < len(as_a) and i < len(as_b):
        similaridade += abs(as_a[i] - as_b[i])
        i += 1
    similaridade_final=similaridade/6
    return similaridade_final
        



def calcula_assinatura(texto):
    
    total_sentencas=separa_sentencas(texto)
    
    total_frases=[]
    for sentenca in total_sentencas:
        total_frases.extend(separa_frases(sentenca))
    
    total_palavras=[]
    for frase in total_frases:
        total_palavras.extend(separa_palavras(frase))

    total_palavras_unicas=n_palavras_unicas(total_palavras)

    total_palavras_diferentes=n_palavras_diferentes(total_palavras)
    
    total_carac_sentenca=0
    for sentenca in total_sentencas:
        total_carac_sentenca+=len(sentenca)

    total_carac_frase=0
    for frase in total_frases:
        total_carac_frase+=len(frase)
    
    total_carac_palavras=0
    for palavra in total_palavras:
        total_carac_palavras+=len(palavra)

    total_sentencas=len(total_sentencas)
    total_frases=len(total_frases)
    total_palavras=len(total_palavras)
    
    wal = total_carac_palavras/total_palavras
    ttr = total_palavras_diferentes/total_palavras
    hlr = total_palavras_unicas/total_palavras
    sal = total_carac_sentenca/total_sentencas
    sac = total_frases/total_sentencas
    pal = total_carac_frase/total_frases

    return [wal,ttr,hlr,sal,sac,pal]


def avalia_textos(textos, ass_cp): 
    assinatura=[]
    for i in textos:
        assinatura.append(compara_assinatura(calcula_assinatura(i),ass_cp))

    i=0
    menor_assinatura = assinatura[i]
    while i < len(assinatura)-1:
        if assinatura[i+1] < menor_assinatura:
            menor_assinatura = assinatura[i+1]
        i+=1

    i=0
    while i < len(assinatura)-1:
        if menor_assinatura==assinatura[i]:
            return i+1
        i+=1

