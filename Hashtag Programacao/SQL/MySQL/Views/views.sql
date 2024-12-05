-- criando view
CREATE VIEW vwclientes AS
SELECT
	ID_Cliente,
    Nome,
    Email,
    Telefone
FROM clientes;

SELECT * FROM vwclientes;

-- alterando a view
ALTER VIEW vwclientes AS
SELECT
	ID_Cliente,
    Nome,
    Email,
    Telefone,
    Escolaridade
FROM clientes
WHERE Escolaridade = 'Parcial';

SELECT * FROM vwclientes;

-- excluindo a view
DROP VIEW vwclientes;

-- EX 1:
CREATE VIEW vwReceitaAcima4000 AS
SELECT
	*
FROM pedidos
WHERE Receita_Venda >= 4000 AND ID_Loja IN (1, 2, 3, 4);

SELECT * FROM vwreceitaacima4000;

-- EX 2:
CREATE VIEW vwProdutosAtualizada AS
SELECT
	*
FROM produtos
WHERE Marca_Produto IN ('DELL', 'SAMSUNG', 'SONY');

SELECT * FROM vwprodutosatualizada;

-- EX 3:
CREATE VIEW vwReceitaECustoTotal AS
SELECT
	ID_Produto,
    SUM(Receita_Venda) 	AS 'Receita Total',
    SUM(Custo_Venda)	AS 'Custo Total'
FROM pedidos
GROUP BY ID_Produto;

SELECT * FROM vwreceitaecustototal;

-- EX 4:
ALTER VIEW vwReceitaECustoTotal AS
SELECT
	ID_Produto,
    SUM(Receita_Venda) 	AS 'Receita Total',
    SUM(Custo_Venda)	AS 'Custo Total'
FROM pedidos
WHERE ID_Loja = 2
GROUP BY ID_Produto;

SELECT * FROM vwreceitaecustototal;

-- EX 5:
ALTER VIEW vwReceitaECustoTotal AS
SELECT
	ID_Produto,
    SUM(Receita_Venda) 	AS 'Receita Total',
    SUM(Custo_Venda)	AS 'Custo Total'
FROM pedidos
WHERE ID_Loja = 2
GROUP BY ID_Produto
HAVING SUM(Receita_Venda) >= 1000000;

SELECT * FROM vwreceitaecustototal;

-- EX 6:
CREATE VIEW vwPedidosCompleta AS
SELECT
	p.*,
    pr.Nome_Produto,
    pr.Marca_Produto,
    pr.Num_Serie
FROM pedidos AS p
INNER JOIN produtos AS pr
	ON p.ID_Produto = pr.ID_Produto;
    
SELECT * FROM vwpedidoscompleta;

-- EX 7:
ALTER VIEW vwReceitaECustoTotalPorNome AS
SELECT
	produtos.Nome_Produto,
    SUM(Receita_Venda) 	AS 'Receita Total',
    SUM(Custo_Venda)	AS 'Custo Total'
FROM pedidos
INNER JOIN produtos
	ON pedidos.ID_Produto = produtos.ID_Produto
GROUP BY produtos.Nome_Produto;

SELECT * FROM vwreceitaecustototalpornome;