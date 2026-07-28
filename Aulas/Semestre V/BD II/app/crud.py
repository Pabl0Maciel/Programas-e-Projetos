"""
crud.py — Cadastro das entidades (alinhado ao gabarito).
Mudanças principais: EMPRESA por id_empresa; OFERECEM ternário
(empresa x serviço x cidade); ACRESCIMO_TRANSPORTE por serviço; SERVICO
com tipo_servico; ITEM_PEDIDO referencia id_oferta.
Depende de db.py.
"""
from sqlalchemy import text
import db

UFS_VALIDAS = {
    "AC","AL","AP","AM","BA","CE","DF","ES","GO","MA","MT","MS","MG","PA",
    "PB","PR","PE","PI","RJ","RN","RS","RO","RR","SC","SP","SE","TO",
}


def _exigir(**campos):
    vazios = [n for n, v in campos.items() if v is None or not str(v).strip()]
    if vazios:
        raise ValueError("Preencha o(s) campo(s): " + ", ".join(vazios) + ".")


def _uf(estado):
    uf = str(estado or "").strip().upper()
    if uf not in UFS_VALIDAS:
        raise ValueError(f"Estado (UF) inválido: '{estado}'. Use uma sigla como SP, RJ, MG.")
    return uf


# ===================== CIDADE =====================
def listar_cidades(engine=None):
    return db.fetch_df("SELECT estado, nome_cidade FROM CIDADE ORDER BY estado, nome_cidade", engine=engine)


def criar_cidade(estado, nome_cidade, engine=None):
    _exigir(**{"nome da cidade": nome_cidade})
    return db.execute("INSERT INTO CIDADE (estado, nome_cidade) VALUES (:uf, :c)",
                      {"uf": _uf(estado), "c": nome_cidade.strip()}, engine=engine)


def excluir_cidade(estado, nome_cidade, engine=None):
    return db.execute("DELETE FROM CIDADE WHERE estado=:uf AND nome_cidade=:c",
                      {"uf": estado, "c": nome_cidade}, engine=engine)


# ===================== EMPRESA (id próprio) =====================
def listar_empresas(engine=None):
    return db.fetch_df("SELECT id_empresa, nome, endereco FROM EMPRESA ORDER BY nome", engine=engine)


def criar_empresa(nome, endereco, engine=None):
    _exigir(**{"nome da empresa": nome})
    r = db.execute("INSERT INTO EMPRESA (nome, endereco) VALUES (:n, :e)",
                   {"n": nome.strip(), "e": endereco}, engine=engine)
    return r["lastrowid"]


def atualizar_empresa(id_empresa, nome, endereco, engine=None):
    _exigir(**{"nome da empresa": nome})
    return db.execute("UPDATE EMPRESA SET nome=:n, endereco=:e WHERE id_empresa=:id",
                      {"id": id_empresa, "n": nome.strip(), "e": endereco}, engine=engine)


def excluir_empresa(id_empresa, engine=None):
    return db.execute("DELETE FROM EMPRESA WHERE id_empresa=:id", {"id": id_empresa}, engine=engine)


def adicionar_telefone_empresa(id_empresa, telefone, engine=None):
    return db.execute("INSERT INTO TELEFONE_EMPRESA (id_empresa, telefone) VALUES (:e, :t)",
                      {"e": id_empresa, "t": telefone}, engine=engine)


# ----- OFERECEM (empresa x serviço x cidade) -----
def listar_ofertas(id_empresa=None, engine=None):
    base = ("SELECT o.id_oferta, e.nome AS empresa, o.nome_servico, o.estado, "
            "o.nome_cidade, o.preco_hora FROM OFERECEM o "
            "JOIN EMPRESA e ON e.id_empresa = o.id_empresa ")
    if id_empresa:
        return db.fetch_df(base + "WHERE o.id_empresa=:e ORDER BY o.nome_servico, o.nome_cidade",
                           {"e": id_empresa}, engine=engine)
    return db.fetch_df(base + "ORDER BY e.nome, o.nome_servico, o.nome_cidade", engine=engine)


def adicionar_oferta(id_empresa, nome_servico, estado, nome_cidade, preco_hora, engine=None):
    _exigir(**{"serviço": nome_servico, "cidade": nome_cidade})
    if preco_hora is None or float(preco_hora) <= 0:
        raise ValueError("O preço/hora deve ser maior que zero.")
    return db.execute(
        "INSERT INTO OFERECEM (id_empresa, nome_servico, estado, nome_cidade, preco_hora) "
        "VALUES (:e, :s, :uf, :c, :p)",
        {"e": id_empresa, "s": nome_servico, "uf": _uf(estado), "c": nome_cidade, "p": preco_hora},
        engine=engine)


