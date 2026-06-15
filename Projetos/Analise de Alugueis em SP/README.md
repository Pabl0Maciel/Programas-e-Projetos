<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Análise%20de%20Aluguéis%20em%20SP&fontSize=34&fontColor=4F8EF7&fontAlignY=38&desc=Web%20scraping%20do%20QuintoAndar%20·%20Pipeline%20completo%20de%20dados&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Requests](https://img.shields.io/badge/Requests-2CA5E0?style=for-the-badge&logo=python&logoColor=white)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)
![Status](https://img.shields.io/badge/Status-Coleta%20concluída-00D4FF?style=for-the-badge)

</div>

---

## 🎯 Objetivo

Construir um pipeline completo de dados do mercado imobiliário de SP — do zero. Em vez de usar datasets prontos, foi desenvolvido um **web scraper próprio** que consome a API do QuintoAndar, com controle total sobre coleta, estrutura e qualidade dos dados.

**+4.000 imóveis coletados** em São Paulo, com variáveis como valor do aluguel, área, quartos, banheiros, vagas, bairro e tipo de imóvel.

---

## 🏗️ Arquitetura

```
📦 Analise de Alugueis em SP/
│
├── src/
│   ├── scraping/
│   │   ├── extract_data.py          # v1 — versão inicial
│   │   ├── extract_data_v2.py       # v2 — iteração intermediária
│   │   ├── extract_data_v3.py       # v3 — iteração intermediária
│   │   └── extract_data_final.py    # ✅ versão consolidada (use esta)
│   │
│   └── utils/
│       ├── lib_scraper.py           # Toda a lógica de coleta (core do projeto)
│       └── logger_config.py         # Configuração do sistema de logs
│
└── data/
    ├── raw/                         # CSVs coletados (nomeados com timestamp)
    └── logs/                        # Logs de execução por coleta
```

---

## ⚙️ Como funciona

### Pipeline de coleta

```
SEGMENTS (14 segmentos por tipo + quartos)
          │
          ▼
   scrape()  ←  orquestra tudo
          │
          ├── scrape_segment()       ← coleta por segmento com paginação
          │       │
          │       ├── fetch_page()   ← requisição HTTP com retry automático
          │       │       │
          │       │       └── build_payload()  ← constrói filtros dinâmicos
          │       │
          │       └── flatten_listing()  ← normaliza cada imóvel
          │
          ├── deduplicação global por ID
          ├── cálculo de rentPerSqm (aluguel/m²)
          └── exportação para CSV (data/raw/)
```

### Segmentação

Para maximizar cobertura (a API limita resultados por busca), a coleta é dividida em **14 segmentos** combinando tipo de imóvel e número de quartos:

| Quartos | Apartamento | Casa | Condomínio | Studio |
|---------|-------------|------|------------|--------|
| 0 | — | — | — | ✅ |
| 1 | ✅ | ✅ | ✅ | ✅ |
| 2 | ✅ | ✅ | ✅ | — |
| 3 | ✅ | ✅ | ✅ | — |
| 4+ | ✅ | ✅ | ✅ | — |

---

## 🛡️ Robustez do scraper

| Recurso | Implementação |
|---------|---------------|
| **Retry automático** | Até 3 tentativas por request com backoff progressivo |
| **Rate limit (429)** | Detectado e aguardado automaticamente |
| **Delay aleatório** | Entre 1.2s e 3.0s entre requisições para evitar bloqueios |
| **Pausa entre segmentos** | 5–10s de espera entre cada segmento |
| **Deduplicação** | Por ID, em tempo real durante coleta e novamente no final |
| **Logging detalhado** | Progresso, contagens, alertas e erros salvos em arquivo `.txt` |
| **Alerta de saturação** | Aviso automático quando segmento acumula 900+ imóveis |

---

## 📊 Dados coletados

Cada imóvel retorna os seguintes campos:

| Campo | Descrição |
|-------|-----------|
| `id` | Identificador único |
| `type` | Tipo (APARTMENT, HOME, STUDIO, HOUSE_CONDO) |
| `address` / `neighbourhood` | Endereço e bairro |
| `rent` | Valor do aluguel |
| `totalCost` | Custo total (aluguel + taxas) |
| `area` | Área em m² |
| `bedrooms` / `bathrooms` | Quartos e banheiros |
| `parkingSpaces` | Vagas de garagem |
| `isFurnished` | Mobiliado ou não |
| `rentPerSqm` | **Calculado** — aluguel por m² |
| `segment` | Segmento de coleta (ex: `2q_apto`) |

---

## 🚀 Como executar

**1. Instale as dependências**

```bash
pip install requests pandas
```

**2. Execute o scraper**

```bash
# Execução padrão (todos os segmentos)
python src/scraping/extract_data_final.py

# Limitar páginas por segmento
python src/scraping/extract_data_final.py --pages 10

# Desativar segmentação (busca única)
python src/scraping/extract_data_final.py --no-segment
```

**3. Outputs gerados automaticamente**

```
data/raw/quintoandar_sp_<timestamp>.csv   ← dataset coletado
data/logs/logging_<timestamp>.txt         ← log completo da execução
```

---

## 📌 Próximos passos

- [ ] Limpeza e tratamento dos dados coletados
- [ ] Feature engineering — ex: faixa de preço, preço por m² por bairro
- [ ] Análise exploratória (EDA) — distribuições, outliers, correlações
- [ ] Visualizações geográficas por bairro
- [ ] Modelagem preditiva de preço de aluguel

---

> ⚠️ Dados coletados para fins educacionais e analíticos. Este projeto não tem vínculo com o QuintoAndar.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
