"""
queries.py — As 6 consultas de resultado exigidas pelo enunciado.

Cada função devolve um pandas.DataFrame pronto para o Streamlit desenhar
(tabela ou gráfico). Nenhuma faz cálculo em Python: tudo é agregado no SQL.

Convenções (documentadas para defesa; fáceis de trocar):
  • "por cidade"  -> cidade de PARTIDA do pedido (origem da mudança).
  • CONTAGENS de "serviços solicitados" -> TODOS os pedidos (aceitos ou não).
  • VALORES (investido/pagamentos/ganhos) -> apenas pedidos 'ACEITO'
    (dinheiro só entra em serviço executado; o enunciado separa
    "solicitados" de "executados").

Depende de db.py.
"""
import db

STATUS_EXECUTADO = "ACEITO"


# ---------------------------------------------------------------------
# 1) Histograma: número de serviços solicitados POR CIDADE (todas)
# ---------------------------------------------------------------------
def q1_servicos_por_cidade(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida, '/', p.estado_partida) AS cidade,
               COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY num_servicos DESC, cidade
    """, engine=engine)


# ---------------------------------------------------------------------
# 2) Histograma: pagamentos dos serviços POR CIDADE (executados)
# ---------------------------------------------------------------------
def q2_pagamentos_por_cidade(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida, '/', p.estado_partida) AS cidade,
               SUM(i.preco_servico) AS total_pago
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY total_pago DESC, cidade
    """, {"st": STATUS_EXECUTADO}, engine=engine)


# ---------------------------------------------------------------------
# 3) Top 5 cidades por MAIOR VALOR investido em serviços (executados)
# ---------------------------------------------------------------------
def q3_top5_cidades_valor(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida, '/', p.estado_partida) AS cidade,
               SUM(i.preco_servico) AS valor_investido
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY valor_investido DESC, cidade
        LIMIT 5
    """, {"st": STATUS_EXECUTADO}, engine=engine)


# ---------------------------------------------------------------------
# 4) Top 5 cidades por NÚMERO de serviços (solicitados)
# ---------------------------------------------------------------------
def q4_top5_cidades_servicos(engine=None):
    return db.fetch_df("""
        SELECT CONCAT(p.cidade_partida, '/', p.estado_partida) AS cidade,
               COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY p.estado_partida, p.cidade_partida
        ORDER BY num_servicos DESC, cidade
        LIMIT 5
    """, engine=engine)


# ---------------------------------------------------------------------
# 5) Top 5 empresas por NÚMERO de serviços solicitados
# ---------------------------------------------------------------------
def q5_top5_empresas_servicos(engine=None):
    return db.fetch_df("""
        SELECT p.nome_empresa AS empresa,
               COUNT(i.id_item) AS num_servicos
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        GROUP BY p.nome_empresa
        ORDER BY num_servicos DESC, empresa
        LIMIT 5
    """, engine=engine)


# ---------------------------------------------------------------------
# 6) Top 5 empresas por VALORES ganhos em serviços executados
# ---------------------------------------------------------------------
def q6_top5_empresas_ganhos(engine=None):
    return db.fetch_df("""
        SELECT p.nome_empresa AS empresa,
               SUM(i.preco_servico) AS total_ganho
        FROM PEDIDO p
        JOIN ITEM_PEDIDO i ON i.cod_pedido = p.cod_pedido
        WHERE p.status_aceitacao = :st
        GROUP BY p.nome_empresa
        ORDER BY total_ganho DESC, empresa
        LIMIT 5
    """, {"st": STATUS_EXECUTADO}, engine=engine)
