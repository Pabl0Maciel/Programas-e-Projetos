# :bar_chart: Como usar o Dashboard Documentation Agent (DDA)
**Por: Pablo Maciel**
**Link para o DDA:** [:link:Documentador de Dashboards](https://tess.im/pt-BR/dashboard/user/ai/chat/ai-chat/documentador-de-dashboards-QQoK9w)

---

## :computer: 1) O que o agente faz

O Dashboard Documentation Agent (DDA) gera documentação técnica padronizada em Markdown (.md) a partir de referências visuais e do modelo semântico do dashboard.

Ele recebe:
- :jigsaw: YAML do modelo semântico (extraído via Tabular Editor 2)
- :bar_chart: PDF exportado do Power BI e/ou prints das páginas
- :gear: Informações técnicas do dashboard

E entrega:
- :page_facing_up: Documentação completa das páginas do dashboard (visuais, filtros, indicadores)
- :file_cabinet: Modelo de dados detalhado (tabelas, colunas, tipos)
- :triangular_ruler: Todas as medidas DAX preservadas literalmente
- :link: Todos os relacionamentos entre tabelas
- :white_check_mark: Arquivo .md pronto para uso na Wiki, SharePoint, Git ou Notion

---

## :dart: 2) Quando usar este agente

Use este agente quando você precisar:
- Documentar um dashboard Power BI de forma padronizada
- Registrar o modelo semântico de um relatório .pbix
- Criar uma referência técnica para equipes de dados ou negócio
- Manter histórico de dashboards em repositórios como Git ou SharePoint

Exemplos:
- :moneybag: Documentar um dashboard financeiro antes de uma entrega
- :bar_chart: Registrar as medidas DAX de um modelo complexo
- :blue_book: Criar um manual de referência para um relatório crítico da operação

---

## :inbox_tray: 3) Entradas obrigatórias

Você deve fornecer:

**a) YAML do modelo semântico**
- Extraído via script no Tabular Editor 2
- Deve conter obrigatoriamente: `modelName`, `tables`, `columns`, `measures`, `relationships`
- Ver seção 6 para instruções de extração

**b) Visual do dashboard**
- PDF exportado do Power BI (recomendado)
- e/ou prints das páginas em alta resolução

**c) Informações técnicas**
- Caminho na rede (UNC ou URL do arquivo .pbix)
- Frequência de atualização
- Nome do desenvolvedor e equipe
- Equipe destinada ao uso do dashboard
- Link do relatório publicado no Power BI Service

---

## :heavy_plus_sign: 4) Entradas opcionais

Você pode complementar com:
- :page_with_curl: Prints adicionais para reforçar páginas do PDF
- :brain: Contexto adicional por página (ex: "esta página é voltada para o time comercial")
- :bulb: Observações de negócio relevantes para o dashboard

Esses itens ajudam a:
- Melhorar a descrição funcional dos visuais
- Preencher lacunas quando o PDF ou YAML estiver incompleto

---

## :rocket: 5) Como acionar o agente

Envie todas as informações em uma única mensagem, usando o modelo abaixo:

```
Caminho: <\\servidor\pasta\arquivo.pbix>
Frequência: <Diária / Semanal / Mensal>
Desenvolvido por: <Nome — Equipe>
Equipe destinada: <Nome da equipe>
Link: <https://app.powerbi.com/...>

Páginas: <opcional — se quiser nomear manualmente>

Observações: <contexto adicional, se houver>

Gere a documentação completa do dashboard.

(Anexar: YAML + PDF e/ou prints)
```

---

## :gear: 6) Como extrair o YAML (Tabular Editor 2)

**Pré-requisito:**
- Tabular Editor 2 instalado
- Script `extrator_infos_dashboard_V4.txt` disponível abaixo:
<details>
<summary>Ver conteúdo</summary>

