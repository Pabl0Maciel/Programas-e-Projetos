"""
main.py — Interface do Sistema de Empresas de Mudanças (alinhado ao gabarito).
Navegação agrupada (Cadastros / Consultas). Depende de db, crud, queries.
Rodar: streamlit run app/main.py
"""
import streamlit as st
import plotly.express as px

import db
import crud
import queries as q


# ===================== Utilidades =====================
def fmt_moeda(v):
    try:
        return "R$ " + f"{float(v):,.2f}".replace(",", "X").replace(".", ",").replace("X", ".")
    except (TypeError, ValueError):
        return "-"


def horas_para_time(horas):
    total = int(round(float(horas) * 3600))
    h, r = divmod(total, 3600)
    m, s = divmod(r, 60)
    return f"{h:02d}:{m:02d}:{s:02d}"


def erro_amigavel(e):
    msg = str(e)
    if "Disjuncao" in msg:
        return "Restrição de disjunção: o tipo do serviço não corresponde ao subtipo."
    if "nao pertence a empresa" in msg:
        return "A oferta escolhida não pertence à empresa do pedido."
    if "Duplicate entry" in msg:
        return "Registro duplicado: essa chave já existe."
    if "foreign key constraint fails" in msg:
        return "Violação de integridade: existe(m) registro(s) relacionado(s), ou o valor referenciado não existe."
    return msg


def sel_empresa(empresas, key, label="Empresa"):
    """Selectbox de empresa que mostra o nome mas devolve o id_empresa."""
    return st.selectbox(label, options=list(empresas["id_empresa"]),
                        format_func=lambda i: empresas.loc[empresas.id_empresa == i, "nome"].iloc[0],
                        key=key)


# ===================== INÍCIO =====================
def pagina_inicio():
    st.title("🚚 Sistema de Empresas de Mudanças")
    st.caption("Trabalho Semestral de Banco de Dados 2 — EACH/USP · 2026-I")
    ok, msg = db.test_connection()
    (st.success if ok else st.error)(msg)
    if not ok:
        st.stop()
    c1, c2, c3 = st.columns(3)
    c1.metric("🏢 Empresas", len(crud.listar_empresas()))
    c2.metric("👤 Clientes", len(crud.listar_clientes()))
    c3.metric("📦 Pedidos", len(crud.listar_pedidos()))
    c4, c5, c6 = st.columns(3)
    c4.metric("🏙️ Cidades", len(crud.listar_cidades()))
    c5.metric("🧰 Serviços", len(crud.listar_servicos()))
    c6.metric("👷 Funcionários", len(crud.listar_funcionarios()))
    st.info("Use o menu à esquerda: **Cadastros** para inserir dados, **Consultas** para os relatórios.")


# ===================== CADASTROS =====================
def pagina_cidades():
    st.title("🏙️ Cidades")
    with st.form("form_cidade", clear_on_submit=True):
        c1, c2 = st.columns([1, 3])
        estado = c1.text_input("Estado (UF)", max_chars=2).upper()
        nome = c2.text_input("Nome da cidade")
        if st.form_submit_button("Adicionar cidade", type="primary"):
            try:
                crud.criar_cidade(estado, nome)
                st.success(f"Cidade {nome}/{estado} adicionada.")
            except Exception as e:
                st.error(erro_amigavel(e))
    df = crud.listar_cidades()
    st.dataframe(df, width="stretch", hide_index=True)
    if not df.empty:
        opc = {f"{r.nome_cidade}/{r.estado}": (r.estado, r.nome_cidade) for r in df.itertuples()}
        alvo = st.selectbox("Excluir cidade", options=list(opc.keys()))
        if st.button("🗑️ Excluir", key="del_cidade"):
            try:
                crud.excluir_cidade(*opc[alvo]); st.success("Cidade excluída."); st.rerun()
            except Exception as e:
                st.error(erro_amigavel(e))


