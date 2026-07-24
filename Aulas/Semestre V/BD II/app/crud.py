"""
crud.py — Cadastro das 6 entidades do sistema de Mudanças
(empresas, clientes, cidades, serviços, pedidos, funcionários) e dos
relacionamentos necessários (ofertas, atuação, telefones, trabalha, itens).

Regra de ouro: este módulo NÃO calcula preços. Quem calcula preco_servico e
preco_total é o banco (triggers da Etapa 2). Aqui só inserimos os dados.

Depende de db.py.
"""
from sqlalchemy import text
import db


def _proximo_id(tabela, coluna, engine=None):
    """Gera o próximo código inteiro (MAX + 1) para PKs que não são AUTO_INCREMENT."""
    df = db.fetch_df(
        f"SELECT COALESCE(MAX({coluna}), 0) + 1 AS prox FROM {tabela}",
        engine=engine)
    return int(df.iloc[0]["prox"])


UFS_VALIDAS = {
    "AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA", "MT", "MS",
    "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN", "RS", "RO", "RR", "SC",
    "SP", "SE", "TO",
}


def _exigir(**campos):
    """Valida campos de texto obrigatórios; levanta ValueError se algum vier
    vazio ou só com espaços. A mensagem sobe até o app e vira um aviso amigável."""
    vazios = [nome for nome, val in campos.items()
              if val is None or not str(val).strip()]
    if vazios:
        raise ValueError("Preencha o(s) campo(s): " + ", ".join(vazios) + ".")


def _uf(estado):
    """Normaliza e valida a UF (2 letras, estado brasileiro existente)."""
    uf = str(estado or "").strip().upper()
    if uf not in UFS_VALIDAS:
        raise ValueError(f"Estado (UF) inválido: '{estado}'. Use uma sigla como SP, RJ, MG.")
    return uf


# =====================================================================
# CIDADE
# =====================================================================
def listar_cidades(engine=None):
    return db.fetch_df(
        "SELECT estado, nome_cidade FROM CIDADE ORDER BY estado, nome_cidade",
        engine=engine)


def criar_cidade(estado, nome_cidade, engine=None):
    _exigir(**{"nome da cidade": nome_cidade})
    return db.execute(
        "INSERT INTO CIDADE (estado, nome_cidade) VALUES (:uf, :c)",
        {"uf": _uf(estado), "c": nome_cidade.strip()}, engine=engine)


def excluir_cidade(estado, nome_cidade, engine=None):
    return db.execute(
        "DELETE FROM CIDADE WHERE estado = :uf AND nome_cidade = :c",
        {"uf": estado, "c": nome_cidade}, engine=engine)


# =====================================================================
# CLIENTE (+ telefones)
# =====================================================================
def listar_clientes(engine=None):
    return db.fetch_df(
        "SELECT cod_cliente, cpf, rg, nome_completo, endereco "
        "FROM CLIENTE ORDER BY cod_cliente", engine=engine)


def criar_cliente(cpf, rg, nome_completo, endereco, engine=None):
    _exigir(**{"CPF": cpf, "nome completo": nome_completo})
    cod = _proximo_id("CLIENTE", "cod_cliente", engine=engine)
    db.execute(
        "INSERT INTO CLIENTE (cod_cliente, cpf, rg, nome_completo, endereco) "
        "VALUES (:cod, :cpf, :rg, :nome, :end)",
        {"cod": cod, "cpf": cpf.strip(), "rg": rg, "nome": nome_completo.strip(),
         "end": endereco}, engine=engine)
    return cod


def atualizar_cliente(cod_cliente, cpf, rg, nome_completo, endereco, engine=None):
    return db.execute(
        "UPDATE CLIENTE SET cpf=:cpf, rg=:rg, nome_completo=:nome, endereco=:end "
        "WHERE cod_cliente=:cod",
        {"cod": cod_cliente, "cpf": cpf, "rg": rg,
         "nome": nome_completo, "end": endereco}, engine=engine)


def excluir_cliente(cod_cliente, engine=None):
    return db.execute("DELETE FROM CLIENTE WHERE cod_cliente=:cod",
                      {"cod": cod_cliente}, engine=engine)


