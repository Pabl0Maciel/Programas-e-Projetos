<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Dashboard%20Documentation%20Agent&fontSize=30&fontColor=4F8EF7&fontAlignY=38&desc=Agente%20de%20IA%20para%20documentação%20técnica%20de%20dashboards%20Power%20BI&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![LLM](https://img.shields.io/badge/LLM-Agent-4F8EF7?style=for-the-badge&logo=openai&logoColor=white)
![Power BI](https://img.shields.io/badge/Power%20BI-F2C811?style=for-the-badge&logo=powerbi&logoColor=black)
![Markdown](https://img.shields.io/badge/Saída-Markdown-000000?style=for-the-badge&logo=markdown&logoColor=white)
![C#](https://img.shields.io/badge/Extrator-C%23-239120?style=for-the-badge&logo=csharp&logoColor=white)

</div>

---

## 🎯 O que é

Agente de IA que gera automaticamente **documentação técnica completa e padronizada** de dashboards Power BI em formato Markdown — pronto para uso em SharePoint, Git ou Notion.

A partir de três insumos (YAML do modelo semântico, PDF/prints do dashboard e metadados técnicos), o agente documenta exaustivamente páginas, visuais, filtros, tabelas, colunas, medidas DAX e relacionamentos — **sem inventar conteúdo** e com auditoria de cobertura obrigatória antes de cada entrega.

> Desenvolvido e adotado como **padrão de documentação interna** na Integral Trust.


## 📂 Estrutura

```
📦 Dashboard Documentation Agent (DDA)/
│
├── Instrucoes do Agente/
│   ├── instrucoes_V1.txt  … instrucoes_V2.2.txt   # versões depreciadas
│   ├── instrucoes_V3.txt  … instrucoes_V4.txt      # versões depreciadas
│   ├── instrucoes_V5.txt                            # versão base da V5
│   └── instrucoes_V5.1.txt                          # ✅ versão atual em produção
│
├── Script de Extracao/
│   ├── extrator_infos_dashboard.txt    … _V3.txt    # versões depreciadas
│   └── extrator_infos_dashboard_V4.txt              # ✅ script atual (C# / Tabular Editor 2)
│
├── Template/
│   └── template_documentacao.txt                    # template de saída em Markdown
│
├── manual_wiki.md           # manual de uso interno
├── exemplo_extracao.gif     # demonstração em vídeo
└── README.md
```

---

## ⚙️ Como funciona

```
┌──────────────────────────────────────────────────────────────────┐
│                          INSUMOS                                 │
│                                                                  │
│  YAML do modelo semântico  +  PDF/prints  +  Metadados técnicos  │
└───────────────────────────────┬──────────────────────────────────┘
                                │
                                ▼
┌──────────────────────────────────────────────────────────────────┐
│                    AGENTE (LLM) — V5.1                           │
│                                                                  │
│  1. Valida os insumos recebidos                                  │
│  2. Define o modo de cobertura (APROVADO / PARCIAL / REPROVADO)  │
│  3. Extrai páginas, visuais e filtros das referências visuais    │
│  4. Extrai tabelas, colunas, medidas e relacionamentos do YAML   │
│  5. Executa checklist de auditoria (16 verificações)             │
│  6. Gera o arquivo .md via Python (UTF-8 com BOM)                │
│  7. Retorna confirmação + link de download                       │
└───────────────────────────────┬──────────────────────────────────┘
                                │
                                ▼
┌──────────────────────────────────────────────────────────────────┐
│                           SAÍDA                                  │
│                                                                  │
│  documentacao.md — estrutura padronizada pronta para wiki        │
└──────────────────────────────────────────────────────────────────┘
```

---

## 📥 Insumos necessários

| Insumo | Tipo | Como obter |
|--------|------|------------|
| YAML do modelo semântico | Obrigatório | Script C# no Tabular Editor 2 (ver seção abaixo) |
| PDF do dashboard | Obrigatório* | Exportar pelo Power BI Desktop |
| Prints das páginas | Opcional* | Alta resolução, complementar ao PDF |
| Metadados técnicos | Obrigatório | Preencher manualmente (ver template abaixo) |

> *Se apenas um dos dois (PDF ou prints) estiver ausente, o agente documenta o que for possível e declara a limitação explicitamente.

**Template de metadados técnicos:**

```
Caminho: \\servidor\pasta\arquivo.pbix
Equipe: <Equipe Destinada>
Link: https://app.powerbi.com/...
Frequência: Diária / Semanal / Mensal
Desenvolvido por: Nome – Equipe
```

---

## 🛠️ Como extrair o YAML (Tabular Editor 2)

O script de extração (`extrator_infos_dashboard_V4.txt`) é escrito em **C#** e roda diretamente no Tabular Editor 2, extraindo o modelo semântico completo do `.pbix`.

**Passo a passo:**

1. Abrir o arquivo `.pbix` no **Power BI Desktop**
2. Ir em `Ferramentas Externas → Tabular Editor`
3. No Tabular Editor, acessar `C# Script`
4. Colar o conteúdo de `extrator_infos_dashboard_V4.txt`
5. Ajustar o caminho de saída e nome do arquivo `.yaml`
6. Clicar em **Run script** (seta verde)

**O YAML gerado contém:**

| Campo | Descrição |
|-------|-----------|
| `modelName` | Nome do modelo semântico |
| `tables` | Todas as tabelas (nome, tipo, source/query) |
| `columns` | Colunas de cada tabela com tipo de dado |
| `measures` | Medidas com expressão DAX completa |
| `relationships` | Relacionamentos com cardinalidade e direção |

---

## 📄 Estrutura da documentação gerada

```markdown
# 📊 [Nome do Dashboard]

## ⚠️ Status da Auditoria
  Status: APROVADO / PARCIAL / REPROVADO
  Cobertura visual: completa / parcial / ausente
  Cobertura semântica: completa / parcial / ausente

## 🏠 Apresentação Geral
## ⚙️ Informações Técnicas
## 🔖 Páginas do Dashboard
    └── Por página: objetivo, KPIs, visuais, filtros
## 🗂️ Modelo dos Dados
    └── Por tabela: descrição, fonte, query (expansível), colunas
## 🔀 Relacionamentos do Modelo
## 🧠 Medidas
    └── Por medida: descrição técnica + DAX (expansível)
```

---

## 🛡️ Regras do agente

O agente opera com um conjunto rígido de regras para garantir qualidade e confiabilidade:

| Regra | Descrição |
|-------|-----------|
| **Hierarquia de fontes** | PDF → verdade visual · YAML → verdade semântica · Metadados → verdade técnica |
| **Anti-alucinação** | Nunca inferir elementos ausentes — usar `"não identificado"` quando necessário |
| **Anti-placeholder** | Proibido entregar `{0}`, `null`, `None` ou campos vazios sem justificativa |
| **Exaustividade** | Documentar 100% das tabelas, colunas, medidas e relacionamentos do YAML |
| **Encoding** | Saída sempre em UTF-8 com BOM — preservação integral de acentuação |
| **Auditoria obrigatória** | Checklist de 16 verificações antes de gerar o arquivo final |

---

## 🔄 Evolução do prompt

O agente foi refinado ao longo de **13 versões** iterativas:

| Versão | Status | Principais evoluções |
|--------|--------|----------------------|
| V1 → V2.2 | ~~Depreciadas~~ | Estrutura inicial, primeiros refinamentos de extração visual |
| V3 → V4 | ~~Depreciadas~~ | Regras de hierarquia de fontes e anti-alucinação |
| V5 | ~~Depreciada~~ | Sistema de auditoria, modos APROVADO/PARCIAL/REPROVADO |
| **V5.1** | ✅ **Produção** | Regras de encoding UTF-8, checklist de 16 pontos, protocolo de geração via Python, fallbacks obrigatórios |

---

## 📊 Modos de cobertura

| Status | Quando ocorre |
|--------|---------------|
| ✅ **APROVADO** | Todos os insumos presentes e cobertura integral verificada |
| ⚠️ **PARCIAL** | Insumos presentes mas incompletos — documenta o que for confiável e declara limitações |
| ❌ **REPROVADO** | Sem base mínima confiável — qualquer documentação exigiria invenção de conteúdo |

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
