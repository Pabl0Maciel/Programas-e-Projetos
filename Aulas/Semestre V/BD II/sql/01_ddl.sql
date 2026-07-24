DROP DATABASE IF EXISTS mudancas;
CREATE DATABASE mudancas CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE mudancas;

-- ------------------------- Cadastros base ----------------------------

CREATE TABLE CIDADE (
    estado      VARCHAR(2)   NOT NULL,
    nome_cidade VARCHAR(100) NOT NULL,
    PRIMARY KEY (estado, nome_cidade)
) ENGINE=InnoDB;

CREATE TABLE CLIENTE (
    cod_cliente   INT          NOT NULL,
    cpf           VARCHAR(14)  NOT NULL,
    rg            VARCHAR(20),
    nome_completo VARCHAR(150) NOT NULL,
    endereco      VARCHAR(200),
    PRIMARY KEY (cod_cliente),
    UNIQUE KEY uq_cliente_cpf (cpf)
) ENGINE=InnoDB;

CREATE TABLE EMPRESA (
    nome     VARCHAR(100) NOT NULL,
    endereco VARCHAR(200),
    PRIMARY KEY (nome)
) ENGINE=InnoDB;

CREATE TABLE FUNCIONARIO (
    cpf              VARCHAR(14)   NOT NULL,
    rg               VARCHAR(20),
    salario          DECIMAL(10,2),
    tipo_funcionario VARCHAR(40),
    nome_completo    VARCHAR(150)  NOT NULL,
    endereco         VARCHAR(200),
    PRIMARY KEY (cpf),
    CONSTRAINT chk_func_salario CHECK (salario IS NULL OR salario >= 0)
) ENGINE=InnoDB;

CREATE TABLE SERVICO (
    nome_servico VARCHAR(60) NOT NULL,
    PRIMARY KEY (nome_servico)
) ENGINE=InnoDB;

-- ------------------------ Telefones (multivalorados) -----------------