def pagina_clientes():
    st.title("👤 Clientes")
    with st.form("form_cliente", clear_on_submit=True):
        nome = st.text_input("Nome completo")
        c1, c2 = st.columns(2)
        cpf = c1.text_input("CPF"); rg = c2.text_input("RG")
        endereco = st.text_input("Endereço")
        tel = st.text_input("Telefone (opcional)")
        if st.form_submit_button("Cadastrar cliente", type="primary"):
            try:
                cod = crud.criar_cliente(cpf, rg, nome, endereco)
                if tel.strip():
                    crud.adicionar_telefone_cliente(cod, tel.strip())
                st.success(f"Cliente cadastrado (código {cod}).")
            except Exception as e:
                st.error(erro_amigavel(e))
    df = crud.listar_clientes()
    st.dataframe(df, width="stretch", hide_index=True)
    if not df.empty:
        alvo = st.selectbox("Excluir cliente", options=list(df["cod_cliente"]),
                            format_func=lambda c: f"{c} — {df.loc[df.cod_cliente==c,'nome_completo'].iloc[0]}")
        if st.button("🗑️ Excluir", key="del_cliente"):
            try:
                crud.excluir_cliente(int(alvo)); st.success("Cliente excluído."); st.rerun()
            except Exception as e:
                st.error(erro_amigavel(e))


def pagina_empresas():
    st.title("🏢 Empresas")
    empresas = crud.listar_empresas()
    aba_dados, aba_ofertas = st.tabs(["📋 Dados", "💰 Ofertas (serviço × cidade)"])

    with aba_dados:
        with st.form("form_empresa", clear_on_submit=True):
            nome = st.text_input("Nome da empresa (único)")
            endereco = st.text_input("Endereço")
            tel = st.text_input("Telefone (opcional)")
            if st.form_submit_button("Cadastrar empresa", type="primary"):
                try:
                    idx = crud.criar_empresa(nome, endereco)
                    if tel.strip():
                        crud.adicionar_telefone_empresa(idx, tel.strip())
                    st.success(f"Empresa '{nome}' cadastrada (id {idx})."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))
        st.dataframe(empresas, width="stretch", hide_index=True)
        if not empresas.empty:
            alvo = sel_empresa(empresas, "del_emp_sel", "Excluir empresa")
            if st.button("🗑️ Excluir", key="del_emp"):
                try:
                    crud.excluir_empresa(int(alvo)); st.success("Empresa excluída."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))

    if empresas.empty:
        return
    with aba_ofertas:
        st.caption("A oferta é por **empresa × serviço × cidade** (preço/hora pode variar por cidade). "
                   "As cidades onde a empresa atua vêm das ofertas cadastradas.")
        emp_id = sel_empresa(empresas, "emp_of")
        servs = list(crud.listar_servicos()["nome_servico"])
        cidades = crud.listar_cidades()
        opc_cid = {f"{r.nome_cidade}/{r.estado}": (r.estado, r.nome_cidade) for r in cidades.itertuples()}
        with st.form("form_oferta", clear_on_submit=True):
            c1, c2, c3 = st.columns([2, 2, 1])
            s = c1.selectbox("Serviço", options=servs) if servs else None
            cid = c2.selectbox("Cidade", options=list(opc_cid.keys())) if opc_cid else None
            preco = c3.number_input("Preço/hora (R$)", min_value=0.0, step=10.0)
            if st.form_submit_button("Adicionar oferta", type="primary") and s and cid:
                try:
                    uf, nc = opc_cid[cid]
                    crud.adicionar_oferta(int(emp_id), s, uf, nc, preco)
                    st.success("Oferta adicionada."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))
        ofertas = crud.listar_ofertas(int(emp_id))
        st.dataframe(ofertas, width="stretch", hide_index=True)
        if not ofertas.empty:
            alvo = st.selectbox("Remover oferta", options=list(ofertas["id_oferta"]),
                                format_func=lambda i: f"{ofertas.loc[ofertas.id_oferta==i,'nome_servico'].iloc[0]} "
                                f"em {ofertas.loc[ofertas.id_oferta==i,'nome_cidade'].iloc[0]}")
            if st.button("🗑️ Remover", key="del_of"):
                try:
                    crud.remover_oferta(int(alvo)); st.success("Oferta removida."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))


