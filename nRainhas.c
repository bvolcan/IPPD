#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int n;
int solucao[100];
int encontrou = 0;

int valido(int linha, int coluna) {
    int i;
    for (i = 0; i < linha; i++) {
        if (solucao[i] == coluna || 
            solucao[i] - coluna == i - linha ||
            coluna - solucao[i] == i - linha) {
            return 0;
        }
    }
    return 1;
}

void busca(int linha) {
    int i;
    if (linha == n) {
        encontrou = 1;
        return;
    }
    #pragma omp parallel for shared(encontrou) num_threads(omp_get_num_threads())
    for (i = 0; i < n; i++) {
        if (!encontrou && valido(linha, i)) {
            solucao[linha] = i;
            busca(linha + 1);
        }
    }
}

int main() {
    int i, t;
    double start, end;
    printf("Digite o número de rainhas: ");
    scanf("%d", &n);
    printf("Digite o numero de threads: ");
    scanf("%d", &t);
    omp_set_num_threads(t);
    start = omp_get_wtime();
    busca(0);
    end = omp_get_wtime();
    if (encontrou) {
        printf("Solucao encontrada:\n");
        for (i = 0; i < n; i++) {
            int j;
            for (j = 0; j < solucao[i]; j++) {
                printf(". ");
            }
            printf("Q ");
            for (j = solucao[i] + 1; j < n; j++) {
                printf(". ");
            }
            printf("\n");
        }
    } else {
        printf("Nao ha solucao para N=%d\n", n);
    }
    printf("Tempo de execucao: %.2f segundos\n", end - start);
    return 0;
}
