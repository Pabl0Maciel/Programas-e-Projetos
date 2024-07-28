# Detector Automático de COH-PIAH

Bem-vindo ao projeto do Detector Automático de COH-PIAH. Este projeto tem como objetivo identificar a assinatura linguística típica de um aluno infectado com COH-PIAH, utilizando uma série de características linguísticas para comparar textos.

## 📚 O que você encontrará aqui

Esta pasta contém um script Python que realiza as seguintes funções:

- **Leitura da assinatura**: Captura as características linguísticas típicas de um aluno infectado.
- **Leitura de textos**: Recebe vários textos para comparação.
- **Processamento de texto**: Divide textos em sentenças, frases e palavras.
- **Cálculo da assinatura**: Calcula a assinatura linguística dos textos fornecidos.
- **Comparação de assinaturas**: Compara a assinatura calculada com a assinatura típica e determina o texto mais semelhante.

## 🚀 Como Utilizar

1. **Execute o Script**:

    Para executar o script, basta executar o arquivo Python no seu ambiente local:

    ```bash
    python coh_piah.py
    ```

    O script solicitará as seguintes entradas:
    
    - **Assinatura típica**: Características linguísticas típicas do aluno infectado.
      - **Dados para testar**:
        - Tamanho médio de palavra: 4.51
        - Relação Type-Token: 0.693
        - Razão Hapax Legomana: 0.55
        - Tamanho médio de sentença: 70.82
        - Complexidade média da sentença: 1.82
        - Tamanho médio de frase: 38.5
    - **Textos para comparação**: Insira vários textos para que o script possa compará-los com a assinatura fornecida.
      -  **Dados para testar**:
          - **Texto 1**: Num fabulário ainda por encontrar será um dia lida esta fábula: A uma bordadora dum país longínquo foi encomendado pela sua rainha que bordasse, sobre seda ou cetim, entre folhas, uma rosa branca. A bordadora, como era muito jovem, foi procurar por toda a parte aquela rosa branca perfeitíssima, em cuja semelhança bordasse a sua. Mas sucedia que umas rosas eram menos belas do que lhe convinha, e que outras não eram brancas como deviam ser. Gastou dias sobre dias, chorosas horas, buscando a rosa que imitasse com seda, e, como nos países longínquos nunca deixa de haver pena de morte, ela sabia bem que, pelas leis dos contos como este, não podiam deixar de a matar se ela não bordasse a rosa branca. Por fim, não tendo melhor remédio, bordou de memória a rosa que lhe haviam exigido. Depois de a bordar foi compará-la com as rosas brancas que existem realmente nas roseiras. Sucedeu que todas as rosas brancas se pareciam exactamente com a rosa que ela bordara, que cada uma delas era exactamente aquela. Ela levou o trabalho ao palácio e é de supor que casasse com o príncipe. No fabulário, onde vem, esta fábula não traz moralidade. Mesmo porque, na idade de ouro, as fábulas não tinham moralidade nenhuma.
          - **Texto 2**: Voltei-me para ela; Capitu tinha os olhos no chão. Ergueu-os logo, devagar, e ficamos a olhar um para o outro... Confissão de crianças, tu valias bem duas ou três páginas, mas quero ser poupado. Em verdade, não falamos nada; o muro falou por nós. Não nos movemos, as mãos é que se estenderam pouco a pouco, todas quatro, pegando-se, apertando-se, fundindo-se. Não marquei a hora exata daquele gesto. Devia tê-la marcado; sinto a falta de uma nota escrita naquela mesma noite, e que eu poria aqui com os erros de ortografia que trouxesse, mas não traria nenhum, tal era a diferença entre o estudante e o adolescente. Conhecia as regras do escrever, sem suspeitar as do amar; tinha orgias de latim e era virgem de mulheres.
          - **Texto 3**: Senão quando, estando eu ocupado em preparar e apurar a minha invenção, recebi em cheio um golpe de ar; adoeci logo, e não me tratei. Tinha o emplasto no cérebro; trazia comigo a idéia fixa dos doidos e dos fortes. Via-me, ao longe, ascender do chão das turbas, e remontar ao Céu, como uma águia imortal, e não é diante de tão excelso espetáculo que um homem pode sentir a dor que o punge. No outro dia estava pior; tratei-me enfim, mas incompletamente, sem método, nem cuidado, nem persistência; tal foi a origem do mal que me trouxe à eternidade. Sabem já que morri numa sexta-feira, dia aziago, e creio haver provado que foi a minha invenção que me matou. Há demonstrações menos lúcidas e não menos triunfantes. Não era impossível, entretanto, que eu chegasse a galgar o cimo de um século, e a figurar nas folhas públicas, entre macróbios. Tinha saúde e robustez. Suponha-se que, em vez de estar lançando os alicerces de uma invenção farmacêutica, tratava de coligir os elementos de uma instituição política, ou de uma reforma religiosa. Vinha a corrente de ar, que vence em eficácia o cálculo humano, e lá se ia tudo. Assim corre a sorte dos homens.     

## 🛠️ Estrutura da Pasta

Esta Pasta é organizado da seguinte forma:

- **`coh_piah.py`**: O script principal contendo todas as funções e lógica do detector.
- **`README.md`**: Este arquivo que você está lendo.

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
