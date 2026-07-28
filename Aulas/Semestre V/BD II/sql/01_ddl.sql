-- =====================================================================
-- Trabalho BD2 - Empresas de Mudanças - PARTE 2 (ALINHADO AO GABARITO)
-- Etapa 1 (20%) - DDL: criação das tabelas e restrições. MySQL 8.0+.
-- =====================================================================
DROP DATABASE IF EXISTS mudancas;
CREATE DATABASE mudancas CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE mudancas;

CREATE TABLE CIDADE (
    estado      VARCHAR(2)   NOT NULL,
    nome_cidade VARCHAR(100) NOT NULL,
    PRIMARY KEY (estado, nome_cidade),
    CONSTRAINT chk_cidade_nome CHECK (CHAR_LENGTH(TRIM(nome_cidade)) > 0),
    CONSTRAINT chk_cidade_uf CHECK (estado IN (
        'AC','AL','AP','AM','BA','CE','DF','ES','GO','MA','MT','MS','MG','PA',
        'PB','PR','PE','PI','RJ','RN','RS','RO','RR','SC','SP','SE','TO'))
) ENGINE=InnoDB;

-- Empresa com CHAVE PRÓPRIA (id_empresa); nome é único.
CREATE TABLE EMPRESA (
    id_empresa INT          NOT NULL AUTO_INCREMENT,
    nome       VARCHAR(100) NOT NULL,
    endereco   VARCHAR(200),
    PRIMARY KEY (id_empresa),
    UNIQUE KEY uq_empresa_nome (nome),
    CONSTRAINT chk_empresa_nome CHECK (CHAR_LENGTH(TRIM(nome)) > 0)
) ENGINE=InnoDB;

CREATE TABLE CLIENTE (
    cod_cliente   INT          NOT NULL,
    cpf           VARCHAR(14)  NOT NULL,
    rg            VARCHAR(20),
    nome_completo VARCHAR(150) NOT NULL,
    endereco      VARCHAR(200),
    PRIMARY KEY (cod_cliente),
    UNIQUE KEY uq_cliente_cpf (cpf),
    CONSTRAINT chk_cliente_cpf  CHECK (CHAR_LENGTH(TRIM(cpf)) > 0),
    CONSTRAINT chk_cliente_nome CHECK (CHAR_LENGTH(TRIM(nome_completo)) > 0)
) ENGINE=InnoDB;

CREATE TABLE FUNCIONARIO (
    cpf              VARCHAR(14)   NOT NULL,
    rg               VARCHAR(20),
    salario          DECIMAL(10,2),
    tipo_funcionario VARCHAR(40),
    nome_completo    VARCHAR(150)  NOT NULL,
    endereco         VARCHAR(200),
    PRIMARY KEY (cpf),
    CONSTRAINT chk_func_salario CHECK (salario IS NULL OR salario >= 0),
    CONSTRAINT chk_func_cpf  CHECK (CHAR_LENGTH(TRIM(cpf)) > 0),
    CONSTRAINT chk_func_nome CHECK (CHAR_LENGTH(TRIM(nome_completo)) > 0)
) ENGINE=InnoDB;

-- Serviço com DISCRIMINADOR de tipo (hierarquia parcial e disjunta).
CREATE TABLE SERVICO (
    nome_servico VARCHAR(60) NOT NULL,
    tipo_servico VARCHAR(12) NOT NULL DEFAULT 'SIMPLES',
    PRIMARY KEY (nome_servico),
    CONSTRAINT chk_servico_nome CHECK (CHAR_LENGTH(TRIM(nome_servico)) > 0),
    CONSTRAINT chk_servico_tipo CHECK (tipo_servico IN ('SIMPLES','GUINDASTE','TRANSPORTE'))
) ENGINE=InnoDB;

