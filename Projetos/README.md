<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=200&section=header&text=Projetos&fontSize=52&fontColor=4F8EF7&fontAlignY=38&desc=Análise%20de%20Dados%20·%20Machine%20Learning%20·%20Automação%20·%20Banco%20de%20Dados&descColor=00D4FF&descSize=16&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&weight=500&size=15&pause=1200&color=4F8EF7&center=true&vCenter=true&width=650&lines=Projetos+construídos+para+resolver+problemas+reais;Do+web+scraping+ao+modelo+preditivo;De+pipelines+ETL+a+agentes+de+IA;Cada+projeto+com+um+objetivo+claro)](https://git.io/typing-svg)

</div>

---

## 🗂️ Navegação Rápida

| Categoria | Projetos |
|-----------|---------|
| [📊 Análise de Dados & ML](#-análise-de-dados--machine-learning) | EDA, Aluguéis SP, Segmentação, Score de Crédito, Cases |
| [🗄️ Banco de Dados](#️-banco-de-dados) | Loja de Vendas — PostgreSQL completo |
| [🤖 Automação & IA](#-automação--ia) | Cadastros, Insumos, Agente de Currículo |
| [🧠 Algoritmos & Simulações](#-algoritmos--simulações) | Monte Carlo, Detector de Plágio, Gerador de Arrays |
| [🎮 Jogos & Interativos](#-jogos--interativos) | NIM, Forca, Questionário |

---

## 📊 Análise de Dados & Machine Learning

---

### 🔍 Análise Exploratória de Dados
`Python` `Pandas` `Matplotlib` `Seaborn`

Investigação completa de dataset corporativo com foco em identificação de padrões de sazonalidade, performance regional e comportamento de vendas. Inclui visualizações interativas para apoio à decisão estratégica.

**Destaques:** análise de outliers, correlações, distribuições e gráficos comparativos por período e região.

📁 [`Analise Exploratoria de Dados/`](./Analise%20Exploratoria%20de%20Dados)

---

### 🏠 Análise de Aluguéis em São Paulo
`Python` `Selenium` `BeautifulSoup` `Pandas`

Pipeline completo de dados construído do zero para o mercado imobiliário de SP. Em vez de usar datasets prontos, foi desenvolvido um **web scraper próprio** do QuintoAndar — com controle total sobre coleta, estrutura e qualidade dos dados.

**+4.000 imóveis coletados** — studios a apartamentos, com variáveis como valor do aluguel, área, quartos, banheiros, vagas e localização.

```
QuintoAndar (scraping) → CSV → Análise exploratória
```

📁 [`Analise de Alugueis em SP/`](./Analise%20de%20Alugueis%20em%20SP)

---

### 👥 Segmentação de Clientes
`Python` `Scikit-learn` `K-Means` `StandardScaler` `Pandas`

Modelo de clusterização não supervisionada para agrupar clientes em **3 segmentos** com base em idade, renda anual e pontuação de gastos. Permite criação de perfis estratégicos para ações direcionadas de marketing e relacionamento.

```
dados_clientes.csv → StandardScaler → K-Means → 3 clusters → clientes_segmentados.csv
```

📁 [`Segmentacao de Clientes/`](./Segmentacao%20de%20Clientes)

---

### 💳 Score de Crédito de Cliente
`Python` `Scikit-learn` `Random Forest` `KNN` `Pandas`

Modelo preditivo de classificação multiclasse — **Ruim / Ok / Bom** — para prever o score de crédito de clientes bancários. Compara Random Forest e KNN, seleciona o melhor modelo e aplica sobre novos clientes.

**Features:** profissão, mix de crédito, comportamento de pagamento.

```
clientes.csv → treino (RF + KNN) → melhor modelo → novos_clientes.csv → score previsto
```

📁 [`Score de Credito de Cliente/`](./Score%20de%20Credito%20de%20Cliente)

---

### 📈 Case Integral Trust
`Python` `Pandas` `Matplotlib` `Seaborn` `Power BI`

Análise de dataset de vendas desenvolvida como **case técnico de processo seletivo**. Inclui correção de categorias incorretas, análise temporal e regional, matriz de correlação com heatmap e dashboard interativo no Power BI.

📁 [`Case Integral Trust/`](./Case%20Integral%20Trust)

---

### 🎓 Case Fundação Lemann
`Python` `Pandas`

Análise exploratória de dados educacionais desenvolvida como case técnico, com tratamento de dados e extração de métricas de desempenho.

📁 [`Case Fundação Lemann/`](./Case%20Fundação%20Lemann)

---

## 🗄️ Banco de Dados

---

### 🏪 Loja de Vendas — PostgreSQL Completo
`Python` `PostgreSQL` `SQLAlchemy` `psycopg2` `Faker` `Flask` `HTML/CSS/JS`

O projeto mais completo do repositório. Cria e popula automaticamente um banco de dados PostgreSQL inteiro para uma loja fictícia de eletrônicos — do zero, com dados realistas gerados via Faker.

**O que está implementado:**

| Camada | Detalhes |
|--------|----------|
| Modelagem | DER completo — conceitual, lógico e físico |
| Banco | 10+ tabelas com ENUMs, constraints e relacionamentos |
| Dados | Clientes, produtos, pedidos, itens, vendas, pagamentos, descontos e fidelidade |
| Lógicas | Sazonalidade, parcelamento, impostos, frete, pontos de fidelidade |
| Backend | API REST em Flask |
| Frontend | Dashboard web em HTML/CSS/JS com listagem, filtros e relatórios |

```
criacao_banco.py → funcoes_populacao.py → Criador_e_Populador.py
                                                    ↓
                                          backend/app.py (Flask API)
                                                    ↓
                                          frontend/ (Dashboard web)
```

📁 [`Banco de Dados/`](./Banco%20de%20Dados)

---

## 🤖 Automação & IA

---

### 🖱️ Automação de Cadastros
`Python` `PyAutoGUI`

Script que lê uma planilha CSV e preenche automaticamente cadastros em massa em sistemas web, eliminando inserções manuais repetitivas.

📁 [`Automacao de Cadastros/`](./Automacao%20de%20Cadastros)

---

### 📦 Automação — Cadastro de Insumos
`Python` `Selenium`

Automação que percorre notas de entrada com conciliação pendente no sistema **Saipos**, identifica os nomes dos insumos e associa automaticamente aos ingredientes já cadastrados. Criação automática de novos cadastros em desenvolvimento.

📁 [`Automação – Cadastro de Insumos/`](./Automação%20–%20Cadastro%20de%20Insumos)

---

### 🤖 Agente Escritor de Currículo
`Python` `LLM` `python-docx` `Agentes de IA`

Agente de IA que gera currículos personalizados em `.docx` para vagas específicas, otimizados para **ATS (Applicant Tracking Systems)** e limitados a exatamente **1 página**.

A partir de três insumos — currículo base, descrição da vaga e acervo de projetos — o agente analisa a vaga, adapta o conteúdo, seleciona os projetos mais aderentes e preenche o documento com layout preservado.

> O agente **nunca inventa** habilidades ou experiências — todo conteúdo é baseado estritamente nos insumos fornecidos.

```
currículo base + descrição da vaga + acervo de projetos
                        ↓
                   Agente (LLM)
                        ↓
           análise → adaptação → seleção de projetos
                        ↓
                  currículo.docx (1 página)
```

📁 [`Agente Escritor de Curriculo/`](./Agente%20Escritor%20de%20Curriculo)

---

## 🧠 Algoritmos & Simulações

---

### 🔵 PI pelo Método de Monte Carlo
`Python` `Matplotlib` `NumPy`

Aproximação do valor de π através de simulação probabilística. Pontos aleatórios são gerados dentro de um quadrado e a proporção dos que caem dentro do círculo inscrito converge para π/4. Inclui visualização gráfica dos pontos e comparação de precisão por número de iterações.

📁 [`PI Monte Carlo/`](./PI%20Monte%20Carlo)

---

### 🔎 Detector de Plágio
`Python`

Analisa documentos em busca de similaridades textuais para identificar possíveis ocorrências de plágio, usando técnicas de processamento e comparação de texto.

📁 [`Detector de Plagio/`](./Detector%20de%20Plagio)

---

### ⚙️ Gerador de Arrays
`C`

Ferramenta em C para geração de arrays aleatórios, crescentes ou decrescentes com tamanho configurável — útil para testar e comparar algoritmos de ordenação e busca.

📁 [`Gerador de arrays/`](./Gerador%20de%20arrays)

---

## 🎮 Jogos & Interativos

---

### ♟️ Jogo NIM
`Python`

Implementação do clássico jogo de estratégia matemática. Dois jogadores removem objetos de pilhas alternadamente; quem pegar o último perde. Inclui lógica de IA simples baseada na teoria de Nim.

📁 [`Jogo NIM/`](./Jogo%20NIM)

---

### 🪢 Jogo da Forca
`Python`

Versão do clássico jogo da forca com controle de tentativas, feedback visual e validação de letras repetidas.

📁 [`Jogo da Forca/`](./Jogo%20da%20Forca)

---

### ❓ Questionário
`C`

Aplicação interativa de perguntas e respostas em C, com validação de respostas e feedback imediato ao usuário.

📁 [`Questionario/`](./Questionario)

---

## 🛠️ Stack dos Projetos

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![PostgreSQL](https://img.shields.io/badge/PostgreSQL-316192?style=for-the-badge&logo=postgresql&logoColor=white)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)
![Scikit-learn](https://img.shields.io/badge/Scikit--learn-%23F7931E.svg?style=for-the-badge&logo=scikit-learn&logoColor=white)
![Selenium](https://img.shields.io/badge/Selenium-43B02A?style=for-the-badge&logo=selenium&logoColor=white)
![Power BI](https://img.shields.io/badge/Power%20BI-F2C811?style=for-the-badge&logo=powerbi&logoColor=black)
![Flask](https://img.shields.io/badge/Flask-000000?style=for-the-badge&logo=flask&logoColor=white)
![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

</div>

---

## ⚙️ Como executar

Cada projeto tem seu próprio `README.md` com instruções detalhadas. De forma geral:

```bash
# 1. Acesse a pasta do projeto
cd Projetos/<nome-do-projeto>

# 2. Instale as dependências (projetos Python)
pip install -r requirements.txt

# 3. Execute o script principal
python <nome_do_script>.py
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=100&section=footer" width="100%"/>

</div>
