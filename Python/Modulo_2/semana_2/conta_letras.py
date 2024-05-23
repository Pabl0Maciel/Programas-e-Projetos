def conta_letras(frase, contar = 'vogais'):
    if contar == "consoantes":
        consoante = 0
        for letra in frase:
            if letra != 'A' and letra != 'E' and letra != 'I' and letra != 'O' and letra !='U' and letra != 'a' and letra != 'e' and letra != 'i' and letra != 'o' and letra !='u' and letra != " ":
                consoante+=1
        return consoante
    else:
        vogais = 0
        for letra in frase:
            if letra == 'A' or letra == 'E' or letra == 'I' or letra == 'O' or letra =='U' or letra == 'a' or letra == 'e' or letra == 'i' or letra == 'o' or letra =='u' and letra != " ":
                vogais += 1
        return vogais
    