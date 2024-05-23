def maiusculas(frase):
    letras_maiusculas = ""
    for letra in frase:
        if ord(letra) >= ord("A") and ord(letra) <= ord("Z") :
            letras_maiusculas = letras_maiusculas + letra
    return letras_maiusculas

