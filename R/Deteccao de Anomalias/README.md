<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=R&fontSize=48&fontColor=4F8EF7&fontAlignY=45&desc=Detecção%20de%20Anomalias%20com%20Machine%20Learning&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

Scripts em R desenvolvidos durante o curso **Power BI para Business Intelligence e Data Science** da Data Science Academy.

---

## 📂 Conteúdo

### 🚨 Detecção de Anomalias em Transações Financeiras

`R` `tidyverse` `solitude` `ggplot2`

Modelo de Machine Learning com **Isolation Forest** para identificar transações financeiras anômalas. O script treina o modelo com dados históricos, aplica em novos dados e classifica cada registro como `normal` ou `anomalia` com base no anomaly score.

**Fluxo do projeto:**

```
dados_historicos.csv
        ↓
  Isolation Forest (treino)
        ↓
  anomaly_score > 0.62 → anomalia
        ↓
novos_dados.csv → previsões → previsoes_novos_dados.csv
```

**Arquivos:**

| Arquivo | Descrição |
|---------|-----------|
| [`deteccao_anomalias.R`](./Deteccao%20de%20Anomalias/deteccao_anomalias.R) | Script principal — treino, previsão e visualizações |
| [`dados_historicos.csv`](./Deteccao%20de%20Anomalias/dados_historicos.csv) | Dataset de treino com transações históricas |
| [`novos_dados.csv`](./Deteccao%20de%20Anomalias/novos_dados.csv) | Novos dados para classificação |
| [`previsoes_novos_dados.csv`](./Deteccao%20de%20Anomalias/previsoes_novos_dados.csv) | Output com anomaly score e status por transação |

---

## ⚙️ Como executar

1. Abra o script no **RStudio**
2. Instale os pacotes necessários (o próprio script faz isso):

```r
install.packages(c("tidyverse", "dplyr", "solitude", "ggplot2", "readr"))
```

3. Ajuste o caminho dos CSVs se necessário e execute linha a linha

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