CREATE TABLE TELEFONE_EMPRESA (
    id_tel_empresa INT NOT NULL AUTO_INCREMENT,
    id_empresa     INT NOT NULL,
    telefone       VARCHAR(20) NOT NULL,
    PRIMARY KEY (id_tel_empresa),
    UNIQUE KEY uq_tel_empresa (id_empresa, telefone),
    CONSTRAINT fk_telemp_empresa FOREIGN KEY (id_empresa)
        REFERENCES EMPRESA (id_empresa) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE TELEFONE_CLIENTE (
    id_tel_cliente INT NOT NULL AUTO_INCREMENT,
    cod_cliente    INT NOT NULL,
    telefone       VARCHAR(20) NOT NULL,
    PRIMARY KEY (id_tel_cliente),
    UNIQUE KEY uq_tel_cliente (cod_cliente, telefone),
    CONSTRAINT fk_telcli_cliente FOREIGN KEY (cod_cliente)
        REFERENCES CLIENTE (cod_cliente) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE TELEFONE_FUNCIONARIO (
    id_tel_func     INT NOT NULL AUTO_INCREMENT,
    cpf_funcionario VARCHAR(14) NOT NULL,
    telefone        VARCHAR(20) NOT NULL,
    PRIMARY KEY (id_tel_func),
    UNIQUE KEY uq_tel_func (cpf_funcionario, telefone),
    CONSTRAINT fk_telfun_func FOREIGN KEY (cpf_funcionario)
        REFERENCES FUNCIONARIO (cpf) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE GUINDASTE (
    nome_servico VARCHAR(60)   NOT NULL,
    tamanho_base DECIMAL(8,2),
    altura       DECIMAL(8,2),
    bonus_altura DECIMAL(10,2) NOT NULL DEFAULT 0,
    PRIMARY KEY (nome_servico),
    CONSTRAINT fk_guindaste_servico FOREIGN KEY (nome_servico)
        REFERENCES SERVICO (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT chk_guindaste_bonus CHECK (bonus_altura >= 0)
) ENGINE=InnoDB;

CREATE TABLE TRANSPORTE (
    nome_servico VARCHAR(60) NOT NULL,
    PRIMARY KEY (nome_servico),
    CONSTRAINT fk_transporte_servico FOREIGN KEY (nome_servico)
        REFERENCES SERVICO (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

-- OFERECEM: relacionamento TERNÁRIO empresa x serviço x cidade -> preco_hora.
-- (Substitui a antiga OFERTA_SERVICO + EMPRESA_ATUA_CIDADE.)
CREATE TABLE OFERECEM (
    id_oferta    INT           NOT NULL AUTO_INCREMENT,
    id_empresa   INT           NOT NULL,
    nome_servico VARCHAR(60)   NOT NULL,
    estado       VARCHAR(2)    NOT NULL,
    nome_cidade  VARCHAR(100)  NOT NULL,
    preco_hora   DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id_oferta),
    UNIQUE KEY uq_oferecem (id_empresa, nome_servico, estado, nome_cidade),
    CONSTRAINT fk_ofer_empresa FOREIGN KEY (id_empresa)
        REFERENCES EMPRESA (id_empresa) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_ofer_servico FOREIGN KEY (nome_servico)
        REFERENCES SERVICO (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_ofer_cidade FOREIGN KEY (estado, nome_cidade)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT chk_ofer_preco CHECK (preco_hora >= 0)
) ENGINE=InnoDB;

-- Acréscimo por SERVIÇO de transporte (padronizado por lei; sem empresa).
CREATE TABLE ACRESCIMO_TRANSPORTE (
    id_acrescimo            INT          NOT NULL AUTO_INCREMENT,
    nome_servico_transporte VARCHAR(60)  NOT NULL,
    percentual_acrescimo    DECIMAL(5,2) NOT NULL,
    kg_limite               DECIMAL(8,2) NOT NULL,
    PRIMARY KEY (id_acrescimo),
    UNIQUE KEY uq_acrescimo (nome_servico_transporte, kg_limite),
    CONSTRAINT fk_acresc_transporte FOREIGN KEY (nome_servico_transporte)
        REFERENCES TRANSPORTE (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT chk_acresc_pct CHECK (percentual_acrescimo >= 0),
    CONSTRAINT chk_acresc_kg  CHECK (kg_limite >= 0)
) ENGINE=InnoDB;

CREATE TABLE PEDIDO (
    cod_pedido       INT           NOT NULL,
    data_solicitacao DATE          NOT NULL,
    data_resolucao   DATE,
    status_aceitacao VARCHAR(12)   NOT NULL DEFAULT 'PENDENTE',
    preco_total      DECIMAL(12,2) NOT NULL DEFAULT 0,
    endereco_partida VARCHAR(200),
    endereco_destino VARCHAR(200),
    cod_cliente      INT           NOT NULL,
    id_empresa       INT           NOT NULL,
    estado_partida   VARCHAR(2)    NOT NULL,
    cidade_partida   VARCHAR(100)  NOT NULL,
    estado_destino   VARCHAR(2)    NOT NULL,
    cidade_destino   VARCHAR(100)  NOT NULL,
    PRIMARY KEY (cod_pedido),
    CONSTRAINT fk_pedido_cliente FOREIGN KEY (cod_cliente)
        REFERENCES CLIENTE (cod_cliente) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_empresa FOREIGN KEY (id_empresa)
        REFERENCES EMPRESA (id_empresa) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_cid_part FOREIGN KEY (estado_partida, cidade_partida)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_cid_dest FOREIGN KEY (estado_destino, cidade_destino)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT chk_pedido_status CHECK (status_aceitacao IN ('PENDENTE','ACEITO','REJEITADO')),
    CONSTRAINT chk_pedido_total  CHECK (preco_total >= 0),
    CONSTRAINT chk_pedido_datas  CHECK (data_resolucao IS NULL OR data_resolucao >= data_solicitacao)
) ENGINE=InnoDB;

-- ITEM_PEDIDO (Solicitam): referencia a OFERTA (fixa empresa+serviço+cidade+preço).
CREATE TABLE ITEM_PEDIDO (
    id_item         INT           NOT NULL,
    cod_pedido      INT           NOT NULL,
    id_oferta       INT           NOT NULL,
    preco_servico   DECIMAL(12,2) NOT NULL DEFAULT 0,
    tempo_demorado  TIME,
    data_realizacao DATE,
    peso            DECIMAL(8,2),
    PRIMARY KEY (id_item, cod_pedido),
    CONSTRAINT fk_item_pedido FOREIGN KEY (cod_pedido)
        REFERENCES PEDIDO (cod_pedido) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_item_oferta FOREIGN KEY (id_oferta)
        REFERENCES OFERECEM (id_oferta) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT chk_item_preco CHECK (preco_servico >= 0),
    CONSTRAINT chk_item_peso  CHECK (peso IS NULL OR peso >= 0)
) ENGINE=InnoDB;

CREATE TABLE TRABALHA (
    cpf_funcionario  VARCHAR(14) NOT NULL,
    id_empresa       INT         NOT NULL,
    horario          VARCHAR(50),
    telefone_empresa VARCHAR(20),
    PRIMARY KEY (cpf_funcionario, id_empresa),
    CONSTRAINT fk_trabalha_func FOREIGN KEY (cpf_funcionario)
        REFERENCES FUNCIONARIO (cpf) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_trabalha_empresa FOREIGN KEY (id_empresa)
        REFERENCES EMPRESA (id_empresa) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE EXECUTA (
    id_item         INT         NOT NULL,
    cod_pedido      INT         NOT NULL,
    cpf_funcionario VARCHAR(14) NOT NULL,
    PRIMARY KEY (id_item, cod_pedido, cpf_funcionario),
    CONSTRAINT fk_executa_item FOREIGN KEY (id_item, cod_pedido)
        REFERENCES ITEM_PEDIDO (id_item, cod_pedido) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_executa_func FOREIGN KEY (cpf_funcionario)
        REFERENCES FUNCIONARIO (cpf) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;