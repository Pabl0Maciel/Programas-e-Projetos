USE mudancas;

-- Limpeza -----------------------
DROP TRIGGER   IF EXISTS trg_guindaste_disjuncao_ins;
DROP TRIGGER   IF EXISTS trg_guindaste_disjuncao_upd;
DROP TRIGGER   IF EXISTS trg_transporte_disjuncao_ins;
DROP TRIGGER   IF EXISTS trg_transporte_disjuncao_upd;
DROP TRIGGER   IF EXISTS trg_item_preco_ins;
DROP TRIGGER   IF EXISTS trg_item_preco_upd;
DROP TRIGGER   IF EXISTS trg_item_total_ins;
DROP TRIGGER   IF EXISTS trg_item_total_upd;
DROP TRIGGER   IF EXISTS trg_item_total_del;
DROP PROCEDURE IF EXISTS sp_recalcula_total_pedido;
DROP FUNCTION  IF EXISTS fn_preco_item;

DELIMITER $$

-- =====================================================================
-- RESTRIÇÃO 1: hierarquia PARCIAL e DISJUNTA
-- Um mesmo nome_servico não pode existir em GUINDASTE e TRANSPORTE ao
-- mesmo tempo. A tabela-por-subtipo garante o "parcial" (um serviço pode
-- não ter subtipo), mas a DISJUNÇÃO se perde -> reforçada por trigger.
-- =====================================================================

CREATE TRIGGER trg_guindaste_disjuncao_ins
BEFORE INSERT ON GUINDASTE
FOR EACH ROW
BEGIN
    IF EXISTS (SELECT 1 FROM TRANSPORTE WHERE nome_servico = NEW.nome_servico) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao violada: o servico ja e TRANSPORTE, nao pode ser GUINDASTE.';
    END IF;
END$$

CREATE TRIGGER trg_guindaste_disjuncao_upd
BEFORE UPDATE ON GUINDASTE
FOR EACH ROW
BEGIN
    IF EXISTS (SELECT 1 FROM TRANSPORTE WHERE nome_servico = NEW.nome_servico) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao violada: o servico ja e TRANSPORTE, nao pode ser GUINDASTE.';
    END IF;
END$$

CREATE TRIGGER trg_transporte_disjuncao_ins
BEFORE INSERT ON TRANSPORTE
FOR EACH ROW
BEGIN
    IF EXISTS (SELECT 1 FROM GUINDASTE WHERE nome_servico = NEW.nome_servico) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao violada: o servico ja e GUINDASTE, nao pode ser TRANSPORTE.';
    END IF;
END$$

CREATE TRIGGER trg_transporte_disjuncao_upd
BEFORE UPDATE ON TRANSPORTE
FOR EACH ROW
BEGIN
    IF EXISTS (SELECT 1 FROM GUINDASTE WHERE nome_servico = NEW.nome_servico) THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao violada: o servico ja e GUINDASTE, nao pode ser TRANSPORTE.';
    END IF;
END$$

-- =====================================================================
-- RESTRIÇÃO 2: preço de cada serviço (item)
-- Centraliza a fórmula numa FUNCTION reutilizável:
--   base = preco_hora(oferta) * horas(tempo_demorado)
--   + bonus_altura            se o servico for GUINDASTE
--   * (1 + percentual/100)    se for TRANSPORTE, usando a MAIOR regra
--                             cujo kg_limite a carga (peso) ultrapassa.
-- =====================================================================

CREATE FUNCTION fn_preco_item(
    p_empresa VARCHAR(100),
    p_servico VARCHAR(60),
    p_tempo   TIME,
    p_peso    DECIMAL(8,2)
) RETURNS DECIMAL(12,2)
NOT DETERMINISTIC
READS SQL DATA
BEGIN
    DECLARE v_preco_hora DECIMAL(10,2) DEFAULT 0;
    DECLARE v_horas      DECIMAL(12,4) DEFAULT 0;
    DECLARE v_preco      DECIMAL(16,4) DEFAULT 0;
    DECLARE v_bonus      DECIMAL(10,2) DEFAULT 0;
    DECLARE v_pct        DECIMAL(6,2)  DEFAULT 0;

    SELECT IFNULL(preco_hora, 0) INTO v_preco_hora
      FROM OFERTA_SERVICO
     WHERE nome_empresa = p_empresa
       AND nome_servico = p_servico;

    SET v_horas = IFNULL(TIME_TO_SEC(p_tempo) / 3600, 0);
    SET v_preco = v_preco_hora * v_horas;

    -- Guindaste: soma o bônus fixo (em R$)
    IF EXISTS (SELECT 1 FROM GUINDASTE WHERE nome_servico = p_servico) THEN
        SELECT IFNULL(bonus_altura, 0) INTO v_bonus
          FROM GUINDASTE WHERE nome_servico = p_servico;
        SET v_preco = v_preco + v_bonus;
    END IF;

    -- Transporte: aplica o maior percentual cujo kg_limite a carga ultrapassa
    IF EXISTS (SELECT 1 FROM TRANSPORTE WHERE nome_servico = p_servico) THEN
        SELECT IFNULL(MAX(percentual_acrescimo), 0) INTO v_pct
          FROM REGRA_ACRESCIMO_TRANSPORTE
         WHERE nome_empresa = p_empresa
           AND nome_servico_transporte = p_servico
           AND p_peso IS NOT NULL
           AND p_peso > kg_limite;
        SET v_preco = v_preco * (1 + v_pct / 100);
    END IF;

    RETURN ROUND(v_preco, 2);
END$$

-- O preco_servico passa a ser SEMPRE calculado pelo banco: qualquer valor
-- enviado no INSERT/UPDATE é sobrescrito pela fórmula (impede erro manual).
CREATE TRIGGER trg_item_preco_ins
BEFORE INSERT ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    SET NEW.preco_servico = fn_preco_item(
        NEW.nome_empresa_oferta, NEW.nome_servico_oferta,
        NEW.tempo_demorado, NEW.peso);
END$$

CREATE TRIGGER trg_item_preco_upd
BEFORE UPDATE ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    SET NEW.preco_servico = fn_preco_item(
        NEW.nome_empresa_oferta, NEW.nome_servico_oferta,
        NEW.tempo_demorado, NEW.peso);
END$$

-- =====================================================================
-- RESTRIÇÃO 3: preço total do pedido = soma dos itens
-- Procedure central recalcula o total de um pedido; os triggers de
-- INSERT/UPDATE/DELETE em ITEM_PEDIDO a disparam, mantendo tudo em dia.
-- =====================================================================

CREATE PROCEDURE sp_recalcula_total_pedido(IN p_cod INT)
MODIFIES SQL DATA
BEGIN
    UPDATE PEDIDO
       SET preco_total = (
            SELECT IFNULL(SUM(preco_servico), 0)
              FROM ITEM_PEDIDO
             WHERE cod_pedido = p_cod)
     WHERE cod_pedido = p_cod;
END$$

CREATE TRIGGER trg_item_total_ins
AFTER INSERT ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    CALL sp_recalcula_total_pedido(NEW.cod_pedido);
END$$

CREATE TRIGGER trg_item_total_upd
AFTER UPDATE ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    CALL sp_recalcula_total_pedido(NEW.cod_pedido);
    IF OLD.cod_pedido <> NEW.cod_pedido THEN
        CALL sp_recalcula_total_pedido(OLD.cod_pedido);
    END IF;
END$$

CREATE TRIGGER trg_item_total_del
AFTER DELETE ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    CALL sp_recalcula_total_pedido(OLD.cod_pedido);
END$$

DELIMITER ;