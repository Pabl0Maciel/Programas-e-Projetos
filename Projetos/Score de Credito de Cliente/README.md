# 🏦 Score de Crédito de Cliente

Este projeto visa prever o **score de crédito** dos clientes de um banco, classificando-os nas categorias: **Ruim**, **Ok** e **Bom**. A partir de uma análise dos dados dos clientes, o modelo treinado é capaz de ler as informações de novos clientes e automaticamente prever o score de crédito deles.

## 📁 Estrutura do Projeto

- `clientes.csv`: Base de dados com as informações dos clientes.
- `novos_clientes.csv`: Base de dados com novos clientes para teste do modelo.
- `score_credito.py`: Código-fonte que realiza o treinamento e a previsão do score de crédito.

## 📊 Descrição do Dataset

A base de dados contém as seguintes colunas:
- **id_cliente**: Identificador único do cliente.
- **profissao**: Profissão do cliente.
- **mix_credito**: Combinação de tipos de crédito que o cliente possui.
- **comportamento_pagamento**: Histórico de pagamentos do cliente.
- **score_credito**: O score de crédito atual do cliente (Ruim, Ok, Bom).

## 🛠️ Tecnologias Utilizadas

- **Python**: Linguagem de programação principal.
- **Pandas**: Para manipulação e análise de dados.
- **Scikit-learn**: Biblioteca para machine learning e construção dos modelos preditivos.
  - **RandomForestClassifier**: Algoritmo baseado em árvores de decisão.
  - **KNeighborsClassifier**: Algoritmo de classificação por vizinhos mais próximos (KNN).

## ⚙️ Funcionamento do Código

1. **Importação dos dados**: Os dados dos clientes são carregados e analisados.
2. **Codificação de dados categóricos**: Colunas de texto como `profissao`, `mix_credito` e `comportamento_pagamento` são transformadas em números usando `LabelEncoder`, para que os modelos possam trabalhar com eles.
3. **Divisão dos dados**: A base de dados é dividida em conjuntos de treino e teste (70% treino, 30% teste).
4. **Treinamento dos modelos**: Dois modelos são treinados:
   - **RandomForestClassifier**: Um algoritmo de árvore de decisão que usa diversas árvores para melhorar a precisão.
   - **KNeighborsClassifier**: Um modelo que classifica os clientes com base nos seus vizinhos mais próximos.
5. **Avaliação dos modelos**: O código calcula a precisão de ambos os modelos para verificar qual é o mais eficiente.
6. **Previsão para novos clientes**: O modelo RandomForest é utilizado para prever o score de novos clientes, cujas informações estão armazenadas em um segundo arquivo CSV.

## 🚀 Como Executar o Projeto

1. Clone este repositório:
   ```bash
   git clone https://github.com/pabl0maciel/Programas-e-Projetos.git
   ```
2. Certifique-se de ter o Python e as bibliotecas necessárias instaladas:
   ```bash
   pip install pandas scikit-learn
   ```
3. Execute o script `score_credito.py`:
    ```bash
   python score_credito.py
   ```
4. Verifique a previsão do score de crédito para os novos clientes.

## 📈 Resultados
Após treinar o modelo com os dados de treino, a acurácia dos modelos será exibida no terminal. O modelo escolhido também será usado para prever o score dos novos clientes.

## 📄 Conclusão
Este projeto demonstra o uso de algoritmos de machine learning para classificação de clientes com base em suas características financeiras e comportamentais. O modelo RandomForest apresentou uma melhor acurácia na previsão dos scores de crédito e foi utilizado para prever o score de novos clientes.

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
