USE mudancas;
SET FOREIGN_KEY_CHECKS = 1;

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

-- EMPRESA
INSERT INTO EMPRESA (nome, endereco) VALUES
  ('Mudanças Rápidas', 'Av. Paulista, 1000 - São Paulo/SP'),
  ('TransMudar', 'Rua das Flores, 250 - Belo Horizonte/MG'),
  ('Carrega Tudo', 'Av. Atlântica, 500 - Rio de Janeiro/RJ'),
  ('Mudou Fácil', 'Rua XV de Novembro, 80 - Curitiba/PR'),
  ('GuinchoMax', 'Av. Beira Mar, 320 - Florianópolis/SC'),
  ('Boa Mudança', 'Rua da Bahia, 145 - Salvador/BA');

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
INSERT INTO SERVICO (nome_servico) VALUES
  ('Transporte'),
  ('Guindaste Pequeno'),
  ('Guindaste Grande'),
  ('Embalagem'),
  ('Montagem'),
  ('Desmontagem');

-- TELEFONE_CLIENTE
INSERT INTO TELEFONE_CLIENTE (telefone, cod_cliente) VALUES
  ('(11) 90000-0001', 1),
  ('(11) 90000-0011', 1),
  ('(21) 90000-0002', 2),
  ('(31) 90000-0003', 3),
  ('(41) 90000-0004', 4),
  ('(71) 90000-0005', 5),
  ('(51) 90000-0006', 6),
  ('(48) 90000-0007', 7),
  ('(19) 90000-0008', 8);

-- TELEFONE_EMPRESA
INSERT INTO TELEFONE_EMPRESA (telefone, nome_empresa) VALUES
  ('(11) 3000-1000', 'Mudanças Rápidas'),
  ('(31) 3000-2000', 'TransMudar'),
  ('(21) 3000-3000', 'Carrega Tudo'),
  ('(41) 3000-4000', 'Mudou Fácil'),
  ('(48) 3000-5000', 'GuinchoMax'),
  ('(71) 3000-6000', 'Boa Mudança');

-- TELEFONE_FUNCIONARIO
INSERT INTO TELEFONE_FUNCIONARIO (telefone, cpf_funcionario) VALUES
  ('(11) 98000-0001', '111.111.111-11'),
  ('(11) 98000-0002', '222.222.222-22'),
  ('(21) 98000-0003', '333.333.333-33'),
  ('(48) 98000-0004', '444.444.444-44'),
  ('(31) 98000-0005', '555.555.555-55'),
  ('(41) 98000-0006', '666.666.666-66'),
  ('(71) 98000-0007', '777.777.777-77'),
  ('(51) 98000-0008', '888.888.888-88');

-- GUINDASTE (subtipo)
INSERT INTO GUINDASTE (nome_servico, tamanho_base, altura, bonus_altura) VALUES
  ('Guindaste Pequeno', 3.0, 15.0, 100.0),
  ('Guindaste Grande', 6.0, 40.0, 500.0);

-- TRANSPORTE (subtipo)
INSERT INTO TRANSPORTE (nome_servico) VALUES
  ('Transporte');

-- OFERTA_SERVICO
INSERT INTO OFERTA_SERVICO (nome_empresa, nome_servico, preco_hora) VALUES
  ('Mudanças Rápidas', 'Transporte', 120.0),
  ('Mudanças Rápidas', 'Embalagem', 60.0),
  ('Mudanças Rápidas', 'Montagem', 80.0),
  ('TransMudar', 'Transporte', 100.0),
  ('TransMudar', 'Desmontagem', 70.0),
  ('TransMudar', 'Montagem', 75.0),
  ('Carrega Tudo', 'Transporte', 130.0),
  ('Carrega Tudo', 'Guindaste Pequeno', 200.0),
  ('Carrega Tudo', 'Embalagem', 55.0),
  ('Mudou Fácil', 'Transporte', 110.0),
  ('Mudou Fácil', 'Embalagem', 65.0),
  ('Mudou Fácil', 'Montagem', 85.0),
  ('Mudou Fácil', 'Desmontagem', 70.0),
  ('GuinchoMax', 'Guindaste Pequeno', 220.0),
  ('GuinchoMax', 'Guindaste Grande', 450.0),
  ('GuinchoMax', 'Transporte', 140.0),
  ('Boa Mudança', 'Transporte', 95.0),
  ('Boa Mudança', 'Embalagem', 50.0),
  ('Boa Mudança', 'Montagem', 70.0);

