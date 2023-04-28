#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int n;
int total = 0;
int solucao[100][100];

int valido(int linha, int coluna, int thread) {
    int i;
    for (i = 0; i < linha; i++) {
        if (solucao[i][thread] == coluna || abs(i - linha) == abs(solucao[i][thread] - coluna)) {
            return 0;
        }
    }
    return 1;
}

void busca(int linha, int thread) {
    int i;
    if (linha == n) {
        #pragma omp atomic
        total++;
    }
    // #pragma omp parallel for
    for (i = 0; i < n; i++) {
        // printf("Thread %d, linha %d, coluna %d\n",omp_get_thread_num(), linha, i);
        if (valido(linha, i, thread)) {
            solucao[linha][thread] = i;
            busca(linha + 1, thread);
        }
    }
}

void iniciaBusca() {
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        int current_thread = omp_get_thread_num();
        solucao[0][current_thread] = i;
        busca(1, current_thread);
    }
}

int main() {
    int t;
    double start, end;
    printf("Digite o número de rainhas: ");
    scanf("%d", &n);
    printf("Digite o numero de threads: ");
    scanf("%d", &t);
    while (t > omp_get_max_threads() || t < 1) {
        printf("Digite o numero de threads: ");
        scanf("%d", &t);
    }
    omp_set_num_threads(t);
    start = omp_get_wtime();
    iniciaBusca();
    end = omp_get_wtime();
    if (total > 0) {
        printf("Soluções encontradas: %d\n", total);
    } else {
        printf("Nao ha solução para N=%d\n", n);
    }
    printf("Tempo de execucao: %.2f segundos\n", end - start);
    return 0;
}
