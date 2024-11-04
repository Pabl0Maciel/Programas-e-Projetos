SELECT
	ROUND(87.149, 2)		AS 'Arrendondamento',
    FLOOR(87.149)			AS 'Arrendondamento p/ baixo',
    CEILING(87.149)			AS 'Arrendondamento p/ cima',
    TRUNCATE(87.149, 2)		AS 'Truncar';
    
-- conta a qntd de clientes pelo nome    
SELECT 
	COUNT(Nome) AS 'Qntd de Clientes'
FROM clientes;

-- conta a qntd de clientes pelo telefone (possui alguns valores nulos, por isso retorna um numero diferente)    
SELECT 
	COUNT(Telefone) AS 'Qntd de Clientes'
FROM clientes;

-- conta a qntd de clientes pela quantidade de linhas
SELECT 
	COUNT(*) AS 'Qntd de Clientes'
FROM clientes;

-- conta o numero de marcas distintas
SELECT 
	COUNT(DISTINCT Marca_Produto)
FROM produtos;


SELECT
	SUM(Receita_Venda)		AS 'Soma de Receita',
    AVG(Receita_Venda)		AS 'Media da Receita',
    MIN(Receita_Venda)		AS 'Menor Receita',
    MAX(Receita_Venda)		AS 'Maior Receita'
FROM pedidos;

