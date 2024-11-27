-- EX 1:
DELIMITER $$

CREATE PROCEDURE sp_AtualizaPreco(NovoPreco DECIMAL(10,2), ID INT)
BEGIN
	-- fazendo update do preco do curso
	UPDATE dCursos
    SET Preco_Curso = NovoPreco
    WHERE ID_Curso = ID;
    
    SELECT 'Preco atualizado com sucesso';
END $$
DELIMITER ;

SELECT * FROM dcursos;

CALL sp_AtualizaPreco(400, 1);
CALL sp_AtualizaPreco(600, 2);
CALL sp_AtualizaPreco(360, 3);

-- EX 2:
DELIMITER $$

CREATE PROCEDURE sp_AplicaDesconto(Desconto DECIMAL(10,2), ID INT)
BEGIN
	DECLARE varPrecoComDesconto DECIMAL(10, 2);
    DECLARE varNomeCurso VARCHAR(100);
    DECLARE varPrecoAntigo DECIMAL(10, 2);
    
    SET varPrecoAntigo = (SELECT Preco_Curso FROM dCursos WHERE ID_Curso = ID);
    SET varPrecoComDesconto = varPrecoAntigo * (1 - Desconto);
    SET varNomeCurso = (SELECT Nome_Curso FROM dCursos WHERE ID_Curso = ID);
    
    UPDATE dCursos
    SET Preco_Curso = varPrecoComDesconto
    WHERE ID_Curso = ID;
    
    SELECT CONCAT('Desconto de ', Desconto, ' aplicado com sucesso');
    SELECT CONCAT('Curso: ', varNomeCurso, ' ; Preco antigo = ', varPrecoAntigo, '; Preco Novo = ', varPrecoComDesconto);
    SELECT 'Codigo executado com Sucesso!';
    
END $$
DELIMITER ;

CALL sp_AplicaDesconto(0.5, 1);
CALL sp_AplicaDesconto(0.25, 2);
CALL sp_AplicaDesconto(0.5, 3);

SELECT * FROM dCursos;
