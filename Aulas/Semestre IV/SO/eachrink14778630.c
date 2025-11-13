#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/* ------------------------------------------------------------------- PARAMETROS ------------------------------------------------------------ */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int freq_global[256 * 256] = {0};

typedef struct {
    unsigned char *dados;
    size_t inicio;
    size_t fim;
    size_t tamanho_total;
} ThreadArgs;

/* ------------------------------------------------------------------- CONTA PARES ------------------------------------------------------------ */

void *contar_pares(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int freq_local[256 * 256] = {0};

    for (size_t i = args->inicio; i + 1 < args->fim; i++) {
        unsigned char a = args->dados[i];
        unsigned char b = args->dados[i + 1];
        freq_local[a * 256 + b]++;
    }

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 256 * 256; i++)
        freq_global[i] += freq_local[i];
    pthread_mutex_unlock(&mutex);

    return NULL;
}

/* ------------------------------------------------------------------- COMPACTACAO ------------------------------------------------------------ */

void compactar(const char *entrada, const char *saida, int nthreads) {
    printf("Compactando '%s' com %d threads...\n", entrada, nthreads);

    int fd = open(entrada, O_RDONLY);
    if (fd < 0) { perror("Erro ao abrir arquivo de entrada"); exit(1); }

    struct stat st;
    if (fstat(fd, &st) < 0) { perror("Erro ao obter tamanho"); close(fd); exit(1); }
    size_t tamanho = st.st_size;

    unsigned char *dados = mmap(NULL, tamanho, PROT_READ, MAP_PRIVATE, fd, 0);
    if (dados == MAP_FAILED) { perror("Erro ao mapear arquivo"); close(fd); exit(1); }
    close(fd);

    unsigned char *buffer = malloc(tamanho);
    memcpy(buffer, dados, tamanho);
    munmap(dados, tamanho);

    int capacidade = 256;
    unsigned char (*tabela)[2] = malloc(capacidade * sizeof(*tabela));
    int total_pares = 0;
    unsigned char simbolo = 0x80;

    while (simbolo < 0xFF) {
        memset(freq_global, 0, sizeof(freq_global));

        pthread_t threads[nthreads];
        ThreadArgs args[nthreads];

        size_t bloco_base = tamanho / nthreads;
        size_t resto = tamanho % nthreads;
        size_t pos = 0;

        for (int i = 0; i < nthreads; i++) {
            size_t tam_atual = bloco_base + (i < resto ? 1 : 0);
            args[i].inicio = pos;
            args[i].fim = pos + tam_atual;

            if (args[i].fim < tamanho)
                args[i].fim++;

            args[i].dados = buffer;
            args[i].tamanho_total = tamanho;
            pos += tam_atual;
            pthread_create(&threads[i], NULL, contar_pares, &args[i]);
        }

        for (int i = 0; i < nthreads; i++)
            pthread_join(threads[i], NULL);

        int max_freq = -1;
        int melhor_par = 0;
        for (int i = 0; i < 256 * 256; i++) {
            unsigned char a = i / 256;
            unsigned char b = i % 256;

            if (a >= simbolo || b >= simbolo)
                continue;

            if (freq_global[i] > max_freq ||
               (freq_global[i] == max_freq && i < melhor_par)) {
                max_freq = freq_global[i];
                melhor_par = i;
            }
        }

        if (melhor_par < 0 || max_freq <= 1)
            break;

        unsigned char a = melhor_par / 256;
        unsigned char b = melhor_par % 256;

        if (total_pares >= capacidade) {
            capacidade *= 2;
            tabela = realloc(tabela, capacidade * sizeof(*tabela));
            if (!tabela) { perror("realloc tabela"); exit(1); }
        }

        tabela[total_pares][0] = a;
        tabela[total_pares][1] = b;
        total_pares++;

        unsigned char *novo = malloc(tamanho);
        if (!novo) { perror("malloc novo"); exit(1); }

        size_t j = 0;
        for (size_t i = 0; i < tamanho;) {
            if (i < tamanho - 1 && buffer[i] == a && buffer[i + 1] == b) {
                novo[j++] = simbolo;
                i += 2;
            } else {
                novo[j++] = buffer[i++];
            }
        }

        free(buffer);
        buffer = novo;
        tamanho = j;
        simbolo++;

        if (simbolo >= 0xFF)
            break;
    }

    printf("Compactação concluída. %d pares substituídos.\n", total_pares);

    int fd_out = open(saida, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) { perror("Erro ao criar arquivo de saída"); exit(1); }

    for (int i = 0; i < total_pares; i++) {
        if (write(fd_out, tabela[i], 2) != 2)
            perror("Erro ao escrever par");
    }

    unsigned char fim = 0xFF;
    if (write(fd_out, &fim, 1) != 1)
        perror("Erro ao escrever delimitador");

    if (write(fd_out, buffer, tamanho) != (ssize_t)tamanho)
        perror("Erro ao escrever dados");

    close(fd_out);
    free(buffer);
    free(tabela);
}