-- EMPRESA_ATUA_CIDADE
INSERT INTO EMPRESA_ATUA_CIDADE (nome_empresa, estado, nome_cidade) VALUES
  ('Mudanças Rápidas', 'SP', 'São Paulo'),
  ('Mudanças Rápidas', 'SP', 'Campinas'),
  ('Mudanças Rápidas', 'RJ', 'Rio de Janeiro'),
  ('TransMudar', 'SP', 'São Paulo'),
  ('TransMudar', 'MG', 'Belo Horizonte'),
  ('TransMudar', 'PR', 'Curitiba'),
  ('Carrega Tudo', 'RJ', 'Rio de Janeiro'),
  ('Carrega Tudo', 'BA', 'Salvador'),
  ('Carrega Tudo', 'SP', 'São Paulo'),
  ('Mudou Fácil', 'SP', 'Campinas'),
  ('Mudou Fácil', 'PR', 'Curitiba'),
  ('Mudou Fácil', 'RS', 'Porto Alegre'),
  ('GuinchoMax', 'SP', 'São Paulo'),
  ('GuinchoMax', 'SC', 'Florianópolis'),
  ('GuinchoMax', 'RJ', 'Rio de Janeiro'),
  ('Boa Mudança', 'MG', 'Belo Horizonte'),
  ('Boa Mudança', 'BA', 'Salvador'),
  ('Boa Mudança', 'RS', 'Porto Alegre');

-- REGRA_ACRESCIMO_TRANSPORTE
INSERT INTO REGRA_ACRESCIMO_TRANSPORTE (id_regra, nome_empresa, nome_servico_transporte, percentual_acrescimo, kg_limite) VALUES
  (1, 'Mudanças Rápidas', 'Transporte', 10.0, 500.0),
  (2, 'Mudanças Rápidas', 'Transporte', 15.0, 1000.0),
  (3, 'TransMudar', 'Transporte', 12.0, 600.0),
  (4, 'Carrega Tudo', 'Transporte', 8.0, 400.0),
  (5, 'Carrega Tudo', 'Transporte', 14.0, 800.0),
  (6, 'Mudou Fácil', 'Transporte', 10.0, 500.0),
  (7, 'GuinchoMax', 'Transporte', 10.0, 700.0),
  (8, 'Boa Mudança', 'Transporte', 5.0, 300.0),
  (9, 'Boa Mudança', 'Transporte', 10.0, 600.0);

-- TRABALHA
INSERT INTO TRABALHA (cpf_funcionario, nome_empresa, horario, telefone_empresa) VALUES
  ('111.111.111-11', 'Mudanças Rápidas', '08:00-17:00', '(11) 3000-1000'),
  ('111.111.111-11', 'Carrega Tudo', '18:00-22:00', '(21) 3000-3000'),
  ('222.222.222-22', 'Mudanças Rápidas', '08:00-17:00', '(11) 3000-1000'),
  ('222.222.222-22', 'TransMudar', '07:00-12:00', '(31) 3000-2000'),
  ('333.333.333-33', 'Carrega Tudo', '09:00-18:00', '(21) 3000-3000'),
  ('444.444.444-44', 'GuinchoMax', '07:00-16:00', '(48) 3000-5000'),
  ('555.555.555-55', 'TransMudar', '08:00-17:00', '(31) 3000-2000'),
  ('666.666.666-66', 'Mudou Fácil', '08:00-17:00', '(41) 3000-4000'),
  ('777.777.777-77', 'Boa Mudança', '08:00-17:00', '(71) 3000-6000'),
  ('777.777.777-77', 'Carrega Tudo', '19:00-23:00', '(21) 3000-3000'),
  ('888.888.888-88', 'Mudou Fácil', '10:00-19:00', '(41) 3000-4000'),
  ('888.888.888-88', 'Boa Mudança', '07:00-11:00', '(71) 3000-6000');

