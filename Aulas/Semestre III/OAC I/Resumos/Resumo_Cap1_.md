# Capítulo 1 – Basic Concepts and Computer Evolution (Resumo completo e expandido)

## 1.1 🧠 Organization and Architecture

### Arquitetura de Computadores
- Diz respeito aos atributos **visíveis ao programador**.
- Define como o sistema se comporta do ponto de vista lógico:
  - Conjunto de instruções (ISA)
  - Modos de endereçamento
  - Tamanhos de dados e registradores

### Organização de Computadores
- Trata da **implementação interna real** da arquitetura.
- Responsável por como os recursos arquiteturais são efetivamente realizados:
  - Circuitos lógicos
  - Interconexões físicas
  - Técnicas de controle e temporização

> 📌 *Exemplo*: A existência de uma instrução `MUL` (multiplicação) é uma decisão **arquitetural**. A escolha de usar um circuito dedicado ou uma sequência de somas para implementá-la é uma decisão **organizacional**.

### Importância prática
- Permite que diferentes modelos de hardware sejam compatíveis com o mesmo software.
- Exemplo real: diversos modelos do **IBM System/370** compartilham arquitetura, mas variam em organização.

---

## 1.2 🏗️ Structure and Function

### As quatro funções fundamentais de um computador

| Função | Descrição |
|--------|-----------|
| 🧮 Processamento de Dados | Cálculos e operações lógicas |
| 💾 Armazenamento de Dados | Retenção temporária (RAM) ou permanente (discos) |
| 🔄 Movimentação de Dados | Transferência entre componentes internos ou externos |
| 🧭 Controle | Coordenação das operações por meio de sinais |

### Componentes estruturais (Figura 1.1)

| Componente | Subcomponentes / Função |
|------------|--------------------------|
| 🧠 CPU (Processador) | ALU, unidade de controle, registradores internos |
| 🧠 ALU | Executa operações aritméticas e lógicas |
| 🧠 Registradores | Armazenam temporariamente dados e instruções em processamento |
| 📦 Memória Principal | Armazena instruções e dados ativos |
| 🔌 I/O (Entrada/Saída) | Comunicação com o ambiente externo |
| 🔁 Interconexão (barramentos) | Transporte de dados, endereços e sinais de controle |

### Hierarquia de níveis
- O sistema é descrito **do topo para baixo**.
- Exemplo:
  - Sistema computacional → subsistemas → unidades funcionais → circuitos → lógica → transistores.
 
![Diagrama da CPU](Imagens/figura_1_1.png)
 
 ---
 
### Estrutura de um Chip Multicore  

A Figura 1.2 mostra a organização interna de um **processador multicore moderno**, ou seja, um único chip contendo **múltiplos núcleos de CPU**, cada um capaz de executar instruções de forma independente e paralela.

Esse design é fundamental na computação atual, especialmente para aplicações multitarefa, processamento paralelo e sistemas embarcados de alto desempenho.


### Componentes do chip multicore

| Componente | Função |
|------------|--------|
| **Cores de CPU** | Núcleos independentes com ALU, unidade de controle, registradores e cache L1 própria. Executam instruções simultaneamente. |
| **Cache L1 (nível 1)** | Cache privada de cada núcleo, dividida em instruções e dados. Tem acesso extremamente rápido. |
| **Cache L2 (nível 2)** | Cache intermediária, geralmente dedicada a cada núcleo ou compartilhada entre poucos núcleos. Armazena dados acessados com frequência. |
| **Cache L3 (nível 3)** | Cache grande e **compartilhada entre todos os núcleos**. Atua como buffer antes da memória principal. |
| **Interconexão interna** | Conjunto de barramentos ou rede interna que conecta os núcleos, caches e controladores de memória. |
| **Controlador de Memória** | Gerencia as requisições dos núcleos à memória principal (RAM). Pode ser integrado ao chip para maior eficiência. |

![Componentes Chip Multicore](Imagens/figura_1_2.png)

---

### Vantagens do modelo multicore

- ✅ **Paralelismo real**: múltiplos núcleos executam tarefas simultaneamente.
- ✅ **Eficiência energética**: mais desempenho com menor aumento de consumo e calor.
- ✅ **Escalabilidade**: mais núcleos = maior capacidade de processamento para cargas intensivas.
- ✅ **Comunicação interna rápida**: as caches e interconexões internas evitam gargalos com a RAM.