def adicionar_telefone_cliente(cod_cliente, telefone, engine=None):
    return db.execute(
        "INSERT INTO TELEFONE_CLIENTE (telefone, cod_cliente) VALUES (:t, :cod)",
        {"t": telefone, "cod": cod_cliente}, engine=engine)


def listar_telefones_cliente(cod_cliente, engine=None):
    return db.fetch_df(
        "SELECT telefone FROM TELEFONE_CLIENTE WHERE cod_cliente=:cod",
        {"cod": cod_cliente}, engine=engine)


# =====================================================================
# EMPRESA (+ telefones, ofertas de serviço, atuação em cidades)
# =====================================================================
def listar_empresas(engine=None):
    return db.fetch_df("SELECT nome, endereco FROM EMPRESA ORDER BY nome",
                       engine=engine)


def criar_empresa(nome, endereco, engine=None):
    _exigir(**{"nome da empresa": nome})
    return db.execute("INSERT INTO EMPRESA (nome, endereco) VALUES (:n, :e)",
                      {"n": nome.strip(), "e": endereco}, engine=engine)


def atualizar_empresa(nome, endereco, engine=None):
    return db.execute("UPDATE EMPRESA SET endereco=:e WHERE nome=:n",
                      {"n": nome, "e": endereco}, engine=engine)


def excluir_empresa(nome, engine=None):
    return db.execute("DELETE FROM EMPRESA WHERE nome=:n", {"n": nome}, engine=engine)


def adicionar_telefone_empresa(nome_empresa, telefone, engine=None):
    return db.execute(
        "INSERT INTO TELEFONE_EMPRESA (telefone, nome_empresa) VALUES (:t, :e)",
        {"t": telefone, "e": nome_empresa}, engine=engine)


def listar_ofertas(empresa=None, engine=None):
    if empresa:
        return db.fetch_df(
            "SELECT nome_empresa, nome_servico, preco_hora FROM OFERTA_SERVICO "
            "WHERE nome_empresa=:e ORDER BY nome_servico", {"e": empresa}, engine=engine)
    return db.fetch_df(
        "SELECT nome_empresa, nome_servico, preco_hora FROM OFERTA_SERVICO "
        "ORDER BY nome_empresa, nome_servico", engine=engine)


def adicionar_oferta(empresa, servico, preco_hora, engine=None):
    _exigir(**{"empresa": empresa, "serviço": servico})
    if preco_hora is None or float(preco_hora) <= 0:
        raise ValueError("O preço/hora deve ser maior que zero.")
    return db.execute(
        "INSERT INTO OFERTA_SERVICO (nome_empresa, nome_servico, preco_hora) "
        "VALUES (:e, :s, :p)", {"e": empresa, "s": servico, "p": preco_hora},
        engine=engine)


def remover_oferta(empresa, servico, engine=None):
    return db.execute(
        "DELETE FROM OFERTA_SERVICO WHERE nome_empresa=:e AND nome_servico=:s",
        {"e": empresa, "s": servico}, engine=engine)


def listar_atuacao(empresa=None, engine=None):
    if empresa:
        return db.fetch_df(
            "SELECT nome_empresa, estado, nome_cidade FROM EMPRESA_ATUA_CIDADE "
            "WHERE nome_empresa=:e ORDER BY estado, nome_cidade", {"e": empresa},
            engine=engine)
    return db.fetch_df(
        "SELECT nome_empresa, estado, nome_cidade FROM EMPRESA_ATUA_CIDADE "
        "ORDER BY nome_empresa, estado, nome_cidade", engine=engine)


def adicionar_atuacao(empresa, estado, cidade, engine=None):
    _exigir(**{"empresa": empresa, "cidade": cidade})
    return db.execute(
        "INSERT INTO EMPRESA_ATUA_CIDADE (nome_empresa, estado, nome_cidade) "
        "VALUES (:e, :uf, :c)", {"e": empresa, "uf": _uf(estado), "c": cidade},
        engine=engine)


