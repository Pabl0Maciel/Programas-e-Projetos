#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 15 14:36:14 2025

@author: pablo
"""

import pandas as pd
from sqlalchemy import create_engine
from sqlalchemy import text
from datetime import date, timedelta

########################################################### CONEXAO ####################################################
usuario = 'postgres'
senha = '123'
host = 'localhost'
porta = '5432'
banco = 'teste'

engine = create_engine(f'postgresql+psycopg2://{usuario}:{senha}@{host}:{porta}/{banco}')

######################################################################################################################
###                                                            FUNCOES                                             ###
######################################################################################################################
######################################################################################################################
def getLivros(autor=None, editora=None, livro=None, engine=None):
    if engine is None:
        raise ValueError("É necessário passar o parâmetro 'engine' com a conexão ativa do SQLAlchemy.")
    
    
    query = """
        SELECT
            l.isbn,
            l.titulo,
            l.data_de_publicacao,
            e.nome AS nome_editora,
            a.nome AS nome_autor
        FROM livros l
        LEFT JOIN editora e ON e.id = l.editora_id
        LEFT JOIN escreve es ON es.isbn = l.isbn
        LEFT JOIN autor a ON a.rg = es.rg
    """

    
    conditions = []
    params = {}

    if autor:
        conditions.append("a.nome ILIKE :autor")
        params["autor"] = f"%{autor}%"

    if editora:
        conditions.append("e.nome ILIKE :editora")
        params["editora"] = f"%{editora}%"

    if livro:
        conditions.append("l.titulo ILIKE :livro")
        params["livro"] = f"%{livro}%"

    
    if conditions:
        query += " WHERE " + " AND ".join(conditions)

    query += " ORDER BY l.titulo;"

    df = pd.read_sql(text(query), engine, params=params)
    return df
######################################################################################################################
def impressoesNoPeriodo(data_inicio=None, data_fim=None, engine=None):
    if engine is None:
        raise ValueError("É necessário passar o parâmetro 'engine' com a conexão ativa do SQLAlchemy.")


    query = """
        SELECT
            i.lisbn AS isbn,
            l.titulo AS nome_livro,
            g.nome AS nome_grafica,
            i.nto_copias,
            i.data_entrega
        FROM imprime i
        LEFT JOIN livros l ON l.isbn = i.lisbn
        LEFT JOIN grafica g ON g.id = i.grafica_id
    """

    
    conditions = []
    params = {}

    if data_inicio:
        conditions.append("i.data_entrega >= :data_inicio")
        params["data_inicio"] = data_inicio

    if data_fim:
        conditions.append("i.data_entrega <= :data_fim")
        params["data_fim"] = data_fim

    
    if conditions:
        query += " WHERE " + " AND ".join(conditions)

    query += " ORDER BY i.data_entrega;"

    
    df = pd.read_sql(text(query), engine, params=params)
    return df
######################################################################################################################
def solicitarImpressao(livro, grafica, copias, engine=None):
    if engine is None:
        raise ValueError("É necessário passar o parâmetro 'engine' com a conexão ativa do SQLAlchemy.")
    
    # verificando se livro existe
    query_livro = text("SELECT isbn, titulo FROM livros WHERE titulo ILIKE :livro;")
    df_livro = pd.read_sql(query_livro, engine, params={'livro': livro})
    
    if df_livro.empty:
        print(f"O livro '{livro}' não está cadastrado. Cadastre-o antes de solicitar a impressão.")
        return
    
    isbn = str(df_livro.iloc[0]['isbn'])
    
    # verificando se grafica existe
    query_grafica = text("SELECT id, nome FROM grafica WHERE nome ILIKE :grafica;")
    df_grafica = pd.read_sql(query_grafica, engine, params={'grafica': grafica})
    
    if df_grafica.empty:
        print(f"A gráfica '{grafica}' não está cadastrada. Cadastre-a antes de solicitar a impressão.")
        return
    
    grafica_id = int(df_grafica.iloc[0]['id'])
    
    # calculando data de entrega
    data_hoje = date.today()
    dias_adicionados = 0
    data_entrega = data_hoje
    while dias_adicionados < 5:
        data_entrega += timedelta(days=1)
        if data_entrega.weekday() < 5:  
            dias_adicionados += 1
    
    # inserindo na tabela
    insert_query = text("""
        INSERT INTO imprime (lisbn, grafica_id, nto_copias, data_entrega)
        VALUES (:isbn, :grafica_id, :copias, :data_entrega);
    """)
    
    with engine.begin() as conn:
        conn.execute(insert_query, {
            'isbn': str(isbn),
            'grafica_id': int(grafica_id),
            'copias': int(copias),
            'data_entrega': data_entrega
        })
    
    print(f"Impressão solicitada com sucesso!\n"
          f"Livro: {livro}\n"
          f"Gráfica: {grafica}\n"
          f"Cópias: {copias}\n"
          f"Data de entrega prevista: {data_entrega.strftime('%Y/%m/%d')}")
######################################################################################################################    


### TESTES ###
df_livros = getLivros(engine=engine)
df_livros1 = getLivros(autor='Carlos', engine=engine)
df_livros2 = getLivros(editora='Alfa', engine=engine)
df_livros3 = getLivros(livro='Sigma', engine=engine)
df_livros4 = getLivros(autor='Carlos', editora='Alfa', engine=engine)
df_livros5 = getLivros(autor='Carlos', editora='Alfa', livro='Tau', engine=engine)
##
df_impressoes = impressoesNoPeriodo(engine=engine)
df_impressoes2 = impressoesNoPeriodo(data_inicio = '2024-11-20', data_fim = '2024-11-20', engine=engine)
df_impressoes3 = impressoesNoPeriodo(data_inicio = '2024-11-07', data_fim = '2024-11-12', engine=engine)
##
solicitarImpressao('O Livro Zeta', 'Grafica Beta', 120, engine=engine)
solicitarImpressao('O Livro Zeta', 'Grafica', 120, engine=engine)
solicitarImpressao('O Livro', 'Grafica Beta', 120, engine=engine)
##
### TESTES ###




