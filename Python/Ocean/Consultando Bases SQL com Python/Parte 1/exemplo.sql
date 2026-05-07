-- Link Notion: https://www.notion.so/SQL-2e942663f36f8013a6f8c42ca62c5fbe

CREATE DATABASE IF NOT EXISTS OCEAN;        -- Cria o database OCEAN

SHOW databases;                             -- Mostra os databases existentes

SHOW tables;                                -- Mostra as tabelas existentes

USE OCEAN;                                  -- Seleciona o database OCEAN para usar

-- Cria a tabela de alunos
CREATE TABLE IF NOT EXISTS ALUNOS(
    
    id_aluno INT PRIMARY KEY,               -- Cria o id_aluno como INT e Chave Primaria
    nome_aluno VARCHAR(50) NOT NULL,        -- Cria o nome_aluno como VARCHAR de tamanho maximo 50 e nao nulo
    nro_usp VARCHAR(20) UNIQUE,             -- Cria o nro_usp como VARCHAR de tamanho maximo 20 e unico
    altura DECIMAL(3,2)                     -- Cria o altura como DECIMAL de 3 digitos e duas casas depois da virgula
);

-- Cria a tabela de professores
CREATE TABLE IF NOT EXISTS PROFESSOR(

    id_professor INT PRIMARY KEY,           -- Cria o id_professor como INT e Chave Primaria
    nome_professor VARCHAR(50) NOT NULL,    -- Cria o nome_professor como VARCHAR de tamanho maximo 50 e nao nulo
    matricula VARCHAR(20) UNIQUE NOT NULL,  -- Cria o matricula como VARCHAR de tamanho maximo 20, unico e nao nulo
    email VARCHAR(50) NOT NULL              -- Cria o email como VARCHAR de tamanho maximo 50 e nao nulo

);

SHOW tables;

DESCRIBE ALUNOS;                            -- Descreve os campos da tabela de alunos
DESCRIBE PROFESSOR;                         -- Descreve os campos da tabela de professores

-- Altera a tabela de alunos, adicionando a coluna de naturalidade com valor padrao "brasileiro"
ALTER TABLE ALUNOS 
    ADD COLUMN naturalidade VARCHAR(20) NOT NULL DEFAULT "brasileiro";
        
DESCRIBE ALUNOS;

-- Altera a tabela de alunos e exclui a coluna naturalidade
ALTER TABLE ALUNOS
    DROP COLUMN naturalidade;
    
DESCRIBE ALUNOS;

-- Altera a tabela de alunos e adiciona id_professor
ALTER TABLE ALUNOS
    ADD COLUMN id_professor INT;
    
-- Altera a tabela de alunos e adiciona a constraint foreign key fk_professor na tabela de alunos, referenciando o id_professor da tabela professor
ALTER TABLE ALUNOS
    ADD CONSTRAINT fk_professor FOREIGN KEY(id_professor) REFERENCES PROFESSOR(id_professor);

-- Insere valores na tabela de professores
INSERT INTO PROFESSOR(id_professor, nome_professor, matricula, email) 
    VALUES (1, "Danilo", "987654321", "danilo@gmail.com");

-- Insere valores na tabela de alunos
INSERT INTO ALUNOS(id_aluno, nome_aluno, nro_usp, altura, id_professor) 
    VALUES (1, "Joao", "123456789", 1.71, 1);
    
SELECT * FROM ALUNOS;                       -- Seleciona tudo da tabela de alunos
