-- =====================================================================
-- PARTE 2 | Etapa 1 (20%) - Povoamento (alinhado ao gabarito)
-- =====================================================================
USE mudancas;

-- CIDADE
INSERT INTO CIDADE (estado, nome_cidade) VALUES
  ('SP', 'São Paulo'),
  ('SP', 'Campinas'),
  ('RJ', 'Rio de Janeiro'),
  ('MG', 'Belo Horizonte'),
  ('PR', 'Curitiba'),
  ('BA', 'Salvador'),
  ('RS', 'Porto Alegre'),
  ('SC', 'Florianópolis');

-- EMPRESA
INSERT INTO EMPRESA (id_empresa, nome, endereco) VALUES
  (1, 'Mudanças Rápidas', 'Av. Paulista, 1000 - São Paulo/SP'),
  (2, 'TransMudar', 'Rua das Flores, 250 - Belo Horizonte/MG'),
  (3, 'Carrega Tudo', 'Av. Atlântica, 500 - Rio de Janeiro/RJ'),
  (4, 'Mudou Fácil', 'Rua XV de Novembro, 80 - Curitiba/PR'),
  (5, 'GuinchoMax', 'Av. Beira Mar, 320 - Florianópolis/SC'),
  (6, 'Boa Mudança', 'Rua da Bahia, 145 - Salvador/BA');

-- CLIENTE
INSERT INTO CLIENTE (cod_cliente, cpf, rg, nome_completo, endereco) VALUES
  (1, '101.101.101-01', '11.101.101-1', 'Beatriz Fernandes', 'Rua das Acácias, 12 - São Paulo/SP'),
  (2, '202.202.202-02', '22.202.202-2', 'Rafael Gomes', 'Av. Brasil, 900 - Rio de Janeiro/RJ'),
  (3, '303.303.303-03', '33.303.303-3', 'Camila Ribeiro', 'Rua Minas, 45 - Belo Horizonte/MG'),
  (4, '404.404.404-04', '44.404.404-4', 'Thiago Martins', 'Rua Paraná, 210 - Curitiba/PR'),
  (5, '505.505.505-05', '55.505.505-5', 'Juliana Barbosa', 'Av. Oceânica, 33 - Salvador/BA'),
  (6, '606.606.606-06', '66.606.606-6', 'Marcelo Pinto', 'Rua Gaúcha, 77 - Porto Alegre/RS'),
  (7, '707.707.707-07', '77.707.707-7', 'Patrícia Nunes', 'Rua Ilha, 5 - Florianópolis/SC'),
  (8, '808.808.808-08', '88.808.808-8', 'Gustavo Teixeira', 'Rua Campinas, 300 - Campinas/SP');

-- FUNCIONARIO
INSERT INTO FUNCIONARIO (cpf, rg, salario, tipo_funcionario, nome_completo, endereco) VALUES
  ('111.111.111-11', '10.111.111-1', 2500.0, 'motorista', 'João Silva', 'Rua A, 10 - São Paulo/SP'),
  ('222.222.222-22', '20.222.222-2', 2200.0, 'ajudante', 'Pedro Souza', 'Rua B, 20 - São Paulo/SP'),
  ('333.333.333-33', '30.333.333-3', 4000.0, 'gerente', 'Maria Oliveira', 'Rua C, 30 - Rio de Janeiro/RJ'),
  ('444.444.444-44', '40.444.444-4', 2600.0, 'guincho', 'Carlos Lima', 'Rua D, 40 - Florianópolis/SC'),
  ('555.555.555-55', '50.555.555-5', 2300.0, 'motorista', 'Ana Costa', 'Rua E, 50 - Belo Horizonte/MG'),
  ('666.666.666-66', '60.666.666-6', 2100.0, 'ajudante', 'Lucas Alves', 'Rua F, 60 - Curitiba/PR'),
  ('777.777.777-77', '70.777.777-7', 2800.0, 'motorista', 'Fernanda Rocha', 'Rua G, 70 - Salvador/BA'),
  ('888.888.888-88', '80.888.888-8', 3500.0, 'gerente', 'Roberto Dias', 'Rua H, 80 - Porto Alegre/RS');