Essa estrutura representa a principal evolução da organização de processadores desde os anos 2000, substituindo o foco no aumento de frequência pelo aumento no número de núcleos.

---

## 1.3 🕰️ A Brief History of Computers

### Gerações de computadores

| Geração | Tecnologia | Exemplo clássico |
|---------|------------|------------------|
| 1ª (1946–57) | Válvulas | ENIAC, IAS |
| 2ª (1958–64) | Transistores | IBM 7094 |
| 3ª (1965–71) | Circuitos Integrados (SSI/MSI) | IBM System/360 |
| 4ª (1972–77) | LSI | PDP-11 |
| 5ª (1978–91) | VLSI | Intel 8086, PCs |
| 6ª (1991–presente) | ULSI, multicore, nuvem | ARM, x86 modernos |

---

## 🏛️ A Máquina IAS (Institute for Advanced Study Computer)

### Contexto histórico
- Concebida por John von Neumann e equipe entre 1946 e 1952.
- Foi a **primeira máquina com arquitetura de programa armazenado**.
- Tornou-se o modelo base de todos os computadores de arquitetura clássica (“arquitetura de von Neumann”).

### Componentes funcionais (Figura 1.6)

| Unidade | Descrição |
|--------|-----------|
| AC (Accumulator) | Armazena o resultado das operações da ALU |
| MQ (Multiplier-Quotient Register) | Guarda a parte inferior do produto ou o quociente da divisão |
| MBR (Memory Buffer Register) | Armazena temporariamente os dados que entram ou saem da memória |
| MAR (Memory Address Register) | Endereço de memória a ser acessado |
| PC (Program Counter) | Mantém o endereço da próxima instrução a ser executada |
| IR (Instruction Register) | Código da instrução atual em execução |
| IBR (Instruction Buffer Register) | Guarda a segunda instrução de uma palavra de memória |

![Componentes IAS](Imagens/figura_1_6.png)

---
### Formato da memória (Figura 1.7)

- Cada palavra da memória tem **40 bits**.
- Pode conter:
  - Um número binário de 40 bits (com sinal)
  - Ou duas instruções de 20 bits (8 bits de opcode + 12 bits de endereço)

![Diagrama da CPU](Imagens/figura_1_7.png)

---
### Fluxo de Execução da Máquina IAS  

A Figura 1.8 representa o **fluxograma parcial do ciclo de operação da máquina IAS**, abordando as fases de **busca (fetch)**, **decodificação** e **execução** das instruções.

Essa representação gráfica é essencial para compreender como os componentes da arquitetura IAS — como registradores, memória e unidade de controle — interagem para processar instruções armazenadas na memória principal.



### 📋 Registradores da Máquina IAS (com base na Figura 1.8)

A seguir, apresentamos os principais registradores utilizados no ciclo de busca e execução da máquina IAS, com base na Figura 1.8. Cada um tem papel específico na manipulação e controle de dados e instruções.

| Registrador | Nome Completo                  | Função no Ciclo de Instrução |
|-------------|--------------------------------|-------------------------------|
| **PC**      | Program Counter                | Armazena o endereço da próxima palavra de memória a ser buscada. Após buscar uma palavra, é incrementado (`PC ← PC + 1`). |
| **MAR**     | Memory Address Register        | Recebe o endereço a ser acessado (leitura ou escrita). Intermedia a comunicação com a memória. |
| **MBR**     | Memory Buffer Register         | Armazena o conteúdo lido da memória (ou a ser escrito nela). Pode conter dados ou palavras de instrução completas. |
| **IR**      | Instruction Register           | Armazena o código da instrução (opcode) que está sendo decodificada e executada. |
| **IBR**     | Instruction Buffer Register    | Armazena temporariamente a **segunda instrução** de uma palavra de 40 bits, quando a primeira já foi processada. |
| **AC**      | Accumulator                    | Armazena os resultados intermediários das operações aritméticas ou lógicas. |
| **MQ**      | Multiplier-Quotient Register   | Usado em operações de multiplicação e divisão. Armazena uma parte do resultado. |

