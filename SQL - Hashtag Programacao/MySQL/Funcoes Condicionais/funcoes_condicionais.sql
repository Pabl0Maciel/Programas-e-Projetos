-- IF (teste_logico, valor_se_verdadeiro, valor_se_falso)

SELECT
	IF(10 > 5, 'Verdadeiro', 'Falso');
   
-- EX 2:
SET @varNotaDesempenho = 8.5;
   
SELECT
	IF (@varNotaDesempenho >= 7, 0.1, 'Sem Bonus');
    
-- EX 3:
SET @varNotaDesempenho = 9.5;

SELECT
	IF(@varNotaDesempenho >= 7, 0.1, IF (@varNotaDesempenho >= 5, 0.05, 'Sem bonus'));
    
-- EX 4:
SELECT
	*,
    IF(Num_Funcionarios >= 20, 'Recebe reforma', 'Nao recebe reforma')		AS 'Status'
FROM lojas;

-- IFNULL retorna um valor passado caso a expressao verificada seja NULL
SELECT
	*,
	IFNULL(Telefone, '0800-999-999')		AS 'Telefone Corrigido'
FROM lojas;

-- ISNULL retorna 1 caso o campo seja NULL e 0 caso contrario
SELECT
	*,
	IF(ISNULL(Telefone), 'Verificar', 'OK')		AS 'Status'
FROM clientes;

-- NULLIF retorna NULL caso as duas expressoes sejam iguais, caso contrario retorna a primeira expressao
SET @varNum1 = 200;
SET @varNum2 = 100;

SELECT
	NULLIF(@varNum1, @varNum2);
    
-- CASE e THEN possibilita fazer uma acao em cada caso
SELECT
	*,
    CASE
		WHEN Sexo = 'M' THEN 'Masculino'
        ELSE 'Feminino'
	END AS 'Sexo 2'
FROM clientes;

-- EX 2:
SELECT
	*,
    CASE
		WHEN Receita_Venda >= 3000 THEN 'Faturamento Alto'
        WHEN Receita_Venda >= 1000 THEN 'Faturamento Medio'
        ELSE 'Faturamento Medio'
	END AS 'Status'
FROM pedidos;

-- EX 3:
SELECT
	*,
    CASE
		WHEN Sexo = 'F' AND Qtd_Filhos > 0 THEN 'Oferta dia das maes'
        WHEN Sexo = 'M' AND Qtd_Filhos > 0 THEN 'Oferta dia dos pais'
        ELSE 'Sem oferta'
	END	AS 'Status Oferta'
FROM clientes;

-- EX 4:
SELECT
	*,
    CASE
		WHEN Marca_Produto = 'DELL' OR Marca_Produto = 'SAMSUNG' THEN 0.85 * Custo_Unit
        ELSE Custo_Unit
    END AS 'Valor com Desconto'
FROM produtos;

