# EP - Jogo da Forca em Rede (ACH2026)

## Descrição Geral
Este projeto implementa um **jogo da forca online** (Hangman) baseado em **sockets TCP** e em um protocolo de aplicação próprio denominado **Hangman Protocol**. Ele foi desenvolvido como parte do Exercício Programa da disciplina **ACH2026 - Redes de Computadores** (2º semestre de 2025).

A aplicação segue o modelo **cliente-servidor**, no qual:
- O **servidor** coordena o jogo, gerencia os jogadores conectados e define o jogador mestre;
- Os **clientes** representam os jogadores que fazem palpites (ou definem a palavra, no caso do mestre).

A comunicação é feita através de **mensagens em texto ASCII** terminadas com `\r\n`, utilizando **conexões TCP persistentes**.

---

## Estrutura do Projeto
```
EP_Hangman/
│
├── server.py   # Aplicação servidor (coordena o jogo)
├── client.py   # Aplicação cliente (jogadores)
└── README.md    # Instruções e documentação
```

---

## Execução

### Iniciar o Servidor
```
python server.py <num_jogadores> [porta]
```
**Exemplo:**
```
python server.py 2 9999
```
Saída esperada:
```
Servidor inicializado na porta 9999
Iniciando novo jogo...
Aguardando jogador 1...
Jogador conectado: Alice
Aguardando jogador 2...
Jogador conectado: Bob
Jogador mestre: Bob
Jogador mestre forneceu a palavra: BANANA
Jogo iniciado com sucesso!
```

### Iniciar os Clientes
Cada cliente deve ser executado em um terminal diferente:
```
python client.py <nome> [ip:porta]
```
**Exemplo:**
```
python client.py Alice 127.0.0.1:9999
python client.py Bob 127.0.0.1:9999
```

---

## Funcionamento do Protocolo Hangman

### Fluxo principal
1. Cliente envia `NEWPLAYER <nome>`
2. Servidor responde `STANDBY`
3. Servidor escolhe o **mestre** e envia `MASTER`
4. Mestre responde com `WORD <palavra>`
5. Servidor confirma com `OK`
6. Servidor envia `NEWGAME <vidas> <tamanho_palavra>`
7. Jogadores comuns recebem `YOURTURN` e respondem:
   - `GUESS LETTER <letra>` ou
   - `GUESS WORD <palavra>`
8. Servidor envia `STATUS <vidas> <estado> <jogador> <palpite>` a todos
9. Ao final, servidor envia `GAMEOVER WIN|LOSE <jogador> <palavra>` e encerra conexões.

### Tratamento de erros
O servidor responde com as mensagens de erro previstas no protocolo:
- `ERROR INVALID_FORMAT`
- `ERROR INVALID_MASTER_MESSAGE`
- `ERROR INVALID_PLAYER_NAME`
- `ERROR ALREADY_GUESSED`
- `ERROR INVALID_LETTER`
- `ERROR INVALID_WORD_LENGTH`
- `ERROR NOT_ENOUGH_PLAYERS`
- `QUIT` → encerramento voluntário do jogador

---

## Funcionalidades do Cliente
- Exibe o desenho ASCII da forca de acordo com o número de vidas.
- Mostra as **letras erradas** e **palavras erradas** tentadas.
- Reconhece o mestre e exibe uma mensagem informativa (“Você é o mestre e apenas observará o jogo.”).
- Permite sair do jogo digitando `\\q`.

**Exemplo de execução:**
```
Jogador Alice fez a jogada: GUESS LETTER r
Estado atual: _A_A_A — Vidas restantes: 6
_____
|   |
|   o
|
|
|
------
Letras erradas: r
Palavras erradas: -
```

---

## Observações Finais
- Linguagem utilizada: **Python 3.10+**
- Compatível com **Ubuntu 22.04** (ambiente de correção da disciplina)
- Comunicação baseada em **sockets TCP**
- O código trata todos os erros especificados no enunciado do EP
- As mensagens seguem rigorosamente o protocolo Hangman (terminadas com `\r\n`)

---

## Autores
- Pablo Caballero Maciel - nroUSP: 14778630

Universidade de São Paulo — Escola de Artes, Ciências e Humanidades (EACH)
Disciplina: **ACH2026 - Redes de Computadores** — 2º semestre de 2025

