# Automação – Cadastro de Insumos

Este projeto implementa um script de automação com Selenium para realizar a conciliação de itens no sistema Saipos, a partir de notas de entrada pendentes. O objetivo é agilizar o processo de associação entre os insumos das notas e os ingredientes cadastrados, além de preparar a base para criação automática de novos ingredientes quando necessário.

## 🚀 Como Utilizar

### 1. Abrir o Chrome com depuração remota

Execute no terminal antes de rodar o script:

```bash
google-chrome --remote-debugging-port=9222 --user-data-dir=/tmp/selenium-profile
```

### 2. Acessar a tela correta no sistema Saipos

No navegador aberto, acesse:

```
Estoque > Notas de Entrada
```

E aplique os seguintes filtros:

- **Período**: por exemplo, de 01/01/2025 até 31/07/2025
- **Conciliação de Estoque**: "Não"

### 3. Rodar o script

Com a tela já posicionada e logado, execute:

```bash
python3 automacao_insumos.py
```

## 🛠️ Estrutura da Pasta

- `automacao_insumos.py`: Script principal da automação
- `README.md`: Este arquivo com instruções de uso

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

Pull requests são sempre bem-vindos!

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