-- PEDIDO
INSERT INTO PEDIDO (cod_pedido, data_solicitacao, data_resolucao, status_aceitacao, preco_total, endereco_partida, endereco_destino, cod_cliente, nome_empresa, estado_partida, cidade_partida, estado_destino, cidade_destino) VALUES
  (1, '2026-05-01', '2026-05-03', 'ACEITO', 648.0, 'Rua das Acácias, 12', 'Av. Brasil, 45', 1, 'Mudanças Rápidas', 'SP', 'São Paulo', 'SP', 'Campinas'),
  (2, '2026-05-04', '2026-05-06', 'ACEITO', 1068.0, 'Rua Campinas, 300', 'Praça Central, 1', 8, 'Mudanças Rápidas', 'SP', 'Campinas', 'SP', 'São Paulo'),
  (3, '2026-05-05', '2026-05-07', 'ACEITO', 1315.0, 'Av. Brasil, 900', 'Rua do Porto, 10', 2, 'Carrega Tudo', 'RJ', 'Rio de Janeiro', 'RJ', 'Rio de Janeiro'),
  (4, '2026-05-10', '2026-05-12', 'ACEITO', 1185.6, 'Av. Oceânica, 33', 'Rua Nova, 55', 5, 'Carrega Tudo', 'BA', 'Salvador', 'BA', 'Salvador'),
  (5, '2026-05-06', '2026-05-08', 'ACEITO', 476.0, 'Rua Minas, 45', 'Av. Afonso Pena, 200', 3, 'TransMudar', 'MG', 'Belo Horizonte', 'MG', 'Belo Horizonte'),
  (6, '2026-05-11', '2026-05-13', 'ACEITO', 550.0, 'Rua Paraná, 210', 'Rua Sete, 9', 4, 'TransMudar', 'PR', 'Curitiba', 'PR', 'Curitiba'),
  (7, '2026-05-12', '2026-05-14', 'ACEITO', 805.0, 'Rua Gaúcha, 77', 'Av. Ipiranga, 300', 6, 'Mudou Fácil', 'RS', 'Porto Alegre', 'RS', 'Porto Alegre'),
  (8, '2026-05-15', '2026-05-17', 'ACEITO', 670.0, 'Rua Paraná, 210', 'Rua das Araucárias, 8', 4, 'Mudou Fácil', 'PR', 'Curitiba', 'PR', 'Curitiba'),
  (9, '2026-05-13', '2026-05-15', 'ACEITO', 2466.0, 'Rua Ilha, 5', 'Av. Central, 120', 7, 'GuinchoMax', 'SC', 'Florianópolis', 'SC', 'Florianópolis'),
  (10, '2026-05-18', '2026-05-20', 'ACEITO', 540.0, 'Rua das Acácias, 12', 'Av. Rio Branco, 400', 1, 'GuinchoMax', 'SP', 'São Paulo', 'RJ', 'Rio de Janeiro'),
  (11, '2026-05-16', '2026-05-18', 'ACEITO', 917.0, 'Av. Oceânica, 33', 'Rua do Farol, 2', 5, 'Boa Mudança', 'BA', 'Salvador', 'BA', 'Salvador'),
  (12, '2026-05-19', '2026-05-21', 'ACEITO', 380.0, 'Rua Gaúcha, 77', 'Av. Assis Brasil, 900', 6, 'Boa Mudança', 'RS', 'Porto Alegre', 'RS', 'Porto Alegre'),
  (13, '2026-05-22', NULL, 'PENDENTE', 780.0, 'Av. Brasil, 900', 'Rua Verde, 30', 2, 'Mudanças Rápidas', 'RJ', 'Rio de Janeiro', 'SP', 'São Paulo'),
  (14, '2026-05-20', '2026-05-21', 'REJEITADO', 1482.0, 'Rua Minas, 45', 'Av. Litorânea, 50', 3, 'Carrega Tudo', 'SP', 'São Paulo', 'BA', 'Salvador');