def pagina_funcionarios():
    st.title("👷 Funcionários")
    funcs = crud.listar_funcionarios()
    empresas = crud.listar_empresas()
    aba_dados, aba_vinc = st.tabs(["📋 Dados", "🔗 Vínculo com empresa"])

    with aba_dados:
        with st.form("form_func", clear_on_submit=True):
            nome = st.text_input("Nome completo")
            c1, c2 = st.columns(2)
            cpf = c1.text_input("CPF"); rg = c2.text_input("RG")
            c3, c4 = st.columns(2)
            tipo = c3.text_input("Tipo (motorista, guincho, gerente...)")
            salario = c4.number_input("Salário (R$)", min_value=0.0, step=100.0)
            endereco = st.text_input("Endereço")
            tel = st.text_input("Telefone (opcional)")
            if st.form_submit_button("Cadastrar funcionário", type="primary"):
                try:
                    crud.criar_funcionario(cpf, rg, salario, tipo, nome, endereco)
                    if tel.strip():
                        crud.adicionar_telefone_funcionario(cpf, tel.strip())
                    st.success(f"Funcionário '{nome}' cadastrado."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))
        st.dataframe(funcs, width="stretch", hide_index=True)
        if not funcs.empty:
            alvo = st.selectbox("Excluir funcionário", options=list(funcs["cpf"]),
                                format_func=lambda c: funcs.loc[funcs.cpf==c, 'nome_completo'].iloc[0], key="del_func_sel")
            if st.button("🗑️ Excluir", key="del_func"):
                try:
                    crud.excluir_funcionario(alvo); st.success("Funcionário excluído."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))

    with aba_vinc:
        if funcs.empty or empresas.empty:
            st.caption("Cadastre funcionário e empresa primeiro.")
        else:
            with st.form("form_trabalha", clear_on_submit=True):
                cpf_sel = st.selectbox("Funcionário", options=list(funcs["cpf"]),
                                       format_func=lambda c: funcs.loc[funcs.cpf==c, 'nome_completo'].iloc[0])
                emp_id = sel_empresa(empresas, "emp_trab")
                c1, c2 = st.columns(2)
                horario = c1.text_input("Horário (ex.: 08:00-17:00)")
                tel_emp = c2.text_input("Telefone da empresa (opcional)")
                if st.form_submit_button("Vincular", type="primary"):
                    try:
                        crud.adicionar_trabalha(cpf_sel, int(emp_id), horario, tel_emp or None)
                        st.success("Vínculo criado."); st.rerun()
                    except Exception as e:
                        st.error(erro_amigavel(e))
            st.dataframe(crud.listar_trabalha(), width="stretch", hide_index=True)


