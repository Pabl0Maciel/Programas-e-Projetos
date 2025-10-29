import socket
import sys

# Função para desenhar a forca de acordo com o número de vidas
def desenhar_forca(vidas):
    estagios = [
        """
        _____
        |
        |
        |
        |
        |
        ------
        """,
        """
        _____
        |   |
        |
        |
        |
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |
        |
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |   |
        |
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |  /|
        |
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |  /|\\
        |
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |  /|\\
        |  /
        |
        ------
        """,
        """
        _____
        |   |
        |   o
        |  /|\\
        |  / \\
        |
        ------
        """
    ]

    # Converte o número de vidas para o índice da forca
    indice = 7 - vidas
    if indice < 0:
        indice = 0
    if indice > 7:
        indice = 7

    print(estagios[indice])


def main():
    # Verifica argumentos
    if len(sys.argv) < 2:
        print("Uso: python client.py <nome> [ip:porta]")
        sys.exit(1)

    # Define nome e endereço do servidor
    nome = sys.argv[1]
    destino = sys.argv[2] if len(sys.argv) > 2 else "127.0.0.1:6891"
    ip, porta = destino.split(":")
    porta = int(porta)

    # Cria o socket e conecta ao servidor
    cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Conectando ao servidor...")
    cliente.connect((ip, porta))
    cliente.sendall(f"NEWPLAYER {nome}\r\n".encode())

    # Variáveis de controle do jogo
    mestre = False
    letras_erradas = []
    palavras_erradas = []

    # Loop principal de comunicação
    while True:
        dados = cliente.recv(1024).decode()
        if not dados:
            break

        # Divide mensagens caso cheguem juntas
        mensagens = [m.strip() for m in dados.split("\r\n") if m.strip()]
        for resposta in mensagens:

            # Espera o início do jogo
            if resposta == "STANDBY":
                print("Aguardando o jogo começar...")

            # Jogador escolhido como mestre
            elif resposta == "MASTER":
                mestre = True
                print("Você é o mestre do jogo!")
                palavra = input("Digite a palavra: ")
                cliente.sendall(f"WORD {palavra}\r\n".encode())

            # Início da partida
            elif resposta.startswith("NEWGAME"):
                _, vidas, tamanho = resposta.split()
                print(f"Jogo iniciado! Vidas: {vidas}, Tamanho da palavra: {tamanho}")
                if mestre:
                    print("Você é o mestre e apenas observará o jogo.")

            # Turno do jogador comum
            elif resposta == "YOURTURN":
                jogada = input("Digite sua jogada (letra ou palavra), ou \\q para sair: ").strip()
                if jogada == "\\q":
                    cliente.sendall("QUIT\r\n".encode())
                    break
                # Jogada é uma letra
                if len(jogada) == 1 and jogada.isalpha():
                    cliente.sendall(f"GUESS LETTER {jogada}\r\n".encode())
                # Jogada é uma palavra
                elif len(jogada) > 1 and jogada.isalpha():
                    cliente.sendall(f"GUESS WORD {jogada}\r\n".encode())
                # Entrada inválida
                else:
                    print("Entrada inválida. Digite apenas letras ou palavras sem números.")
                    continue

            # Atualização do estado do jogo
            elif resposta.startswith("STATUS"):
                partes = resposta.split(" ", 4)
                vidas, estado, jogador, palpite = partes[1:5]
                vidas = int(vidas)

                print(f"\nJogador {jogador} fez a jogada: {palpite}")
                print(f"Estado atual: {estado} — Vidas restantes: {vidas}")

                # Guarda letras erradas
                if "LETTER" in palpite:
                    letra = palpite.split()[-1]
                    if letra.lower() not in estado.lower() and letra.lower() not in letras_erradas:
                        letras_erradas.append(letra.lower())

                # Guarda palavras erradas
                elif "WORD" in palpite:
                    palavra_palpite = palpite.split()[-1]
                    if palavra_palpite.lower() not in estado.lower() and palavra_palpite.lower() not in palavras_erradas:
                        palavras_erradas.append(palavra_palpite.lower())

                # Mostra forca e palpites errados
                desenhar_forca(vidas)
                print(f"Letras erradas: {', '.join(letras_erradas) if letras_erradas else '-'}")
                print(f"Palavras erradas: {', '.join(palavras_erradas) if palavras_erradas else '-'}")

            # Fim do jogo
            elif resposta.startswith("GAMEOVER"):
                _, resultado, jogador, palavra = resposta.split(" ", 3)
                if resultado == "WIN":
                    print(f"\nA palavra '{palavra}' foi adivinhada por {jogador}!")
                else:
                    print(f"\nA palavra '{palavra}' não foi adivinhada. Último palpite: {jogador}")
                    desenhar_forca(0)
                break

            # Tratamento de erros genéricos e inesperados
            elif resposta.startswith("ERROR"):
                print("Erro recebido:", resposta)
                # Se o erro for de mensagem fora da vez
                if "UNEXPECTED_MESSAGE" in resposta:
                    print("Você enviou uma mensagem fora da vez ou inválida. Conexão encerrada pelo servidor.")
                    cliente.close()
                    return

    # Fecha a conexão ao sair do loop
    cliente.close()
    print("Conexão encerrada.")


if __name__ == "__main__":
    main()
