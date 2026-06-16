<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=180&section=header&text=Banco%20de%20Dados%20—%20Loja%20de%20Vendas&fontSize=32&fontColor=4F8EF7&fontAlignY=38&desc=PostgreSQL%20·%20Flask%20API%20·%20Frontend%20Web%20·%20Dados%20gerados%20com%20Faker&descColor=00D4FF&descSize=15&descAlignY=58&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![Python](https://img.shields.io/badge/Python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![PostgreSQL](https://img.shields.io/badge/PostgreSQL-316192?style=for-the-badge&logo=postgresql&logoColor=white)
![SQLAlchemy](https://img.shields.io/badge/SQLAlchemy-D71F00?style=for-the-badge&logo=python&logoColor=white)
![Flask](https://img.shields.io/badge/Flask-000000?style=for-the-badge&logo=flask&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)

</div>

---

## 🎯 Objetivo

Banco de dados PostgreSQL completo para uma loja fictícia de eletrônicos — criado e populado automaticamente via Python. Serve como base sólida para estudos de **SQL**, **modelagem de dados**, **ETL** e **BI**, com um frontend web e API REST para explorar os dados de forma interativa.

---

## 🏗️ Arquitetura

```
📦 Banco de Dados/
│
├── Scripts/
│   ├── criacao_banco.py          # Cria banco, ENUMs e todas as tabelas
│   ├── funcoes_populacao.py      # Funções de população de cada tabela
│   └── Criador_e_Populador.py    # ✅ Script principal — executa tudo
│
├── backend/
│   ├── app.py                    # API REST (Flask)
│   └── backend.py                # Configurações e helpers
│
├── frontend/
│   ├── index.html                # Página principal (catálogo)
│   ├── home.html                 # Home
│   ├── relatorio.html            # Dashboard de relatórios
│   ├── css/                      # Estilos
│   └── js/
│       ├── components/           # Navbar, Modal, ProductList, AdminDashboard
│       ├── api.js                # Chamadas à API
│       ├── app.js                # Inicialização
│       ├── state.js              # Gerenciamento de estado
│       └── utils.js              # Utilitários
│
└── Materiais Videos/
    └── screencast.gif            # Demonstração em vídeo
```

---

## 🗄️ Modelo de Dados

### Tabelas e ENUMs

```sql
-- ENUMs definidos
status_pedido_t    →  iniciado | pendente | enviando | concluido | cancelado
prioridade_pedido_t →  baixa | media | alta
modo_envio_t       →  entrega | retirada
forma_pagamento_t  →  cartao_credito | cartao_debito | boleto | pix | transferencia | dinheiro
tipo_desconto_t    →  promocional | cupom | fidelidade | parceria | outros
```

### Diagrama de entidades

```
Cliente ──────────────────────────┐
                                  │
Produto (pai)                   Pedido ──── Item_Pedido ──── Produto
  ├── Dispositivo   (cor, dim.)    │
  ├── Hardware      (specs, W)     ├── Venda (impostos, frete, total)
  └── Periferico    (cor, conex.)  ├── Pagamento (método, parcelas)
                                  ├── Desconto_Aplicado
                                  └── Fidelidade_Cliente (pontos %)
```

### Lógicas de negócio implementadas

| Entidade | Lógica |
|----------|--------|
| **Pedido** | Datas coerentes, status e prazos realistas, sazonalidade |
| **Venda** | Subtotal, descontos, impostos variados, frete condicional |
| **Pagamento** | Parcelamento inteligente por valor, datas próximas ao pedido |
| **Fidelidade** | ≤ R$500 → 1% · R$500–2000 → 2% · >R$2000 → 3% |
| **Desconto** | Porcentagem calculada automaticamente dos itens |

---

## 🌐 API REST (Flask)

| Método | Rota | Descrição |
|--------|------|-----------|
| `GET` | `/api/produtos` | Lista todos os produtos com tipo e atributos específicos |
| `GET` | `/api/clientes` | Lista clientes |
| `GET` | `/api/descontos` | Descontos disponíveis |
| `GET` | `/api/clientes/fidelidade` | Clientes do programa de fidelidade |
| `GET` | `/api/clientes/promocional` | Clientes elegíveis para promoções |
| `GET` | `/api/clientes/primeira-compra` | Clientes de primeira compra |
| `GET` | `/api/produtos/<id>/recomendacoes` | Recomendações por produto |
| `POST` | `/api/checkout` | Registra um novo pedido |

---

## 🎬 Demonstração

![Demonstração](./Materiais%20Videos/screencast.gif)

---

## 🚀 Como executar

### 1. Pré-requisitos

- PostgreSQL instalado e rodando
- Python 3.x

```bash
pip install sqlalchemy psycopg2-binary faker flask flask-cors
```

### 2. Configure as credenciais

Em `Scripts/Criador_e_Populador.py`, ajuste:

```python
usuario = 'postgres'
senha = 'sua_senha'
host = 'localhost'
porta = '5432'
banco = 'loja_vendas'
```

E defina o tamanho do dataset:

```python
qtd_clientes = 50    # número de clientes gerados
qtd_pedidos  = 200   # número de pedidos gerados
```

### 3. Crie e popule o banco

```bash
python Scripts/Criador_e_Populador.py
```

O script executa em sequência:
1. Cria o banco (se não existir)
2. Cria todas as tabelas e ENUMs
3. Popula todas as entidades na ordem correta de dependência

### 4. Suba a API

Em `backend/app.py`, ajuste as credenciais do banco:

```python
DB_CONFIG = {
    'dbname': 'loja_vendas',
    'user': 'postgres',
    'password': 'sua_senha',
    'host': 'localhost',
    'port': '5432'
}
```

```bash
python backend/app.py
```

A API estará disponível em `http://localhost:5000`.

### 5. Abra o frontend

Abra `frontend/index.html` diretamente no navegador ou sirva com:

```bash
cd frontend
python -m http.server 8080
```

---

## 📊 Exemplos de consultas SQL

```sql
-- Clientes por estado
SELECT estado, COUNT(*) as total FROM cliente GROUP BY estado ORDER BY total DESC;

-- Top 10 vendas
SELECT id_pedido, valor_total FROM venda ORDER BY valor_total DESC LIMIT 10;

-- Pedidos por status
SELECT status_pedido, COUNT(*) FROM pedido GROUP BY status_pedido;

-- Produtos com estoque abaixo do mínimo
SELECT nome_produto, estoque_atual, estoque_minimo
FROM produto WHERE estoque_atual < estoque_minimo;

-- Receita por categoria de produto
SELECT p.categoria, SUM(v.valor_total) as receita_total
FROM venda v
JOIN pedido pe ON v.id_pedido = pe.id_pedido
JOIN item_pedido ip ON pe.id_pedido = ip.id_pedido
JOIN produto p ON ip.id_produto = p.id_produto
GROUP BY p.categoria ORDER BY receita_total DESC;
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