-- SERVICO
INSERT INTO SERVICO (nome_servico, tipo_servico) VALUES
  ('Transporte', 'TRANSPORTE'),
  ('Guindaste Pequeno', 'GUINDASTE'),
  ('Guindaste Grande', 'GUINDASTE'),
  ('Embalagem', 'SIMPLES'),
  ('Montagem', 'SIMPLES'),
  ('Desmontagem', 'SIMPLES');

-- TELEFONE_EMPRESA
INSERT INTO TELEFONE_EMPRESA (id_tel_empresa, id_empresa, telefone) VALUES
  (1, 1, '(11) 3000-1000'),
  (2, 2, '(31) 3000-2000'),
  (3, 3, '(21) 3000-3000'),
  (4, 4, '(41) 3000-4000'),
  (5, 5, '(48) 3000-5000'),
  (6, 6, '(71) 3000-6000');

-- TELEFONE_CLIENTE
INSERT INTO TELEFONE_CLIENTE (id_tel_cliente, cod_cliente, telefone) VALUES
  (1, 1, '(11) 90000-0001'),
  (2, 1, '(11) 90000-0011'),
  (3, 2, '(21) 90000-0002'),
  (4, 3, '(31) 90000-0003'),
  (5, 4, '(41) 90000-0004'),
  (6, 5, '(71) 90000-0005'),
  (7, 6, '(51) 90000-0006'),
  (8, 7, '(48) 90000-0007'),
  (9, 8, '(19) 90000-0008');

-- TELEFONE_FUNCIONARIO
INSERT INTO TELEFONE_FUNCIONARIO (id_tel_func, cpf_funcionario, telefone) VALUES
  (1, '111.111.111-11', '(11) 98000-0001'),
  (2, '222.222.222-22', '(11) 98000-0002'),
  (3, '333.333.333-33', '(21) 98000-0003'),
  (4, '444.444.444-44', '(48) 98000-0004'),
  (5, '555.555.555-55', '(31) 98000-0005'),
  (6, '666.666.666-66', '(41) 98000-0006'),
  (7, '777.777.777-77', '(71) 98000-0007'),
  (8, '888.888.888-88', '(51) 98000-0008');

-- GUINDASTE
INSERT INTO GUINDASTE (nome_servico, tamanho_base, altura, bonus_altura) VALUES
  ('Guindaste Pequeno', 3.0, 15.0, 100.0),
  ('Guindaste Grande', 6.0, 40.0, 500.0);

-- TRANSPORTE
INSERT INTO TRANSPORTE (nome_servico) VALUES
  ('Transporte');