def remover_oferta(id_oferta, engine=None):
    return db.execute("DELETE FROM OFERECEM WHERE id_oferta=:id", {"id": id_oferta}, engine=engine)


def cidades_da_empresa(id_empresa, engine=None):
    """Cidades onde a empresa atua = cidades distintas nas suas ofertas."""
    return db.fetch_df(
        "SELECT DISTINCT estado, nome_cidade FROM OFERECEM WHERE id_empresa=:e "
        "ORDER BY estado, nome_cidade", {"e": id_empresa}, engine=engine)


def ofertas_empresa_cidade(id_empresa, estado, nome_cidade, engine=None):
    """Serviços (com id_oferta e preço) que a empresa oferece numa cidade."""
    return db.fetch_df(
        "SELECT id_oferta, nome_servico, preco_hora FROM OFERECEM "
        "WHERE id_empresa=:e AND estado=:uf AND nome_cidade=:c ORDER BY nome_servico",
        {"e": id_empresa, "uf": estado, "c": nome_cidade}, engine=engine)


# ===================== CLIENTE =====================
def listar_clientes(engine=None):
    return db.fetch_df("SELECT cod_cliente, cpf, rg, nome_completo, endereco "
                       "FROM CLIENTE ORDER BY cod_cliente", engine=engine)


def _proximo_id(tabela, coluna, engine=None):
    df = db.fetch_df(f"SELECT COALESCE(MAX({coluna}),0)+1 AS prox FROM {tabela}", engine=engine)
    return int(df.iloc[0]["prox"])


def criar_cliente(cpf, rg, nome_completo, endereco, engine=None):
    _exigir(**{"CPF": cpf, "nome completo": nome_completo})
    cod = _proximo_id("CLIENTE", "cod_cliente", engine=engine)
    db.execute("INSERT INTO CLIENTE (cod_cliente, cpf, rg, nome_completo, endereco) "
               "VALUES (:cod,:cpf,:rg,:nome,:end)",
               {"cod": cod, "cpf": cpf.strip(), "rg": rg, "nome": nome_completo.strip(), "end": endereco},
               engine=engine)
    return cod


def atualizar_cliente(cod_cliente, cpf, rg, nome_completo, endereco, engine=None):
    _exigir(**{"CPF": cpf, "nome completo": nome_completo})
    return db.execute("UPDATE CLIENTE SET cpf=:cpf,rg=:rg,nome_completo=:nome,endereco=:end "
                      "WHERE cod_cliente=:cod",
                      {"cod": cod_cliente, "cpf": cpf.strip(), "rg": rg,
                       "nome": nome_completo.strip(), "end": endereco}, engine=engine)


def excluir_cliente(cod_cliente, engine=None):
    return db.execute("DELETE FROM CLIENTE WHERE cod_cliente=:cod", {"cod": cod_cliente}, engine=engine)


def adicionar_telefone_cliente(cod_cliente, telefone, engine=None):
    return db.execute("INSERT INTO TELEFONE_CLIENTE (cod_cliente, telefone) VALUES (:cod,:t)",
                      {"cod": cod_cliente, "t": telefone}, engine=engine)


def listar_telefones_cliente(cod_cliente, engine=None):
    return db.fetch_df("SELECT telefone FROM TELEFONE_CLIENTE WHERE cod_cliente=:cod",
                       {"cod": cod_cliente}, engine=engine)


# ===================== FUNCIONARIO / TRABALHA =====================
def listar_funcionarios(engine=None):
    return db.fetch_df("SELECT cpf, rg, salario, tipo_funcionario, nome_completo, endereco "
                       "FROM FUNCIONARIO ORDER BY nome_completo", engine=engine)


def criar_funcionario(cpf, rg, salario, tipo_funcionario, nome_completo, endereco, engine=None):
    _exigir(**{"CPF": cpf, "nome completo": nome_completo})
    return db.execute("INSERT INTO FUNCIONARIO (cpf,rg,salario,tipo_funcionario,nome_completo,endereco) "
                      "VALUES (:cpf,:rg,:sal,:tipo,:nome,:end)",
                      {"cpf": cpf.strip(), "rg": rg, "sal": salario, "tipo": tipo_funcionario,
                       "nome": nome_completo.strip(), "end": endereco}, engine=engine)


