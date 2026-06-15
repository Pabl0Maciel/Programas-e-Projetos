<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Automação%20–%20Cadastro%20de%20Insumos&fontSize=32&fontColor=4F8EF7&fontAlignY=38&desc=Conciliação%20automática%20de%20notas%20de%20entrada%20no%20sistema%20Saipos&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![Selenium](https://img.shields.io/badge/Selenium-43B02A?style=for-the-badge&logo=selenium&logoColor=white)
![Chrome](https://img.shields.io/badge/Chrome-Remote%20Debug-4285F4?style=for-the-badge&logo=googlechrome&logoColor=white)

</div>

---

## 🎯 Objetivo

Automatizar a conciliação de insumos no sistema **Saipos**, eliminando o processo manual de associar itens de notas de entrada aos ingredientes cadastrados. O script percorre todas as notas com conciliação pendente e realiza o vínculo automaticamente — e quando o ingrediente não existe, cria o cadastro.

---

## ⚙️ Como funciona

```
Tela: Estoque > Notas de Entrada (filtro: Conciliação = "Não")
                        │
                        ▼
          Detecta botões de "Conciliação de Itens"
                        │
                        ▼
              Para cada nota encontrada:
                        │
              ┌─────────┴──────────┐
              │  Captura insumos   │
              │  da nota (lado     │
              │  esquerdo)         │
              └─────────┬──────────┘
                        │
              Para cada insumo:
                        │
              ┌─────────┴────────────────────────────────┐
              │  Pesquisa o ingrediente no sistema        │
              │                                           │
              │  Encontrou? → clica e concilia   ✅       │
              │                                           │
              │  Não encontrou? → clica em "+"            │
              │                → abre modal de cadastro   │
              │                → salva novo ingrediente   │
              │                → concilia                 ✅│
              └─────────┬────────────────────────────────┘
                        │
              Clica em SALVAR a conciliação
                        │
              Trata modal de confirmação (se aparecer)
                        │
              Aguarda retorno e passa para a próxima nota
```

---

## 🛡️ Robustez implementada

| Situação | Tratamento |
|----------|-----------|
| Clique bloqueado por sobreposição | Fallback via `execute_script` (JavaScript) |
| Ingrediente não encontrado | Cria cadastro automaticamente via modal |
| Modal de confirmação ("OK") | Detectado com `WebDriverWait` e fechado |
| Elemento não clicável | `scrollIntoView` antes de cada interação crítica |
| Atualização da lista de botões | Lista recarregada a cada iteração do `while` |

---

## 🚀 Como executar

### Pré-requisito: ChromeDriver

Baixe o [ChromeDriver](https://chromedriver.chromium.org/downloads) compatível com sua versão do Chrome e ajuste o caminho no script:

```python
service = Service("/caminho/para/chromedriver")
```

### 1. Abra o Chrome com depuração remota

Execute no terminal **antes** de rodar o script:

```bash
google-chrome --remote-debugging-port=9222 --user-data-dir=/tmp/selenium-profile
```

> Isso permite que o Selenium controle a sessão já autenticada no Saipos, sem precisar fazer login via script.

### 2. Acesse a tela correta no Saipos

No navegador aberto, navegue até:

```
Estoque > Notas de Entrada
```

Aplique os filtros obrigatórios:

| Filtro | Valor |
|--------|-------|
| Período | Intervalo desejado (ex: 01/01/2025 – 31/07/2025) |
| Conciliação de Estoque | **Não** |

A tela deve exibir **apenas** as notas que ainda precisam de conciliação.

### 3. Execute o script

```bash
python3 cadastro_insumos.py
```

O script assume que o navegador já está aberto e posicionado na tela correta.

---

## 📋 Saída no terminal

Durante a execução, o script imprime o progresso em tempo real:

```
Encontradas 12 notas com botão de conciliação.
🔄 Conciliando insumo: Farinha de Trigo
✅ Conciliado: Farinha de Trigo
🔍 Ingrediente não encontrado: Azeite Extra Virgem. Tentando cadastrar...
✅ Ingrediente Azeite Extra Virgem cadastrado com sucesso.
🟡 Clique no botão SALVAR realizado.
✅ Modal 'Atenção' detectado e fechado com OK.
✅ Todas as notas foram processadas.
```

---

## 📂 Estrutura

```
📦 Automação – Cadastro de Insumos/
│
├── cadastro_insumos.py    # Script principal
└── README.md
```

---

## 📌 Observações

- O script busca os ingredientes pelo **nome exato** como constam nas notas
- A criação automática de novos ingredientes está implementada, mas pode precisar de ajuste conforme a estrutura do formulário no seu ambiente do Saipos
- Tempos de espera (`time.sleep`) podem ser ajustados conforme a velocidade da sua conexão

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
