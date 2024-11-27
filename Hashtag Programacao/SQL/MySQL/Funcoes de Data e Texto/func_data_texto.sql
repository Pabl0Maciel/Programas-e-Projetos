
-- funcao LENGTH retorna o numero de caracteres no texto
SET @varTexto = 'SQL Impressionador';

SELECT LENGTH(@varTexto);

-- mostra a qntd de caracteres de cada nome da tabela de clientes
SELECT
	Nome AS 'Nome',
    LENGTH(Nome) AS 'Num. de Caracteres'
FROM clientes;

-- a funcao CONCAT concatena duas ou mais strings. a funcao CONCAT_WS concatena strings com um delimitador passado no primeiro campo da funcao.
SET @varNome = 'Pablo';
SET @varSobrenome = 'Caballero';

SET @varNomeCompleto = CONCAT(@varNome, ' ', @varSobrenome);
SET @varNomeCompleto2 = CONCAT_WS(' ', @varNome, @varSobrenome);

SELECT 
	@varNomeCompleto, 
	@varNomeCompleto2;
    
-- aplicando na tabela clientes
SELECT 
	ID_Cliente,
    Nome,
    Sobrenome,
    CONCAT_WS(' ', Nome, Sobrenome) AS 'Nome Completo',
    Email
FROM clientes;

-- LCASE deixa o texo em minusculo e UCASE em maisculo
SELECT
	LCASE(CONCAT(Nome, ' ', Sobrenome)) AS 'Nome Completo (CONCAT)',
    UCASE(CONCAT_WS(' ', Nome, Sobrenome)) AS 'Nome Completo (CONCAT_WS)'
FROM clientes;

-- LEFT divide a parte mais a esquerda da variavel conforme o numero de caracteres passado. RIGHT eh a mesma coisa
SELECT
	LEFT(Num_Serie, 6) AS 'Codigo 1', -- pega a parte esquerda de Num_Serie (6 primeiros digitos)
    RIGHT(Num_Serie, 6) AS 'Codigo 2' -- pega a parte direita de Num_Serie (6 ultimos digitos)
FROM produtos;

-- REPLACE substitui um texto por outro
SELECT
	Nome,
    Estado_Civil,
    REPLACE(REPLACE(Estado_Civil, 'S', 'Solteiro'), 'C', 'Casado')
FROM clientes;

-- INSTR descobre a posicao do caractere passado em uma string. MID seleciona os caracteres entre um comeco e fim passados.
SET @varEmail = 'pablocaballero07@gmail.com';
SET @varPosArroba = INSTR(@varEmail, '@');

SELECT @varPosArroba;

SET @varIdEmail = MID(@varEmail, 1, @varPosArroba-1);

SELECT @varIdEmail;

-- aplica o mesmo exemplo na tabela
SELECT 
	Email,
    MID(Email, 1, INSTR(Email, '@')-1) AS 'ID Email'
FROM clientes;

-- funcoes de DAY, MONTH e YEAR para retirar trechos especificos de uma data
SELECT 
	Nome,
    Data_Nascimento,
    DAY(Data_Nascimento) AS 'Dia',
    MONTH(Data_Nascimento) AS 'Mes',
    YEAR(Data_Nascimento) AS 'Ano'
FROM clientes;

-- NOW retorna data e hora. CURDATE retorna a data. CURTIME retorna a hora
SELECT
	NOW(),
    CURDATE(),
    CURTIME();
    
-- DATEDIFF calcula a diferenca entre duas datas em dias. DATE_ADD adiciona uma data a variavel. DATE_SUB subtrai uma data a variavel
SET @varDataInicio = '2021-04-10';
SET @varDataFim = '2021-07-15';

SELECT 
	DATEDIFF(@varDataFim, @varDataInicio),
	DATE_ADD(@varDataInicio, INTERVAL 10 DAY), -- adiciona 10 dias na data de inicio, poderia ser meses ou anos.
    DATE_SUB(@varDataFim, INTERVAL 10 DAY); -- subtrai 10 dias na data de inicio, poderia ser meses ou anos.