# =====================================================================
# FUNCIONARIO (+ telefones, vínculo TRABALHA)
# =====================================================================
def listar_funcionarios(engine=None):
    return db.fetch_df(
        "SELECT cpf, rg, salario, tipo_funcionario, nome_completo, endereco "
        "FROM FUNCIONARIO ORDER BY nome_completo", engine=engine)


def criar_funcionario(cpf, rg, salario, tipo_funcionario, nome_completo,
                      endereco, engine=None):
    _exigir(**{"CPF": cpf, "nome completo": nome_completo})
    return db.execute(
        "INSERT INTO FUNCIONARIO (cpf, rg, salario, tipo_funcionario, "
        "nome_completo, endereco) VALUES (:cpf, :rg, :sal, :tipo, :nome, :end)",
        {"cpf": cpf.strip(), "rg": rg, "sal": salario, "tipo": tipo_funcionario,
         "nome": nome_completo.strip(), "end": endereco}, engine=engine)


def atualizar_funcionario(cpf, rg, salario, tipo_funcionario, nome_completo,
                          endereco, engine=None):
    return db.execute(
        "UPDATE FUNCIONARIO SET rg=:rg, salario=:sal, tipo_funcionario=:tipo, "
        "nome_completo=:nome, endereco=:end WHERE cpf=:cpf",
        {"cpf": cpf, "rg": rg, "sal": salario, "tipo": tipo_funcionario,
         "nome": nome_completo, "end": endereco}, engine=engine)


def excluir_funcionario(cpf, engine=None):
    return db.execute("DELETE FROM FUNCIONARIO WHERE cpf=:cpf",
                      {"cpf": cpf}, engine=engine)


def adicionar_telefone_funcionario(cpf, telefone, engine=None):
    return db.execute(
        "INSERT INTO TELEFONE_FUNCIONARIO (telefone, cpf_funcionario) "
        "VALUES (:t, :cpf)", {"t": telefone, "cpf": cpf}, engine=engine)


def adicionar_trabalha(cpf, empresa, horario, telefone_empresa, engine=None):
    return db.execute(
        "INSERT INTO TRABALHA (cpf_funcionario, nome_empresa, horario, "
        "telefone_empresa) VALUES (:cpf, :e, :h, :tel)",
        {"cpf": cpf, "e": empresa, "h": horario, "tel": telefone_empresa},
        engine=engine)


def listar_trabalha(empresa=None, engine=None):
    if empresa:
        return db.fetch_df(
            "SELECT cpf_funcionario, nome_empresa, horario FROM TRABALHA "
            "WHERE nome_empresa=:e", {"e": empresa}, engine=engine)
    return db.fetch_df(
        "SELECT cpf_funcionario, nome_empresa, horario FROM TRABALHA "
        "ORDER BY nome_empresa", engine=engine)


# =====================================================================
# SERVICO (+ subtipos guindaste/transporte, regras de acréscimo)
# =====================================================================
def listar_servicos(engine=None):
    """Lista serviços já classificados por subtipo (GUINDASTE/TRANSPORTE/SIMPLES)."""
    return db.fetch_df("""
        SELECT s.nome_servico,
               CASE WHEN g.nome_servico IS NOT NULL THEN 'GUINDASTE'
                    WHEN t.nome_servico IS NOT NULL THEN 'TRANSPORTE'
                    ELSE 'SIMPLES' END AS tipo,
               g.tamanho_base, g.altura, g.bonus_altura
        FROM SERVICO s
        LEFT JOIN GUINDASTE  g ON g.nome_servico = s.nome_servico
        LEFT JOIN TRANSPORTE t ON t.nome_servico = s.nome_servico
        ORDER BY tipo, s.nome_servico""", engine=engine)


def criar_servico_simples(nome, engine=None):
    _exigir(**{"nome do serviço": nome})
    return db.execute("INSERT INTO SERVICO (nome_servico) VALUES (:n)",
                      {"n": nome.strip()}, engine=engine)


