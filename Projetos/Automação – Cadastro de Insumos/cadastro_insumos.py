#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul 24 13:30:00 2025

@author: pablo

🔧 Instruções de uso:

1. Abra o Google Chrome com depuração remota ativada executando o seguinte comando no terminal:

       google-chrome --remote-debugging-port=9222 --user-data-dir=/tmp/selenium-profile

   Isso permitirá que o Selenium controle a aba do navegador já aberta.

2. No navegador aberto, acesse a seguinte página do sistema Saipos:

    https://conta.saipos.com/#/app/store/provider-nfe

   Aplique obrigatoriamente os seguintes filtros:
   - Período: selecione o intervalo desejado (por exemplo, de 01/01/2025 até 31/07/2025);
   - Conciliação Estoque: marque como "Não";

   A tela deve exibir apenas as notas que ainda precisam de conciliação de itens.

3. Com o navegador posicionado nessa tela e logado, execute este script normalmente com:

       python3 nome_do_arquivo.py
       
📌 Observações:

- O script busca pelos nomes dos insumos exatamente como estão nas notas;
- Se o nome pesquisado não for encontrado no cadastro de ingredientes, 
  será criado automaticamente um novo ingrediente com esse nome e a conciliação será realizada.
"""


from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import ElementClickInterceptedException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
import time

# Configuração do Selenium conectado ao Chrome aberto com depuração remota
options = Options()
options.debugger_address = "127.0.0.1:9222"
driver = webdriver.Chrome(options=options)

# Aguarda a página de notas carregar
time.sleep(5)

# Função auxiliar para rolar a página
def scroll_to_bottom():
    driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
    time.sleep(2)

# Scroll para garantir carregamento da tabela completa
scroll_to_bottom()

# Localiza todos os botões de "Conciliação de Itens" (terceiro botão da linha)
botoes_conc_estoq = driver.find_elements(By.XPATH, "//button[@ng-click=\"vm.conciliationItem(nfe.id_store_provider_nfe)\"]")


print(f"Encontradas {len(botoes_conc_estoq)} notas com botão de conciliação.")

# Percorre cada botão da lista
while True:
    # Atualiza a lista de botões a cada iteração
    botoes_conc_estoq = driver.find_elements(
        By.XPATH, "//button[@ng-click='vm.conciliationItem(nfe.id_store_provider_nfe)']"
    )

    if not botoes_conc_estoq:
        print("✅ Todas as notas foram processadas.")
        break

    botao = botoes_conc_estoq[0]  # sempre pega o primeiro disponível

    # Tenta clicar com segurança (scroll + fallback JavaScript)
    try:
        driver.execute_script("arguments[0].scrollIntoView(true);", botao)
        time.sleep(0.5)
        botao.click()
    except ElementClickInterceptedException:
        print("⚠️ Clique interceptado, tentando via JavaScript")
        driver.execute_script("arguments[0].click();", botao)

    time.sleep(7)  # espera a tela de conciliação abrir

    # Captura os insumos da esquerda
    insumos = driver.find_elements(By.XPATH, "//div[contains(@class, 'modal-dialog')]//a[@class='ng-binding']")
    
    for item in insumos:
        nome = item.text.strip()
        if not nome:
            continue
    
        print(f"🔄 Conciliando insumo: {nome}")
    
        try:
            # Campo de busca da direita
            campo_pesquisa = driver.find_element(By.XPATH, "//input[@placeholder='Digite sua pesquisa...']")
            campo_pesquisa.clear()
            campo_pesquisa.send_keys(nome)
            time.sleep(1.5)  # espera preencher resultados
    
            # Clicar no insumo da ESQUERDA
            driver.execute_script("arguments[0].scrollIntoView(true);", item)
            item.click()
            time.sleep(0.5)
    
            # Tenta clicar no ingrediente à direita
            resultado = driver.find_element(By.XPATH,
                f"//div[@ng-click='vm.selectIngredient(ingredient);' and normalize-space(text())='{nome}']")
            driver.execute_script("arguments[0].scrollIntoView(true);", resultado)
            resultado.click()
            print(f"✅ Conciliado: {nome}")
            time.sleep(0.5)
    
        except Exception as e:
            print(f"❌ Erro ao conciliar {nome}: {e}")
            continue


    # Clica no botão SALVAR
    try:
        btn_salvar = driver.find_element(By.XPATH, "//button[@ng-click='vm.save()']")
        driver.execute_script("arguments[0].scrollIntoView(true);", btn_salvar)
        btn_salvar.click()
        print("🟡 Clique no botão SALVAR realizado.")
    
        # Espera até 5s pelo botão OK (caso o modal apareça)
        try:
            btn_ok = WebDriverWait(driver, 5).until(
                EC.element_to_be_clickable((
                    By.XPATH,
                    "//button[contains(@class, 'confirm') and normalize-space(text())='OK']"
                ))
            )
            btn_ok.click()
            print("✅ Modal 'Atenção' detectado e fechado com OK.")
    
        except TimeoutException:
            print("ℹ️ Nenhum modal de 'Atenção' apareceu. Prosseguindo normalmente.")
    
    except Exception as e:
        print(f"⚠️ Erro ao clicar em SALVAR ou processar modal: {e}")

    time.sleep(12)  # Aguarda retorno para a tela principal

# Finaliza
print("✅ Processo concluído para todas as notas.")

