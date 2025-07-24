# Universidade de São Paulo (USP)
## Curso de Sistemas de Informação
### Disciplina: Organização e Arquitetura de Computadores

**Pablo Caballero Maciel** — Nº USP: 14778630  
**Pedro Henrique Teixeira Soares** — Nº USP: 15484158

---

# Comparação de Assembly entre ARM64 e RISC-V

## Visão Geral

Este experimento tem como objetivo comparar como um mesmo código em linguagem C é convertido para linguagem Assembly em duas arquiteturas distintas: **ARM64 (AArch64)** e **RISC-V (RV64)**. Através da análise detalhada dos registradores, instruções e chamadas de função, foram levantadas diferenças importantes que ilustram o funcionamento interno dessas arquiteturas.

---

## Arquiteturas Utilizadas

Neste trabalho, foram utilizadas duas arquiteturas distintas para comparação da tradução de código C para Assembly: **ARM64 (AArch64)** e **RISC-V (RV64)**.

### ARM64 (AArch64)

A arquitetura ARM64, também conhecida como AArch64, é a versão de 64 bits da arquitetura ARM. Ela é amplamente utilizada em dispositivos móveis, como smartphones e tablets, além de aparecer em placas como o Raspberry Pi.

- Conjunto de instruções do tipo RISC (Reduced Instruction Set Computer).
- Suporte a instruções de ponto flutuante e vetoriais nativas.
- Passagem de parâmetros por registradores `x0`–`x7` (inteiros) e `d0`–`d7` (ponto flutuante).
- Utiliza registradores de 64 bits (`x0`–`x30`) e suas versões de 32 bits (`w0`–`w30`).
- Manipulação de pilha com instruções como `stp`, `ldp`, `mov`, `adr`, `bl`.