> 💡 Esses registradores compõem o "coração" do fluxo de controle da máquina IAS, e sua movimentação determina o caminho entre a memória, a decodificação e a execução da instrução.

---
### 🧭 Etapas do Fluxo de Execução

#### 1. Início e Busca da Instrução

O processo se inicia com a verificação:  
**“Há uma instrução restante no IBR?”** (Instruction Buffer Register)

- ✅ **Sim**: o conteúdo do IBR é transferido diretamente para o **Instruction Register (IR)** e o **Memory Address Register (MAR)**.  
  Nenhum acesso adicional à memória é necessário.
- ❌ **Não**: a próxima palavra de instrução completa é buscada da memória:
  - `MAR ← PC` (o Program Counter indica a palavra a ser lida)
  - `MBR ← M(MAR)` (a palavra é lida da memória e armazenada no Memory Buffer Register)

#### 2. Decisão: Qual metade da palavra usar?

Cada palavra de 40 bits pode conter até **duas instruções de 20 bits**: esquerda e direita.

- A unidade de controle verifica se é necessário executar a instrução da esquerda (bit alto).
- Se sim, ela é extraída dos bits 0:19 e movida para:
  - `IR ← MBR(0:7)` (opcode)
  - `MAR ← MBR(8:19)` (endereço)
- Caso contrário, a instrução da direita é processada:
  - `IR ← MBR(20:27)`
  - `MAR ← MBR(28:39)`

Após isso, o **PC é incrementado**: `PC ← PC + 1`

---

### ⚙️ Decodificação e Execução da Instrução

- A instrução carregada no `IR` é decodificada e o controle passa para o **ciclo de execução**.
- Exemplos de execução com base na instrução:

| Tipo de Instrução | Ação Realizada |
|-------------------|----------------|
| `LOAD M(X)` | `AC ← M(X)` (carrega o conteúdo da memória para o acumulador) |
| `ADD M(X)` | `AC ← AC + M(X)` |
| `SUB M(X)` | `AC ← AC - M(X)` |
| `JUMP M(X)` | `PC ← X` (salta para novo endereço) |
| `JUMP+ M(X)` | Se `AC > 0` então `PC ← X` |
| `STOR M(X)` | `M(X) ← AC` (salva o acumulador na memória) |

Durante a execução:
- Se for necessário acessar a memória:
  - `MBR ← M(MAR)`
  - O dado lido é movido para o AC: `AC ← MBR`
- Ou no caso de escrita:
  - `MBR ← AC`
  - `M(MAR) ← MBR`

---

### 🌀 Ciclo de Controle

Esse processo de busca → decodificação → execução se repete ciclicamente, conforme o conteúdo do **Program Counter (PC)**. A máquina só altera seu fluxo quando encontra uma instrução de desvio (`JUMP`) ou uma instrução condicional (`JUMP+`).

Esse fluxo de controle é central no projeto de todas as arquiteturas baseadas no modelo de Von Neumann.

![IAS](Imagens/figura_1_8.png)


---

### 📌 Observações Importantes

- O **IBR** permite a execução de duas instruções consecutivas sem novo acesso à memória, aumentando a eficiência.
- A estrutura sequencial é típica de CPUs sem pipeline.
- O uso explícito de registradores intermediários (MBR, MAR, IR, etc.) demonstra como o controle da IAS é **totalmente microprogramado**.




---

## 1.5 🔌 Embedded Systems

### Definição

Sistemas embarcados (*embedded systems*) são sistemas computacionais dedicados a executar **uma função específica** como parte de um produto maior. Ao contrário de computadores de uso geral, que executam diversos programas, os sistemas embarcados são construídos para realizar **tarefas específicas com alta eficiência, baixo consumo e confiabilidade**.

Estes sistemas estão presentes em áreas como automação residencial, veículos, dispositivos médicos, equipamentos industriais e dispositivos portáteis, sendo atualmente a forma mais difundida de computador no mundo.

---

### Características Fundamentais

| Característica | Descrição |
|----------------|-----------|
| ⚡ Baixo consumo de energia | Projetados para operar com alimentação limitada (baterias, painéis solares) |
| 🧠 Função fixa | Dedicados a uma aplicação ou conjunto muito restrito de tarefas |
| 💾 Firmware | Código embarcado armazenado em ROM/Flash, raramente modificado |
| 🔄 Controle em tempo real | Muitas aplicações exigem resposta rápida a eventos físicos |
| 📦 Alta integração | Um único chip pode conter CPU, memória e periféricos |
| 🧩 Interface com o ambiente físico | Controlam motores, sensores, LEDs, atuadores, entre outros |

