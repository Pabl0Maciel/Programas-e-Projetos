SELECT * FROM pedidos; -- seleciona tudo da tabela de pedidos

SELECT * FROM produtos; -- seleciona tudo da tabela de produtos

SELECT Nome_Produto FROM produtos; -- seleciona apenas a coluna 'Nome_Produto' da tabela de produtos

SELECT ID_Produto, Nome_Produto, Preco_Unit FROM produtos; -- selecionas apenas as colunas especificadas

-- aplicando a identacao e formatacao de escrita de codigo
SELECT 
	ID_Produto, 
    Nome_Produto, 
    Marca_Produto, 
    Custo_Unit 
FROM produtos;

-- renomeando colunas
SELECT 
	ID_Produto 		AS 'ID do Produto', 
    Nome_Produto 	AS 'Nome do Produto', 
    Marca_Produto 	AS 'Marca do Produto', 
    Custo_Unit 		AS 'Custo Unitario'
FROM produtos;

SELECT * FROM pedidos LIMIT 100; -- limita a query para as 100 primeiras linhas

SELECT * FROM pedidos LIMIT 100 OFFSET 5; -- mostra as 100 primeiras linhas, pulando as 5 primeiras

SELECT DISTINCT Marca_Produto FROM produtos; -- seleciona os valores distintos da coluna marca

-- seleciona tudo da tabela de clientes e organiza em ordem crescente por nome
SELECT *
FROM clientes
ORDER BY Nome;

-- seleciona tudo da tabela de clientes e organiza em ordem decrescente por nome
SELECT *
FROM clientes
ORDER BY Nome DESC;

-- seleciona tudo da tabela de clientes e organiza em ordem crescente por renda anual 
SELECT *
FROM clientes
ORDER BY Renda_Anual;

-- seleciona tudo da tabela de clientes e organiza em ordem decrescente por renda anual 
SELECT *
FROM clientes
ORDER BY Renda_Anual DESC;

-- seleciona tudo da tabela de clientes e organiza em ordem crescente por data de nascimento
SELECT *
FROM clientes
ORDER BY Data_Nascimento;

-- seleciona tudo da tabela de clientes e organiza em ordem decrescente por data de nascimento
SELECT *
FROM clientes
ORDER BY Data_Nascimento DESC;

-- seleciona tudo da tabela de clientes e organiza em ordem decrescente por renda anual e data de nascimento 
SELECT *
FROM clientes
ORDER BY Renda_Anual DESC, Data_Nascimento DESC;

-- seleciona tudo da tabela de clientes e organiza em ordem crescente por nome e sobrenome
SELECT *
FROM clientes
ORDER BY Nome, Sobrenome;

