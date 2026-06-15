# :snake: Como usar o Python Documentation Agent (PDA)
**Por: Pablo Maciel**
**Link para o PDA:** [:link:Documentador de Códigos Python](https://tess.im/pt-BR/dashboard/user/ai/chat/ai-chat/documentador-de-codigos-dzPkjo)


---

## :computer: 1) O que o agente faz

O Documentador de Códigos Python gera documentação técnica padronizada em Markdown (.md) a partir de scripts Python e informações do ambiente de execução.

Ele recebe:
- :page_facing_up: Código-fonte dos scripts (.py)
- :gear: Informações técnicas e contextuais do projeto
- :package: Ambiente e dependências do script

E entrega uma documentação rigorosamente estruturada em duas partes:
- **Parte 1 (Visão Geral):** Objetivo, valor de negócio, fluxo entre os arquivos, entradas/saídas globais e limitações do projeto.
- **Parte 2 (Documentação por Script):** Detalhamento de cada arquivo (principal e auxiliares), com trechos de código relevantes, classificações de lógica, pontos de atenção e oportunidades de melhoria.

---

## :dart: 2) Quando usar este agente

Use este agente quando você precisar:
- Documentar projetos em Python de forma padronizada e completa.
- Registrar a lógica, as regras de negócio e a estrutura de códigos existentes.
- Criar manuais técnicos rigorosos para facilitar o handover de pipelines de dados ou automações.
- Identificar premissas "hardcoded" e pontos críticos de scripts não documentados.

---

## :inbox_tray: 3) Entradas obrigatórias

Você deve fornecer as informações abaixo com rigor. O agente possui um **modo de bloqueio** e vai abortar a execução se qualquer um destes campos faltar, estiver vago (como "-", "N/A") ou se o Script Principal informado não estiver entre os arquivos enviados:

**a) Código-fonte**
- Arquivo(s) `.py` do projeto.

**b) Informações do Bloco Inicial**
- Nome do Projeto:
- Descrição de Funcionamento:
- Script Principal: (Deve ser o nome exato de um dos arquivos anexados.)
- Desenvolvido por:
- Caminho: (Em rede (UNC) ou repositório.)
- Ambiente e Dependências: (Ver seção 6 para extração automatizada.)

---

## :heavy_plus_sign: 4) Entradas opcionais

Você pode complementar enviando na mensagem:
- :page_with_curl: Prints de outputs gerados pelo script.
- :brain: Regras de negócio adicionais que justifiquem o comportamento do código.

---

## :rocket: 5) Como acionar o agente

Envie tudo em uma única mensagem usando exatamente o template abaixo:

```
Nome do Projeto: <nome do projeto>
Descrição de Funcionamento: <breve descrição do projeto>
Script Principal: <nome exato do arquivo principal.py>
Caminho: <\\servidor\pasta\arquivo ou url do repositório>
Desenvolvido por: <Nome – Equipe>
Ambiente e Dependências: <colar saída do terminal>

Gere a documentação completa do(s) script(s).

(Anexar: arquivo(s) .py)
```

---

## :gear: 6) Como extrair o Ambiente e Dependências

**Pré-requisito:** Python instalado no ambiente de execução.

### :computer: 6.1) Script automatizado

Script disponível em:
```
\\integraltrust.net\Dados\Dados\Pesquisa e Desenvolvimento\Documentador de Códigos Python\gerador_requirements.py
```
Caso não tenha acesso ao caminho do script, crie um arquivo .py e copie o conteúdo abaixo:

<details>
<summary>Ver conteúdo</summary>

