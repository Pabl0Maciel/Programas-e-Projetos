-- cria tres variaveis para armazenar a quantidade, o preco e a receita.
SET @varQuantidade = 10;
SET @varPreco = 10.9;
SET @varReceita =  @varQuantidade * @varPreco;

SELECT @varReceita AS 'Receita Total'; -- mostra o valor

-- armazena a informacao da marca na variavel para que possa mudar mais facilmente a busca caso queira trocar a marca.
SET @varMarca = 'DELL';

SELECT *
FROM produtos
WHERE Marca_Produto = @varMarca;

-- convertendo a variavel para diferentes tipos
SET @varNumero = 10.9200;

SELECT @varNumero,
	CAST(@varNumero AS SIGNED), -- numero inteiro
    CAST(@varNumero AS DECIMAL(10, 2)), -- decimal com no maximo 10 digitos e duas casas decimais
    CAST(@varNumero AS CHAR(3)); -- texto com 3 caracteres
    
-- convertendo para tipos de data    
SET @varData = '2021-01-01';

SELECT @varData,
	CAST(@varData AS DATE), -- data
    CAST(@varData AS DATETIME); -- data e hora