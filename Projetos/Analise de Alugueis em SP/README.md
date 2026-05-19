# 🏙️ Análise de Aluguéis em São Paulo

Este projeto tem como objetivo coletar e analisar dados de imóveis para aluguel na cidade de São Paulo, utilizando dados obtidos diretamente da plataforma **QuintoAndar**.

Ao invés de utilizar datasets prontos, foi desenvolvido um **web scraper próprio**, permitindo controle total sobre a coleta, estrutura e qualidade dos dados.

---

## 🎯 Objetivo

Construir um pipeline completo de dados, desde a **extração** até a futura **análise exploratória**, permitindo investigar padrões como:

- Preço médio por região
- Relação entre preço e metragem
- Impacto de características (quartos, banheiros, vagas, etc.)
- Distribuição de imóveis pela cidade

---

## 📊 Dados Coletados

- Mais de **4.000 imóveis** coletados
- Cobertura: **São Paulo (capital)**
- Tipos: studios até apartamentos de múltiplos quartos

### Exemplos de variáveis:
- Valor do aluguel
- Valor total (com taxas)
- Área (m²)
- Número de quartos e banheiros
- Localização (bairro)
- Outras características do imóvel

---

## 🏗️ Estrutura do Projeto

```
📦 Analise de Alugueis em SP/
│
├── data/
│   ├── logs/              # Logs de execução do scraper
│   ├── raw/               # Dados brutos coletados (CSV)
│
├── src/
│   ├── scraping/
│   │   ├── extract_data.py
│   │   ├── extract_data_v2.py
│   │   ├── extract_data_v3.py
│   │   └── extract_data_final.py   # Versão consolidada do scraper
│   │
│   ├── utils/
│   │   ├── lib_scraper.py         # Lógica principal de scraping
│   │   └── logger_config.py       # Configuração de logs
```

---

## ⚙️ Como Funciona o Scraper

O scraper foi desenvolvido para consumir dados diretamente da API, com foco em robustez e controle do processo.

### Principais características:

- **Coleta segmentada** para ampliar cobertura de dados
- **Paginação automática** com controle de limite
- **Deduplicação de imóveis**
- **Retry automático em falhas**
- **Delay aleatório entre requisições** (evita bloqueios)
- **Logging detalhado de execução**

A função principal (`scrape`) é responsável por:

- Orquestrar a coleta por segmentos  
- Consolidar os dados em um único dataset  
- Aplicar pós-processamento  
- Exportar os dados finais em CSV  

---

## 🚀 Como Executar

### 1. Clone o repositório
```bash
git clone <seu-repo>
cd Analise-de-Alugueis-SP
```

### 2. Instale as dependências
```bash
pip install -r requirements.txt
```

*(Caso ainda não exista, você pode adicionar depois)*

### 3. Execute o scraper
```bash
python src/scraping/extract_data_final.py
```

---

## 📁 Outputs

- **Dados brutos** → `data/raw/`
- **Logs de execução** → `data/logs/`

---

## 📌 Próximos Passos

- Limpeza e tratamento dos dados
- Feature engineering (ex: preço por m²)
- Análise exploratória (EDA)
- Visualizações e dashboards
- Possível modelagem preditiva

---

## 🛠️ Tecnologias Utilizadas

- Python 3.x
- Requests
- Pandas
- Logging
- API scraping

---

## ⚠️ Observações

- Os dados foram coletados para fins educacionais e analíticos.
- O projeto não tem vínculo com o QuintoAndar.

---

## 💬 Contato

Caso queira trocar ideias sobre o projeto ou análises de dados:

- 📧 Email: pablocaballero07@gmail.com  
- 💼 LinkedIn: https://www.linkedin.com/in/pabl0maciel  

---

## 📜 Licença

Este projeto está sob a licença MIT.