-- OFERECEM
INSERT INTO OFERECEM (id_oferta, id_empresa, nome_servico, estado, nome_cidade, preco_hora) VALUES
  (1, 1, 'Transporte', 'SP', 'São Paulo', 120.0),
  (2, 1, 'Transporte', 'SP', 'Campinas', 120.0),
  (3, 1, 'Transporte', 'RJ', 'Rio de Janeiro', 120.0),
  (4, 1, 'Embalagem', 'SP', 'São Paulo', 60.0),
  (5, 1, 'Embalagem', 'SP', 'Campinas', 60.0),
  (6, 1, 'Embalagem', 'RJ', 'Rio de Janeiro', 60.0),
  (7, 1, 'Montagem', 'SP', 'São Paulo', 80.0),
  (8, 1, 'Montagem', 'SP', 'Campinas', 80.0),
  (9, 1, 'Montagem', 'RJ', 'Rio de Janeiro', 80.0),
  (10, 2, 'Transporte', 'SP', 'São Paulo', 100.0),
  (11, 2, 'Transporte', 'MG', 'Belo Horizonte', 100.0),
  (12, 2, 'Transporte', 'PR', 'Curitiba', 100.0),
  (13, 2, 'Desmontagem', 'SP', 'São Paulo', 70.0),
  (14, 2, 'Desmontagem', 'MG', 'Belo Horizonte', 70.0),
  (15, 2, 'Desmontagem', 'PR', 'Curitiba', 70.0),
  (16, 2, 'Montagem', 'SP', 'São Paulo', 75.0),
  (17, 2, 'Montagem', 'MG', 'Belo Horizonte', 75.0),
  (18, 2, 'Montagem', 'PR', 'Curitiba', 75.0),
  (19, 3, 'Transporte', 'RJ', 'Rio de Janeiro', 130.0),
  (20, 3, 'Transporte', 'BA', 'Salvador', 130.0),
  (21, 3, 'Transporte', 'SP', 'São Paulo', 130.0),
  (22, 3, 'Guindaste Pequeno', 'RJ', 'Rio de Janeiro', 200.0),
  (23, 3, 'Guindaste Pequeno', 'BA', 'Salvador', 200.0),
  (24, 3, 'Guindaste Pequeno', 'SP', 'São Paulo', 200.0),
  (25, 3, 'Embalagem', 'RJ', 'Rio de Janeiro', 55.0),
  (26, 3, 'Embalagem', 'BA', 'Salvador', 55.0),
  (27, 3, 'Embalagem', 'SP', 'São Paulo', 55.0),
  (28, 4, 'Transporte', 'SP', 'Campinas', 110.0),
  (29, 4, 'Transporte', 'PR', 'Curitiba', 110.0),
  (30, 4, 'Transporte', 'RS', 'Porto Alegre', 110.0),
  (31, 4, 'Embalagem', 'SP', 'Campinas', 65.0),
  (32, 4, 'Embalagem', 'PR', 'Curitiba', 65.0),
  (33, 4, 'Embalagem', 'RS', 'Porto Alegre', 65.0),
  (34, 4, 'Montagem', 'SP', 'Campinas', 85.0),
  (35, 4, 'Montagem', 'PR', 'Curitiba', 85.0),
  (36, 4, 'Montagem', 'RS', 'Porto Alegre', 85.0),
  (37, 4, 'Desmontagem', 'SP', 'Campinas', 70.0),
  (38, 4, 'Desmontagem', 'PR', 'Curitiba', 70.0),
  (39, 4, 'Desmontagem', 'RS', 'Porto Alegre', 70.0),
  (40, 5, 'Guindaste Pequeno', 'SP', 'São Paulo', 220.0),
  (41, 5, 'Guindaste Pequeno', 'SC', 'Florianópolis', 220.0),
  (42, 5, 'Guindaste Pequeno', 'RJ', 'Rio de Janeiro', 220.0),
  (43, 5, 'Guindaste Grande', 'SP', 'São Paulo', 450.0),
  (44, 5, 'Guindaste Grande', 'SC', 'Florianópolis', 450.0),
  (45, 5, 'Guindaste Grande', 'RJ', 'Rio de Janeiro', 450.0),
  (46, 5, 'Transporte', 'SP', 'São Paulo', 140.0),
  (47, 5, 'Transporte', 'SC', 'Florianópolis', 140.0),
  (48, 5, 'Transporte', 'RJ', 'Rio de Janeiro', 140.0),
  (49, 6, 'Transporte', 'MG', 'Belo Horizonte', 95.0),
  (50, 6, 'Transporte', 'BA', 'Salvador', 95.0),
  (51, 6, 'Transporte', 'RS', 'Porto Alegre', 95.0),
  (52, 6, 'Embalagem', 'MG', 'Belo Horizonte', 50.0),
  (53, 6, 'Embalagem', 'BA', 'Salvador', 50.0),
  (54, 6, 'Embalagem', 'RS', 'Porto Alegre', 50.0),
  (55, 6, 'Montagem', 'MG', 'Belo Horizonte', 70.0),
  (56, 6, 'Montagem', 'BA', 'Salvador', 70.0),
  (57, 6, 'Montagem', 'RS', 'Porto Alegre', 70.0);

-- ACRESCIMO_TRANSPORTE
INSERT INTO ACRESCIMO_TRANSPORTE (id_acrescimo, nome_servico_transporte, percentual_acrescimo, kg_limite) VALUES
  (1, 'Transporte', 10.0, 500.0),
  (2, 'Transporte', 15.0, 1000.0);