```Python
  
  # -*- coding: utf-8 -*-
"""
Created on Tue Mar 31 09:24:19 2026

@author: pablo.maciel
"""

"""
Este script se trata de uma automação para a geração do bloco de dependências 
(requirements) exigido pelo agente de Inteligência Artificial Documentador 
da empresa.

O objetivo é substituir processos manuais que geravam instabilidade no Spyder 
e facilitar o uso por parte dos colaboradores, garantindo a captura precisa 
dos pacotes e suas versões corretas.
"""

import os
import ast
from importlib import metadata
import sys


#######################################################################################################################
##                                               CONFIGURAÇÕES GERAIS                                                ##
#######################################################################################################################
"""
Define os mapeamentos necessários para garantir que as importações lidas nos arquivos 
coincidam perfeitamente com os nomes registrados no gerenciador de pacotes do Python (pip).
"""

# Dicionário para tratar as divergências entre:
# - O código digitado no script no momento do importe (ex: import pptx)
# - O nome original da biblioteca instalada no ambiente via PIP (ex: pip install python-pptx)
IMPORT_TO_PACKAGE = {
    "pptx": "python-pptx",
    "cv2": "opencv-python",
    "PIL": "Pillow",
    "sklearn": "scikit-learn",
    "bs4": "beautifulsoup4",
    "yaml": "PyYAML",
    "dotenv": "python-dotenv",
    "dateutil": "python-dateutil",
    "gi": "PyGObject",
    "wx": "wxPython",
    "usb": "pyusb",
    "serial": "pyserial",
    "Crypto": "pycryptodome",
    "OpenSSL": "pyOpenSSL",
    "jwt": "PyJWT",
    "magic": "python-magic",
    "attr": "attrs",
    "google": "google-cloud",
    "azure": "azure-core",
    "boto3": "boto3",
}

#######################################################################################################################
##                                               LEITURA E CRUZAMENTO DOS DADOS                                      ##
#######################################################################################################################

def get_installed_versions(folder_path, save_requirements=True):
    """
    Função principal que varre o diretório, identifica bibliotecas e imprime as dependências reais.
    """
    
    # Puxa imediatamente todas as bibliotecas ativas no ambiente Python atual (ex: Spyder)
    installed_packages = {
        dist.metadata['Name'].lower(): dist.version
        for dist in metadata.distributions()
        if dist.metadata and dist.metadata.get('Name')
    }

    imported_modules = set()

    # Percorre todas as pastas, subpastas e arquivos no diretório alvo
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith('.py'):
                file_path = os.path.join(root, file)
                try:
                    # Abre o arquivo e monta uma "Árvore Sintática Abstrata" (AST)
                    # Isso permite ler o código estruturalmente sem precisar executá-lo
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        tree = ast.parse(f.read())

                        # Procura os blocos "import" e "from ... import"
                        for node in ast.walk(tree):
                            if isinstance(node, ast.Import):
                                for alias in node.names:
                                    imported_modules.add(alias.name.split('.')[0])
                            elif isinstance(node, ast.ImportFrom):
                                if node.module:
                                    imported_modules.add(node.module.split('.')[0])
                except Exception:
                    pass
                
    # Dicionário que armazenará apenas bibliotecas que foram importadas E que não são nativas do Python
    found_packages = {}

    # Cruza os módulos importados com o mapeamento e a lista de pacotes do ambiente
    for module in sorted(imported_modules):
        package_name = IMPORT_TO_PACKAGE.get(module, module).lower()
        if package_name in installed_packages:
            found_packages[package_name] = installed_packages[package_name]

#######################################################################################################################
##                                               IMPRESSÃO E GERAÇÃO DE SAÍDA                                        ##
#######################################################################################################################

    python_version = sys.version.split(" ")[0]

    # Imprime no terminal em um formato limpo, tabular e pronto para ser copiado pelo analista
    print("\n" + "=" * 60)
    print("DEPENDÊNCIAS IDENTIFICADAS")
    print("=" * 60)
    print(f"Caminho: {folder_path}\n")
    
    print("Ambiente e Dependências:")
    print(f"  - Python : {python_version}")
    
    if found_packages:
        # Pega o nome mais longo para alinhar o print
        max_len = max(len(name) for name in found_packages.keys())
        for package_name, version in sorted(found_packages.items()):
            print(f"  - {package_name.ljust(max_len)} == {version}")
    else:
        print("  Nenhuma biblioteca externa necessária encontrada.")

    print("\n" + "=" * 60)

    # Caso ativado (True), produz diretamente um arquivo padrão na raiz da pasta analisada
    if save_requirements:
        requirements_path = os.path.join(folder_path, 'requirements.txt')
        with open(requirements_path, 'w', encoding='utf-8') as f:
            f.write(f"Python:{python_version}\n")
            for package_name, version in sorted(found_packages.items()):
                f.write(f"{package_name}=={version}\n")
            

        print(f"Arquivo requirements.txt gerado com sucesso em:\n{requirements_path}")
        print("=" * 60 + "\n")

    return found_packages

#######################################################################################################################
##                                               EXECUÇÃO PRINCIPAL                                                  ##
#######################################################################################################################

# Altere para o Caminho na rede onde estão os scripts
caminho = r"\\integraltrust.net\Dados\Dados\Automações\Processamentos\Validação Parsing CNAB\Scripts"

# Executa o gerador
get_installed_versions(caminho, save_requirements=True)


```
</details>

**Passo a passo:**

