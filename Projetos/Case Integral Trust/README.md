<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Case%20Integral%20Trust&fontSize=36&fontColor=4F8EF7&fontAlignY=38&desc=Análise%20de%20Vendas%20·%20Correção%20de%20Dados%20·%20Heatmap%20·%20Dashboard%20Power%20BI&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)
![Seaborn](https://img.shields.io/badge/Seaborn-4C72B0?style=for-the-badge&logo=python&logoColor=white)
![Power BI](https://img.shields.io/badge/Power%20BI-F2C811?style=for-the-badge&logo=powerbi&logoColor=black)
![Google Colab](https://img.shields.io/badge/Google%20Colab-F9AB00?style=for-the-badge&logo=googlecolab&logoColor=black)

</div>

---

## 🎯 Contexto

Case técnico desenvolvido como **teste prático para processo seletivo de estágio de dados**. O desafio consistia em analisar um dataset de vendas de e-commerce em três partes — exploração estatística, dashboard interativo e relatório de insights — em um único entregável.

🔗 [Abrir no Google Colab](https://colab.research.google.com/drive/1YpDq3V3stKTvJhrzXcFsplATNXW6Pfy2?usp=sharing)

---

## 📂 Estrutura

```
📦 Case Integral Trust/
│
├── case_integral_trust.py          # Script principal (exportado do Colab)
├── dataset_vendas.csv              # Dataset bruto (1.000 registros)
├── dataset_vendas_corrigido.csv    # Dataset após correção de categorias
├── Case_IntegralTrust.pbix         # Dashboard Power BI
└── README.md
```

---

## 📊 Dataset

**1.000 registros** de vendas com as seguintes variáveis:

| Coluna | Tipo | Descrição |
|--------|------|-----------|
| `data_venda` | `datetime` | Data da transação |
| `categoria` | `str` | Categoria do produto *(com erros no bruto)* |
| `produto` | `str` | Nome do produto |
| `preco` | `float` | Preço unitário |
| `quantidade_vendida` | `int` | Quantidade vendida na transação |
| `regiao` | `str` | Região da venda (Norte, Sul, Leste, Oeste, Centro-Oeste) |

---

## 🗂️ Estrutura do Case

### Parte 1 — Análise Estatística e Exploratória (40%)

**Correção de categorias**

O primeiro problema identificado foi que produtos estavam associados às categorias erradas (ex: `Celular` na categoria `Beleza`). A correção foi feita via mapeamento explícito com dicionário:

```python
categorias_produtos = {
    'Celular': 'Eletrônicos', 'Calça': 'Roupas', 'Câmera': 'Eletrônicos',
    'Vestido': 'Roupas', 'Laptop': 'Eletrônicos', 'Casaco': 'Roupas',
    'Perfume': 'Beleza', 'Maquiagem': 'Beleza', 'Shampoo': 'Beleza',
    'Creme': 'Beleza', 'Fone de Ouvido': 'Eletrônicos',
    'Bola de Futebol': 'Esportes', 'Raquete': 'Esportes',
    'Capacete': 'Esportes', 'Corda': 'Esportes', 'Camisa': 'Roupas',
    'Biografia': 'Livros', 'Técnico': 'Livros',
    'Ficção Científica': 'Livros', 'Romance': 'Livros'
}
df['categoria'] = df['produto'].map(categorias_produtos)
```

**Estatísticas descritivas**

- Alto desvio padrão no preço — confirma faixa ampla de produtos (livros a eletrônicos)
- Preço mínimo de R$12,54 investigado — identificado como livro, sem outlier real

**Análise temporal e regional**

- Agrupamento por data para identificar picos de quantidade vendida
- Ranking de regiões por volume total de vendas

**Matriz de correlação com heatmap**

One Hot Encoding aplicado nas variáveis categóricas para calcular a correlação. Filtro de `|correlação| ≥ 0.3` para facilitar leitura:

```python
df_corr = pd.get_dummies(df, columns=['categoria', 'produto', 'regiao'])
matriz_corr = df_corr.corr()

mask = np.abs(matriz_corr) < 0.3  # filtra correlações fracas
sns.heatmap(matriz_corr, mask=mask, annot=True, cmap='coolwarm', fmt='.2f')
```

> Resultado: correlação entre **preço e quantidade vendida abaixo de 0.1** — praticamente sem relação linear.

---

### Parte 2 — Dashboard Power BI (40%)

Dashboard interativo com:
- Visão geral de vendas por categoria
- Gráfico de vendas ao longo do tempo com picos e quedas identificados
- Filtros por data, categoria e região

📁 Arquivo: [`Case_IntegralTrust.pbix`](./Case_IntegralTrust.pbix)

---

### Parte 3 — Interpretação e Insights (20%)

| Tema | Insight |
|------|---------|
| **Beleza** | Categoria com menor volume de vendas — distante das demais tanto em total quanto em média |
| **Roupas** | Produtos como `Creme` e `Casaco` entre os menos vendidos — merecem atenção |
| **Sazonalidade** | Março, Agosto e Setembro com vendas abaixo da média — oportunidade para promoções |
| **Regional** | Centro-Oeste: eletrônicos; Leste/Oeste: livros; Norte: roupas; Sul: esportes |
| **Sul** | Região com menor volume geral — necessita investigação do perfil do consumidor |

**Conclusão:** O setor de beleza e alguns meses específicos demandam ações proativas. A variação de preferência por categoria entre regiões sugere potencial para estratégias de investimento direcional.

---

## 🚀 Como reproduzir

**Opção 1 — Google Colab** *(recomendado)*

Acesse diretamente: [Abrir no Colab](https://colab.research.google.com/drive/1YpDq3V3stKTvJhrzXcFsplATNXW6Pfy2?usp=sharing)

**Opção 2 — Local**

```bash
pip install pandas numpy matplotlib seaborn

python case_integral_trust.py
```

> Ajuste o caminho do `dataset_vendas.csv` no script antes de executar.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
