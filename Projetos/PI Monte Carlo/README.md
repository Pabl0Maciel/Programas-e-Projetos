<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=PI%20pelo%20Método%20de%20Monte%20Carlo&fontSize=30&fontColor=4F8EF7&fontAlignY=45&desc=Aproximação%20probabilística%20de%20π%20com%20visualização&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Matplotlib](https://img.shields.io/badge/Matplotlib-%23ffffff.svg?style=for-the-badge&logo=matplotlib&logoColor=black)

</div>

---

## 🎯 Objetivo

Aproximar o valor de π usando simulação probabilística — sem nenhuma fórmula geométrica explícita. Quanto mais pontos gerados, mais precisa é a estimativa.

---

## 🧠 Como funciona

Um quadrado de lado 1 contém um quarto de círculo de raio 1. A razão entre a área do quarto de círculo e a área do quadrado é exatamente π/4:

```
Área do quarto de círculo   π × 1²   π
─────────────────────────── = ────── = ─
    Área do quadrado            4      4
```

O algoritmo gera N pontos aleatórios dentro do quadrado e verifica quantos caem dentro do círculo (`x² + y² ≤ 1`):

```
π ≈ 4 × (pontos dentro do círculo / total de pontos)
```

**Pipeline do código:**

```
random.uniform(0,1) × N pontos
          │
          ├── x² + y² ≤ 1 → dentro  (azul)
          └── x² + y² > 1 → fora    (laranja)
                    │
                    ▼
          π = 4 × dentro / (dentro + fora)
                    │
                    ▼
          scatter plot com valor estimado no título
```

---

## 📊 Resultados

Os gráficos gerados estão disponíveis na pasta [`Graficos/`](./Graficos):

| Gráfico | Descrição |
|---------|-----------|
| `Grafico.png` | Simulação com distribuição dos pontos |
| `Grafico_2.png` | Segunda execução com semente diferente |

Notas sobre precisão: com **1.000 pontos**, o valor estimado converge tipicamente entre `3.10` e `3.18`. Para maior precisão, aumente N no código.

---

## 🚀 Como executar

```bash
pip install matplotlib
python pi_MonteCarlo.py
```

Para alterar o número de pontos, modifique a chamada no final do script:

```python
grafico(1000)   # padrão: 1.000 pontos
grafico(100000) # maior precisão: 100.000 pontos
```

---

## 📂 Estrutura

```
📦 PI Monte Carlo/
│
├── pi_MonteCarlo.py     # Script principal
├── Graficos.md          # Notas sobre os gráficos
├── Graficos/
│   ├── Grafico.png      # Resultado da simulação 1
│   └── Grafico_2.png    # Resultado da simulação 2
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
