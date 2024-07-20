import random
from os import system, name

def limpa_tela():

    if name == 'nt': # Windows
        _ = system('cls')
    else: # Mac ou Linux
        _ = system('clear')

def game():
    limpa_tela()

    print("\nBem-vindo(a) ao jogo da forca!")
    print("Adivinhe a palavra abaixo:\n")

    palavras = ['banana', 'abacate', 'uva', 'morango', 'laranja']

    palavra = random.choice(palavras) # escolhe uma palavra

    letras_descobertas = ['_' for letra in palavra] # list comprehension

    chances = 6

    letras_erradas = []

    while chances > 0:
        print(" ".join(letras_descobertas))
        print("\nChances restantes:", chances)
        print("Letras erradas:", " ".join(letras_erradas))

        tentativas_possiveis = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
        
        tentativa = input("\nDigite uma letra: ").lower()
        while tentativa not in tentativas_possiveis or len(tentativa) > 1:
            print("Tentativa invalida! Digite apenas um caractere do alfabeto!")
            tentativa = input("\nDigite uma letra: ").lower()

        if tentativa in palavra:
            index = 0
            for letra in palavra:
                if tentativa == letra:
                    letras_descobertas[index] = letra
                index += 1
        else:
            chances -= 1
            letras_erradas.append(tentativa)

        if '_' not in letras_descobertas:
            print("\nVoce venceu, a palavra era:", palavra)
            break
    if "_" in letras_descobertas:
        print("\nVoce perdeu, a palavra era:", palavra)

if __name__ == '__main__':
    game()