/* ---------------------------------------------------------------- DESCOMPACTACAO ------------------------------------------------------------ */

void descompactar(const char *entrada, const char *saida, int nthreads) {
    printf("Descompactando '%s'...\n", entrada);

    int fd = open(entrada, O_RDONLY);
    if (fd < 0) { perror("Erro ao abrir arquivo compactado"); exit(1); }

    struct stat st;
    if (fstat(fd, &st) < 0) { perror("Erro ao obter tamanho"); close(fd); exit(1); }
    size_t tamanho = st.st_size;

    unsigned char *dados = mmap(NULL, tamanho, PROT_READ, MAP_PRIVATE, fd, 0);
    if (dados == MAP_FAILED) { perror("Erro ao mapear arquivo"); close(fd); exit(1); }
    close(fd);

    size_t pos_ff = 0;
    while (pos_ff < tamanho && dados[pos_ff] != 0xFF)
        pos_ff++;

    if (pos_ff == tamanho) {
        fprintf(stderr, "Erro: delimitador 0xFF não encontrado!\n");
        munmap(dados, tamanho);
        exit(1);
    }

    int total_pares = pos_ff / 2;
    unsigned char tabela[total_pares][2];
    for (int i = 0; i < total_pares; i++) {
        tabela[i][0] = dados[i * 2];
        tabela[i][1] = dados[i * 2 + 1];
    }

    size_t inicio_dados = pos_ff + 1;
    size_t len_dados = tamanho - inicio_dados;

    unsigned char *buffer = malloc(len_dados);
    memcpy(buffer, dados + inicio_dados, len_dados);
    size_t tamanho_atual = len_dados;

    for (int i = total_pares - 1; i >= 0; i--) {
        unsigned char simbolo = 0x80 + i;
        unsigned char a = tabela[i][0];
        unsigned char b = tabela[i][1];

        unsigned char *novo = malloc(tamanho_atual * 2);
        if (!novo) { perror("malloc"); exit(1); }

        size_t j = 0;
        for (size_t k = 0; k < tamanho_atual; k++) {
            if (buffer[k] == simbolo) {
                novo[j++] = a;
                novo[j++] = b;
            } else {
                novo[j++] = buffer[k];
            }
        }

        free(buffer);
        buffer = novo;
        tamanho_atual = j;
    }

    int fd_out = open(saida, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) { perror("Erro ao criar arquivo de saída"); exit(1); }

    if (write(fd_out, buffer, tamanho_atual) != (ssize_t)tamanho_atual)
        perror("Erro ao escrever saída");

    close(fd_out);
    free(buffer);
    munmap(dados, tamanho);

    printf("Descompactação concluída. Arquivo salvo em '%s'\n", saida);
}

/* ------------------------------------------------------------------- MAIN ------------------------------------------------------------ */
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <c|d> <entrada> <saida> <threads>\n", argv[0]);
        return 1;
    }

    char comando = argv[1][0];
    char *entrada = argv[2];
    char *saida = argv[3];
    int nthreads = atoi(argv[4]);

    if (nthreads == 0) {
        nthreads = get_nprocs();
        printf("Número de threads ajustado automaticamente: %d\n", nthreads);
    }

    if (comando == 'c')
        compactar(entrada, saida, nthreads);
    else if (comando == 'd')
        descompactar(entrada, saida, nthreads);
    else
        fprintf(stderr, "Erro: comando deve ser 'c' (compactar) ou 'd' (descompactar).\n");

    return 0;
}
