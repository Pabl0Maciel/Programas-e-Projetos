-- EX 1:
-- seleciona tudo na tabela de pedidos onde o gerente eh o marcelo castro
SET @varNome = 'Marcelo Castro';

SELECT
	*
FROM pedidos
WHERE ID_Loja = (
			SELECT ID_Loja 
			FROM lojas 
            WHERE Gerente = @varNome
            );
            
-- EX 2:
-- seleciona os produtos onde o preco unitario esta acima da media
SELECT
	*
FROM produtos
WHERE Preco_Unit > (
				SELECT 
					AVG(Preco_Unit) 
                    FROM produtos
                    );
                    
-- EX 3:
-- seleciona os produtos da categoria de notebook
SELECT
	*
FROM produtos
WHERE ID_Categoria = (
				SELECT 
					ID_Categoria
				FROM categorias
                WHERE Categoria = 'Notebook'
				);
                
-- EX 4:
-- mostra o cliente com maior receita de venda
SELECT
	*
FROM clientes
WHERE ID_Cliente = (
					SELECT 
						ID_Cliente
					FROM pedidos
					GROUP BY ID_Cliente
					ORDER BY SUM(Receita_Venda) DESC
					LIMIT 1
					);
                    
-- EX 5:
-- mostra a receita total da marca dell
SELECT
	SUM(Receita_Venda)
FROM pedidos
WHERE ID_Produto IN (
					SELECT
						ID_Produto
					FROM produtos
                    WHERE Marca_Produto = 'DELL'
					);

-- EX 6:
-- mostra os pedidos da regiao sudeste
SELECT
	*
FROM pedidos
WHERE ID_Loja IN (
				SELECT
					ID_Loja
				FROM lojas
                WHERE Loja IN (
								SELECT Cidade
                                FROM locais
                                WHERE Região = 'Sudeste'
								)
				);

-- EX 7:
-- cria uma coluna de media de preco na tabela de produtos
SELECT
	*,
    (
    SELECT
		AVG(Preco_Unit)
	FROM produtos
    ) AS 'Media Geral de Preco'
FROM produtos;

-- EX 8:
-- mostra o maximo, minimo e media do numero de vendas
SELECT
	MAX(Vendas) AS 'Maximo Vendas',
    MIN(Vendas) AS 'Minimo Vendas',
    AVG(Vendas) AS 'Media Vendas'
FROM(
	SELECT
		ID_Produto,
		COUNT(*) AS 'Vendas'
	FROM pedidos
	GROUP BY ID_Produto
) AS t;

-- EX 9:
-- mostra os ID das categoria que tem pelo menos um produto na tabela de produtos
SELECT
	ID_Categoria
FROM categorias
WHERE EXISTS (
				SELECT
					ID_Categoria
				FROM produtos
                WHERE categorias.ID_Categoria = produtos.ID_Categoria
			);