def pagina_servicos():
    st.title("🧰 Serviços")
    st.caption("Hierarquia parcial e disjunta: Simples, Guindaste OU Transporte (o tipo é gravado em tipo_servico).")
    df = crud.listar_servicos()
    aba_serv, aba_regras = st.tabs(["🧰 Serviços", "⚖️ Regras de transporte"])

    with aba_serv:
        tipo = st.radio("Tipo a cadastrar", ["Simples", "Guindaste", "Transporte"], horizontal=True)
        with st.form("form_servico", clear_on_submit=True):
            nome = st.text_input("Nome do serviço")
            base = altura = bonus = 0.0
            if tipo == "Guindaste":
                c1, c2, c3 = st.columns(3)
                base = c1.number_input("Tamanho da base", min_value=0.0, step=0.5)
                altura = c2.number_input("Altura", min_value=0.0, step=1.0)
                bonus = c3.number_input("Bônus de altura (R$)", min_value=0.0, step=50.0)
            if st.form_submit_button("Cadastrar serviço", type="primary"):
                try:
                    if tipo == "Simples":
                        crud.criar_servico_simples(nome)
                    elif tipo == "Guindaste":
                        crud.criar_guindaste(nome, base, altura, bonus)
                    else:
                        crud.criar_transporte(nome)
                    st.success(f"Serviço '{nome}' ({tipo}) cadastrado."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))
        st.dataframe(df, width="stretch", hide_index=True)
        if not df.empty:
            alvo = st.selectbox("Excluir serviço", options=list(df["nome_servico"]), key="del_serv_sel")
            if st.button("🗑️ Excluir", key="del_serv"):
                try:
                    crud.excluir_servico(alvo); st.success("Serviço excluído."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))

    with aba_regras:
        st.caption("O acréscimo é padronizado **por serviço de transporte** (não por empresa).")
        transportes = list(df.loc[df["tipo"] == "TRANSPORTE", "nome_servico"])
        if transportes:
            with st.form("form_regra", clear_on_submit=True):
                c1, c2, c3 = st.columns(3)
                tr = c1.selectbox("Serviço de transporte", options=transportes)
                pct = c2.number_input("Percentual (%)", min_value=0.0, step=1.0)
                kg = c3.number_input("Acima de (kg)", min_value=0.0, step=50.0)
                if st.form_submit_button("Adicionar regra", type="primary"):
                    try:
                        crud.adicionar_regra_transporte(tr, pct, kg)
                        st.success("Regra adicionada."); st.rerun()
                    except Exception as e:
                        st.error(erro_amigavel(e))
        else:
            st.caption("Cadastre ao menos um serviço de transporte.")
        st.dataframe(crud.listar_regras(), width="stretch", hide_index=True)