---

### Estrutura de um Sistema Embarcado  

A Figura 1.14 mostra um sistema embarcado moderno baseado na arquitetura ARM Cortex-M3, no qual diversos blocos funcionais são integrados:

- **ARM Cortex-M3 Core**: núcleo do processador, baseado em arquitetura RISC, com registradores e ALU internos.
- **SRAM e Flash**: memória interna usada para dados e programa (firmware).
- **MPU (Memory Protection Unit)**: protege regiões de memória e isola tarefas.
- **Temporizadores**: controlam eventos temporizados e interrupções periódicas.
- **Watchdog Timer**: reinicia o sistema automaticamente em caso de falhas.
- **GPIO**: portas de entrada e saída digital para conexão com LEDs, botões, etc.
- **Interfaces seriais**: UART, SPI, I2C — usadas para comunicar com sensores e módulos externos.
- **ADC/DAC**: conversores analógico-digital e digital-analógico, permitindo leitura de sensores físicos.

![Sistema Embarcado](Imagens/figura_1_14.png)

---

### Arquitetura Interna  

A Figura 1.15 detalha o interior do núcleo Cortex-M3:

- **ALU (Arithmetic Logic Unit)**: executa operações matemáticas e lógicas.
- **Banco de Registradores**: armazenam temporariamente dados e endereços (ex: R0–R15, incluindo SP, LR, PC).
- **Bus Interface Unit**: faz a ponte entre o núcleo e a memória/periféricos.
- **NVIC (Nested Vectored Interrupt Controller)**: gerencia múltiplas interrupções com diferentes prioridades.
- **Decoder**: decodifica as instruções do conjunto Thumb/Thumb-2 (16 e 32 bits).
- **Pipeline**: permite sobreposição de busca, decodificação e execução, otimizando o desempenho.
- **System Control Block**: registros de sistema, controle de exceções e modos de operação.

![Núcleo Cortex-M3](Imagens/figura_1_15.png)

---

### Aplicações Comuns

| Setor | Exemplos |
|-------|----------|
| 🚗 Automotivo | Freios ABS, airbag, sensores de estacionamento, ignição |
| 🏠 Doméstico | Termostatos, micro-ondas, máquinas de lavar, aspiradores inteligentes |
| 🏥 Médico | Monitores cardíacos, marcapassos, equipamentos de dosagem |
| 🏭 Industrial | Controladores lógicos programáveis (CLPs), sensores de presença |
| 🌐 IoT | Câmeras, smart locks, sensores climáticos, hubs conectados |

---

### Desenvolvimento de Software

- Linguagens: C (predominante), C++, Assembly (casos críticos de desempenho).
- IDEs específicas de fabricantes: STM32CubeIDE, MPLAB X, Keil µVision.
- Ferramentas de depuração: JTAG, SWD, simuladores.
- Em sistemas com multitarefa, usa-se um **RTOS** (Real-Time Operating System), como FreeRTOS, para gerenciar tarefas, temporizadores e interrupções.

---

### Relevância para Arquitetura de Computadores

O estudo de sistemas embarcados revela:

- Como a arquitetura (ISA) e a organização (internals, periféricos, barramentos) são ajustadas para tarefas especializadas.
- A importância da **integração entre software e hardware**, já que o programador lida diretamente com registradores, endereços de memória e interrupções.
- A aplicação real das decisões de projeto que envolvem consumo, desempenho e responsividade.
- O uso prático da **arquitetura ARM**, que combina simplicidade, escalabilidade e suporte a aplicações industriais e comerciais.

---

## 1.6 🧬 ARM Architecture

### Histórico
- Criada nos anos 80 pela Acorn (Reino Unido).
- Evoluiu como uma arquitetura **RISC** (Reduced Instruction Set Computer).
- Atualmente licenciada pela ARM Holdings.

### Vantagens

- Pouco consumo de energia.
- Menor quantidade de transistores → menor calor.
- Alta eficiência para dispositivos móveis.

