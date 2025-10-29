import socket
import sys
import random
import re

# Atualiza o estado da palavra quando o palpite for correto
def atualizar_estado(palavra, estado, letra):
    nova = list(estado)
    for i, c in enumerate(palavra):
        if c.lower() == letra.lower():
            nova[i] = c
    return "".join(nova)

# Valida o nome do jogador
def nome_valido(nome):
    return bool(re.match(r"^[A-Za-z0-9]+$", nome))

# Valida a palavra escolhida
def palavra_valida(palavra):
    return bool(re.match(r"^[A-Za-z]+$", palavra))

def main():
    if len(sys.argv) < 2:
        print("Uso: python server.py <num_jogadores> [porta]")
        sys.exit(1)

    num_jogadores = int(sys.argv[1])
    porta = int(sys.argv[2]) if len(sys.argv) > 2 else 6891

    servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    servidor.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Permite reusar a porta
    servidor.bind(("0.0.0.0", porta))
    servidor.listen(num_jogadores)


    print(f"Servidor inicializado na porta {porta}")
    print("Iniciando novo jogo...")

    jogadores = {}

    # Conexão com jogadores 
    for i in range(num_jogadores):
        print(f"Aguardando jogador {i+1}...")
        conn, addr = servidor.accept()
        dados = conn.recv(1024).decode().strip()

        if not dados.startswith("NEWPLAYER "):
            conn.sendall("ERROR INVALID_FORMAT\r\n".encode())
            conn.close()
            continue

        nome = dados.split(" ")[1]
        if not nome_valido(nome):
            conn.sendall("ERROR INVALID_PLAYER_NAME\r\n".encode())
            conn.close()
            continue

        jogadores[nome] = conn
        print(f"Jogador conectado: {nome} ({addr})")
        conn.sendall("STANDBY\r\n".encode())

    if len(jogadores) < 2:
        for c in jogadores.values():
            c.sendall("ERROR NOT_ENOUGH_PLAYERS\r\n".encode())
            c.close()
        print("Erro: jogadores insuficientes.")
        servidor.close()
        return

    # Escolhe o mestre
    mestre = random.choice(list(jogadores.keys()))
    print(f"Jogador mestre: {mestre}")
    jogadores[mestre].sendall("MASTER\r\n".encode())

    dados = jogadores[mestre].recv(1024).decode().strip()
    if not dados.startswith("WORD "):
        jogadores[mestre].sendall("ERROR INVALID_MASTER_MESSAGE\r\n".encode())
        print("Erro: mestre enviou formato inválido.")
        servidor.close()
        return

    palavra = dados.split(" ", 1)[1].strip()
    if not palavra_valida(palavra):
        jogadores[mestre].sendall("ERROR INVALID_MASTER_MESSAGE\r\n".encode())
        print("Erro: palavra do mestre inválida.")
        servidor.close()
        return

    jogadores[mestre].sendall("OK\r\n".encode())
    print(f"Jogador mestre forneceu a palavra: {palavra}")
    print("Jogo iniciado com sucesso!\n")

    # Início do jogo
    vidas = 7
    estado = "_" * len(palavra)
    ordem = [j for j in jogadores if j != mestre]
    palpites_letras = set()
    palpites_palavras = set()

    for conn in jogadores.values():
        conn.sendall(f"NEWGAME {vidas} {len(palavra)}\r\n".encode())

    rodada = 1
    indice = 0

    while True:
        jogador = ordem[indice % len(ordem)]
        conn = jogadores[jogador]
        conn.sendall("YOURTURN\r\n".encode())
        print(f"Rodada {rodada} | Vez de {jogador}")

        dados = conn.recv(1024).decode().strip()
        print(f"Mensagem recebida: {dados}")

        # Saída voluntária
        if dados == "QUIT":
            conn.sendall("OK\r\n".encode())
            print(f"Jogador {jogador} saiu do jogo.")
            conn.close()
            del jogadores[jogador]
            ordem = [j for j in jogadores if j != mestre]
            if len(ordem) == 0:
                print("Nenhum jogador restante. Encerrando jogo.")
                break
            continue

        # Palpite de letra
        if dados.startswith("GUESS LETTER "):
            letra = dados.split(" ")[2].strip()

            if not letra.isalpha() or len(letra) != 1:
                conn.sendall("ERROR INVALID_LETTER\r\n".encode())
                continue

            if letra.lower() in palpites_letras:
                conn.sendall("ERROR ALREADY_GUESSED\r\n".encode())
                continue

            palpites_letras.add(letra.lower())
            conn.sendall("OK\r\n".encode())

            if letra.lower() in palavra.lower():
                estado = atualizar_estado(palavra, list(estado), letra)
                print(f"{jogador} acertou a letra '{letra}' → {estado}")
            else:
                vidas -= 1
                print(f"{jogador} errou a letra '{letra}' → vidas restantes: {vidas}")

        # Palpite de palavra
        elif dados.startswith("GUESS WORD "):
            tentativa = dados.split(" ", 2)[2].strip()

            if len(tentativa) != len(palavra):
                conn.sendall("ERROR INVALID_WORD_LENGTH\r\n".encode())
                continue

            if tentativa.lower() in palpites_palavras:
                conn.sendall("ERROR ALREADY_GUESSED\r\n".encode())
                continue

            palpites_palavras.add(tentativa.lower())
            conn.sendall("OK\r\n".encode())

            if tentativa.lower() == palavra.lower():
                for c in jogadores.values():
                    c.sendall(f"GAMEOVER WIN {jogador} {palavra}\r\n".encode())
                print(f"{jogador} adivinhou a palavra '{palavra}'!")
                break
            else:
                vidas -= 1
                print(f"{jogador} errou a palavra '{tentativa}' → vidas restantes: {vidas}")

        else:
            conn.sendall("ERROR INVALID_FORMAT\r\n".encode())
            continue

        # Verifica fim de jogo
        if "_" not in estado:
            for c in jogadores.values():
                c.sendall(f"GAMEOVER WIN {jogador} {palavra}\r\n".encode())
            print(f"{jogador} completou a palavra!")
            break

        if vidas <= 0:
            for c in jogadores.values():
                c.sendall(f"GAMEOVER LOSE {jogador} {palavra}\r\n".encode())
            print(f"A palavra não foi adivinhada. Último palpite: {jogador}")
            break

        # Envia STATUS para todos
        for c in jogadores.values():
            c.sendall(f"STATUS {vidas} {estado} {jogador} {dados}\r\n".encode())

        print(f"Estado atual: {estado} | Vidas: {vidas}\n")
        indice += 1
        rodada += 1

    # Encerra conexões
    for c in jogadores.values():
        try:
            c.close()
        except:
            pass

    servidor.close()
    print("Finalizando jogo... Servidor encerrado.")

if __name__ == "__main__":
    main()
