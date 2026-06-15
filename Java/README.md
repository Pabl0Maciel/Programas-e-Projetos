<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Java&fontSize=42&fontColor=4F8EF7&fontAlignY=45&desc=Fundamentos%20·%20POO%20·%20Maratona%20Java&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

Conteúdos de Java organizados em três blocos: fundamentos da linguagem, projetos práticos de POO e a Maratona Java (DevDojo) com cobertura completa de orientação a objetos.

---

## 📂 Estrutura

### 🔰 Fundamentos

Primeiros passos com a linguagem — sintaxe, tipos, controle de fluxo e leitura de dados.

| Pasta | O que cobre |
|-------|-------------|
| [`Primeiro Contato`](./Primeiro%20Contato) | Hello World e estrutura básica |
| [`Variaveis`](./Variaveis) | Tipos primitivos e declaração de variáveis |
| [`Scanner`](./Scanner) | Leitura de dados do usuário |
| [`condicional`](./condicional) | `if/else` e `switch/case` |
| [`loop`](./loop) | `for` e `while` |
| [`desafio`](./desafio) | Controle de conta bancária — desafio prático |

---

### 🏗️ Projetos POO

Dois projetos que aplicam orientação a objetos em cenários reais.

**🎬 Catálogo de Títulos** — [`poo/`](./poo)

Modela filmes, séries e episódios com herança e interfaces. Calcula tempo total e gera recomendações com base em classificação.

```
Titulo (abstrata)
├── Filme
└── Serie → Episodio
Classificavel (interface) → Recomendacao
CalculadoraDeTempo
```

**🎵 Reprodutor de Áudio** — [`reprodutor_audio/`](./reprodutor_audio)

Simula um reprodutor com músicas e podcasts, usando herança e polimorfismo para unificar comportamentos de áudio.

```
Audio (abstrata)
├── Musica
└── Podcast
MinhasPreferidas (lista de favoritos)
```

---

### 🏃 Maratona Java — DevDojo

Curso completo de POO em Java com domínios, testes e padrões de projeto.

<details>
<summary><strong>Ver todos os módulos</strong></summary>

| Módulo | Conceito | Domínios de exemplo |
|--------|----------|---------------------|
| [`introducaoclasses`](./maratonaJava/src/academy/devdojo/maratonajava/poo/introducaoclasses) | Classes e objetos | `Carro`, `Estudante`, `Professor` |
| [`introducaometodos`](./maratonaJava/src/academy/devdojo/maratonajava/poo/introducaometodos) | Métodos e sobrecarga | `Calculadora`, `Funcionario`, `Pessoa` |
| [`construtores`](./maratonaJava/src/academy/devdojo/maratonajava/poo/construtores) | Construtores | `Anime` |
| [`blocosinicializacao`](./maratonaJava/src/academy/devdojo/maratonajava/poo/blocosinicializacao) | Blocos de inicialização | `Anime` |
| [`modificadorestatic`](./maratonaJava/src/academy/devdojo/maratonajava/poo/modificadorestatic) | `static` | `Anime`, `Carro` |
| [`modificadorfinal`](./maratonaJava/src/academy/devdojo/maratonajava/poo/modificadorfinal) | `final` | `Carro`, `Ferrari`, `Comprador` |
| [`heranca`](./maratonaJava/src/academy/devdojo/maratonajava/poo/heranca) | Herança e `super` | `Pessoa`, `Funcionario`, `Endereco` |
| [`classesabstratas`](./maratonaJava/src/academy/devdojo/maratonajava/poo/classesabstratas) | Classes abstratas | `Funcionario`, `Gerente`, `Desenvolvedor` |
| [`interfaces`](./maratonaJava/src/academy/devdojo/maratonajava/poo/interfaces) | Interfaces | `DataLoader`, `FileLoader`, `DataBaseLoader` |
| [`polimorfismo`](./maratonaJava/src/academy/devdojo/maratonajava/poo/polimorfismo) | Polimorfismo e repositórios | `Produto`, `Computador`, `Tomate` |
| [`sobrecargametodos`](./maratonaJava/src/academy/devdojo/maratonajava/poo/sobrecargametodos) | Sobrecarga de métodos | `Anime` |
| [`sobreescrita`](./maratonaJava/src/academy/devdojo/maratonajava/poo/sobreescrita) | Sobrescrita (`@Override`) | `Anime` |
| [`associacao`](./maratonaJava/src/academy/devdojo/maratonajava/poo/associacao) | Associação entre classes | `Jogador`, `Time`, `Escola` |
| [`enumeracao`](./maratonaJava/src/academy/devdojo/maratonajava/poo/enumeracao) | Enums | `TipoCliente`, `TipoPagamento` |
| [`colecoes`](./maratonaJava/src/academy/devdojo/maratonajava/poo/colecoes) | Collections e ordenação | `Manga`, `Smartphone` |
| [`exception`](./maratonaJava/src/academy/devdojo/maratonajava/poo/exception) | Exceções e erros | `RuntimeException`, `StackOverflow` |

</details>

---

## ⚙️ Como executar

```bash
# Compilar um arquivo isolado
javac NomeDoArquivo.java

# Executar
java NomeDoArquivo
```

Para a Maratona Java, recomenda-se abrir o projeto [`maratonaJava/`](./maratonaJava) diretamente no **IntelliJ IDEA** (já inclui o `.iml` configurado).

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
