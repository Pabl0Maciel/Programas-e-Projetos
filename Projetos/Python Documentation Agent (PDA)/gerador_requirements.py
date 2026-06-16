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
caminho = r"/home/pabl0maciel/Documents/Programas-e-Projetos/Projetos/Analise de Alugueis em SP/src"

# Executa o gerador
get_installed_versions(caminho, save_requirements=True)