1. Abrir o arquivo `gerador_requirements.py`
2. Localizar a variável `caminho` no final do script:
```python
caminho = r"\\servidor\pasta\Scripts"
```
3. Substituir pelo caminho da pasta onde estão os scripts a documentar e executar.
4. Copiar o bloco impresso no console:
```
============================================================
DEPENDÊNCIAS IDENTIFICADAS
============================================================
Caminho: \\londres\Dados2\Risco\Comercial\...

Ambiente e Dependências:
  - Python      : 3.13.5
  - pandas      == 2.2.3
  - paramiko    == 3.4.0
============================================================
```
5. Colar no campo "Ambiente e Dependências" da mensagem inicial.

**Exemplo de Extração:**
  
<video controls autoplay loop muted style="max-width:100%; border:1px solid #ddd; border-radius:8px;">
  <source src="/dados/documentador_python/exemplo_requirements.mp4" type="video/mp4">
  Seu navegador não suporta vídeo HTML5.
</video>

---

## :arrows_clockwise: 7) Fluxo recomendado

1. Execute o `gerador_requirements.py` na pasta do projeto e copie as dependências.
2. Reúna e anexe os arquivos `.py` a serem documentados.
3. Preencha os 6 campos obrigatórios do template (Atenção redobrada ao "Script Principal").
4. Envie a mensagem.

---

## :bricks: 8) Estrutura esperada da saída

A documentação gerada pelo agente seguirá uma organização dividida em duas áreas fundamentais:

### :mag: Parte 1 – Visão Geral do Projeto
- **Objetivo & Valor de Negócio:** Qual o problema o projeto resolve.
- **Fluxo Geral:** Como as partes do projeto interagem entre si.
- **Mapa dos Arquivos:** Classificação em Script Principal e Scripts Auxiliares.
- **Entradas e Saídas Globais:** Arquivos lidos e arquivos/tabelas exportados de forma geral.
- **Premissas e Limitações:** Variáveis estáticas ("hardcoded"), validações e gargalos técnicos identificados.

### :gear: Parte 2 – Documentação Técnica por Script
*(Repetido ativamente para cada arquivo `.py` fornecido)*
- **Responsabilidade do Script.**
- **Entradas e Saídas Específicas / Dependências Diretas.**
- **Fluxo Interno:** Explicação passo a passo.
- **Trechos de Código Relevantes:** O agente extrai os pedaços mais críticos do código e os classifica como: *Regra de Negócio, Transformação de Dados, Integração Externa, Controle de Fluxo* ou *Utilitário Técnico*.
- **Pontos de Atenção e Melhorias.**

---

## :bar_chart: 9) Modos de cobertura

O banco de dados e arquivos gerados será enquadrado em um destes modos:

| Status | O que significa |
|---|---|
| :white_check_mark: APROVADO | Tudo perfeito: bloco completo e código integral documentado. |
| :warning: PARCIAL | Bloco do usuário presente, mas código truncado limitando a cobertura. Sinalização ativa de quais trechos pularam. |
| :x: REPROVADO | Abortado antes da documentação devido a falha nos campos obrigatórios. |

---

## :warning: 10) Comportamento de Bloqueio e Limitações

O agente possui uma validação estrita:
- :no_entry: **Bloqueio Automático:** Se faltar o Bloco de Entrada ou qualquer um de seus campos (mesmo preenchido com "N/A"), o agente não irá inventar dados. Ele **abortará a execução** e pedirá o reenvio adequado.
- :no_entry: **Script Principal Inválido:** Se o arquivo apontado como "Script Principal" não estiver entre os anexos, o processo também será abortado.
- :memo: **Regra de Conflito:** Caso o texto do usuário diga algo diferente do que está no código, o agente vai priorizar a "entrada do usuário" para regras de negócio e informações de contexto, mas priorizará o "código" para a lógica técnica efetiva.

---

## :white_check_mark: 11) Checklist antes do envio

Antes de enviar para o agente, confirme **rigorosamente:**

- [ ] Arquivo(s) `.py` anexados com sucesso.
- [ ] Múltiplos arquivos? Determine com clareza quem é o "Script Principal".
- [ ] Bloco formatado com TODAS as 6 chaves (Nome, Descrição, Script Principal, Desenvolvido por, Caminho, Ambiente e Dependências).
- [ ] Nenhuma chave preenchida de forma vaga ("-").

---

## :gift: 12) Resultado esperado

Ao final, você receberá:
- :page_facing_up: Arquivo `[Nome-do-Projeto].md` em português claro e mantendo as formatações originais do código.
- :jigsaw: Hierarquia real do seu código (Entrada > Lógica > Retorno), com apontamentos de pontos de melhoria feitos exclusivamente para os scripts analisados.