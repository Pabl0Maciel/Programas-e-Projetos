# 🛒 Segmentação de Clientes

Este projeto tem como objetivo agrupar clientes com base em suas características de similaridade, utilizando o algoritmo de **K-Means**. A partir de dados históricos de clientes que realizaram compras, foi gerado um modelo que segmenta os clientes em 3 grupos distintos.

## 📁 Estrutura do Projeto

- `dados_clientes.csv`: Base de dados com informações dos clientes.
- `clientes_segmentados.csv`: Arquivo gerado com os clientes e seus respectivos grupos (clusters).
- `segmentacao_clientes.py`: Código-fonte que realiza a segmentação dos clientes.

## 📊 Descrição do Dataset

A base de dados contém as seguintes colunas:
- **idade**: Idade do cliente.
- **renda_anual**: Renda anual do cliente.
- **pontuacao_gastos**: Pontuação que representa o comportamento de gastos do cliente.

## 🛠️ Tecnologias Utilizadas

- **Python**: Linguagem de programação principal.
- **Pandas**: Para manipulação e análise de dados.
- **Scikit-learn**: Biblioteca para machine learning.
  - **KMeans**: Algoritmo de agrupamento de clientes.
  - **StandardScaler**: Ferramenta para padronização dos dados.

## ⚙️ Funcionamento do Código

1. **Importação dos dados**: O arquivo CSV com as informações dos clientes é carregado.
2. **Análise exploratória**: Os dados são analisados para entender melhor a distribuição e as características das colunas relevantes (idade, renda anual, e pontuação de gastos).
3. **Padronização dos dados**: As variáveis são padronizadas para garantir que todas tenham a mesma escala antes de aplicar o modelo de clustering.
4. **Definição do número de clusters**: O número de grupos foi definido como **3**, com base no objetivo do negócio.
5. **Treinamento do modelo**: O modelo **K-Means** é treinado e as amostras são agrupadas em clusters.
6. **Resultados**: O resultado da segmentação é adicionado ao dataset original, criando uma nova coluna chamada `cluster` que identifica o grupo ao qual cada cliente pertence.
7. **Exportação dos dados**: O arquivo com os clientes segmentados é salvo em CSV para análise posterior.

## 🚀 Como Executar o Projeto

1. Clone este repositório:
   ```bash
   git clone https://github.com/pabl0maciel/Programas-e-Projetos.git
   ```
2. Certifique-se de ter o Python e as bibliotecas necessárias instaladas:
   ```bash
   pip install pandas scikit-learn
   ```
3. Execute o script `segmentação_clientes.py`:
    ```bash
   python score_credito.py
   ```
4. O arquivo `clientes_segmentados.csv` será gerado com as informações dos clusters.

## 📈 Resultados
O algoritmo de K-Means segmentou os clientes em 3 grupos de acordo com as variáveis `idade`, `renda_anual`, e `pontuacao_gastos`. O arquivo gerado pode ser utilizado para criar estratégias de marketing personalizadas ou para outras análises mais profundas.

## 📄 Conclusão
A segmentação de clientes é uma ferramenta essencial para entender o comportamento dos consumidores e criar estratégias direcionadas. Este projeto demonstra como o K-Means pode ser aplicado para realizar essa tarefa de maneira eficaz.

## 💬 Contato

Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato!

<p align="left">
  <a href="mailto:pablocaballero07@gmail.com" title="Gmail">
    <img src="https://img.shields.io/badge/-Gmail-FF0000?style=flat-square&labelColor=FF0000&logo=gmail&logoColor=white" alt="Gmail"/>
  </a>
  <a href="https://www.linkedin.com/in/pabl0maciel" title="LinkedIn">
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

Se você deseja contribuir com este repositório, sinta-se à vontade para enviar pull requests! Suas contribuições são sempre bem-vindas.

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

Obrigado por visitar o meu repositório e espero que os conteúdos aqui sejam úteis para o seu aprendizado!

