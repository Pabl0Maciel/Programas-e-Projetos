<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Hashtag%20Programação&fontSize=34&fontColor=4F8EF7&fontAlignY=45&desc=SQL%20e%20Excel%20na%20prática&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

Conteúdos estudados na plataforma **Hashtag Treinamentos**, com foco em SQL (MySQL) do básico ao avançado e atalhos práticos de Excel.

---

## 🗃️ SQL — MySQL

Curso **SQL Impressionador**, cobrindo desde a introdução até recursos avançados como stored procedures e subqueries.

| Módulo | Arquivo | O que cobre |
|--------|---------|-------------|
| [`Introdução`](./SQL/MySQL/Introducao) | `introducao.sql` + bases | Primeiros comandos, SELECT, WHERE, estrutura do banco |
| [`CRUD`](./SQL/MySQL/CRUD) | `crud.sql` | INSERT, UPDATE, DELETE, SELECT |
| [`Filtros`](./SQL/MySQL/Filtros) | `filtros.sql` | WHERE, BETWEEN, IN, LIKE, operadores lógicos |
| [`Group By`](./SQL/MySQL/Group%20By) | `group_by.sql` | Agregações com GROUP BY, HAVING, COUNT, SUM, AVG |
| [`Inner Join`](./SQL/MySQL/Inner%20Join) | `inner_join.sql` | JOINs entre tabelas (INNER, LEFT, RIGHT) |
| [`Funções Condicionais`](./SQL/MySQL/Funcoes%20Condicionais) | `funcoes_condicionais.sql` | CASE WHEN, IF, IFNULL, COALESCE |
| [`Funções Matemáticas`](./SQL/MySQL/Funcoes%20Matematicas) | `funcoes_matematicas.sql` | ROUND, CEIL, FLOOR, ABS, MOD, POWER |
| [`Funções de Data e Texto`](./SQL/MySQL/Funcoes%20de%20Data%20e%20Texto) | `func_data_texto.sql` | DATE_FORMAT, DATEDIFF, CONCAT, SUBSTRING, TRIM |
| [`Subqueries`](./SQL/MySQL/Subqueries) | `subqueries.sql` | Subconsultas correlacionadas e não-correlacionadas |
| [`Views`](./SQL/MySQL/Views) | `views.sql` | Criação e uso de views |
| [`Functions`](./SQL/MySQL/Functions) | `functions.sql` | Funções definidas pelo usuário |
| [`Stored Procedures`](./SQL/MySQL/Stored%20Procedures) | `stored_procedures.sql` | Procedures com parâmetros e lógica condicional |
| [`Variáveis e CAST`](./SQL/MySQL/Variaveis) | `variaveis_cast.sql` | Declaração de variáveis, conversão de tipos |

---

## 📊 Excel

| Conteúdo | Arquivo | O que cobre |
|----------|---------|-------------|
| [`Atalhos`](./Excel/Atalhos) | `Atalhos.xlsx` | Principais atalhos de teclado para produtividade no Excel |

---

## ⚙️ Como usar os scripts SQL

1. Tenha o **MySQL** instalado (ou use [MySQL Workbench](https://www.mysql.com/products/workbench/))
2. Execute primeiro os arquivos da pasta [`Introdução/Base`](./SQL/MySQL/Introducao/Base) para criar e popular o banco
3. Rode os demais scripts na ordem que preferir

```sql
-- Exemplo: carregar a base no MySQL
SOURCE /caminho/para/Introducao/Base/base_clientes.sql;
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