```C#
  using System.IO;
using System.Text;
using System.Text.RegularExpressions;

string outputFolder = @"caminho-da-pasta";
string fileName = "nome-do-arquivo.yaml";
bool includeHidden = false;

string fullPath = Path.Combine(outputFolder, fileName);

if (!Directory.Exists(outputFolder))
    Directory.CreateDirectory(outputFolder);

Func<int, string> I = n => new string(' ', n * 2);

Func<string, string> Safe = s => s ?? "";

Func<string, string> Scalar = value =>
{
    value = Safe(value);

    if (string.IsNullOrEmpty(value))
        return "\"\"";

    bool needsQuotes =
        value.Contains(":") ||
        value.Contains("#") ||
        value.Contains("\"") ||
        value.Contains("'") ||
        value.StartsWith(" ") ||
        value.StartsWith("-") ||
        value.StartsWith("*") ||
        value.StartsWith("{") ||
        value.StartsWith("[") ||
        value.StartsWith("|") ||
        value.StartsWith(">") ||
        value.StartsWith("!") ||
        value.StartsWith("&") ||
        value.StartsWith("%") ||
        value.Contains("\\") ||
        value.Contains("[") ||
        value.Contains("]");

    if (needsQuotes)
    {
        string escaped = value.Replace("\\", "\\\\").Replace("\"", "\\\"");
        return "\"" + escaped + "\"";
    }

    return value;
};

Func<string, int, string> Block = (text, indent) =>
{
    text = Safe(text);

    if (string.IsNullOrWhiteSpace(text))
        return "\"\"";

    string pad = I(indent);
    string[] lines = text.Replace("\r\n", "\n").Replace("\r", "\n").Split('\n');
    var sb = new StringBuilder();

    sb.AppendLine("|");
    foreach (var line in lines)
        sb.AppendLine(pad + line);

    return sb.ToString().TrimEnd();
};

Func<string, string> NormalizeLineBreaks = text =>
{
    return Safe(text).Replace("\r\n", "\n").Replace("\r", "\n");
};

Func<string, string> DetectTableType = source =>
{
    source = NormalizeLineBreaks(source).Trim();

    if (string.IsNullOrWhiteSpace(source))
        return "Unknown";

    if (source.StartsWith("let", StringComparison.OrdinalIgnoreCase))
        return "Imported";

    return "Calculated";
};

Func<string, string> DetectSourceType = source =>
{
    source = NormalizeLineBreaks(source);

    if (string.IsNullOrWhiteSpace(source))
        return "Unknown";

    if (!source.TrimStart().StartsWith("let", StringComparison.OrdinalIgnoreCase))
        return "DAX";

    if (source.IndexOf("Sql.Database", StringComparison.OrdinalIgnoreCase) >= 0)
        return "PowerQuerySql";

    if (source.IndexOf("Csv.Document", StringComparison.OrdinalIgnoreCase) >= 0 &&
        source.IndexOf("File.Contents", StringComparison.OrdinalIgnoreCase) >= 0)
        return "PowerQueryCsv";

    if (source.IndexOf("Excel.Workbook", StringComparison.OrdinalIgnoreCase) >= 0 &&
        source.IndexOf("File.Contents", StringComparison.OrdinalIgnoreCase) >= 0)
        return "PowerQueryExcel";

    if (source.IndexOf("SharePoint.Files", StringComparison.OrdinalIgnoreCase) >= 0)
        return "PowerQuerySharePoint";

    return "PowerQuery";
};

Func<string, string> ExtractSourceSummary = source =>
{
    source = NormalizeLineBreaks(source);

    if (string.IsNullOrWhiteSpace(source))
        return "não identificado";

    string trimmed = source.TrimStart();

    if (!trimmed.StartsWith("let", StringComparison.OrdinalIgnoreCase))
        return "Tabela calculada (DAX)";

    try
    {
        Match fileMatch = Regex.Match(
            source,
            "File\\.Contents\\(\"(?<path>[^\"]+)\"\\)",
            RegexOptions.IgnoreCase
        );

        if (fileMatch.Success)
        {
            string path = fileMatch.Groups["path"].Value;
            string normalizedPath = path.Replace("/", "\\");
            string[] parts = normalizedPath.Split(new[] { '\\' }, StringSplitOptions.RemoveEmptyEntries);

            string host = "arquivo";
            string file = parts.Length > 0 ? parts[parts.Length - 1] : "não identificado";

            if (normalizedPath.StartsWith("\\\\") && parts.Length > 0)
                host = parts[0];
            else if (parts.Length > 1)
                host = parts[parts.Length - 2];

            return host + " - " + file;
        }
    }
    catch { }

    try
    {
        Match sqlDbMatch = Regex.Match(
            source,
            "Sql\\.Database\\(\\s*\"(?<server>[^\"]+)\"\\s*,\\s*\"(?<database>[^\"]+)\"",
            RegexOptions.IgnoreCase
        );

        string server = "";
        if (sqlDbMatch.Success)
            server = sqlDbMatch.Groups["server"].Value;

        Match fromMatch = Regex.Match(
            source,
            "FROM\\s+\\[(?<schema>[^\\]]+)\\]\\.\\[(?<object>[^\\]]+)\\]",
            RegexOptions.IgnoreCase
        );

        if (fromMatch.Success)
        {
            string schemaName = fromMatch.Groups["schema"].Value;
            string objectName = fromMatch.Groups["object"].Value;

            if (!string.IsNullOrWhiteSpace(server))
                return server + " - " + schemaName + "." + objectName;

            return schemaName + "." + objectName;
        }

        Match simpleFromMatch = Regex.Match(
            source,
            "FROM\\s+(?<schema>[A-Za-z0-9_]+)\\.(?<object>[A-Za-z0-9_]+)",
            RegexOptions.IgnoreCase
        );

        if (simpleFromMatch.Success)
        {
            string schemaName = simpleFromMatch.Groups["schema"].Value;
            string objectName = simpleFromMatch.Groups["object"].Value;

            if (!string.IsNullOrWhiteSpace(server))
                return server + " - " + schemaName + "." + objectName;

            return schemaName + "." + objectName;
        }

        if (!string.IsNullOrWhiteSpace(server))
            return server + " - origem SQL";
    }
    catch { }

    return "Consulta Power Query (origem não identificada)";
};

Func<object, string> DetectCardinality = relObj =>
{
    try
    {
        var rel = relObj as TabularEditor.TOMWrapper.SingleColumnRelationship;
        if (rel != null)
        {
            string fromMult = rel.FromCardinality.ToString();
            string toMult = rel.ToCardinality.ToString();

            if (fromMult == "One" && toMult == "Many") return "1:N";
            if (fromMult == "Many" && toMult == "One") return "N:1";
            if (fromMult == "One" && toMult == "One") return "1:1";
            if (fromMult == "Many" && toMult == "Many") return "N:N";

            return fromMult + ":" + toMult;
        }
    }
    catch { }

    return "nao-identificado";
};


var yaml = new StringBuilder();

yaml.AppendLine("modelName: " + Scalar(Model.Name));
yaml.AppendLine("exportInfo:");
yaml.AppendLine(I(1) + "generatedAt: " + Scalar(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss")));
yaml.AppendLine(I(1) + "exporter: " + Scalar("Tabular Editor 2"));
yaml.AppendLine(I(1) + "includeHidden: " + includeHidden.ToString().ToLower());
yaml.AppendLine();
yaml.AppendLine("tables:");

foreach (var t in Model.Tables)
{
    if (!includeHidden && t.IsHidden) continue;

    string source = "";
    try
    {
        if (t.Partitions.Count > 0 && t.Partitions[0].Query != null)
            source = t.Partitions[0].Query;
    }
    catch
    {
        source = "";
    }

    string tableType = DetectTableType(source);
    string sourceType = DetectSourceType(source);
    string sourceSummary = ExtractSourceSummary(source);

    yaml.AppendLine(I(1) + "- name: " + Scalar(t.Name));
    yaml.AppendLine(I(2) + "isHidden: " + t.IsHidden.ToString().ToLower());
    yaml.AppendLine(I(2) + "tableType: " + Scalar(tableType));
    yaml.AppendLine(I(2) + "sourceType: " + Scalar(sourceType));
    yaml.AppendLine(I(2) + "sourceSummary: " + Scalar(sourceSummary));

    yaml.Append(I(2) + "source: ");
    if (string.IsNullOrWhiteSpace(source))
        yaml.AppendLine("\"\"");
    else
        yaml.AppendLine(Block(source, 3));

    var cols = t.Columns.Where(c => includeHidden || !c.IsHidden).ToList();

    yaml.AppendLine(I(2) + "columns:");
    if (cols.Count == 0)
    {
        yaml.AppendLine(I(3) + "[]");
    }
    else
    {
        foreach (var c in cols)
        {
            yaml.AppendLine(I(3) + "- name: " + Scalar(c.Name));
            yaml.AppendLine(I(4) + "dataType: " + Scalar(c.DataType.ToString()));
            yaml.AppendLine(I(4) + "isHidden: " + c.IsHidden.ToString().ToLower());
        }
    }

    var measures = t.Measures.Where(m => includeHidden || !m.IsHidden).ToList();

    yaml.AppendLine(I(2) + "measures:");
    if (measures.Count == 0)
    {
        yaml.AppendLine(I(3) + "[]");
    }
    else
    {
        foreach (var m in measures)
        {
            string expr = m.Expression ?? "";

            yaml.AppendLine(I(3) + "- name: " + Scalar(m.Name));
            yaml.AppendLine(I(4) + "isHidden: " + m.IsHidden.ToString().ToLower());
            yaml.Append(I(4) + "expression: ");
            yaml.AppendLine(Block(expr, 5));
        }
    }

    yaml.AppendLine();
}

yaml.AppendLine("relationships:");

var rels = Model.Relationships.ToList();

if (rels.Count == 0)
{
    yaml.AppendLine(I(1) + "[]");
}
else
{
    foreach (var rel in rels)
    {
        string direction = "nao-identificado";
        string cardinality = "nao-identificado";
        string isActive = "nao-identificado";

        try { direction = rel.CrossFilteringBehavior.ToString(); } catch { }
        try { cardinality = DetectCardinality(rel); } catch { }
        try { isActive = rel.IsActive.ToString().ToLower(); } catch { }

        yaml.AppendLine(I(1) + "- fromTable: " + Scalar(rel.FromTable.Name));
        yaml.AppendLine(I(2) + "fromColumn: " + Scalar(rel.FromColumn.Name));
        yaml.AppendLine(I(2) + "toTable: " + Scalar(rel.ToTable.Name));
        yaml.AppendLine(I(2) + "toColumn: " + Scalar(rel.ToColumn.Name));
        yaml.AppendLine(I(2) + "direction: " + Scalar(direction));
        yaml.AppendLine(I(2) + "cardinality: " + Scalar(cardinality));
        yaml.AppendLine(I(2) + "isActive: " + Scalar(isActive));
    }
}

var utf8Bom = new UTF8Encoding(true);
File.WriteAllText(fullPath, yaml.ToString(), utf8Bom);

Output("Arquivo exportado:");
Output(fullPath);


```