### Famílias ARM

| Série | Aplicações |
|-------|------------|
| Cortex-A | Smartphones, tablets, TVs inteligentes (usa MMU) |
| Cortex-R | Sistemas com tempo real rigoroso (ex: freios ABS, industrial) |
| Cortex-M | Microcontroladores simples e de baixo consumo (IoT, wearables) |

### Estrutura da Arquitetura ARM  

A Figura 1.16 apresenta uma visão geral da arquitetura de um processador ARM genérico. A estrutura é modular e composta por blocos funcionais bem definidos, integrados em um chip compacto e eficiente. Essa organização é amplamente adotada em sistemas embarcados modernos.

#### Componentes principais:

- **Unidade de Processamento ARM**: núcleo central que executa as instruções. Baseado na arquitetura RISC, é otimizado para desempenho com simplicidade:
  - Executa instruções Thumb (16 bits) ou Thumb-2 (16/32 bits).
  - Possui pipeline interno (3 estágios ou mais, dependendo do núcleo).

- **Banco de Registradores**: conjunto de registradores de uso geral e especiais (como SP, LR, PC), utilizados para armazenar dados temporários, endereços e controle de fluxo.

- **Controlador de Interrupções**: gerencia eventos externos e internos que requerem atenção imediata do processador. Pode priorizar múltiplas interrupções simultâneas (NVIC em núcleos Cortex-M).

- **Interface de Barramento**: conecta o núcleo ARM à memória e aos periféricos. Pode ser AMBA (Advanced Microcontroller Bus Architecture), dividida em:
  - AHB (High-performance)
  - APB (Periféricos de baixa velocidade)

- **Memória**:
  - **Memória de Programa (Flash/ROM)**: armazena o firmware.
  - **Memória de Dados (RAM)**: armazena variáveis e buffers temporários.

- **Periféricos de E/S**: incluem interfaces seriais (UART, SPI, I²C), temporizadores, conversores A/D e D/A, controladores de DMA, etc.

- **GPIO (General Purpose Input/Output)**: pinos programáveis usados para comunicação com dispositivos externos (sensores, LEDs, botões).

![Arquitetura ARM](Imagens/figura_1_16.png)

---
#### Integração típica em um microcontrolador ARM:

Todos esses componentes são encapsulados em um único chip (SoC – System on Chip), formando uma **plataforma embarcada altamente eficiente**, com tamanho reduzido e grande capacidade de controle em tempo real.

Essa estrutura explica por que a arquitetura ARM é predominante em sistemas embarcados: ela oferece **alto desempenho com baixo consumo**, além de escalabilidade para múltiplas aplicações.

---

## 🧾 Resumo Final do Capítulo 1

O Capítulo 1 introduz os **fundamentos da organização e arquitetura de computadores**, distinguindo claramente entre **arquitetura** (o que é visível ao programador) e **organização** (como o hardware implementa isso). São apresentadas as **quatro funções principais de um sistema computacional**: processamento, armazenamento, movimentação e controle de dados.

A estrutura básica de um computador moderno é descrita em camadas hierárquicas, passando por **CPU, memória, I/O e interconexões**, culminando na arquitetura **multicore**, onde vários núcleos operam de forma paralela, como mostrado na Figura 1.2.

Na sequência, o capítulo explora a evolução dos computadores por gerações, com destaque para a **máquina IAS** – modelo pioneiro de arquitetura com programa armazenado. Através do estudo detalhado de seus registradores e ciclo de instrução (Figura 1.8), compreendemos os mecanismos básicos que inspiraram as arquiteturas modernas.

Em seguida, são abordados os **sistemas embarcados**, que exemplificam o uso prático da arquitetura ajustada a tarefas específicas, com alta integração e controle direto de hardware. Esse conceito é aprofundado com base nos exemplos do ARM Cortex-M3 (Figuras 1.14 e 1.15), culminando na descrição da **arquitetura ARM genérica** (Figura 1.16), amplamente usada em dispositivos embarcados e IoT.

Com isso, o capítulo estabelece a base teórica e prática para entender como instruções em linguagens de alto nível, como C, se traduzem em ações no nível de hardware, preparando o terreno para os capítulos seguintes sobre desempenho, estrutura da CPU e tipos de instrução.