[Referência: ARM Architecture Reference Manual](https://developer.arm.com/documentation/ddi0596/latest/)

### RISC-V (RV64)

RISC-V é uma arquitetura aberta e modular que vem ganhando destaque em ambientes acadêmicos e comerciais. A versão utilizada aqui é de 64 bits (RV64).

- Estrutura limpa e minimalista, com instruções simples e bem definidas.
- Passagem de parâmetros por registradores `a0`–`a7`.
- Uso de registradores temporários como `t0`–`t6`.
- Instruções como `lw`, `sw`, `slli`, `blt`, `call`, `ret` são comuns.
- Pseudo-instruções como `li`, `la`, `mv` facilitam a leitura.

[Referência: RISC-V Instruction Set Manual](https://riscv.org/technical/specifications/)

---

## Programa p1.c

### Código em C
```c
#include <stdio.h>

void main () {
  printf("Olá\n");
}
```

### Assembly ARM64
```asm
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    mov     x0, 1
    adr     x1, .L.str
    bl      printf
    ldp     x29, x30, [sp], 16
    ret
```
#### Detalhamento das Instruções - ARM64

Este trecho realiza a chamada da função `printf("Olá\n")` usando a convenção da arquitetura ARM64:

- `stp` e `ldp` lidam com o salvamento/restauração da pilha.
- `mov` e `adr` preparam os argumentos.
- `bl` chama a função externa.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
main:
    addi    sp, sp, -32
    li      a0, 1
    la      a1, .L.str
    call    printf
    addi    sp, sp, 32
    ret
```
#### Detalhamento das Instruções - RISC-V

A lógica aqui reserva espaço na pilha, define os argumentos `a0` e `a1`, chama `printf` e libera a pilha:

- `addi` para manipular a pilha.
- `li`, `la` e `call` são pseudo-instruções comuns.
- `ret` finaliza a execução.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---

## Programa p2.c

### Código em C
```c
#include <stdio.h>

void main () {
  int a, b, r;
  a = 12;
  b = 11;
  r = 0;
  if (b & 0x01) r += a;
  a = a << 1;
  if (b & 0x02) r += a;
  a = a << 1;
  if (b & 0x04) r += a;
  a = a << 1;
  if (b & 0x08) r += a;
  printf("%d\n", r);
}
```

### Assembly ARM64
```asm
main:
    mov     w1, #12
    mov     w2, #11
    mov     w3, #0
    tst     w2, #1
    addne   w3, w3, w1
    lsl     w1, w1, #1
    tst     w2, #2
    addne   w3, w3, w1
    lsl     w1, w1, #1
    tst     w2, #4
    addne   w3, w3, w1
    lsl     w1, w1, #1
    tst     w2, #8
    addne   w3, w3, w1
    mov     w0, w3
    bl      printf
    ret
```
#### Detalhamento das Instruções - ARM64

Esse código usa operações bit a bit e deslocamentos para simular uma multiplicação. O valor `a` é somado a `r` apenas quando certos bits de `b` estão ativados.

- `tst` realiza um AND lógico e atualiza os flags.
- `addne` só soma se o resultado anterior for diferente de zero.
- `lsl` faz o deslocamento à esquerda, equivalente a multiplicar por 2.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
main:
    li      t0, 12
    li      t1, 11
    li      t2, 0
    andi    t3, t1, 1
    beqz    t3, skip1
    add     t2, t2, t0
skip1:
    slli    t0, t0, 1
    andi    t3, t1, 2
    beqz    t3, skip2
    add     t2, t2, t0
skip2:
    slli    t0, t0, 1
    andi    t3, t1, 4
    beqz    t3, skip3
    add     t2, t2, t0
skip3:
    slli    t0, t0, 1
    andi    t3, t1, 8
    beqz    t3, skip4
    add     t2, t2, t0
skip4:
    mv      a0, t2
    call    printf
    ret
```
#### Detalhamento das Instruções - RISC-V

Cada bloco condicional testa um bit de `b` e, se verdadeiro, soma `a` a `r`. O registrador `t0` representa `a`, e é deslocado a cada ciclo usando `slli`.

- `andi` executa AND imediato para testar bits específicos.
- `slli` desloca os bits para a esquerda (multiplica por 2).
- `beqz` desvia se o teste falhar.
- `mv` move o resultado para `a0` antes da chamada do `printf`.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---


## Programa p3.c

### Código em C
```c
#include <stdio.h>

void main () {
  int i = 0;
  do {
    printf("%d", i);
  } while (++i < 10);
}
```

### Assembly ARM64
```asm
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    mov     w1, #0
.Lloop:
    mov     w0, w1
    bl      printf
    add     w1, w1, #1
    cmp     w1, #10
    blt     .Lloop
    ldp     x29, x30, [sp], 16
    ret
```
#### Detalhamento das Instruções - ARM64

Este código realiza um laço `do-while` de 0 a 9, imprimindo cada número:

- `mov` inicializa e prepara os argumentos.
- `bl` chama `printf`.
- `add`, `cmp`, e `blt` controlam o laço.
- `stp/ldp` manipulam a pilha.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
main:
    addi    sp, sp, -16
    li      t0, 0
.Lloop:
    mv      a0, t0
    call    printf
    addi    t0, t0, 1
    li      t1, 10
    blt     t0, t1, .Lloop
    addi    sp, sp, 16
    ret
```
#### Detalhamento das Instruções - RISC-V

A lógica do laço `do-while` é representada por:

- `li` e `mv` para inicialização e argumentos.
- `call` para `printf`.
- `addi`, `blt` e `li` controlam o laço.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---


## Programa p5.c

### Código em C
```c
#include <stdio.h>

double f(double x, double y, double z) {
  return x*x + y*y + z*z;
}

void main () {
  int i = 0;
  printf("%lf", f(0.3, 5.0, 15.0));
}
```

### Assembly ARM64
```asm
f:
    fmadd   d0, d0, d0, d1
    fmsub   d0, d2, d2, d0
    ret

main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    mov     w0, 0
    fmov    d0, #0.3
    fmov    d1, #5.0
    fmov    d2, #15.0
    bl      f
    mov     x0, 1
    adr     x1, .L.str
    bl      printf
    ldp     x29, x30, [sp], 16
    ret
```
#### Detalhamento das Instruções - ARM64

A função `f` usa instruções compostas para realizar multiplicações e somas com ponto flutuante:

- `fmadd` executa: d0 = d0*d0 + d1
- `fmsub` faz: d0 = d0 - d2*d2

No `main`, `fmov` carrega constantes, `bl` chama funções e `stp/ldp` manipulam o frame.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
f:
    fld     fa4, 0(sp)
    fld     fa5, 8(sp)
    fld     fa6, 16(sp)
    fmul.d  fa4, fa4, fa4
    fmul.d  fa5, fa5, fa5
    fadd.d  fa4, fa4, fa5
    fmul.d  fa6, fa6, fa6
    fadd.d  fa0, fa4, fa6
    ret

main:
    addi    sp, sp, -32
    li      a0, 0
    fmv.d.x fa0, zero
    li      a1, 1065353216   # 0.3
    li      a2, 1084227584   # 5.0
    li      a3, 1097859072   # 15.0
    call    f
    call    printf
    addi    sp, sp, 32
    ret
```
#### Detalhamento das Instruções - RISC-V

A função `f` carrega três argumentos e aplica três multiplicações (`fmul.d`) e duas somas (`fadd.d`).

- `fld` lê os valores da pilha.
- `li` carrega constantes.
- `call` realiza chamadas de função.
- `fmv.d.x` move zero como inicialização.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---


## Programa p6.c

### Código em C
```c
#include <stdio.h>

int a[] = {3, 5, 7, 11, 13};

void main () {
  int i = 0;
  do {
    printf("%d, %d", i, a[i]);
  } while (++i < 5);
}
```

### Assembly ARM64
```asm
main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    mov     w1, #0
    adrp    x2, a
    add     x2, x2, :lo12:a
.Lloop:
    mov     w0, w1
    ldr     w3, [x2, w1, SXTW #2]
    mov     w1, w3
    bl      printf
    add     w1, w0, #1
    cmp     w0, #4
    ble     .Lloop
    ldp     x29, x30, [sp], 16
    ret
```
#### Detalhamento das Instruções - ARM64

- `adrp` e `add` obtêm o endereço do vetor `a`.
- `ldr` acessa `a[i]` (usando extensão de índice).
- `bl` chama `printf`.
- `cmp`, `add`, `ble` controlam o laço `do-while`.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
main:
    addi    sp, sp, -16
    li      t0, 0
    la      t1, a
.Lloop:
    mv      a0, t0
    slli    t2, t0, 2
    add     t3, t1, t2
    lw      a1, 0(t3)
    call    printf
    addi    t0, t0, 1
    li      t4, 5
    blt     t0, t4, .Lloop
    addi    sp, sp, 16
    ret
```
#### Detalhamento das Instruções - RISC-V

- `la` carrega o endereço do vetor `a`.
- `slli` multiplica o índice por 4 (tamanho de int).
- `lw` carrega `a[i]`.
- `call` e `mv` lidam com argumentos e chamadas.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---


## Programa p7.c

### código em C
```c
#include <stdio.h>

void p(int n, int *a) {
  int i = 0;
  do {
    printf("%d, %d", i, a[i]);
  } while (++i < n);
}

void main () {
  int a[] = {3, 5, 7, 11, 13};
  int n = 5;
  p(n, a);
}
```

### Assembly ARM64
```asm
p:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    mov     w2, #0
.Lloop:
    mov     w0, w2
    ldr     w1, [x1, w2, SXTW #2]
    bl      printf
    add     w2, w2, #1
    cmp     w2, w0
    blt     .Lloop
    ldp     x29, x30, [sp], 16
    ret

main:
    stp     x29, x30, [sp, -16]!
    mov     x29, sp
    adrp    x1, a
    add     x1, x1, :lo12:a
    mov     w0, #5
    bl      p
    ldp     x29, x30, [sp], 16
    ret
```
#### Detalhamento das Instruções - ARM64

- `main` prepara os argumentos: tamanho `n` (w0) e endereço do vetor (x1).
- A função `p` usa `ldr` com índice para acessar `a[i]`.
- `cmp`, `blt`, e `add` controlam o laço.

[Referência: ARM Instruction Set - ARM Developer](https://developer.arm.com/documentation/ddi0596/latest/)

### Assembly RISC-V
```asm
p:
    addi    sp, sp, -16
    li      t0, 0
.Lloop:
    mv      a0, t0
    slli    t1, t0, 2
    add     t2, a1, t1
    lw      a1, 0(t2)
    call    printf
    addi    t0, t0, 1
    blt     t0, a0, .Lloop
    addi    sp, sp, 16
    ret

main:
    addi    sp, sp, -16
    li      a0, 5
    la      a1, a
    call    p
    addi    sp, sp, 16
    ret
```
#### Detalhamento das Instruções - RISC-V

- `main` passa `n` e o vetor como argumentos em `a0` e `a1`.
- A função `p` itera com `blt` e usa `slli`, `add`, `lw` para acessar `a[i]`.

[Referência: RISC-V Instruction Reference](https://riscv.org/technical/specifications/)

---

## Comentários e Conclusões

A comparação entre as arquiteturas ARM64 e RISC-V ao longo dos programas demonstrou como cada uma implementa seus princípios de design:

- **ARM64** tende a apresentar instruções mais compactas e compostas, como `fmadd` e `fmsub`, favorecendo performance por meio de operações combinadas. Além disso, o uso explícito da pilha com `stp/ldp` indica uma organização mais estruturada para chamadas de função.

- **RISC-V**, por outro lado, se mantém fiel à filosofia RISC pura: instruções simples, com um número reduzido de formatos. A clareza e previsibilidade das instruções como `addi`, `slli` e `blt` tornam o Assembly mais acessível para aprendizado e análise.

Algumas observações importantes:

- A manipulação de vetores e ponteiros foi bem ilustrada nos programas `p6.c` e `p7.c`, onde ambos os conjuntos de instruções mostraram eficiência ao acessar índices de arrays.
- A passagem de parâmetros e o uso de registradores seguem convenções bem definidas em ambas as arquiteturas.
- O uso de pseudo-instruções em RISC-V, como `li`, `mv`, `la`, torna o Assembly mais legível, embora elas não existam diretamente no hardware.

Essa análise permite observar não apenas as diferenças sintáticas, mas também **as decisões de projeto de cada arquitetura**, o que é fundamental para engenheiros de software embarcado e compiladores.

Ambas as arquiteturas são poderosas, e cada uma tem seus pontos fortes em diferentes contextos. Enquanto ARM64 é amplamente adotada em produtos comerciais, RISC-V cresce rapidamente como uma alternativa aberta, modular e didática.

---