</details>

**Passo a passo:**

1. Abrir o Power BI Desktop com o arquivo .pbix
2. Ir em: Ferramentas Externas -> Tabular Editor
3. No Tabular Editor, acessar o menu: C# Script
4. Copiar o conteúdo do arquivo `extrator_infos_dashboard_V4.txt` e colar no painel de script
5. Alterar o caminho do diretório onde deseja salvar, o nome do arquivo .yaml e se deseja que extraia conteúdos ocultos
```C#
  string outputFolder = @"caminho-da-pasta";
	string fileName = "nome-do-arquivo.yaml";
  bool includeHidden = false;
  
```
6. Clicar em "Run script" (seta verde)
7. Verificar se o arquivo foi gerado no diretório informado
  
**Exemplo de Extração:**
  
<video controls autoplay loop muted style="max-width:100%; border:1px solid #ddd; border-radius:8px;">
  <source src="/dados/documentador_dashboards/exemplo_extracao.mp4" type="video/mp4">
  Seu navegador não suporta vídeo HTML5.
</video>


**Antes de enviar, confirme se o YAML contém:**
- `modelName`
- `tables`
- `columns`
- `measures`
- `relationships`

---

## :arrows_clockwise: 7) Fluxo recomendado

1. Extrair o YAML via Tabular Editor 2
2. Exportar o dashboard em PDF pelo Power BI
3. Preencher as informações técnicas (caminho, equipe, link, frequência)
4. Enviar tudo em uma única mensagem seguindo o template da seção 5
5. (Opcional) Complementar com prints adicionais se necessário

