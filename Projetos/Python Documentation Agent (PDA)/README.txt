Como usar o Documentador de Códigos Python
Por: Pablo Maciel

---

1) O que o documentador faz

Gera documentação técnica padronizada (Markdown) de scripts Python a partir de:
  - Código-fonte dos scripts (.py)
  - Informações técnicas do projeto
  - Ambiente e dependências do script

A documentação gerada inclui:
  - Descrição geral e objetivo do script
  - Estrutura completa do código (seções, funções, lógica)
  - Modelo de dados (entradas, saídas, variáveis principais)
  - Dependências e ambiente de execução
  - Instruções de uso e execução

---

2) Entradas obrigatórias

Você deve fornecer:

a) Código-fonte
   - Arquivo(s) .py do projeto
   - Pode ser um script único ou múltiplos arquivos

b) Ambiente e Dependências
   - Versão do Python utilizada
   - Bibliotecas externas e suas versões
   - Ver seção 5 para instruções de extração

c) Informações técnicas
   - Caminho na rede (UNC)
   - Desenvolvido por
   - Equipe destinada
   - Frequência de execução (se aplicável)

---

3) Entradas opcionais

- Prints de outputs gerados pelo script
- Contexto adicional de negócio
- Observações sobre limitações conhecidas

---

4) Como enviar o comando inicial

Envie tudo em uma única mensagem usando o template abaixo:

---
Nome do Projeto: <nome do projeto>
Descrição de Funcionamento: <breve descrição do projeto>
Script Principal: <nome do script principal>
Desenvolvido por: <Nome – Equipe>
Frequência: <Diária / Semanal / Sob demanda>
Caminho: <\servidor\pasta\arquivo ou url do repositório>
Ambiente e Dependências: <colar saída do terminal>

Gere a documentação completa do(s) script(s).

(Anexar: arquivo(s) .py)
---

---

5) Como extrair o Ambiente e Dependências

Pré-requisito:
  - Python instalado no ambiente de execução do script
  - IDE com suporte a Python ou terminal

---

5.1) Script automatizado

  Script disponível em:
  "\\integraltrust.net\Dados\Dados\Pesquisa e Desenvolvimento\Documentador de Códigos Python\gerador_requirements.py"

  Passo a passo:

  1. Abrir o arquivo gerador_requirements.py
  2. Localizar a variável "caminho" no final do script:

       caminho = r"\\servidor\pasta\Scripts"

  3. Substituir pelo caminho da pasta onde estão os scripts a documentar (manter todos na mesma pasta)
  4. Executar o script
  5. Copiar o bloco impresso no console, que terá o seguinte formato:

        ============================================================
	DEPENDÊNCIAS IDENTIFICADAS
	============================================================
	Caminho: \\londres\Dados2\Risco\Comercial\Clientes\Guanabara\OUTROS\Calibragem_PD\(0)Acomp\Teste\Scripts

	Ambiente e Dependências:
	  - Python : 3.13.5
	  - matplotlib  == 3.10.0
	  - numpy       == 2.1.3
	  - pandas      == 2.2.3
	  - python-pptx == 1.0.2
	  - tqdm        == 4.67.1

	============================================================

  6. Colar o bloco copiado no campo "Ambiente e Dependências" da mensagem inicial

  Observações:
    - Bibliotecas nativas do Python (os, sys, datetime, etc.) são ignoradas automaticamente
    - Um arquivo requirements.txt também será gerado na pasta dos scripts
    - O script resolve automaticamente divergências entre nome de import e nome do pacote
      (ex: import pptx → pip install python-pptx)

---

6) Saída gerada

  - Arquivo Markdown (.md)
  - Estrutura padronizada e completa
  - Pronto para uso em SharePoint, Git ou Notion

---

7) Fluxo recomendado

  1. Abrir o gerador_requirements.py no Spyder e apontar para a pasta do projeto
  2. Executar com F5 e copiar o bloco de dependências gerado
  3. Reunir os arquivos .py a serem documentados
  4. Preencher as informações técnicas (caminho, equipe, responsável, frequência)
  5. Enviar tudo em uma única mensagem para o Documentador
  6. (Opcional) Complementar com prints dos outputs ou contexto adicional de negócio