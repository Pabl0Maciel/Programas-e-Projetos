<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Jogo%20NIM&fontSize=38&fontColor=4F8EF7&fontAlignY=45&desc=Jogo%20de%20estratégia%20com%20IA%20imbatível&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)

</div>

---

## 🎯 O que é

Implementação do clássico jogo matemático **NIM** com dois modos: partida isolada e campeonato (melhor de 3). O computador joga com estratégia ótima baseada na **Teoria de Nim** — se estiver em posição vantajosa, é imbatível.

---

## 🧠 A estratégia do computador

O computador usa a fórmula matemática exata da teoria de Nim:

```python
jogada = n % (m + 1)
if jogada == 0:
    jogada = 1   # fallback quando já está em posição perdedora
```

Onde `n` = peças restantes e `m` = limite por jogada. Isso garante que o computador sempre deixe o adversário em posição perdedora — a menos que comece em desvantagem.

**Quem começa é definido matematicamente:**
- Se `n % (m + 1) == 0` → jogador começa (computador já está em vantagem)
- Caso contrário → computador começa

---

## 🎮 Modos de jogo

| Modo | Descrição |
|------|-----------|
| **Partida isolada** | Uma única partida com N peças e limite M por jogada |
| **Campeonato** | 3 rodadas com configurações independentes — placar ao final |

---

## 🚀 Como executar

```bash
python nim.py
```

**Fluxo do jogo:**

```
Bem-vindo ao jogo do NIM!
1 - para jogar uma partida isolada
2 - para jogar um campeonato

Digite a opcao: 1
Quantas peças? 15
Limite de peças por jogada? 3

Computador começa!
O computador tirou 3 peça(s). Restam 12 peça(s) no tabuleiro.
Quantas peças voce quer tirar?
```

---

## 📂 Estrutura

```
📦 Jogo NIM/
│
├── nim.py       # Script principal
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