def pagina_pedidos():
    st.title("📦 Pedidos")
    clientes = crud.listar_clientes()
    empresas = crud.listar_empresas()
    if clientes.empty or empresas.empty:
        st.warning("Cadastre ao menos um cliente e uma empresa antes de criar pedidos.")
        return
    aba_novo, aba_lista = st.tabs(["➕ Novo pedido", "📋 Pedidos cadastrados"])

    with aba_novo:
        c1, c2 = st.columns(2)
        with c1:
            cli = st.selectbox("Cliente", options=list(clientes["cod_cliente"]),
                               format_func=lambda c: clientes.loc[clientes.cod_cliente==c, "nome_completo"].iloc[0])
        with c2:
            emp_id = sel_empresa(empresas, "emp_ped")

        cidades_emp = crud.cidades_da_empresa(int(emp_id))
        if cidades_emp.empty:
            st.warning("Esta empresa ainda não tem ofertas (serviço × cidade). Cadastre em Empresas → Ofertas.")
            return
        opc_cid = {f"{r.nome_cidade}/{r.estado}": (r.estado, r.nome_cidade) for r in cidades_emp.itertuples()}

        c3, c4 = st.columns(2)
        part = c3.selectbox("Cidade de partida", options=list(opc_cid.keys()))
        dest = c4.selectbox("Cidade de destino", options=list(opc_cid.keys()))
        c5, c6 = st.columns(2)
        end_part = c5.text_input("Endereço de partida")
        end_dest = c6.text_input("Endereço de destino")
        c7, c8 = st.columns(2)
        data_sol = c7.date_input("Data da solicitação")
        status = c8.selectbox("Status", ["PENDENTE", "ACEITO", "REJEITADO"])
        if status == "PENDENTE":
            data_res = None
            st.caption("Pedido pendente: sem data de resolução.")
        else:
            data_res = st.date_input("Data de resolução", value=data_sol)

        # Limpa itens ao trocar empresa/partida (o preço depende da cidade de partida)
        ctx = (int(emp_id), part)
        if st.session_state.get("_ctx_pedido") != ctx:
            st.session_state["itens_pedido"] = []
            st.session_state["_ctx_pedido"] = ctx
        st.session_state.setdefault("itens_pedido", [])

        uf_p, cid_p = opc_cid[part]
        ofertas_part = crud.ofertas_empresa_cidade(int(emp_id), uf_p, cid_p)
        oferta_por_serv = {r.nome_servico: r.id_oferta for r in ofertas_part.itertuples()}
        funcs_emp = crud.funcionarios_da_empresa(int(emp_id))
        opc_func = {f"{r.nome_completo} ({r.cpf})": r.cpf for r in funcs_emp.itertuples()}

        st.markdown(f"**Itens do pedido** — serviços ofertados em {part}")
        with st.form("form_add_item", clear_on_submit=True):
            serv = st.selectbox("Serviço", options=list(oferta_por_serv.keys()))
            cc1, cc2 = st.columns(2)
            horas = cc1.number_input("Duração (horas)", min_value=0.0, step=0.5, value=1.0)
            peso = cc2.number_input("Peso da carga (kg) — só p/ transporte", min_value=0.0, step=50.0, value=0.0)
            data_real = st.date_input("Data de realização (se já executado)", value=None)
            execs = st.multiselect("Funcionários executores (se já executado)", options=list(opc_func.keys()))
            if st.form_submit_button("➕ Adicionar item") and serv:
                st.session_state["itens_pedido"].append({
                    "id_oferta": int(oferta_por_serv[serv]), "servico": serv,
                    "tempo": horas_para_time(horas),
                    "peso": peso if peso > 0 else None,
                    "data_realizacao": str(data_real) if data_real else None,
                    "executores": [opc_func[x] for x in execs],
                })

        itens = st.session_state["itens_pedido"]
        if itens:
            st.table([{"serviço": it["servico"], "tempo": it["tempo"], "peso": it["peso"] or "-",
                       "realização": it.get("data_realizacao") or "-", "executores": len(it["executores"])}
                      for it in itens])
            b1, b2 = st.columns(2)
            if b1.button("💾 Salvar pedido", type="primary"):
                try:
                    ud, cd = opc_cid[dest]
                    cod = crud.criar_pedido(
                        cliente_cod=int(cli), id_empresa=int(emp_id),
                        data_solicitacao=str(data_sol), status=status,
                        data_resolucao=(str(data_res) if data_res else None),
                        estado_partida=uf_p, cidade_partida=cid_p,
                        estado_destino=ud, cidade_destino=cd,
                        endereco_partida=end_part or None, endereco_destino=end_dest or None,
                        itens=itens)
                    st.session_state["itens_pedido"] = []
                    st.success(f"Pedido {cod} salvo! (total calculado pelos triggers)"); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))
            if b2.button("🗑️ Limpar itens"):
                st.session_state["itens_pedido"] = []; st.rerun()
        else:
            st.caption("Adicione pelo menos um item para salvar o pedido.")

    with aba_lista:
        peds = crud.listar_pedidos()
        if peds.empty:
            st.caption("Nenhum pedido cadastrado ainda.")
        else:
            vis = peds.copy(); vis["preco_total"] = vis["preco_total"].map(fmt_moeda)
            st.dataframe(vis, width="stretch", hide_index=True)
            cod_ver = st.selectbox("Ver itens do pedido", options=list(peds["cod_pedido"]))
            st.dataframe(crud.listar_itens_pedido(int(cod_ver)), width="stretch", hide_index=True)
            if st.button("🗑️ Excluir pedido selecionado", key="del_ped"):
                try:
                    crud.excluir_pedido(int(cod_ver)); st.success("Pedido excluído."); st.rerun()
                except Exception as e:
                    st.error(erro_amigavel(e))


