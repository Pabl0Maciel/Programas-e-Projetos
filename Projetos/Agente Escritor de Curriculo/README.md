# 🤖 Agente Escritor de Currículo

Agente de IA que gera automaticamente um currículo personalizado em formato `.docx`
para uma vaga específica, otimizado para **ATS (Applicant Tracking Systems)** e
limitado a **exatamente 1 página** — sem espaços sobrando e sem conteúdo cortado.

---

## 🎯 O que ele faz

A partir de três insumos — um currículo base, a descrição da vaga e um acervo de
projetos — o agente:

1. **Analisa a vaga** e extrai palavras-chave, requisitos técnicos e perfil esperado.
2. **Adapta o conteúdo** do currículo base para o vocabulário e prioridades da vaga.
3. **Seleciona projetos relevantes** do acervo (máximo 2) com base na aderência real.
4. **Preenche a página completa**, expandindo ou condensando conteúdo conforme necessário.
5. **Gera o arquivo `.docx` final** via Python, preservando o layout e a identidade visual do currículo base.
6. **Retorna um relatório** de status, aderência e ajustes realizados.

> ⚠️ O agente **nunca inventa** habilidades, ferramentas ou experiências.
> Todo conteúdo gerado é baseado estritamente no currículo base e no acervo de projetos.

---

## 📂 Estrutura do Projeto

```
📦 Agente Escritor de Curriculo/
│
├── Instrucoes/
│   ├── instrucoes_v1.txt       # Primeira versão do prompt de instrução
│   ├── instrucoes_v2.txt       # Segunda versão com refinamentos
│   ├── instrucoes_v3.txt       # Versão atual (em produção)
│   └── acervo_projetos.txt     # Repositório de projetos disponíveis para o currículo
```

---

## ⚙️ Como Funciona

### Insumos obrigatórios

| Arquivo | Descrição |
|---|---|
| `curriculo_base.docx` | Currículo original do candidato |
| `vaga.txt` | Descrição completa da vaga |
| `acervo_projetos.txt` | Lista de projetos disponíveis para seleção |

> Se qualquer insumo estiver ausente, o agente aborta e solicita reenvio.

---

### Hierarquia de Fontes

```
1º  Currículo Base     → Fonte primária de fatos (experiências, formação, contato)
2º  Acervo de Projetos → Fonte validada de projetos e automações
3º  Vaga               → Direcionador de vocabulário e palavras-chave
```

---

### Estrutura do Currículo Gerado

O agente segue obrigatoriamente esta ordem:

1. Nome completo
2. Linha de contato — cidade | telefone | e-mail | LinkedIn | GitHub
3. Resumo profissional
4. Competências técnicas
5. Experiência profissional
6. Projetos relevantes
7. Formação acadêmica
8. Certificações e cursos
9. Idiomas

---

### Regras de Conteúdo

- Máximo **4 experiências** profissionais
- Máximo **3 bullets** por experiência (4 para a principal)
- Máximo **2 projetos** do acervo
- Currículo deve ocupar **visualmente 1 página completa**

**Se sobrar espaço**, o agente expande bullets, adiciona projetos ou detalha competências.  
**Se houver excesso**, o agente remove redundâncias e projetos menos relevantes.

---

## 🛠️ Tecnologias Utilizadas

- **Python 3.x**
- **`python-docx`** — geração e edição do arquivo `.docx`
- **LLM** — análise da vaga e adaptação inteligente do conteúdo
- **ATS Optimization** — uso estratégico de palavras-chave da vaga

---

## 📤 Saída do Agente

Após a execução, o agente retorna:

```
BLOCO 1 - STATUS
  [APROVADO / PARCIAL / REPROVADO]

BLOCO 2 - ADERÊNCIA
  - Requisitos atendidos
  - Requisitos parciais
  - Lacunas identificadas

BLOCO 3 - AJUSTES DE ESPAÇO
  - Como o conteúdo foi expandido ou reduzido para caber em 1 página

BLOCO 4 - DOWNLOAD
  - Caminho do arquivo .docx gerado
```

---

## 🔄 Versionamento das Instruções

O prompt do agente passou por 3 versões de refinamento:

| Versão | Status |
|---|---|
| `instrucoes_v1.txt` | Depreciada |
| `instrucoes_v2.txt` | Depreciada |
| `instrucoes_v3.txt` | ✅ Em produção |

---

## 💬 Contato

Se você tiver alguma dúvida ou sugestão, fique à vontade para entrar em contato!

<p align="left">
  <a href="mailto:pablocaballero07@gmail.com" title="Gmail">
    <img src="https://img.shields.io/badge/-Gmail-FF0000?style=flat-square&labelColor=FF0000&logo=gmail&logoColor=white" alt="Gmail"/>
  </a>
  <a href="https://www.linkedin.com/in/pabl0maciel" title="LinkedIn">
    <img src="https://img.shields.io/badge/-Linkedin-0e76a8?style=flat-square&logo=Linkedin&logoColor=white" alt="LinkedIn"/>
  </a>
  <a href="https://wa.me/11963934212" title="WhatsApp">
    <img src="https://img.shields.io/badge/-WhatsApp-25d366?style=flat-square&labelColor=25d366&logo=whatsapp&logoColor=white" alt="WhatsApp"/>
  </a>
  <a href="https://www.instagram.com/pabl0maciel" title="Instagram">
    <img src="https://img.shields.io/badge/-Instagram-DF0174?style=flat-square&labelColor=DF0174&logo=instagram&logoColor=white" alt="Instagram"/>
  </a>
</p>

---

## 🤝 Contribuições

Sugestões e melhorias são bem-vindas! Sinta-se à vontade para abrir uma issue ou enviar um pull request.

---

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
