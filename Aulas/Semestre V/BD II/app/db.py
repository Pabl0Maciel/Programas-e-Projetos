"""
db.py — Conexão central com o banco MySQL do sistema de Mudanças.

Todo o resto da aplicação (crud.py, queries.py, main.py) importa daqui,
para que os dados de conexão fiquem definidos em um único lugar.
"""
from sqlalchemy import create_engine, text
import pandas as pd

# ---------------------------------------------------------------------
# Configuração da conexão (banco local do trabalho)
# Se você mudar o usuário/senha do MySQL, altere APENAS estas linhas.
# ---------------------------------------------------------------------
DB_USER = "dev"
DB_PASSWORD = "123"
DB_HOST = "127.0.0.1"
DB_PORT = 3306
DB_NAME = "mudancas"

DB_URL = (
    f"mysql+mysqlconnector://{DB_USER}:{DB_PASSWORD}"
    f"@{DB_HOST}:{DB_PORT}/{DB_NAME}?charset=utf8mb4"
)

# pool_pre_ping: testa a conexão antes de usar (evita erro de conexão
#   expirada quando o app fica ocioso).
# pool_recycle: recicla conexões a cada 1h (menor que o wait_timeout do MySQL).
ENGINE = create_engine(DB_URL, pool_pre_ping=True, pool_recycle=3600)


def fetch_df(sql, params=None, engine=None):
    """Executa um SELECT e devolve o resultado como um pandas.DataFrame.

    Use parâmetros nomeados (:nome) em vez de concatenar strings — protege
    contra SQL injection e evita erros de aspas.
        fetch_df("SELECT * FROM CLIENTE WHERE cod_cliente = :c", {"c": 1})
    """
    eng = engine or ENGINE
    with eng.connect() as conn:
        return pd.read_sql(text(sql), conn, params=params or {})


def execute(sql, params=None, engine=None):
    """Executa INSERT/UPDATE/DELETE dentro de uma transação (commit no fim).

    Retorna um dict com {'lastrowid', 'rowcount'}. O commit é automático;
    se der erro, a transação sofre rollback sozinha.
    """
    eng = engine or ENGINE
    with eng.begin() as conn:
        result = conn.execute(text(sql), params or {})
        return {"lastrowid": result.lastrowid, "rowcount": result.rowcount}


def test_connection(engine=None):
    """Confirma que a conexão está de pé. Devolve (ok: bool, mensagem: str)."""
    eng = engine or ENGINE
    try:
        with eng.connect() as conn:
            versao = conn.execute(text("SELECT VERSION()")).scalar()
        return True, f"Conectado ao MySQL {versao}"
    except Exception as e:
        return False, f"Falha na conexão: {e}"


# Permite testar rapidamente pelo terminal:  python db.py
if __name__ == "__main__":
    ok, msg = test_connection()
    print(msg)