# ===================== CONSULTAS =====================
def pagina_resultados():
    st.title("📊 Resultados")
    aba_cidade, aba_empresa = st.tabs(["🏙️ Por cidade", "🏢 Por empresa"])

    with aba_cidade:
        st.subheader("Serviços solicitados por cidade")
        d1 = q.q1_servicos_por_cidade()
        if not d1.empty:
            fig = px.bar(d1, x="cidade", y="num_servicos", text="num_servicos",
                         color="num_servicos", color_continuous_scale="Blues")
            fig.update_layout(coloraxis_showscale=False)
            st.plotly_chart(fig, width="stretch")
        st.subheader("Pagamentos dos serviços por cidade (executados)")
        d2 = q.q2_pagamentos_por_cidade()
        if not d2.empty:
            fig = px.bar(d2, x="cidade", y="total_pago", text_auto=".2f",
                         color="total_pago", color_continuous_scale="Greens")
            fig.update_layout(coloraxis_showscale=False)
            st.plotly_chart(fig, width="stretch")
        st.divider()
        col1, col2 = st.columns(2)
        with col1:
            st.markdown("**🏆 Top 5 cidades — valor investido**")
            d3 = q.q3_top5_cidades_valor().copy()
            if not d3.empty:
                d3["valor_investido"] = d3["valor_investido"].map(fmt_moeda)
            st.dataframe(d3, width="stretch", hide_index=True)
        with col2:
            st.markdown("**🏆 Top 5 cidades — nº de serviços**")
            st.dataframe(q.q4_top5_cidades_servicos(), width="stretch", hide_index=True)

    with aba_empresa:
        st.subheader("Top 5 empresas por nº de serviços solicitados")
        d5 = q.q5_top5_empresas_servicos()
        if not d5.empty:
            fig = px.bar(d5, x="num_servicos", y="empresa", orientation="h", text="num_servicos",
                         color="num_servicos", color_continuous_scale="Purples")
            fig.update_layout(coloraxis_showscale=False, yaxis={"categoryorder": "total ascending"})
            st.plotly_chart(fig, width="stretch")
            st.dataframe(d5, width="stretch", hide_index=True)
        st.subheader("Top 5 empresas por valores ganhos (executados)")
        d6 = q.q6_top5_empresas_ganhos()
        if not d6.empty:
            fig = px.bar(d6, x="total_ganho", y="empresa", orientation="h", text_auto=".2f",
                         color="total_ganho", color_continuous_scale="Oranges")
            fig.update_layout(coloraxis_showscale=False, yaxis={"categoryorder": "total ascending"})
            st.plotly_chart(fig, width="stretch")
            d6v = d6.copy(); d6v["total_ganho"] = d6v["total_ganho"].map(fmt_moeda)
            st.dataframe(d6v, width="stretch", hide_index=True)


# ===================== Navegação =====================
def main():
    st.set_page_config(page_title="Sistema de Mudanças", page_icon="🚚", layout="wide")
    st.sidebar.title("🚚 Mudanças")
    st.sidebar.caption("BD2 — EACH/USP")
    nav = st.navigation({
        "": [st.Page(pagina_inicio, title="Início", icon="🏠", default=True)],
        "Cadastros": [
            st.Page(pagina_cidades, title="Cidades", icon="🏙️"),
            st.Page(pagina_clientes, title="Clientes", icon="👤"),
            st.Page(pagina_empresas, title="Empresas", icon="🏢"),
            st.Page(pagina_funcionarios, title="Funcionários", icon="👷"),
            st.Page(pagina_servicos, title="Serviços", icon="🧰"),
            st.Page(pagina_pedidos, title="Pedidos", icon="📦"),
        ],
        "Consultas": [st.Page(pagina_resultados, title="Resultados", icon="📊")],
    })
    nav.run()


if __name__ == "__main__":
    main()