def excluir_funcionario(cpf, engine=None):
    return db.execute("DELETE FROM FUNCIONARIO WHERE cpf=:cpf", {"cpf": cpf}, engine=engine)


def adicionar_telefone_funcionario(cpf, telefone, engine=None):
    return db.execute("INSERT INTO TELEFONE_FUNCIONARIO (cpf_funcionario, telefone) VALUES (:cpf,:t)",
                      {"cpf": cpf, "t": telefone}, engine=engine)


def adicionar_trabalha(cpf, id_empresa, horario, telefone_empresa, engine=None):
    return db.execute("INSERT INTO TRABALHA (cpf_funcionario,id_empresa,horario,telefone_empresa) "
                      "VALUES (:cpf,:e,:h,:tel)",
                      {"cpf": cpf, "e": id_empresa, "h": horario, "tel": telefone_empresa}, engine=engine)


def listar_trabalha(id_empresa=None, engine=None):
    base = ("SELECT t.cpf_funcionario, f.nome_completo, e.nome AS empresa, t.horario "
            "FROM TRABALHA t JOIN FUNCIONARIO f ON f.cpf=t.cpf_funcionario "
            "JOIN EMPRESA e ON e.id_empresa=t.id_empresa ")
    if id_empresa:
        return db.fetch_df(base + "WHERE t.id_empresa=:e", {"e": id_empresa}, engine=engine)
    return db.fetch_df(base + "ORDER BY e.nome", engine=engine)


def funcionarios_da_empresa(id_empresa, engine=None):
    return db.fetch_df("SELECT f.cpf, f.nome_completo FROM TRABALHA t "
                       "JOIN FUNCIONARIO f ON f.cpf=t.cpf_funcionario "
                       "WHERE t.id_empresa=:e ORDER BY f.nome_completo", {"e": id_empresa}, engine=engine)


# ===================== SERVICO (tipo) / ACRESCIMO =====================
def listar_servicos(engine=None):
    return db.fetch_df("""
        SELECT s.nome_servico, s.tipo_servico AS tipo,
               g.tamanho_base, g.altura, g.bonus_altura
        FROM SERVICO s LEFT JOIN GUINDASTE g ON g.nome_servico = s.nome_servico
        ORDER BY s.tipo_servico, s.nome_servico""", engine=engine)


def criar_servico_simples(nome, engine=None):
    _exigir(**{"nome do serviço": nome})
    return db.execute("INSERT INTO SERVICO (nome_servico, tipo_servico) VALUES (:n,'SIMPLES')",
                      {"n": nome.strip()}, engine=engine)


def criar_guindaste(nome, tamanho_base, altura, bonus_altura, engine=None):
    _exigir(**{"nome do serviço": nome})
    nome = nome.strip()
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        conn.execute(text("INSERT INTO SERVICO (nome_servico, tipo_servico) VALUES (:n,'GUINDASTE')"), {"n": nome})
        conn.execute(text("INSERT INTO GUINDASTE (nome_servico,tamanho_base,altura,bonus_altura) "
                          "VALUES (:n,:b,:a,:bo)"),
                     {"n": nome, "b": tamanho_base, "a": altura, "bo": bonus_altura})


def criar_transporte(nome, engine=None):
    _exigir(**{"nome do serviço": nome})
    nome = nome.strip()
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        conn.execute(text("INSERT INTO SERVICO (nome_servico, tipo_servico) VALUES (:n,'TRANSPORTE')"), {"n": nome})
        conn.execute(text("INSERT INTO TRANSPORTE (nome_servico) VALUES (:n)"), {"n": nome})


def excluir_servico(nome, engine=None):
    return db.execute("DELETE FROM SERVICO WHERE nome_servico=:n", {"n": nome}, engine=engine)


def listar_regras(engine=None):
    return db.fetch_df("SELECT id_acrescimo, nome_servico_transporte, percentual_acrescimo, kg_limite "
                       "FROM ACRESCIMO_TRANSPORTE ORDER BY nome_servico_transporte, kg_limite", engine=engine)


