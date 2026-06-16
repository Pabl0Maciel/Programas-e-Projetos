<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Score%20de%20Crédito%20de%20Cliente&fontSize=30&fontColor=4F8EF7&fontAlignY=38&desc=Classificação%20de%20risco%20bancário%20com%20Random%20Forest%20e%20KNN&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Scikit-learn](https://img.shields.io/badge/Scikit--learn-%23F7931E.svg?style=for-the-badge&logo=scikit-learn&logoColor=white)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)

</div>

---

## 🎯 Objetivo

Construir um modelo de classificação para prever o **score de crédito** de clientes bancários — `Good`, `Standard` ou `Poor` — comparando Random Forest e KNN, e aplicar o melhor modelo sobre novos clientes.

---

## ⚙️ Pipeline

```
clientes.csv (dados históricos)
        │
        ▼
LabelEncoder × 3 colunas categóricas
(profissao · mix_credito · comportamento_pagamento)
        │
        ▼
x = features   y = score_credito
        │
        ▼
train_test_split (70% treino / 30% teste)
        │
        ├── RandomForestClassifier.fit()
        └── KNeighborsClassifier.fit()
                │
                ▼
        accuracy_score() → selecionar melhor modelo
                │
                ▼
        novos_clientes.csv
                │
                ▼
        previsao = modelo.predict()
```

---

## 📊 Features utilizadas

| Coluna | Tipo | Descrição |
|--------|------|-----------|
| `idade` | Numérico | Idade do cliente |
| `profissao` | Categórico* | Profissão do cliente |
| `salario_anual` | Numérico | Renda anual |
| `num_contas` | Numérico | Número de contas bancárias |
| `num_cartoes` | Numérico | Número de cartões de crédito |
| `juros_emprestimo` | Numérico | Taxa de juros dos empréstimos |
| `num_emprestimos` | Numérico | Quantidade de empréstimos |
| `dias_atraso` | Numérico | Dias de atraso em pagamentos |
| `mix_credito` | Categórico* | Qualidade do mix de crédito |
| `divida_total` | Numérico | Dívida total acumulada |
| `comportamento_pagamento` | Categórico* | Padrão de pagamento |
| `saldo_final_mes` | Numérico | Saldo ao final do mês |
| `emprestimo_*` | Binário | Tipos de empréstimo (carro, casa, pessoal, crédito, estudantil) |

> *Colunas categóricas convertidas com `LabelEncoder` antes do treino.

**Target:** `score_credito` → `Good` / `Standard` / `Poor`

---

## 🚀 Como executar

```bash
pip install pandas scikit-learn
python score_credito.py
```

> Ajuste o caminho dos CSVs no script conforme sua estrutura de diretórios:

```python
dados = pd.read_csv('Projetos/Score de Credito de Cliente/clientes.csv')
novos_dados = pd.read_csv('Projetos/Score de Credito de Cliente/novos_clientes.csv')
```

---

## 📂 Estrutura

```
📦 Score de Credito de Cliente/
│
├── score_credito.py       # Script principal
├── clientes.csv           # Dataset de treino e teste
├── novos_clientes.csv     # Novos clientes para previsão
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