---

## :bricks: 8) Estrutura esperada da saída

A documentação gerada pelo agente inclui:

- :pushpin: **Cabeçalho:** nome do modelo, status de cobertura e informações técnicas
- :page_facing_up: **Páginas do dashboard:** descrição funcional, indicadores principais, visuais e filtros de cada página
- :file_cabinet: **Modelo dos dados:** descrição, fonte, query de origem e lista de colunas de cada tabela
- :triangular_ruler: **Medidas DAX:** nome, tabela de origem e expressão preservada literalmente
- :link: **Relacionamentos:** tabelas relacionadas, cardinalidade e direção

**Formato de entrega:**
- :file_folder: Arquivo `.md` com encoding UTF-8
- :white_check_mark: Pronto para uso na Wiki, SharePoint, Git ou Notion

---

## :bar_chart: 9) Modos de cobertura

O agente classifica cada documentação gerada em um dos três modos:

| Status | Quando ocorre |
|---|---|
| :white_check_mark: APROVADO | Todos os insumos estão presentes e completos |
| :warning: PARCIAL | YAML ou referências visuais estão incompletos, mas há base suficiente para documentar |
| :x: REPROVADO | Não há base mínima confiável para documentar sem inventar conteúdo |

Quando o resultado for **PARCIAL**, o agente indicará explicitamente quais seções não puderam ser auditadas integralmente.