def adicionar_regra_transporte(nome_servico_transporte, percentual, kg_limite, engine=None):
    return db.execute("INSERT INTO ACRESCIMO_TRANSPORTE (nome_servico_transporte,percentual_acrescimo,kg_limite) "
                      "VALUES (:t,:p,:kg)",
                      {"t": nome_servico_transporte, "p": percentual, "kg": kg_limite}, engine=engine)


# ===================== PEDIDO =====================
def listar_pedidos(engine=None):
    return db.fetch_df("""
        SELECT p.cod_pedido, p.data_solicitacao, p.data_resolucao, p.status_aceitacao,
               p.preco_total, c.nome_completo AS cliente, e.nome AS empresa,
               CONCAT(p.cidade_partida,'/',p.estado_partida) AS partida,
               CONCAT(p.cidade_destino,'/',p.estado_destino) AS destino
        FROM PEDIDO p
        JOIN CLIENTE c ON c.cod_cliente = p.cod_cliente
        JOIN EMPRESA e ON e.id_empresa = p.id_empresa
        ORDER BY p.cod_pedido""", engine=engine)


def listar_itens_pedido(cod_pedido, engine=None):
    return db.fetch_df("""
        SELECT i.id_item, o.nome_servico AS servico, o.nome_cidade AS cidade,
               TIME_FORMAT(i.tempo_demorado,'%H:%i:%s') AS tempo,
               i.peso, i.data_realizacao, i.preco_servico
        FROM ITEM_PEDIDO i JOIN OFERECEM o ON o.id_oferta = i.id_oferta
        WHERE i.cod_pedido = :cod ORDER BY i.id_item""", {"cod": cod_pedido}, engine=engine)


def criar_pedido(cliente_cod, id_empresa, data_solicitacao, status,
                 estado_partida, cidade_partida, estado_destino, cidade_destino,
                 itens, endereco_partida=None, endereco_destino=None,
                 data_resolucao=None, engine=None):
    """itens: [{id_oferta, tempo, peso, data_realizacao, executores[]}]. Preço via triggers."""
    if not itens:
        raise ValueError("O pedido precisa ter pelo menos um item.")
    if data_resolucao and str(data_resolucao) < str(data_solicitacao):
        raise ValueError("A data de resolução não pode ser anterior à data de solicitação.")
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        cod = int(conn.execute(text("SELECT COALESCE(MAX(cod_pedido),0)+1 FROM PEDIDO")).scalar())
        conn.execute(text("""
            INSERT INTO PEDIDO (cod_pedido, data_solicitacao, data_resolucao, status_aceitacao,
                preco_total, endereco_partida, endereco_destino, cod_cliente, id_empresa,
                estado_partida, cidade_partida, estado_destino, cidade_destino)
            VALUES (:cod,:dsol,:dres,:st,0,:epart,:edest,:cli,:emp,:up,:cp,:ud,:cd)"""),
            {"cod": cod, "dsol": data_solicitacao, "dres": data_resolucao, "st": status,
             "epart": endereco_partida, "edest": endereco_destino, "cli": cliente_cod, "emp": id_empresa,
             "up": estado_partida, "cp": cidade_partida, "ud": estado_destino, "cd": cidade_destino})
        for idx, it in enumerate(itens, 1):
            conn.execute(text("""
                INSERT INTO ITEM_PEDIDO (id_item, cod_pedido, id_oferta, preco_servico,
                    tempo_demorado, data_realizacao, peso)
                VALUES (:id,:cod,:of,0,:tempo,:dreal,:peso)"""),
                {"id": idx, "cod": cod, "of": it["id_oferta"], "tempo": it.get("tempo"),
                 "dreal": it.get("data_realizacao"), "peso": it.get("peso")})
            for cpf in it.get("executores", []):
                conn.execute(text("INSERT INTO EXECUTA (id_item,cod_pedido,cpf_funcionario) "
                                  "VALUES (:id,:cod,:cpf)"), {"id": idx, "cod": cod, "cpf": cpf})
    return cod


def atualizar_status_pedido(cod_pedido, status, data_resolucao=None, engine=None):
    return db.execute("UPDATE PEDIDO SET status_aceitacao=:st, data_resolucao=:dr WHERE cod_pedido=:cod",
                      {"st": status, "dr": data_resolucao, "cod": cod_pedido}, engine=engine)


def excluir_pedido(cod_pedido, engine=None):
    return db.execute("DELETE FROM PEDIDO WHERE cod_pedido=:cod", {"cod": cod_pedido}, engine=engine)