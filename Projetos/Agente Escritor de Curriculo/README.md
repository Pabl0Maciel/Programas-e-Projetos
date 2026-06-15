<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Agente%20Escritor%20de%20Currículo&fontSize=36&fontColor=4F8EF7&fontAlignY=38&desc=IA%20que%20adapta%20e%20gera%20currículos%20personalizados%20em%20.docx&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![LLM](https://img.shields.io/badge/LLM-Agent-4F8EF7?style=for-the-badge&logo=openai&logoColor=white)
![Word](https://img.shields.io/badge/python--docx-.docx-2B579A?style=for-the-badge&logo=microsoft-word&logoColor=white)
![ATS](https://img.shields.io/badge/ATS-Optimized-00D4FF?style=for-the-badge)

</div>

---

## 🎯 O que é

Agente de IA que recebe três insumos e devolve um currículo `.docx` completo, personalizado para a vaga e otimizado para **ATS (Applicant Tracking Systems)** — em exatamente **1 página**, sem espaços sobrando e sem conteúdo cortado.

> ⚠️ **Regra inflexível:** o agente **nunca inventa** habilidades, ferramentas ou experiências. Todo conteúdo gerado é baseado estritamente nos insumos fornecidos.

---

## ⚙️ Como funciona

```
┌─────────────────────────────────────────────────────────┐
│                      INSUMOS                            │
│                                                         │
│  curriculo_base.docx  +  vaga.txt  +  acervo_projetos  │
└────────────────────────┬────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────┐
│                   AGENTE (LLM)                          │
│                                                         │
│  1. Valida os insumos recebidos                         │
│  2. Analisa a vaga → extrai palavras-chave e requisitos │
│  3. Adapta o conteúdo do currículo base à vaga          │
│  4. Seleciona até 2 projetos do acervo (por aderência)  │
│  5. Ajusta o volume de conteúdo para preencher 1 página │
│  6. Gera o .docx preservando layout e estilos originais │
└────────────────────────┬────────────────────────────────┘
                         │
                         ▼
┌─────────────────────────────────────────────────────────┐
│                      SAÍDA                              │
│                                                         │
│  curriculo_personalizado.docx  +  relatório de status   │
└─────────────────────────────────────────────────────────┘
```

---

## 📂 Estrutura do Projeto

```
📦 Agente Escritor de Curriculo/
│
└── Instrucoes/
    ├── instrucoes_v1.txt       # Versão inicial (depreciada)
    ├── instrucoes_v2.txt       # Segunda iteração (depreciada)
    ├── instrucoes_v3.txt       # ✅ Versão atual em produção
    └── acervo_projetos.txt     # Repositório de projetos disponíveis para seleção
```

> Os insumos `curriculo_base.docx` e `vaga.txt` são fornecidos pelo usuário em cada execução — não ficam versionados no repositório.

---

## 📥 Insumos necessários

| Arquivo | Tipo | Descrição |
|---------|------|-----------|
| `curriculo_base.docx` | Obrigatório | Currículo original do candidato — fonte primária de fatos |
| `vaga.txt` | Obrigatório | Descrição completa da vaga — direciona vocabulário e foco |
| `acervo_projetos.txt` | Obrigatório | Lista de projetos disponíveis para seleção pelo agente |

> Se qualquer insumo estiver ausente, o agente **aborta** e solicita reenvio antes de prosseguir.

---

## 🧠 Hierarquia de fontes

O agente segue uma hierarquia estrita ao construir o conteúdo:

```
1º  Currículo Base      →  Fonte primária: experiências, formação, contato
2º  Acervo de Projetos  →  Fonte validada: projetos e automações disponíveis
3º  Vaga                →  Direcionador: vocabulário, palavras-chave, prioridades
```

A vaga **nunca sobrescreve fatos** — ela apenas orienta quais informações reais destacar.

---

## 📄 Estrutura do currículo gerado

O agente segue obrigatoriamente a estrutura do currículo base, alterando apenas o conteúdo:

```
1. Nome completo
2. Contato — cidade | telefone | e-mail | LinkedIn | GitHub
3. Resumo profissional          ← adaptado ao perfil da vaga
4. Competências técnicas        ← priorizadas por relevância
5. Experiência profissional     ← máx. 4 experiências, máx. 3-4 bullets cada
6. Projetos relevantes          ← máx. 2 projetos do acervo
7. Formação acadêmica
8. Certificações e cursos
9. Idiomas
```

---

## 📐 Regra de 1 página

O agente garante que o currículo ocupe **visualmente a página inteira** — nem mais, nem menos.

| Situação | Ação do agente |
|----------|----------------|
| Sobra espaço | Expande bullets com mais contexto, adiciona projetos, detalha competências |
| Excesso de conteúdo | Remove redundâncias, reduz projetos menos relevantes, ajusta texto |

---

## 📤 Relatório de saída

Ao finalizar, o agente retorna um relatório estruturado em 4 blocos:

```
BLOCO 1 — STATUS
  [APROVADO / PARCIAL / REPROVADO]

BLOCO 2 — ADERÊNCIA
  ✅ Requisitos atendidos
  ⚠️  Requisitos parcialmente atendidos
  ❌ Lacunas identificadas

BLOCO 3 — AJUSTES DE ESPAÇO
  Como o conteúdo foi expandido ou reduzido para caber em 1 página

BLOCO 4 — DOWNLOAD
  Caminho do arquivo .docx gerado
```

---

## 🔄 Evolução do prompt

O agente foi refinado em 3 versões iterativas:

| Versão | Status | Descrição |
|--------|--------|-----------|
| `instrucoes_v1.txt` | ~~Depreciada~~ | Versão inicial — escopo básico |
| `instrucoes_v2.txt` | ~~Depreciada~~ | Refinamentos de regras de conteúdo |
| `instrucoes_v3.txt` | ✅ Produção | Versão completa com protocolo de geração em Python, regra de 1 página e hierarquia de fontes |

---

## 🛠️ Tecnologias

- **Python 3.x** — orquestração e geração do `.docx`
- **python-docx** — edição do documento preservando estilos originais
- **LLM** — análise da vaga e adaptação inteligente do conteúdo
- **Prompt Engineering** — instruções estruturadas com hierarquia, regras e protocolo de saída

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
