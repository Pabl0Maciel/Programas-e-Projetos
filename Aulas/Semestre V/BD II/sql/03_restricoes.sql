-- =====================================================================
-- Trabalho BD2 - Empresas de Mudanças - PARTE 2 (ALINHADO AO GABARITO)
-- Etapa 2 (30%) - Restrições perdidas no mapeamento (triggers/procedures)
-- =====================================================================
USE mudancas;

DROP TRIGGER   IF EXISTS trg_guindaste_tipo_ins;
DROP TRIGGER   IF EXISTS trg_guindaste_tipo_upd;
DROP TRIGGER   IF EXISTS trg_transporte_tipo_ins;
DROP TRIGGER   IF EXISTS trg_transporte_tipo_upd;
DROP TRIGGER   IF EXISTS trg_item_bi;
DROP TRIGGER   IF EXISTS trg_item_bu;
DROP TRIGGER   IF EXISTS trg_item_total_ins;
DROP TRIGGER   IF EXISTS trg_item_total_upd;
DROP TRIGGER   IF EXISTS trg_item_total_del;
DROP PROCEDURE IF EXISTS sp_recalcula_total_pedido;
DROP FUNCTION  IF EXISTS fn_preco_item;

DELIMITER $$

-- =====================================================================
-- RESTRIÇÃO 1: hierarquia PARCIAL e DISJUNTA (via discriminador tipo_servico)
-- Um serviço só entra em GUINDASTE se seu tipo for 'GUINDASTE', e em
-- TRANSPORTE se for 'TRANSPORTE'. Como tipo_servico é único por serviço,
-- isso garante a disjunção (não pode ser guindaste e transporte ao mesmo tempo).
-- =====================================================================
CREATE TRIGGER trg_guindaste_tipo_ins
BEFORE INSERT ON GUINDASTE
FOR EACH ROW
BEGIN
    IF (SELECT tipo_servico FROM SERVICO WHERE nome_servico = NEW.nome_servico) <> 'GUINDASTE' THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao: o servico precisa ter tipo_servico = GUINDASTE.';
    END IF;
END$$

CREATE TRIGGER trg_guindaste_tipo_upd
BEFORE UPDATE ON GUINDASTE
FOR EACH ROW
BEGIN
    IF (SELECT tipo_servico FROM SERVICO WHERE nome_servico = NEW.nome_servico) <> 'GUINDASTE' THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao: o servico precisa ter tipo_servico = GUINDASTE.';
    END IF;
END$$

CREATE TRIGGER trg_transporte_tipo_ins
BEFORE INSERT ON TRANSPORTE
FOR EACH ROW
BEGIN
    IF (SELECT tipo_servico FROM SERVICO WHERE nome_servico = NEW.nome_servico) <> 'TRANSPORTE' THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao: o servico precisa ter tipo_servico = TRANSPORTE.';
    END IF;
END$$

CREATE TRIGGER trg_transporte_tipo_upd
BEFORE UPDATE ON TRANSPORTE
FOR EACH ROW
BEGIN
    IF (SELECT tipo_servico FROM SERVICO WHERE nome_servico = NEW.nome_servico) <> 'TRANSPORTE' THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'Disjuncao: o servico precisa ter tipo_servico = TRANSPORTE.';
    END IF;
END$$

-- =====================================================================
-- RESTRIÇÃO 2: preço de cada serviço (item), a partir da OFERTA
--   base = preco_hora(oferta) * horas
--        + bonus_altura            se o serviço for GUINDASTE
--        * (1 + percentual/100)    se for TRANSPORTE (maior regra cujo
--                                   kg_limite a carga ultrapassa)
-- A oferta (id_oferta) fixa empresa+serviço+cidade+preço/hora.
-- =====================================================================
CREATE FUNCTION fn_preco_item(p_id_oferta INT, p_tempo TIME, p_peso DECIMAL(8,2))
RETURNS DECIMAL(12,2)
NOT DETERMINISTIC
READS SQL DATA
BEGIN
    DECLARE v_ph    DECIMAL(10,2) DEFAULT 0;
    DECLARE v_serv  VARCHAR(60);
    DECLARE v_horas DECIMAL(12,4) DEFAULT 0;
    DECLARE v_preco DECIMAL(16,4) DEFAULT 0;
    DECLARE v_bonus DECIMAL(10,2) DEFAULT 0;
    DECLARE v_pct   DECIMAL(6,2)  DEFAULT 0;

    SELECT preco_hora, nome_servico INTO v_ph, v_serv
      FROM OFERECEM WHERE id_oferta = p_id_oferta;

    SET v_horas = IFNULL(TIME_TO_SEC(p_tempo) / 3600, 0);
    SET v_preco = IFNULL(v_ph, 0) * v_horas;

    IF EXISTS (SELECT 1 FROM GUINDASTE WHERE nome_servico = v_serv) THEN
        SELECT IFNULL(bonus_altura, 0) INTO v_bonus FROM GUINDASTE WHERE nome_servico = v_serv;
        SET v_preco = v_preco + v_bonus;
    END IF;

    IF EXISTS (SELECT 1 FROM TRANSPORTE WHERE nome_servico = v_serv) THEN
        SELECT IFNULL(MAX(percentual_acrescimo), 0) INTO v_pct
          FROM ACRESCIMO_TRANSPORTE
         WHERE nome_servico_transporte = v_serv
           AND p_peso IS NOT NULL
           AND p_peso > kg_limite;
        SET v_preco = v_preco * (1 + v_pct / 100);
    END IF;

    RETURN ROUND(v_preco, 2);
END$$

-- BEFORE INSERT: valida coerência (oferta pertence à empresa do pedido) e grava o preço.
CREATE TRIGGER trg_item_bi
BEFORE INSERT ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    DECLARE v_emp_ofer INT;
    DECLARE v_emp_ped  INT;
    SELECT id_empresa INTO v_emp_ofer FROM OFERECEM WHERE id_oferta  = NEW.id_oferta;
    SELECT id_empresa INTO v_emp_ped  FROM PEDIDO   WHERE cod_pedido = NEW.cod_pedido;
    IF v_emp_ofer <> v_emp_ped THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'A oferta do item nao pertence a empresa do pedido.';
    END IF;
    SET NEW.preco_servico = fn_preco_item(NEW.id_oferta, NEW.tempo_demorado, NEW.peso);
END$$

CREATE TRIGGER trg_item_bu
BEFORE UPDATE ON ITEM_PEDIDO
FOR EACH ROW
BEGIN
    SET NEW.preco_servico = fn_preco_item(NEW.id_oferta, NEW.tempo_demorado, NEW.peso);
END$$

-- =====================================================================
-- RESTRIÇÃO 3: preço total do pedido = soma dos itens (mantido por triggers)
-- =====================================================================
CREATE PROCEDURE sp_recalcula_total_pedido(IN p_cod INT)
MODIFIES SQL DATA
BEGIN
    UPDATE PEDIDO
       SET preco_total = (SELECT IFNULL(SUM(preco_servico), 0)
                            FROM ITEM_PEDIDO WHERE cod_pedido = p_cod)
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