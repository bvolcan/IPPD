#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int total = 0;

int valido(int *tabuleiro, int linha, int coluna) {
    int i, j;
    for (i = 0; i < linha; i++) {
        if (tabuleiro[i] == coluna || abs(i - linha) == abs(tabuleiro[i] - coluna)) {
            return 0;
        }
    }
    return 1;
}

void busca(int *tabuleiro, int n, int linha) {
    int i;
    if (linha == n) {
        #pragma omp atomic
        total++;
    } else {
        for (i = 0; i < n; i++) {
            if (valido(tabuleiro, linha, i)) {
                tabuleiro[linha] = i;
                busca(tabuleiro, n, linha+1);
            }
        }
    }
}

int main() {
    int n, num_threads;
    double start, end;
    printf("Digite o número de rainhas: ");
    scanf("%d", &n);
    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);
    int *tabuleiro = (int*) malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        tabuleiro[i] = -1;
    }
    omp_set_num_threads(num_threads);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int *tabuleiro_privado = (int*) malloc(sizeof(int) * n);
        int j;
        for (j = 0; j < n; j++) {
            tabuleiro_privado[j] = -1;
        }
        #pragma omp for
        for (i = 0; i < n; i++) {
            tabuleiro_privado[0] = i;
            busca(tabuleiro_privado, n, 1);
        }
        free(tabuleiro_privado);
    }
    end = omp_get_wtime();
    printf("Número total de soluções possíveis: %d\n", total);
    printf("Tempo de execução: %f segundos\n", end - start);
    free(tabuleiro);
    return 0;
}