def criar_guindaste(nome, tamanho_base, altura, bonus_altura, engine=None):
    """Cria o serviço e o registra como GUINDASTE (transação única).
    Se o nome já for TRANSPORTE, o trigger de disjunção barra e nada é gravado."""
    _exigir(**{"nome do serviço": nome})
    nome = nome.strip()
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        conn.execute(text("INSERT INTO SERVICO (nome_servico) VALUES (:n)"),
                     {"n": nome})
        conn.execute(text(
            "INSERT INTO GUINDASTE (nome_servico, tamanho_base, altura, "
            "bonus_altura) VALUES (:n, :b, :a, :bo)"),
            {"n": nome, "b": tamanho_base, "a": altura, "bo": bonus_altura})


def criar_transporte(nome, engine=None):
    """Cria o serviço e o registra como TRANSPORTE (transação única)."""
    _exigir(**{"nome do serviço": nome})
    nome = nome.strip()
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        conn.execute(text("INSERT INTO SERVICO (nome_servico) VALUES (:n)"),
                     {"n": nome})
        conn.execute(text("INSERT INTO TRANSPORTE (nome_servico) VALUES (:n)"),
                     {"n": nome})


def excluir_servico(nome, engine=None):
    """Remove o serviço (o subtipo cai junto por ON DELETE CASCADE)."""
    return db.execute("DELETE FROM SERVICO WHERE nome_servico=:n",
                      {"n": nome}, engine=engine)


def listar_regras(engine=None):
    return db.fetch_df(
        "SELECT id_regra, nome_empresa, nome_servico_transporte, "
        "percentual_acrescimo, kg_limite FROM REGRA_ACRESCIMO_TRANSPORTE "
        "ORDER BY nome_empresa, kg_limite", engine=engine)


def adicionar_regra_transporte(empresa, transporte, percentual, kg_limite, engine=None):
    rid = _proximo_id("REGRA_ACRESCIMO_TRANSPORTE", "id_regra", engine=engine)
    return db.execute(
        "INSERT INTO REGRA_ACRESCIMO_TRANSPORTE (id_regra, nome_empresa, "
        "nome_servico_transporte, percentual_acrescimo, kg_limite) "
        "VALUES (:id, :e, :t, :p, :kg)",
        {"id": rid, "e": empresa, "t": transporte, "p": percentual, "kg": kg_limite},
        engine=engine)


# =====================================================================
# PEDIDO (+ itens e executores) — a entidade composta
# =====================================================================
def listar_pedidos(engine=None):
    return db.fetch_df("""
        SELECT p.cod_pedido, p.data_solicitacao, p.data_resolucao,
               p.status_aceitacao, p.preco_total,
               c.nome_completo AS cliente, p.nome_empresa AS empresa,
               CONCAT(p.cidade_partida, '/', p.estado_partida) AS partida,
               CONCAT(p.cidade_destino, '/', p.estado_destino) AS destino
        FROM PEDIDO p
        JOIN CLIENTE c ON c.cod_cliente = p.cod_cliente
        ORDER BY p.cod_pedido""", engine=engine)


def listar_itens_pedido(cod_pedido, engine=None):
    return db.fetch_df("""
        SELECT i.id_item, i.nome_servico_oferta AS servico,
               TIME_FORMAT(i.tempo_demorado, '%H:%i:%s') AS tempo,
               i.peso, i.data_realizacao, i.preco_servico
        FROM ITEM_PEDIDO i
        WHERE i.cod_pedido = :cod
        ORDER BY i.id_item""", {"cod": cod_pedido}, engine=engine)


