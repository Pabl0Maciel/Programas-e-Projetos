<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Programação%20em%20C&fontSize=36&fontColor=4F8EF7&fontAlignY=45&desc=Fundamentos%20e%20algoritmos%20clássicos&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

Coleção de exemplos e exercícios cobrindo os principais conceitos da linguagem C — da sintaxe básica a algoritmos de ordenação e estruturas de dados.

---

## 📂 Conteúdo

| Tópico | Arquivos | O que cobre |
|--------|----------|-------------|
| [`Argc e Argv`](./Argc%20e%20Argv) | `argc_argv.c` | Parâmetros de linha de comando |
| [`Arrays`](./Arrays) | `arrays.c` · `arrays2.c` · `arrays3.c` | Declaração, acesso e manipulação |
| [`Bit a bit, Hex e Matemática`](./Bit%20a%20bit%2C%20hexadecimal%20e%20operacoes%20matematicas) | `bit1.c` · `hexadecimal.c` · `calculo.c` | Operadores bitwise, base hex, aritmética |
| [`Busca`](./Busca) | `busca_sequencial.c` · `busca_binaria.c` | Busca linear e binária |
| [`Funções`](./Funcoes) | `funcoes.c` · `funcoes2.c` · `funcoes3.c` · `funcoes4.c` | Definição, recursão, passagem por referência |
| [`If e Else`](./If%20e%20Else) | `ifelse.c` | Controle de fluxo condicional |
| [`Matriz`](./Matriz) | `matrizes.c` | Matrizes bidimensionais |
| [`Ordenação`](./Ordenacao) | `bubbleSort.c` · `insertionSort.c` · `selectionSort.c` · `quickSort.c` · `mergeSort.c` · `heapSort.c` · `qsort.c` · `ordenacao_struct.c` | 7 algoritmos de ordenação + ordenação de structs |
| [`Ponteiros`](./Ponteiros) | `ponteiros.c` | Aritmética de ponteiros, arrays e funções |
| [`Relacionais`](./Relacionais) | `relacional1.c` · `relacional2.c` | Operadores relacionais e lógicos |
| [`Scanf`](./Scanf) | `scanf.c` | Leitura de dados do usuário |
| [`Strings`](./Strings) | `strings1.c` · `strings2.c` | Manipulação e funções de string |
| [`Structs`](./Structs) | `structs.c` · `structs2.c` | Definição, acesso e uso de structs |
| [`Switch e Loops`](./Switch%20case%20e%20loops) | `switchcase.c` · `do-while-for.c` | Switch case, for, while, do-while |
| [`Main`](./main) | `areas.c` · `poligonos.c` · `main2.c` | Função main, modularização com `.h` |

---

## ⚙️ Como compilar e rodar

```bash
# Compilar
gcc nome_do_arquivo.c -o saida

# Executar
./saida
```

Para arquivos com múltiplos `.c` (ex: `main` + `poligonos`):
```bash
gcc main2.c poligonos.c -o saida
./saida
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
