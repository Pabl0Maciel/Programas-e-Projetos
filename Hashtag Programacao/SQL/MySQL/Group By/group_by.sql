-- seleciona o numero de produtos por marca
SELECT Marca_Produto, COUNT(*)		AS 'Qntd de Produtos'
FROM produtos
GROUP BY Marca_Produto
ORDER BY COUNT(*) DESC;

-- mostra o numero de clientes por sexo
SELECT Sexo, COUNT(*)		AS 'Qntd de Clientes'
FROM clientes
GROUP BY Sexo;

-- mostra o total de venda por produto
SELECT ID_Produto, SUM(Receita_Venda) 	AS 'Total da Receita'
FROM pedidos
GROUP BY ID_Produto;

-- mostra o numero de clientes por escolaridade e sexo
SELECT Sexo, Escolaridade, COUNT(*) 	AS 'Qntd de clientes'
FROM clientes
GROUP BY Sexo, Escolaridade;

-- mostra o total de vendas por produto e loja
SELECT ID_Loja, ID_Produto, SUM(Receita_Venda)		AS 'Total de Vendas'
FROM pedidos
GROUP BY ID_Loja, ID_Produto;

-- mostra a qntd de clientes femininos por escolaridade (o filtro WHERE eh aplicado ANTES do agrupamento)
SELECT Escolaridade, COUNT(*) 		AS 'Qntd de Clientes'
FROM clientes
WHERE Sexo = 'F'
GROUP BY Escolaridade;

-- mostra a qntd de clientes por escolaridade em que a qntd eh maior que 25 (o filtro HAVING eh aplicado DEPOIS do agrupamento)
SELECT Escolaridade, COUNT(*) 		AS 'Qntd de Clientes'
FROM clientes
GROUP BY Escolaridade
HAVING COUNT(*) > 25;

-- mostra os produtos em que a soma da receita eh maior que 5 milhoes
SELECT ID_Produto, SUM(Receita_Venda)		AS 'Receita Total'
FROM pedidos
GROUP BY ID_Produto
HAVING SUM(Receita_Venda) >= 5000000;