def criar_pedido(cliente_cod, empresa, data_solicitacao, status,
                 estado_partida, cidade_partida, estado_destino, cidade_destino,
                 itens, endereco_partida=None, endereco_destino=None,
                 data_resolucao=None, engine=None):
    """Cria um pedido inteiro (cabeçalho + itens + executores) em UMA transação.

    itens: lista de dicts, cada um com:
        {"servico": str, "tempo": "HH:MM:SS" | None, "peso": num | None,
         "data_realizacao": "AAAA-MM-DD" | None, "executores": [cpf, ...]}

    Os preços NÃO são passados: os triggers calculam preco_servico e preco_total.
    Retorna o cod_pedido gerado.
    """
    if not itens:
        raise ValueError("O pedido precisa ter pelo menos um item.")
    if data_resolucao and str(data_resolucao) < str(data_solicitacao):
        raise ValueError("A data de resolução não pode ser anterior à data de solicitação.")
    eng = engine or db.ENGINE
    with eng.begin() as conn:
        cod = int(conn.execute(
            text("SELECT COALESCE(MAX(cod_pedido), 0) + 1 FROM PEDIDO")).scalar())

        conn.execute(text("""
            INSERT INTO PEDIDO (cod_pedido, data_solicitacao, data_resolucao,
                status_aceitacao, preco_total, endereco_partida, endereco_destino,
                cod_cliente, nome_empresa, estado_partida, cidade_partida,
                estado_destino, cidade_destino)
            VALUES (:cod, :dsol, :dres, :st, 0, :epart, :edest, :cli, :emp,
                    :up, :cp, :ud, :cd)"""),
            {"cod": cod, "dsol": data_solicitacao, "dres": data_resolucao,
             "st": status, "epart": endereco_partida, "edest": endereco_destino,
             "cli": cliente_cod, "emp": empresa, "up": estado_partida,
             "cp": cidade_partida, "ud": estado_destino, "cd": cidade_destino})

        for idx, it in enumerate(itens, start=1):
            conn.execute(text("""
                INSERT INTO ITEM_PEDIDO (id_item, cod_pedido, preco_servico,
                    tempo_demorado, data_realizacao, peso, nome_empresa_oferta,
                    nome_servico_oferta)
                VALUES (:id, :cod, 0, :tempo, :dreal, :peso, :emp, :serv)"""),
                {"id": idx, "cod": cod, "tempo": it.get("tempo"),
                 "dreal": it.get("data_realizacao"), "peso": it.get("peso"),
                 "emp": empresa, "serv": it["servico"]})

            for cpf in it.get("executores", []):
                conn.execute(text(
                    "INSERT INTO EXECUTA (id_item, cod_pedido, cpf_funcionario) "
                    "VALUES (:id, :cod, :cpf)"),
                    {"id": idx, "cod": cod, "cpf": cpf})
    return cod


def atualizar_status_pedido(cod_pedido, status, data_resolucao=None, engine=None):
    return db.execute(
        "UPDATE PEDIDO SET status_aceitacao=:st, data_resolucao=:dr "
        "WHERE cod_pedido=:cod",
        {"st": status, "dr": data_resolucao, "cod": cod_pedido}, engine=engine)


def excluir_pedido(cod_pedido, engine=None):
    """Exclui o pedido (itens e execuções caem por ON DELETE CASCADE)."""
    return db.execute("DELETE FROM PEDIDO WHERE cod_pedido=:cod",
                      {"cod": cod_pedido}, engine=engine)


# =====================================================================
# Auxiliares para os formulários (preencher menus suspensos)
# =====================================================================
def ofertas_da_empresa(empresa, engine=None):
    """Serviços que a empresa oferece (para escolher o serviço de um item)."""
    return db.fetch_df(
        "SELECT nome_servico, preco_hora FROM OFERTA_SERVICO "
        "WHERE nome_empresa=:e ORDER BY nome_servico", {"e": empresa}, engine=engine)


def cidades_da_empresa(empresa, engine=None):
    """Cidades onde a empresa atua (para partida/destino do pedido)."""
    return db.fetch_df(
        "SELECT estado, nome_cidade FROM EMPRESA_ATUA_CIDADE "
        "WHERE nome_empresa=:e ORDER BY estado, nome_cidade", {"e": empresa},
        engine=engine)


def funcionarios_da_empresa(empresa, engine=None):
    """Funcionários que trabalham na empresa (para escolher executores)."""
    return db.fetch_df(
        "SELECT f.cpf, f.nome_completo FROM TRABALHA t "
        "JOIN FUNCIONARIO f ON f.cpf = t.cpf_funcionario "
        "WHERE t.nome_empresa=:e ORDER BY f.nome_completo", {"e": empresa},
        engine=engine)