
-- seleciona as linhas da tabela de clientes em que a renda anual eh maior ou igual a 80 mil
SELECT *
FROM clientes
WHERE Renda_Anual >= 80000;

-- seleciona as linhas da tabela de clientes em que a o sexo eh masculino
SELECT *
FROM clientes
WHERE Sexo = 'M';

-- seleciona as linhas da tabela de clientes em que a data de nascimento eh maior que 01/01/2000
SELECT *
FROM clientes
WHERE Data_Nascimento > '2000-01-01';

-- seleciona as linhas da tabela de produtos onde a marca eh DELL E o Preco eh maior ou igual a 2000
SELECT *
FROM produtos
WHERE Marca_Produto = 'DELL' AND Preco_Unit >= 2000;

-- seleciona as linhas da tabela de produtos onde a marca eh DELL OU ALTURA
SELECT *
FROM produtos
WHERE Marca_Produto = 'DELL' OR Marca_Produto = 'ALTURA';

-- seleciona as linhas da tabela de produtos onde a marca NAO eh SAMSUNG
SELECT *
FROM produtos
WHERE  NOT Marca_Produto = 'SAMSUNG';

-- seleciona as linhas da tabela de clientes onde o telefone eh NULL ou VAZIO
SELECT *
FROM clientes
WHERE Telefone IS NULL OR Telefone = '';

-- seleciona as linhas da tabela de lojas onde o telefone eh NULL
SELECT *
FROM lojas
WHERE Telefone IS NULL;

-- seleciona as linhas da tabela de clientes em que o email eh gmail
SELECT *
FROM clientes
WHERE Email LIKE '%gmail%'; -- caractere '% %' significa que nao importa o que tem na esquerda ou na direita, mas importa o que 
							-- tem entre eles
                            
-- seleciona os clientes que possuem o email terminando em '.br'
SELECT *
FROM clientes
WHERE Email LIKE '%.br';

-- seleciona as linhas da tabela de produtos onde a marca eh igual a DELL, SONY ou ALTURA
SELECT *
FROM produtos
WHERE Marca_Produto IN ('DELL', 'SONY', 'ALTURA');

-- seleciona as linhas da tabela de produtos onde a marca NAO eh igual a DELL, SONY ou ALTURA
SELECT *
FROM produtos
WHERE Marca_Produto NOT IN ('DELL', 'SONY', 'ALTURA');

-- seleciona as linhas da tabela de produtos onde o preco unit esta entre 1000 e 2500
SELECT *
FROM produtos
WHERE Preco_Unit BETWEEN 1000 AND 2500; -- inclui as extremidades

-- seleciona as linhas da tabela de clientes onde a data de nascimento esta entre 01/01/1995 e 31/12/1999
SELECT *
FROM clientes
WHERE Data_Nascimento BETWEEN '1995-01-01' AND '1999-12-31';










