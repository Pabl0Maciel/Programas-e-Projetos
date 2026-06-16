<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Detector%20de%20Plágio%20(COH-PIAH)&fontSize=32&fontColor=4F8EF7&fontAlignY=38&desc=Identificação%20de%20autoria%20por%20assinatura%20linguística&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Regex](https://img.shields.io/badge/Regex-Processamento%20de%20Texto-4F8EF7?style=for-the-badge&logo=python&logoColor=white)

</div>

---

## 🎯 Objetivo

Identificar automaticamente qual texto de uma lista foi escrito pelo mesmo autor de uma assinatura linguística de referência. O algoritmo calcula **6 traços linguísticos** de cada texto e compara com os traços típicos do autor suspeito — o texto com menor distância é apontado como o mais provável.

> Projeto inspirado na fictícia doença **COH-PIAH** — metáfora para plágio —, desenvolvido como exercício de programação na USP.

---

## 🧠 Como funciona

### Os 6 traços linguísticos

| Sigla | Traço | Como é calculado |
|-------|-------|-----------------|
| `WAL` | Tamanho médio de palavra | Total de caracteres das palavras ÷ total de palavras |
| `TTR` | Relação Type-Token | Palavras diferentes ÷ total de palavras |
| `HLR` | Razão Hapax Legomana | Palavras únicas (aparecem 1x) ÷ total de palavras |
| `SAL` | Tamanho médio de sentença | Total de caracteres das sentenças ÷ total de sentenças |
| `SAC` | Complexidade média da sentença | Total de frases ÷ total de sentenças |
| `PAL` | Tamanho médio de frase | Total de caracteres das frases ÷ total de frases |

### Pipeline de análise

```
Texto de entrada
      │
      ├── separa_sentencas()   → divide em [.!?]
      │         │
      │         └── separa_frases()    → divide em [,:;]
      │                   │
      │                   └── separa_palavras()  → divide por espaço
      │
      └── calcula_assinatura()
              │
              ├── WAL, TTR, HLR, SAL, SAC, PAL
              │
              └── compara_assinatura()
                      │
                      └── Σ |traço_texto - traço_referência| / 6
                                    │
                                    └── menor valor → texto do autor
```

---

## 🚀 Como executar

```bash
python coh_piah.py
```

O script solicitará as entradas interativamente:

**1. Assinatura típica do autor suspeito** (6 valores numéricos):

```
Entre o tamanho médio de palavra:
Entre a relação Type-Token:
Entre a Razão Hapax Legomana:
Entre o tamanho médio de sentença:
Entre a complexidade média da sentença:
Entre o tamanho médio de frase:
```

**2. Textos para comparação** (um por vez; Enter vazio encerra):

```
Digite o texto 1 (aperte enter para sair): <cole o texto aqui>
Digite o texto 2 (aperte enter para sair): <cole o texto aqui>
Digite o texto 3 (aperte enter para sair): <Enter para encerrar>
```

---

## 🧪 Dados de teste

**Assinatura de referência:**

| Traço | Valor |
|-------|-------|
| Tamanho médio de palavra | `4.51` |
| Relação Type-Token | `0.693` |
| Razão Hapax Legomana | `0.55` |
| Tamanho médio de sentença | `70.82` |
| Complexidade média da sentença | `1.82` |
| Tamanho médio de frase | `38.5` |

**Textos para teste** (3 trechos da literatura brasileira):

| Texto | Trecho | Autor real |
|-------|--------|-----------|
| 1 | *"Num fabulário ainda por encontrar..."* | Fernando Pessoa |
| 2 | *"Voltei-me para ela; Capitu tinha os olhos no chão..."* | Machado de Assis |
| 3 | *"Senão quando, estando eu ocupado em preparar..."* | Machado de Assis |

---

## 📂 Estrutura

```
📦 Detector de Plagio/
│
├── coh_piah.py    # Script principal
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