CREATE TABLE TELEFONE_CLIENTE (
    telefone    VARCHAR(20) NOT NULL,
    cod_cliente INT         NOT NULL,
    PRIMARY KEY (telefone, cod_cliente),
    CONSTRAINT fk_telcli_cliente FOREIGN KEY (cod_cliente)
        REFERENCES CLIENTE (cod_cliente) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE TELEFONE_EMPRESA (
    telefone     VARCHAR(20)  NOT NULL,
    nome_empresa VARCHAR(100) NOT NULL,
    PRIMARY KEY (telefone, nome_empresa),
    CONSTRAINT fk_telemp_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

CREATE TABLE TELEFONE_FUNCIONARIO (
    telefone        VARCHAR(20) NOT NULL,
    cpf_funcionario VARCHAR(14) NOT NULL,
    PRIMARY KEY (telefone, cpf_funcionario),
    CONSTRAINT fk_telfun_func FOREIGN KEY (cpf_funcionario)
        REFERENCES FUNCIONARIO (cpf) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB;

-- ------------------ Hierarquia de serviço (parcial, disjunta) --------

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

-- ------------------ Oferta / atuação / regras ------------------------

CREATE TABLE OFERTA_SERVICO (
    nome_empresa VARCHAR(100)  NOT NULL,
    nome_servico VARCHAR(60)   NOT NULL,
    preco_hora   DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (nome_empresa, nome_servico),
    CONSTRAINT fk_oferta_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_oferta_servico FOREIGN KEY (nome_servico)
        REFERENCES SERVICO (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT chk_oferta_preco CHECK (preco_hora >= 0)
) ENGINE=InnoDB;

CREATE TABLE EMPRESA_ATUA_CIDADE (
    nome_empresa VARCHAR(100) NOT NULL,
    estado       VARCHAR(2)   NOT NULL,
    nome_cidade  VARCHAR(100) NOT NULL,
    PRIMARY KEY (nome_empresa, estado, nome_cidade),
    CONSTRAINT fk_atua_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_atua_cidade FOREIGN KEY (estado, nome_cidade)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT
) ENGINE=InnoDB;

CREATE TABLE REGRA_ACRESCIMO_TRANSPORTE (
    id_regra                INT          NOT NULL,
    nome_empresa            VARCHAR(100) NOT NULL,
    nome_servico_transporte VARCHAR(60)  NOT NULL,
    percentual_acrescimo    DECIMAL(5,2) NOT NULL,
    kg_limite               DECIMAL(8,2) NOT NULL,
    PRIMARY KEY (id_regra),
    UNIQUE KEY uq_regra (nome_empresa, nome_servico_transporte, kg_limite),
    CONSTRAINT fk_regra_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_regra_transporte FOREIGN KEY (nome_servico_transporte)
        REFERENCES TRANSPORTE (nome_servico) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT chk_regra_pct CHECK (percentual_acrescimo >= 0),
    CONSTRAINT chk_regra_kg  CHECK (kg_limite >= 0)
) ENGINE=InnoDB;

-- ------------------------ Pedido e execução --------------------------

CREATE TABLE PEDIDO (
    cod_pedido       INT           NOT NULL,
    data_solicitacao DATE          NOT NULL,
    data_resolucao   DATE,
    status_aceitacao VARCHAR(12)   NOT NULL DEFAULT 'PENDENTE',
    preco_total      DECIMAL(12,2) NOT NULL DEFAULT 0,
    endereco_partida VARCHAR(200),
    endereco_destino VARCHAR(200),
    cod_cliente      INT           NOT NULL,
    nome_empresa     VARCHAR(100)  NOT NULL,
    estado_partida   VARCHAR(2)    NOT NULL,
    cidade_partida   VARCHAR(100)  NOT NULL,
    estado_destino   VARCHAR(2)    NOT NULL,
    cidade_destino   VARCHAR(100)  NOT NULL,
    PRIMARY KEY (cod_pedido),
    CONSTRAINT fk_pedido_cliente FOREIGN KEY (cod_cliente)
        REFERENCES CLIENTE (cod_cliente) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_cid_part FOREIGN KEY (estado_partida, cidade_partida)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT fk_pedido_cid_dest FOREIGN KEY (estado_destino, cidade_destino)
        REFERENCES CIDADE (estado, nome_cidade) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT chk_pedido_status CHECK (status_aceitacao IN ('PENDENTE','ACEITO','REJEITADO')),
    CONSTRAINT chk_pedido_total  CHECK (preco_total >= 0),
    CONSTRAINT chk_pedido_datas  CHECK (data_resolucao IS NULL OR data_resolucao >= data_solicitacao)
) ENGINE=InnoDB;

CREATE TABLE ITEM_PEDIDO (
    id_item             INT           NOT NULL,
    cod_pedido          INT           NOT NULL,
    preco_servico       DECIMAL(12,2) NOT NULL DEFAULT 0,
    tempo_demorado      TIME,
    data_realizacao     DATE,
    peso                DECIMAL(8,2),          -- ADIÇÃO à Parte 1: peso da carga (necessário p/ o acréscimo de transporte)
    nome_empresa_oferta VARCHAR(100)  NOT NULL,
    nome_servico_oferta VARCHAR(60)   NOT NULL,
    PRIMARY KEY (id_item, cod_pedido),
    CONSTRAINT fk_item_pedido FOREIGN KEY (cod_pedido)
        REFERENCES PEDIDO (cod_pedido) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_item_oferta FOREIGN KEY (nome_empresa_oferta, nome_servico_oferta)
        REFERENCES OFERTA_SERVICO (nome_empresa, nome_servico) ON UPDATE CASCADE ON DELETE RESTRICT,
    CONSTRAINT chk_item_preco CHECK (preco_servico >= 0),
    CONSTRAINT chk_item_peso  CHECK (peso IS NULL OR peso >= 0)
) ENGINE=InnoDB;

CREATE TABLE TRABALHA (
    cpf_funcionario  VARCHAR(14)  NOT NULL,
    nome_empresa     VARCHAR(100) NOT NULL,
    horario          VARCHAR(50),
    telefone_empresa VARCHAR(20),
    PRIMARY KEY (cpf_funcionario, nome_empresa),
    CONSTRAINT fk_trabalha_func FOREIGN KEY (cpf_funcionario)
        REFERENCES FUNCIONARIO (cpf) ON UPDATE CASCADE ON DELETE CASCADE,
    CONSTRAINT fk_trabalha_empresa FOREIGN KEY (nome_empresa)
        REFERENCES EMPRESA (nome) ON UPDATE CASCADE ON DELETE CASCADE
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
