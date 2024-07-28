# Análise Exploratória de Dados

Este projeto realiza uma análise detalhada dos dados de vendas a partir de um arquivo CSV. O objetivo é responder a várias perguntas sobre o desempenho de vendas com base em diferentes categorias e segmentações. O projeto utiliza Python e as bibliotecas Pandas, Numpy, Matplotlib, Seaborn e DateTime para análise e visualização dos dados.

## Perguntas
- **1ª Pergunta**: Qual Cidade com Maior Valor de Venda de Produtos da Categoria 'Office Supplies'?
- **2ª Pergunta**: Qual o Total de Vendas Por Data do Pedido? Demonstre o resultado através de um gráfico de barras.
- **3ª Pergunta**: Qual o Total de Vendas por Estado? Demonstre o resultado através de um gráfico de barras.
- **4ª Pergunta**: Quais São as 10 Cidades com Maior Total de Vendas? Demonstre o resultado através de um gráfico de barras.
- **5ª Pergunta**: Qual Segmento Teve o Maior Total de Vendas? Demonstre o resultado através de um gráfico de pizza.
- **6ª Pergunta**: Qual o Total de Vendas Por Segmento e Por Ano?
- **7ª Pergunta**: Os gestores da empresa estão considerando conceder diferentes faixas de descontos e gostariam de fazer uma simulação com base na regra abaixo: 
  - Se o Valor_Venda for maior que 1000 recebe 15% de desconto.
  - Se o Valor_Venda for menor que 1000 recebe 10% de desconto. <br>
  Quantas Vendas Receberiam 15% de Desconto?
- **8ª Pergunta**: Considere Que a Empresa Decida Conceder o Desconto de 15% do Item Anterior. Qual Seria a Média do Valor de Venda Antes e Depois do Desconto?
- **9ª Pergunta**: Qual o Média de Vendas Por Segmento, Por Ano e Por Mês? Demonstre o resultado através de gráfico de linha.
- **10ª Pergunta**: Qual o Total de Vendas Por Categoria e SubCategoria, Considerando Somente as Top 12 SubCategorias? Demonstre tudo através de um único gráfico.

## Respostas

As respostas podem ser visualizadas no arquivo [Respostas.md](https://github.com/Pabl0Maciel/Programas-e-Projetos/blob/main/Projetos/Analise%20Exploratoria%20de%20Dados/Respostas.md)

## Dependências

Certifique-se de que as seguintes bibliotecas estão instaladas:

- `pandas`
- `numpy`
- `matplotlib`
- `seaborn`
- `datetime`

Você pode instalar as dependências usando pip:

```bash
pip install pandas numpy matplotlib seaborn
```

## 🚀 Como Utilizar

1. **Baixe o dataset**:

   Certifique-se de baixar o arquivo [dataset3.csv](https://github.com/Pabl0Maciel/Programas-e-Projetos/blob/main/arquivos/dataset3.csv) disponível na pasta **`arquivos/`** neste repositório. <br><br>
   Caso opte por colocar o arquivo em outro local, altere o caminho de carregamento dos dados na terceira linha:
   ```bash
   dados = pd.read_csv('sua_pasta/dataset3.csv')
   ```
   Ou se o arquivo estiver na mesma pasta do scripty:
   ```bash
   dados = pd.read_csv('dataset3.csv')
   ```
2. **Execute o Programa***
   ```bash
   python analise_1.py
   python analise_2.py
   ```

   ## 🛠️ Estrutura do Repositório

Este repositório é organizado da seguinte forma:

- **`analise_1.py`** e **`analise_2.py`**: Os scripts principais contendo todas as funções e lógica da análise.
- **`README.md`**: Este arquivo que você está lendo.
- **`Respostas.md`**: Contém as respostas das perguntas.
- **`Imagens/`**: Contém as imagens dos gráficos gerados.

## 💬 Contato

Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato!

<p align="left">
  <a href="mailto:pablocaballero07@usp.br" title="Gmail">
    <img src="https://img.shields.io/badge/-Gmail-FF0000?style=flat-square&labelColor=FF0000&logo=gmail&logoColor=white" alt="Gmail"/>
  </a>
  <a href="https://www.linkedin.com/in/seu-perfil-link" title="LinkedIn">
    <img src="https://img.shields.io/badge/-Linkedin-0e76a8?style=flat-square&logo=Linkedin&logoColor=white" alt="LinkedIn"/>
  </a>
  <a href="https://wa.me/11963934212" title="WhatsApp">
    <img src="https://img.shields.io/badge/-WhatsApp-25d366?style=flat-square&labelColor=25d366&logo=whatsapp&logoColor=white" alt="WhatsApp"/>
  </a>
  <a href="https://www.instagram.com/pabl0maciel" title="Instagram">
    <img src="https://img.shields.io/badge/-Instagram-DF0174?style=flat-square&labelColor=DF0174&logo=instagram&logoColor=white" alt="Instagram"/>
  </a>
</p>

## 🤝 Contribuições

Se você deseja contribuir com este arquivo, sinta-se à vontade para enviar pull requests! Suas contribuições são sempre bem-vindas.

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

Obrigado por visitar o meu projeto e espero que o conteúdo aqui seja útil para o seu aprendizado e desenvolvimento!
   


