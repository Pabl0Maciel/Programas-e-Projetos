<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Segmentação%20de%20Clientes&fontSize=32&fontColor=4F8EF7&fontAlignY=38&desc=Clusterização%20não%20supervisionada%20com%20K-Means&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Scikit-learn](https://img.shields.io/badge/Scikit--learn-%23F7931E.svg?style=for-the-badge&logo=scikit-learn&logoColor=white)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)

</div>

---

## 🎯 Objetivo

Agrupar clientes em **3 segmentos** com base em características de perfil e comportamento de consumo, usando clusterização não supervisionada com K-Means. O resultado é exportado em CSV para uso em estratégias direcionadas de marketing e relacionamento.

---

## ⚙️ Pipeline

```
dados_clientes.csv
        │
        ▼
StandardScaler()          ← padroniza idade, renda e pontuação
        │                    para mesma escala (média 0, desvio 1)
        ▼
KMeans(n_clusters=3)
        │
        ▼
kmeans.fit(dados_padronizados)
        │
        ▼
df['cluster'] = kmeans.labels_   ← 0, 1 ou 2
        │
        ▼
clientes_segmentados.csv
```

---

## 📊 Features utilizadas

| Coluna | Tipo | Descrição |
|--------|------|-----------|
| `idade` | Numérico | Idade do cliente |
| `renda_anual` | Numérico | Renda anual em reais |
| `pontuacao_gastos` | Numérico | Score de comportamento de gastos (0–100) |

> A padronização com `StandardScaler` é essencial — sem ela, `renda_anual` (em dezenas de milhares) dominaria o cálculo de distância e distorceria os clusters.

---

## 📁 Saída

O arquivo `clientes_segmentados.csv` contém todos os clientes originais com uma coluna extra `cluster` (0, 1 ou 2), indicando o segmento de cada cliente.

Exemplo de uso dos segmentos:

| Cluster | Perfil típico | Ação sugerida |
|---------|--------------|---------------|
| 0 | Alta renda, alta pontuação | Produtos premium, fidelização |
| 1 | Renda média, pontuação moderada | Ofertas de cross-sell |
| 2 | Baixa renda ou baixa pontuação | Campanhas de retenção |

> Os perfis reais dependem da distribuição dos dados — analisar as médias por cluster após a execução.

---

## 🚀 Como executar

```bash
pip install pandas scikit-learn
python segmentacao.py
```

> Ajuste o caminho dos arquivos CSV no script conforme sua estrutura de diretórios:

```python
df = pd.read_csv('Projetos/Segmentacao de Clientes/dados_clientes.csv')
df.to_csv('Projetos/Segmentacao de Clientes/clientes_segmentados.csv', index=False)
```

---

## 📂 Estrutura

```
📦 Segmentacao de Clientes/
│
├── segmentacao.py              # Script principal
├── dados_clientes.csv          # Dataset de entrada
├── clientes_segmentados.csv    # Dataset com coluna cluster gerada
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
