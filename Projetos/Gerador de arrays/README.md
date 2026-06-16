<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0D0D0D,50:1a1a2e,100:16213e&height=140&section=header&text=Gerador%20de%20Arrays&fontSize=36&fontColor=4F8EF7&fontAlignY=45&desc=Benchmark%20de%20algoritmos%20de%20ordenação%20em%20C&descColor=00D4FF&descSize=15&descAlignY=65&animation=fadeIn" width="100%"/>

</div>

<div align="center">

![C](https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

</div>

---

## 🎯 Objetivo

Ferramenta em C para geração de arrays aleatórios com tamanho configurável, com medição precisa do tempo de execução do algoritmo de ordenação em nanossegundos. Útil para benchmarking e comparação de algoritmos de ordenação.

---

## ⚙️ Como funciona

```
Usuário informa o tamanho N
        │
        ▼
malloc(N × sizeof(int))      ← alocação dinâmica
        │
        ▼
srand(time(NULL))            ← semente baseada no tempo
rand() × N                   ← preenchimento aleatório
        │
        ▼
clock_gettime(CLOCK_MONOTONIC)  ← marca início
insertionSort(array, N)
clock_gettime(CLOCK_MONOTONIC)  ← marca fim
        │
        ▼
elapsed = (fim - início) em nanosegundos
free(array)
        │
        ▼
"Deseja gerar outro array?"  ← loop até 'nao'
```

---

## 🔧 Detalhes técnicos

| Recurso | Implementação |
|---------|---------------|
| Alocação | `malloc` com verificação de falha |
| Semente | `time(NULL)` — imprime o valor usado para reprodutibilidade |
| Ordenação ativa | `insertionSort` |
| Ordenação alternativa | `qsort` com `comparaCrescente` (comentado no código) |
| Medição de tempo | `clock_gettime(CLOCK_MONOTONIC)` — precisão em nanosegundos |
| Liberação | `free` após cada execução |

---

## 🚀 Como compilar e executar

```bash
# Compilar
gcc gerador.c -o gerador

# Executar
./gerador
```

**Exemplo de saída:**

```
Insira o tamanho do array de inteiros: 10000
alocado com sucesso!
semente usada: 1721834592
Ultimo elemento nao ordenado: 847291034
Tempo de execucao: 48203712 nanosegundos
Deseja gerar outro array? Responda 'sim' ou 'nao':
```

> Para testar com `qsort`, basta descomentar a linha `qsort(...)` e comentar a linha `insertionSort(...)` no `main`.

---

## 📂 Estrutura

```
📦 Gerador de arrays/
│
├── gerador.c        # Código fonte
├── output/gerador   # Binário compilado
└── README.md
```

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0D0D0D&height=80&section=footer" width="100%"/>

</div>
