"""
queries.py — As 6 consultas de resultado (alinhado ao novo esquema).
"por cidade": cidade de PARTIDA do pedido. Contagens = todos os pedidos;
valores = apenas 'ACEITO'. As consultas por empresa fazem JOIN em EMPRESA
para exibir o nome (agora a PK é id_empresa).
"""
import db
STATUS_EXECUTADO = "ACEITO"


def q1_servicos_por_cidade(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida,'/',p.estado_partida) AS cidade,
               COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY num_servicos DESC, cidade""", engine=engine)


def q2_pagamentos_por_cidade(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida,'/',p.estado_partida) AS cidade,
               SUM(i.preco_servico) AS total_pago
        FROM PEDIDO p JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY total_pago DESC, cidade""", {"st": STATUS_EXECUTADO}, engine=engine)


def q3_top5_cidades_valor(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida,'/',p.estado_partida) AS cidade,
               SUM(i.preco_servico) AS valor_investido
        FROM PEDIDO p JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY valor_investido DESC, cidade LIMIT 5""", {"st": STATUS_EXECUTADO}, engine=engine)


def q4_top5_cidades_servicos(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida,'/',p.estado_partida) AS cidade,
               COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY num_servicos DESC, cidade LIMIT 5""", engine=engine)


def q5_top5_empresas_servicos(engine=None):
    return db.fetch_df("""
        SELECT e.nome AS empresa, COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p
        JOIN EMPRESA e ON e.id_empresa = p.id_empresa
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY e.nome
        ORDER BY num_servicos DESC, empresa LIMIT 5""", engine=engine)


def q6_top5_empresas_ganhos(engine=None):
    return db.fetch_df("""
        SELECT e.nome AS empresa, SUM(i.preco_servico) AS total_ganho
        FROM PEDIDO p
        JOIN EMPRESA e ON e.id_empresa = p.id_empresa
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY e.nome
        ORDER BY total_ganho DESC, empresa LIMIT 5""", {"st": STATUS_EXECUTADO}, engine=engine)