-- ITEM_PEDIDO
INSERT INTO ITEM_PEDIDO (id_item, cod_pedido, preco_servico, tempo_demorado, data_realizacao, peso, nome_empresa_oferta, nome_servico_oferta) VALUES
  (1, 1, 528.0, '04:00:00', '2026-05-05', 600, 'Mudanças Rápidas', 'Transporte'),
  (2, 1, 120.0, '02:00:00', '2026-05-05', NULL, 'Mudanças Rápidas', 'Embalagem'),
  (1, 2, 828.0, '06:00:00', '2026-05-08', 1200, 'Mudanças Rápidas', 'Transporte'),
  (2, 2, 240.0, '03:00:00', '2026-05-08', NULL, 'Mudanças Rápidas', 'Montagem'),
  (1, 3, 650.0, '05:00:00', '2026-05-09', 350, 'Carrega Tudo', 'Transporte'),
  (2, 3, 500.0, '02:00:00', '2026-05-09', NULL, 'Carrega Tudo', 'Guindaste Pequeno'),
  (3, 3, 165.0, '03:00:00', '2026-05-09', NULL, 'Carrega Tudo', 'Embalagem'),
  (1, 4, 1185.6, '08:00:00', '2026-05-14', 900, 'Carrega Tudo', 'Transporte'),
  (1, 5, 336.0, '03:00:00', '2026-05-10', 650, 'TransMudar', 'Transporte'),
  (2, 5, 140.0, '02:00:00', '2026-05-10', NULL, 'TransMudar', 'Desmontagem'),
  (1, 6, 400.0, '04:00:00', '2026-05-15', 500, 'TransMudar', 'Transporte'),
  (2, 6, 150.0, '02:00:00', '2026-05-15', NULL, 'TransMudar', 'Montagem'),
  (1, 7, 605.0, '05:00:00', '2026-05-16', 700, 'Mudou Fácil', 'Transporte'),
  (2, 7, 130.0, '02:00:00', '2026-05-16', NULL, 'Mudou Fácil', 'Embalagem'),
  (3, 7, 70.0, '01:00:00', '2026-05-16', NULL, 'Mudou Fácil', 'Desmontagem'),
  (1, 8, 330.0, '03:00:00', '2026-05-19', 300, 'Mudou Fácil', 'Transporte'),
  (2, 8, 340.0, '04:00:00', '2026-05-19', NULL, 'Mudou Fácil', 'Montagem'),
  (1, 9, 1850.0, '03:00:00', '2026-05-17', NULL, 'GuinchoMax', 'Guindaste Grande'),
  (2, 9, 616.0, '04:00:00', '2026-05-17', 800, 'GuinchoMax', 'Transporte'),
  (1, 10, 540.0, '02:00:00', '2026-05-22', NULL, 'GuinchoMax', 'Guindaste Pequeno'),
  (1, 11, 627.0, '06:00:00', '2026-05-20', 650, 'Boa Mudança', 'Transporte'),
  (2, 11, 150.0, '03:00:00', '2026-05-20', NULL, 'Boa Mudança', 'Embalagem'),
  (3, 11, 140.0, '02:00:00', '2026-05-20', NULL, 'Boa Mudança', 'Montagem'),
  (1, 12, 380.0, '04:00:00', '2026-05-23', 250, 'Boa Mudança', 'Transporte'),
  (1, 13, 660.0, '05:00:00', NULL, 550, 'Mudanças Rápidas', 'Transporte'),
  (2, 13, 120.0, '02:00:00', NULL, NULL, 'Mudanças Rápidas', 'Embalagem'),
  (1, 14, 1482.0, '10:00:00', NULL, 1500, 'Carrega Tudo', 'Transporte');

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
