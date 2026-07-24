# Trabalho Semestral de Banco de Dados 2 — Empresas de Mudanças (Parte 2)

Sistema para o site de anúncios de empresas de mudanças: modelagem relacional
implementada em **MySQL 8** e uma aplicação **Python + Streamlit** para cadastro
e geração de relatórios.

Disciplina ACH2025 — Bancos de Dados 2 · EACH/USP · 2026-I.

---

## Estrutura do projeto

```
trabalho_mudancas/
├── sql/
│   ├── 01_ddl.sql          # criação das 17 tabelas + restrições (PK/FK/CHECK/UNIQUE)
│   ├── 02_povoamento.sql   # dados de teste (preços já coerentes com a fórmula)
│   └── 03_restricoes.sql   # triggers/procedures das restrições perdidas no mapeamento
├── app/
│   ├── db.py               # conexão única com o MySQL (SQLAlchemy)
│   ├── crud.py             # cadastrar/listar/editar/excluir das 6 entidades
│   ├── queries.py          # as 6 consultas de resultado
│   └── main.py             # interface Streamlit (menu lateral)
├── requirements.txt
└── README.md
```

---

## Como executar

### 1. Banco de dados (MySQL 8+)

Crie um usuário `dev` com senha `123` (usado pela aplicação) e rode os três
scripts, nesta ordem:

```bash
mysql -u dev -p < sql/01_ddl.sql
mysql -u dev -p < sql/02_povoamento.sql
mysql -u dev -p < sql/03_restricoes.sql
```

Ou, pelo MySQL Workbench, abra cada arquivo e execute (⚡) na ordem acima.

> Se usar outro usuário/senha/host, altere apenas as constantes no topo de
> `app/db.py`.

### 2. Aplicação (Python 3.10+)

```bash
pip install -r requirements.txt
python app/db.py            # teste rápido de conexão (opcional)
streamlit run app/main.py
```

O navegador abre em `http://localhost:8501`. Use o menu lateral para navegar
entre os cadastros e a página **Resultados**.

---

## O que cada parte entrega (mapeamento com o enunciado)

### Parte LDD / DDL (20%) — `01_ddl.sql` + `02_povoamento.sql`
As 17 tabelas do esquema relacional com restrições de integridade
(chaves primárias simples e compostas, chaves estrangeiras — inclusive as
compostas de `PEDIDO`→`CIDADE` e `ITEM_PEDIDO`→`OFERTA_SERVICO` —, `CHECK`,
`UNIQUE`) e povoamento com dados de teste.

### Restrições perdidas no mapeamento (30%) — `03_restricoes.sql`
1. **Hierarquia parcial e disjunta:** triggers em `GUINDASTE` e `TRANSPORTE`
   impedem que um mesmo serviço pertença aos dois subtipos (via `SIGNAL`).
2. **Preço de cada serviço:** a função `fn_preco_item` calcula
   `preço_hora × horas`, somando o bônus do guindaste ou aplicando o acréscimo
   percentual do transporte (maior regra cujo `kg_limite` a carga ultrapassa);
   triggers em `ITEM_PEDIDO` gravam sempre esse valor.
3. **Preço total do pedido:** a procedure `sp_recalcula_total_pedido` mantém
   `PEDIDO.preco_total` como a soma dos itens, acionada por triggers de
   `INSERT`/`UPDATE`/`DELETE`.

### Aplicação (50%) — `app/`
- **Cadastros (2,0):** empresas, clientes, cidades, serviços, pedidos e
  funcionários (mais telefones, ofertas, atuação, vínculos e regras).
- **Resultados:**
  1. Histograma de nº de serviços por cidade (0,6)
  2. Histograma de pagamentos por cidade (0,6)
  3. Top 5 cidades por valor investido (0,6)
  4. Top 5 cidades por nº de serviços (0,6)
  5. Top 5 empresas por nº de serviços solicitados (0,8)
  6. Top 5 empresas por valores ganhos em serviços executados (0,8)

---

## Decisões de projeto (para a defesa)

- **`peso` em `ITEM_PEDIDO`:** adicionado à Parte 1 porque o acréscimo de
  transporte depende do peso da carga, que o modelo original não guardava.
- **`DECIMAL` para valores monetários** (em vez de `float`): evita erros de
  arredondamento.
- **Preços calculados no banco (triggers), nunca na aplicação:** o banco é a
  fonte única da verdade; a aplicação só envia os dados.
- **Consultas "por cidade":** usam a cidade de **partida** do pedido.
- **Contagens** consideram todos os pedidos ("solicitados"); **valores**
  consideram apenas pedidos `ACEITO` ("executados").
- **Segurança:** todo acesso ao banco usa parâmetros nomeados (proteção contra
  SQL injection).

---

## Integrantes do grupo

| Nome | Nº USP |
|--------------|---------|
| Bruno Kraker | 8108191 |
| Lucas Antunes | 15471592 |
| Pablo Caballero | 14778630 |
| Rodrigo Franco | 14606450 |
