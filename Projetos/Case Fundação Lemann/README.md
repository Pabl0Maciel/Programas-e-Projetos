<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Case%20Fundação%20Lemann&fontSize=34&fontColor=4F8EF7&fontAlignY=38&desc=Análise%20do%20Censo%20Escolar%20Brasileiro%20·%203.8M%20de%20registros%20·%205%20dashboards&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Pandas](https://img.shields.io/badge/Pandas-%23150458.svg?style=for-the-badge&logo=pandas&logoColor=white)
![Power BI](https://img.shields.io/badge/Power%20BI-F2C811?style=for-the-badge&logo=powerbi&logoColor=black)
![Google Colab](https://img.shields.io/badge/Google%20Colab-F9AB00?style=for-the-badge&logo=googlecolab&logoColor=black)

</div>

---

## 🎯 Objetivo

Análise exploratória completa do **Censo Escolar Brasileiro** — dataset de **5,68 GB** com 3.842.919 registros — abordando infraestrutura, saneamento, matrículas, equipamentos, profissionais e perfil dos alunos. Os dados tratados alimentam **5 dashboards interativos no Power BI** com filtros por estado, rede escolar e ano.

---

## 🔗 Acesso ao projeto

| Recurso | Link |
|---------|------|
| 📓 Notebook no Google Colab | [Abrir no Colab](https://colab.research.google.com/drive/1v_v2wBqzigh20WzomVMo72Yv40CV8pjH?usp=sharing) |
| 📁 Datasets tratados + arquivo Power BI | [Google Drive](https://drive.google.com/drive/folders/1rg09AF8d3qO6nvd6ueIjoO7qN-_463t-?usp=drive_link) |

---

## 🗂️ Estrutura da Análise

```
Parte 1 — Acesso aos dados       (basedosdados + BigQuery)
Parte 2 — Definição dos temas    (7 eixos de análise)
Parte 3 — Limpeza e tratamento   (por dataframe)
Parte 4 — Visualizações          (5 dashboards Power BI)
Parte 5 — Uso de IA              (ChatGPT + Gemini)
Parte 6 — Propostas de melhoria  (reestruturação do dataset)
```

---

## 📊 Dataframes analisados

| Dataframe | Linhas | Colunas | Tema |
|-----------|--------|---------|------|
| `df_infra` | 3.842.919 | 59 | Infraestrutura das escolas |
| `df_saneamento` | 3.842.919 → **2.314.096** | 36 → 21 | Água, esgoto, energia e lixo |
| `df_matricula_X_turma` | 3.842.919 | 24 | Matrículas e turmas por modalidade |
| `df_salas` | 3.842.919 → **~3.2M** | 12 → 8 | Salas existentes vs. utilizadas |
| `df_equipamentos` | 3.842.919 → **1.938.313** | 30 → 12 | Computadores, internet, TV, impressora |
| `df_profissionais` | 3.842.919 → **2.700.009** | 42 → 10 | Funcionários e docentes por etapa |
| `df_alunos` | 3.842.919 → **3.725.430** | 20 | Matrículas por cor, raça, sexo e faixa etária |

---

## 🧹 Decisões de limpeza

Cada dataframe apresentou desafios distintos — abaixo as decisões tomadas e a justificativa:

<details>
<summary><strong>Infraestrutura</strong> — descartado</summary>

Colunas com até 80% de valores ausentes. Extraiu-se apenas a observação sobre a qualidade da coleta dos dados originais.

</details>

<details>
<summary><strong>Saneamento</strong> — dropna após seleção de colunas</summary>

Selecionadas 21 colunas com ausência abaixo de 50%. Demais linhas descartadas com `dropna()` — perda aceitável dado o volume restante (2.3M linhas).

</details>

<details>
<summary><strong>Matrículas × Turmas</strong> — fillna com média</summary>

6 colunas de turmas integrais com 95%+ de ausência descartadas. Demais valores ausentes preenchidos com a média — adequado por serem variáveis numéricas quantitativas.

</details>

<details>
<summary><strong>Salas</strong> — remoção de outliers lógicos</summary>

Outlier `9999` identificado e descartado. Eliminadas 605.271 linhas onde `salas_utilizadas > salas_existentes` — inconsistência lógica irrecuperável.

</details>

<details>
<summary><strong>Equipamentos</strong> — fillna + dropna misto</summary>

`quantidade_computador` preenchida com média. Colunas categóricas com alta ausência removidas com `dropna()`.

</details>

<details>
<summary><strong>Profissionais</strong> — múltiplos filtros encadeados</summary>

Removidos valores `0` e `9999` de funcionários. Eliminadas 782.350 linhas onde `total_docentes > total_funcionários`. Filtro mínimo de 10 funcionários por escola para garantir realismo analítico.

</details>

<details>
<summary><strong>Alunos</strong> — fillna + filtro mínimo</summary>

Ausentes preenchidos com média. Filtro de ≥ 15 matrículas por escola — manteve 3.725.430 linhas (97% do original).

</details>

---

## 📈 Dashboards e Insights

### 💧 Saneamento Básico
- **2,04M** de escolas com água filtrada; **65 mil** sem acesso
- **1,27M** sem esgoto pela rede pública — a maioria usando fossas
- Escolas municipais e estaduais concentram a falta de acesso aos serviços básicos

### 📚 Matrículas × Turmas
- Boom do ensino a distância em 2010 e novamente em 2014–2015
- Obrigatoriedade do ensino infantil (2013) refletida no aumento de matrículas
- Queda consistente de matrículas no ensino médio ao longo dos anos
- Rede municipal: média de **42 alunos por turma** no ensino médio

### 🏫 Salas
- **89%** das salas são utilizadas; **11%** ficam ociosas
- Queda abrupta de 2018 para 2019 — impacto direto da **pandemia de Covid-19**

### 💻 Equipamentos
- Acesso à internet e computadores cresceu consistentemente até 2017
- Queda em 2017 pode indicar cortes em políticas de educação
- Maioria das escolas **não possui retroprojetor**, equipamento essencial para aulas

### 👨‍🏫 Profissionais
- Média de **35 profissionais** por escola; 12 docentes e 23 em outras funções
- **60%** dos docentes atuam no ensino fundamental
- Ensino médio com poucos professores — possível negligência sistêmica

### 🎓 Alunos
- Matrículas pardas e brancas dominam; baixo número de alunos **pretos** — reforça desigualdade
- Faixas etárias do ensino fundamental concentram a maior parte das matrículas
- Queda geral de matrículas ao longo dos anos — sinal de abandono escolar

---

## 💡 Proposta de melhoria do dataset

O case propõe uma reestruturação do schema de equipamentos — de formato largo para formato longo — facilitando agregações e expansões futuras:

```python
# Formato atual (largo) — difícil de agregar
equipamento_impressora | equipamento_tv | quantidade_computador ...

# Formato proposto (longo) — escalável e padronizado
id_escola | equipamento      | quantidade
1         | impressora        | 1
1         | tv                | 2
1         | computador        | 10
```

---

## ⚙️ Como reproduzir

O projeto foi desenvolvido inteiramente no **Google Colab** consumindo dados via `basedosdados`. A forma mais simples de reproduzir é:

1. Acessar o [notebook no Colab](https://colab.research.google.com/drive/1v_v2wBqzigh20WzomVMo72Yv40CV8pjH?usp=sharing)
2. Conectar ao Google Drive para salvar os CSVs tratados
3. Baixar o arquivo `.pbix` do [Drive](https://drive.google.com/drive/folders/1rg09AF8d3qO6nvd6ueIjoO7qN-_463t-?usp=drive_link) e abrir no Power BI Desktop

```bash
# Instalação local (opcional)
pip install basedosdados==2.0.0b16 pandas
```

> ⚠️ O dataset completo tem **5,68 GB** — não é recomendado reiniciar o ambiente no Colab durante a execução, pois o download precisaria ser refeito.

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
