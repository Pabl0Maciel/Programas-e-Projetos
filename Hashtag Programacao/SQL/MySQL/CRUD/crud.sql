-- criando banco de dados
CREATE DATABASE IF NOT EXISTS db_exemplo;

-- mostrando os bancos de dados
SHOW DATABASES;

-- definindo o banco de dados para padrao
USE db_exemplo;

-- para saber qual eh o banco de dados usado no momento
SELECT DATABASE();

-- excluindo o banco de dados
DROP DATABASE IF EXISTS db_exemplo;

-- criando tabelas 
CREATE TABLE IF NOT EXISTS dAlunos(
	ID_Aluno INT,
    Nome_Aluno VARCHAR(100),
    Email VARCHAR(100)
);

CREATE TABLE IF NOT EXISTS dCursos(
	ID_Curso INT,
    Nome_Curso VARCHAR(100),
    Preco_Curso DECIMAL(10, 2)
);

CREATE TABLE IF NOT EXISTS fMatriculas(
	ID_Matricula INT,
    ID_Aluno INT,
    ID_Curso INT,
    Data_Cadastro DATE
);

SHOW TABLES;

SELECT * FROM dAlunos;
SELECT * FROM dCursos;
SELECT * FROM fMatriculas;

-- aplicando CONSTRAINTS (regras)
DROP TABLE IF EXISTS dAlunos;
DROP TABLE IF EXISTS dCursos;
DROP TABLE IF EXISTS fMatriculas;

CREATE TABLE IF NOT EXISTS dAlunos(
	ID_Aluno INT,
    Nome_Aluno VARCHAR(100) NOT NULL,
    Email VARCHAR(100) NOT NULL,
    PRIMARY KEY(ID_Aluno)
);

CREATE TABLE IF NOT EXISTS dCursos(
	ID_Curso INT,
    Nome_Curso VARCHAR(100) NOT NULL,
    Preco_Curso DECIMAL(10, 2) NOT NULL,
    PRIMARY KEY(ID_Curso)
);

CREATE TABLE IF NOT EXISTS fMatriculas(
	ID_Matricula INT,
    ID_Aluno INT NOT NULL,
    ID_Curso INT NOT NULL,
    Data_Cadastro DATE NOT NULL,
    PRIMARY KEY(ID_Matricula),
    FOREIGN KEY (ID_Aluno) REFERENCES dAlunos(ID_Aluno),
    FOREIGN KEY (ID_Curso) REFERENCES dCursos(ID_Curso)
);

-- inserindo dados nas tabelas
INSERT INTO dAlunos(ID_Aluno, Nome_Aluno, Email)
VALUES
	(1, 'Ana'	, 	'ana123@gmail.com'),
    (2, 'Bruno'	, 	'bruno_vargas@outlook.com'),
    (3, 'Carla'	, 	'carlinha1999@gmail.com'),
    (4, 'Diego'	, 	'diicastroneves@gmail.com');
    
SELECT * FROM dAlunos;

INSERT INTO dCursos(ID_Curso, Nome_Curso, Preco_Curso)
VALUES
	(1, 'Excel'		, 100),
    (2, 'VBA'		, 200),
    (3, 'Power BI'	, 150);

SELECT * FROM dCursos;

INSERT INTO fMatriculas(ID_Matricula, ID_Aluno, ID_Curso, Data_Cadastro)
VALUES
	(1, 1, 1, '2021/03/11' ),
    (2, 1, 2, '2021/06/21' ),
    (3, 2, 3, '2021/01/08' ),
    (4, 3, 1, '2021/04/03' ),
    (5, 4, 1, '2021/05/10' ),
    (6, 4, 3, '2021/05/10' );

SELECT * FROM fMatriculas;

-- atualizando os dados das tabelas
SELECT * FROM dAlunos;
SELECT * FROM dCursos;
SELECT * FROM fMatriculas;

UPDATE dCursos
SET Preco_Curso = 300
WHERE ID_Curso = 1;

-- deletando os dados da tabela
SELECT * FROM fMatriculas;

DELETE FROM fMatriculas
WHERE ID_Matricula = 6;

-- TRUNCATE e DROP
TRUNCATE TABLE fMatriculas; -- exclui todos os dados da tabela, mas ela continua existindo
SELECT * FROM fMatriculas;
DROP TABLE fMatriculas; -- exclui todos os dados da tabela, inclusive ela
