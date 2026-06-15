Como usar o Documentador de Dashboards
Por: Pablo Maciel

---

1) O que o documentador faz

Gera documentação técnica padronizada (Markdown) de dashboards Power BI a partir de:
  - YAML do modelo semântico
  - PDF exportado do Power BI e/ou prints das páginas
  - Informações técnicas do dashboard

A documentação gerada inclui:
  - Estrutura completa do dashboard (páginas, visuais, filtros)
  - Modelo de dados (tabelas, colunas, relacionamentos)
  - Todas as medidas DAX
  - Descrição funcional dos visuais

---

2) Entradas obrigatórias

Você deve fornecer:

a) YAML do modelo semântico
   - Extraído via script no Tabular Editor 2
   - Deve conter: tables, columns, measures, relationships
   - Ver seção 5 para instruções de extração

b) Visual do dashboard
   - PDF exportado do Power BI (recomendado)
   e/ou
   - Prints das páginas (alta resolução)

c) Informações técnicas
   - Caminho na rede (UNC ou URL)
   - Frequência de atualização
   - Desenvolvido por
   - Equipe destinada
   - Link do relatório (Power BI Service)

---

3) Entradas opcionais

- Prints adicionais para complementar o PDF
- Contexto adicional por página
- Observações de negócio

---

4) Como enviar o comando inicial

Envie tudo em uma única mensagem usando o template abaixo:

---
Caminho: <\servidor\pastarquivo.pbix>
Equipe: <Equipe Destinada>
Link: <https://app.powerbi.com/...>
Frequência: <Diária/Semanal/Mensal>
Desenvolvido por: <Nome – Equipe>

Páginas: <opcional — se quiser nomear manualmente>

Gere a documentação completa do dashboard.

(Anexar: YAML + PDF e/ou prints)
---

---

5) Como extrair o YAML (Tabular Editor 2)

Pré-requisito:
- Tabular Editor 2 instalado
- Script: extrator_infos_dashboard_V4 disponível na pasta "Script de Extração"

Passo a passo:

1. Abrir o Power BI Desktop com o arquivo .pbix
2. Ir em: Ferramentas Externas → Tabular Editor
3. No Tabular Editor, acessar o menu: C# Script (em cima do espaço de escrever códigos)
4. Copiar o conteúdo do arquivo extrator_infos_dashboard_V4.txt e colar no painel de script
5. Alterar o caminho do diretório onde deseja salvar e nome do arquivo .yaml a ser gerado
6. Clicar em "Run script" (seta verde)
7. Verificar se o arquivo foi gerado no diretório passado no script

Antes de enviar, verificar se o YAML contém:
  - modelName
  - tables
  - columns
  - measures
  - relationships

---

6) Saída gerada

- Arquivo Markdown (.md)
- Estrutura padronizada e completa
- Pronto para uso em SharePoint, Git ou Notion

---

7) Fluxo recomendado

1. Extrair YAML via Tabular Editor 2
2. Exportar o dashboard em PDF pelo Power BI
3. Preencher as informações técnicas
4. Enviar tudo em uma única mensagem
5. (Opcional) Complementar com prints se necessário

---