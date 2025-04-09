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

### Formato da memória (Figura 1.7)

- Cada palavra da memória tem **40 bits**.
- Pode conter:
  - Um número binário de 40 bits (com sinal)
  - Ou duas instruções de 20 bits (8 bits de opcode + 12 bits de endereço)

### Ciclo de instrução (Figura 1.8)

1. **Busca da instrução**: o PC aponta para o próximo endereço a ser lido.
2. **Decodificação**: o opcode da instrução vai para o IR, o endereço para o MAR.
3. **Execução**: ALU e registradores realizam a operação indicada.
4. **Atualização do PC**: avança para a próxima instrução (ou salta, se for `JUMP`).

### Conjunto de instruções da IAS (Tabela 1.1)

| Tipo | Exemplos | Função |
|------|----------|--------|
| Transferência de dados | `LOAD`, `STOR` | Movem dados entre AC e memória |
| Aritmética | `ADD`, `SUB`, `MUL`, `DIV`, `LSH`, `RSH` | Operações sobre dados em AC |
| Desvios | `JUMP`, `JUMP+` | Alteram o fluxo de execução |
| Modificação de endereço | `STOR M(X,8:19)` | Auto-modificação de instruções |

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

### Estrutura típica (Ex: Cortex-M3)

- **ALU** com suporte a multiplicação e divisão por hardware.
- **Registradores** de uso geral + registradores especiais (PC, SP, LR).
- **Thumb/Thumb-2**: conjunto de instruções de 16 bits + extensão de 32 bits.
- **MPU (Memory Protection Unit)**: limita o acesso à memória por tarefas.
- **Periféricos integrados**: timers, UART, ADC, GPIO, USB, SPI, etc.

---

*Resumo baseado no livro "Computer Organization and Architecture – 10ª ed." (William Stallings).*