-- TRABALHA
INSERT INTO TRABALHA (cpf_funcionario, id_empresa, horario, telefone_empresa) VALUES
  ('111.111.111-11', 1, '08:00-17:00', '(11) 3000-1000'),
  ('111.111.111-11', 3, '18:00-22:00', '(21) 3000-3000'),
  ('222.222.222-22', 1, '08:00-17:00', '(11) 3000-1000'),
  ('222.222.222-22', 2, '07:00-12:00', '(31) 3000-2000'),
  ('333.333.333-33', 3, '09:00-18:00', '(21) 3000-3000'),
  ('444.444.444-44', 5, '07:00-16:00', '(48) 3000-5000'),
  ('555.555.555-55', 2, '08:00-17:00', '(31) 3000-2000'),
  ('666.666.666-66', 4, '08:00-17:00', '(41) 3000-4000'),
  ('777.777.777-77', 6, '08:00-17:00', '(71) 3000-6000'),
  ('777.777.777-77', 3, '19:00-23:00', '(21) 3000-3000'),
  ('888.888.888-88', 4, '10:00-19:00', '(41) 3000-4000'),
  ('888.888.888-88', 6, '07:00-11:00', '(71) 3000-6000');

-- PEDIDO
INSERT INTO PEDIDO (cod_pedido, data_solicitacao, data_resolucao, status_aceitacao, preco_total, endereco_partida, endereco_destino, cod_cliente, id_empresa, estado_partida, cidade_partida, estado_destino, cidade_destino) VALUES
  (1, '2026-05-01', '2026-05-03', 'ACEITO', 648.0, 'Rua das Acácias, 12', 'Av. Brasil, 45', 1, 1, 'SP', 'São Paulo', 'SP', 'Campinas'),
  (2, '2026-05-04', '2026-05-06', 'ACEITO', 1068.0, 'Rua Campinas, 300', 'Praça Central, 1', 8, 1, 'SP', 'Campinas', 'SP', 'São Paulo'),
  (3, '2026-05-05', '2026-05-07', 'ACEITO', 1315.0, 'Av. Brasil, 900', 'Rua do Porto, 10', 2, 3, 'RJ', 'Rio de Janeiro', 'RJ', 'Rio de Janeiro'),
  (4, '2026-05-10', '2026-05-12', 'ACEITO', 1144.0, 'Av. Oceânica, 33', 'Rua Nova, 55', 5, 3, 'BA', 'Salvador', 'BA', 'Salvador'),
  (5, '2026-05-06', '2026-05-08', 'ACEITO', 470.0, 'Rua Minas, 45', 'Av. Afonso Pena, 200', 3, 2, 'MG', 'Belo Horizonte', 'MG', 'Belo Horizonte'),
  (6, '2026-05-11', '2026-05-13', 'ACEITO', 550.0, 'Rua Paraná, 210', 'Rua Sete, 9', 4, 2, 'PR', 'Curitiba', 'PR', 'Curitiba'),
  (7, '2026-05-12', '2026-05-14', 'ACEITO', 805.0, 'Rua Gaúcha, 77', 'Av. Ipiranga, 300', 6, 4, 'RS', 'Porto Alegre', 'RS', 'Porto Alegre'),
  (8, '2026-05-15', '2026-05-17', 'ACEITO', 670.0, 'Rua Paraná, 210', 'Rua das Araucárias, 8', 4, 4, 'PR', 'Curitiba', 'PR', 'Curitiba'),
  (9, '2026-05-13', '2026-05-15', 'ACEITO', 2466.0, 'Rua Ilha, 5', 'Av. Central, 120', 7, 5, 'SC', 'Florianópolis', 'SC', 'Florianópolis'),
  (10, '2026-05-18', '2026-05-20', 'ACEITO', 540.0, 'Rua das Acácias, 12', 'Av. Rio Branco, 400', 1, 5, 'SP', 'São Paulo', 'RJ', 'Rio de Janeiro'),
  (11, '2026-05-16', '2026-05-18', 'ACEITO', 917.0, 'Av. Oceânica, 33', 'Rua do Farol, 2', 5, 6, 'BA', 'Salvador', 'BA', 'Salvador'),
  (12, '2026-05-19', '2026-05-21', 'ACEITO', 380.0, 'Rua Gaúcha, 77', 'Av. Assis Brasil, 900', 6, 6, 'RS', 'Porto Alegre', 'RS', 'Porto Alegre'),
  (13, '2026-05-22', NULL, 'PENDENTE', 780.0, 'Av. Brasil, 900', 'Rua Verde, 30', 2, 1, 'RJ', 'Rio de Janeiro', 'SP', 'São Paulo'),
  (14, '2026-05-20', '2026-05-21', 'REJEITADO', 1495.0, 'Rua Minas, 45', 'Av. Litorânea, 50', 3, 3, 'SP', 'São Paulo', 'BA', 'Salvador');

