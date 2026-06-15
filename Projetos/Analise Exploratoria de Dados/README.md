<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Análise%20Exploratória%20de%20Dados&fontSize=34&fontColor=4F8EF7&fontAlignY=38&desc=Vendas%20Corporativas%20·%2010%20perguntas%20de%20negócio%20respondidas%20com%20dados&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)
![NumPy](https://img.shields.io/badge/NumPy-%23013243.svg?style=for-the-badge&logo=numpy&logoColor=white)
![Matplotlib](https://img.shields.io/badge/Matplotlib-%23ffffff.svg?style=for-the-badge&logo=matplotlib&logoColor=black)
![Seaborn](https://img.shields.io/badge/Seaborn-4C72B0?style=for-the-badge&logo=python&logoColor=white)

</div>

---

## 🎯 Objetivo

Investigação completa de um dataset de **vendas corporativas** para extrair insights de negócio respondendo 10 perguntas analíticas — cobrindo desempenho por cidade, estado, segmento, categoria, período e simulações de desconto.

---

## 📂 Estrutura

```
📦 Analise Exploratoria de Dados/
│
├── analise_1.py        # Perguntas 1 a 5
├── analise_2.py        # Perguntas 6 a 10
├── Respostas.md        # Respostas detalhadas de cada pergunta
├── Imagens/            # Gráficos gerados
│   ├── fig_p2.png      # Total de Vendas por Data do Pedido
│   ├── fig_p3.png      # Total de Vendas por Estado
│   ├── fig_p4.png      # Top 10 Cidades
│   ├── fig_p5.png      # Vendas por Segmento (pizza)
│   ├── fig_p6.png      # Vendas por Segmento e Ano
│   ├── fig_p9.png      # Média de Vendas por Segmento/Ano/Mês
│   └── fig_p10.png     # Vendas por Categoria e SubCategoria
└── README.md
```

> O dataset utilizado é o [`dataset3.csv`](../../arquivos/dataset3.csv) localizado na pasta `arquivos/` do repositório.

---

## ❓ Perguntas de Negócio

### `analise_1.py` — Perguntas 1 a 5

| # | Pergunta | Tipo de análise |
|---|----------|-----------------|
| 1 | Qual cidade teve maior valor de vendas na categoria **Office Supplies**? | Filtro + GroupBy + idxmax |
| 2 | Qual o total de vendas por data do pedido? | Série temporal + gráfico de barras |
| 3 | Qual o total de vendas por estado? | GroupBy geográfico + gráfico de barras |
| 4 | Quais as **Top 10 cidades** com maior total de vendas? | Ranking + gráfico de barras |
| 5 | Qual segmento teve o maior total de vendas? | GroupBy + gráfico de pizza com % |

### `analise_2.py` — Perguntas 6 a 10

| # | Pergunta | Tipo de análise |
|---|----------|-----------------|
| 6 | Qual o total de vendas por segmento e por ano? | GroupBy múltiplo + gráfico de barras agrupadas |
| 7 | Quantas vendas receberiam **15% de desconto** (se Valor_Venda > 1000)? | Simulação com `np.where` |
| 8 | Qual a média de venda antes e depois do desconto de 15%? | Comparativo de médias |
| 9 | Qual a média de vendas por segmento, ano e mês? | GroupBy temporal + gráfico de linha |
| 10 | Qual o total de vendas por categoria e subcategoria (Top 12)? | Análise hierárquica + gráfico combinado |

---

## 📊 Visualizações geradas

<div align="center">

| Pergunta | Gráfico |
|----------|---------|
| P2 — Vendas por Data | Barras (série temporal) |
| P3 — Vendas por Estado | Barras horizontais (Seaborn) |
| P4 — Top 10 Cidades | Barras com paleta `coolwarm` |
| P5 — Vendas por Segmento | Pizza com percentuais |
| P6 — Segmento × Ano | Barras agrupadas por hue (paleta `viridis`) |
| P9 — Média por Segmento/Ano/Mês | Linhas por segmento |
| P10 — Categoria × SubCategoria | Gráfico combinado (Top 12) |

</div>

---

## ⚙️ Como executar

**1. Instale as dependências**

```bash
pip install pandas numpy matplotlib seaborn
```

**2. Certifique-se de que o dataset está no caminho correto**

O script espera o arquivo em `arquivos/dataset3.csv` a partir da raiz do repositório. Se quiser rodar de dentro da pasta do projeto, ajuste a linha de leitura:

```python
# Padrão (rodar da raiz do repositório)
dados = pd.read_csv('arquivos/dataset3.csv')

# Alternativa (rodar de dentro da pasta do projeto)
dados = pd.read_csv('../../arquivos/dataset3.csv')
```

**3. Execute os scripts**

```bash
python analise_1.py   # Perguntas 1 a 5
python analise_2.py   # Perguntas 6 a 10
```

Os gráficos serão exibidos em janelas interativas e as respostas impressas no terminal.

---

## 📖 Respostas

As respostas detalhadas de cada pergunta estão documentadas em [`Respostas.md`](./Respostas.md).

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
