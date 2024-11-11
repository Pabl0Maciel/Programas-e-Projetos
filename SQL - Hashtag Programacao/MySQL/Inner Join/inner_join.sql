-- Tabela Fato --> Tabela Pedidos
-- Tabela Dimensao --> Tabela Produtos

-- Chave Primaria (dimensao) --> ID_Produto (produtos)
-- Chave Estrangeira (fato) --> ID_Produto (pedidos)

-- Tabela Pedidos --> ID_Pedido, Data_Venda, ID_Produto, Qtd_Vendida, Receita_Venda
-- Tabela Produtos --> Nome_Produto, Marca_Produto
SELECT
	pedidos.ID_Pedido,
    pedidos.Data_Venda,
    pedidos.ID_Produto,
    pedidos.Qtd_Vendida,
    pedidos.Receita_Venda,
    produtos.Nome_Produto,
    produtos.Marca_Produto
FROM pedidos
INNER JOIN produtos
	ON pedidos.ID_Produto = produtos.ID_Produto;
    
-- Tabela Fato --> Tabela Pedidos
-- Tabela Dimensao --> Tabela Clientes

-- Chave Primaria (dimensao) --> ID_Cliente (clientes)
-- Chave Estrangeira (fato) --> ID_Cliente (pedidos)

-- Tabela Pedidos --> ID_Pedido, Data_Venda, ID_Cliente, Qtd_Vendida
-- Tabela Clientes --> Nome, Email, Telefone

SELECT
	pd.ID_Pedido,
    pd.Data_Venda,
    pd.ID_Cliente,
    pd.Qtd_Vendida,
    cl.Nome,
    cl.Email,
    cl.Telefone
FROM pedidos as pd
INNER JOIN clientes as cl
	ON pd.ID_Cliente = cl.ID_Cliente;

-- adicionando a coluna de sexo e filtro WHERE
SELECT
	pd.ID_Pedido,
    pd.Data_Venda,
    pd.ID_Cliente,
    pd.Qtd_Vendida,
    cl.Nome,
    cl.Email,
    cl.Telefone,
    cl.Sexo
FROM pedidos as pd
INNER JOIN clientes as cl
	ON pd.ID_Cliente = cl.ID_Cliente
WHERE cl.Sexo = 'M';

-- usando o group by em conjunto
SELECT
	Nome_Produto,
	SUM(Receita_Venda) 		AS 'Total da Receita'
FROM pedidos
INNER JOIN produtos
	ON pedidos.ID_Produto = produtos.ID_Produto
GROUP BY Nome_Produto;

-- EX 2
SELECT
	Loja,
	SUM(Receita_Venda) 		AS 'Total da Receita',
    SUM(Custo_Venda) 		AS 'Total do Custo'
FROM pedidos
INNER JOIN lojas
	ON pedidos.ID_Loja = lojas.ID_Loja
GROUP BY Loja;