-- ITEM_PEDIDO
INSERT INTO ITEM_PEDIDO (id_item, cod_pedido, id_oferta, preco_servico, tempo_demorado, data_realizacao, peso) VALUES
  (1, 1, 1, 528.0, '04:00:00', '2026-05-05', 600),
  (2, 1, 4, 120.0, '02:00:00', '2026-05-05', NULL),
  (1, 2, 2, 828.0, '06:00:00', '2026-05-08', 1200),
  (2, 2, 8, 240.0, '03:00:00', '2026-05-08', NULL),
  (1, 3, 19, 650.0, '05:00:00', '2026-05-09', 350),
  (2, 3, 22, 500.0, '02:00:00', '2026-05-09', NULL),
  (3, 3, 25, 165.0, '03:00:00', '2026-05-09', NULL),
  (1, 4, 20, 1144.0, '08:00:00', '2026-05-14', 900),
  (1, 5, 11, 330.0, '03:00:00', '2026-05-10', 650),
  (2, 5, 14, 140.0, '02:00:00', '2026-05-10', NULL),
  (1, 6, 12, 400.0, '04:00:00', '2026-05-15', 500),
  (2, 6, 18, 150.0, '02:00:00', '2026-05-15', NULL),
  (1, 7, 30, 605.0, '05:00:00', '2026-05-16', 700),
  (2, 7, 33, 130.0, '02:00:00', '2026-05-16', NULL),
  (3, 7, 39, 70.0, '01:00:00', '2026-05-16', NULL),
  (1, 8, 29, 330.0, '03:00:00', '2026-05-19', 300),
  (2, 8, 35, 340.0, '04:00:00', '2026-05-19', NULL),
  (1, 9, 44, 1850.0, '03:00:00', '2026-05-17', NULL),
  (2, 9, 47, 616.0, '04:00:00', '2026-05-17', 800),
  (1, 10, 40, 540.0, '02:00:00', '2026-05-22', NULL),
  (1, 11, 50, 627.0, '06:00:00', '2026-05-20', 650),
  (2, 11, 53, 150.0, '03:00:00', '2026-05-20', NULL),
  (3, 11, 56, 140.0, '02:00:00', '2026-05-20', NULL),
  (1, 12, 51, 380.0, '04:00:00', '2026-05-23', 250),
  (1, 13, 3, 660.0, '05:00:00', NULL, 550),
  (2, 13, 6, 120.0, '02:00:00', NULL, NULL),
  (1, 14, 21, 1495.0, '10:00:00', NULL, 1500);

-- EXECUTA
INSERT INTO EXECUTA (id_item, cod_pedido, cpf_funcionario) VALUES
  (1, 1, '111.111.111-11'),
  (1, 1, '222.222.222-22'),
  (2, 1, '222.222.222-22'),
  (1, 2, '111.111.111-11'),
  (2, 2, '222.222.222-22'),
  (1, 3, '333.333.333-33'),
  (2, 3, '111.111.111-11'),
  (2, 3, '333.333.333-33'),
  (3, 3, '777.777.777-77'),
  (1, 4, '333.333.333-33'),
  (1, 4, '777.777.777-77'),
  (1, 5, '555.555.555-55'),
  (2, 5, '555.555.555-55'),
  (1, 6, '222.222.222-22'),
  (1, 6, '555.555.555-55'),
  (2, 6, '555.555.555-55'),
  (1, 7, '888.888.888-88'),
  (2, 7, '666.666.666-66'),
  (3, 7, '666.666.666-66'),
  (1, 8, '666.666.666-66'),
  (2, 8, '666.666.666-66'),
  (2, 8, '888.888.888-88'),
  (1, 9, '444.444.444-44'),
  (2, 9, '444.444.444-44'),
  (1, 10, '444.444.444-44'),
  (1, 11, '777.777.777-77'),
  (1, 11, '888.888.888-88'),
  (2, 11, '777.777.777-77'),
  (3, 11, '888.888.888-88'),
  (1, 12, '888.888.888-88');