---

## :warning: 10) Limitações importantes

O agente:
- :no_entry: Não inventa conteúdo ausente no YAML ou nas imagens
- :no_entry: Não interpreta dados dinâmicos exibidos nos visuais (ex: valores de KPIs em tela)
- :no_entry: Não traduz nomes de tabelas, colunas, medidas, filtros ou expressões DAX
- :no_entry: Não faz suposições de negócio que não estejam explícitas nos insumos

Portanto:
- Envie o YAML o mais completo possível para garantir cobertura total do modelo semântico
- Use PDF com boa resolução para garantir leitura correta dos visuais e filtros

---

## :white_check_mark: 11) Checklist antes do envio

Antes de enviar para o agente, confirme:

- [ ] YAML extraído e verificado (contém `modelName`, `tables`, `columns`, `measures`, `relationships`)
- [ ] PDF exportado ou prints das páginas em alta resolução anexados
- [ ] Caminho na rede informado
- [ ] Nome do desenvolvedor e equipe destinada informados
- [ ] Frequência de atualização informada
- [ ] Link do relatório no Power BI Service informado (ou marcado como "não informado")

---

## :gift: 12) Resultado esperado

Ao final, você receberá:
- :page_facing_up: Arquivo `documentacao.md` para download
- :bar_chart: Documentação completa e padronizada do dashboard
- :mag: Cobertura de todas as tabelas, colunas, medidas e relacionamentos presentes no YAML
- :page_with_curl: Descrição funcional de todas as páginas e visuais identificados nas referências visuais

Se algum insumo estiver ausente ou incompleto:
- :warning: O agente sinalizará o status **PARCIAL** ou **REPROVADO**
- :memo: As seções afetadas conterão aviso explícito de limitação de cobertura