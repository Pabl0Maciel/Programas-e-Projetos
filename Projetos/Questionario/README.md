<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Questionário&fontSize=38&fontColor=4F8EF7&fontAlignY=45&desc=Quiz%20interativo%20sobre%20estresse%20em%20C&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

</div>

---

## 🎯 Objetivo

Quiz interativo de 15 perguntas sobre **gestão do estresse** — desenvolvido em C com validação de entrada, controle de pontuação e opção de jogar novamente.

---

## 🎮 Como funciona

```
"Iniciar Quiz? (s/n)"
        │
        ▼
Loop de 15 perguntas
        │
        ├── Exibe a pergunta com alternativas (a/b/c)
        ├── Valida a entrada (rejeita caracteres inválidos)
        ├── Compara com gabarito → "Correto!" ou "Incorreto!"
        └── Acumula pontuação
        │
        ▼
Exibe pontuação final
"Jogar Novamente? (s/n)"
```

---

## 📋 Conteúdo do quiz

15 perguntas sobre:

- Definição e causas do estresse
- Hormônios e respostas fisiológicas
- Técnicas de relaxamento (respiração diafragmatica, relaxamento muscular)
- Distorções cognitivas e inteligência emocional
- Procrastinação e resolução de problemas

---

## 🚀 Como compilar e executar

```bash
# Compilar
gcc quest.c -o questionario

# Executar
./questionario
```

---

## 📂 Estrutura

```
📦 Questionario/
│
├── quest.c      # Código fonte
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
