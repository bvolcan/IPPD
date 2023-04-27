#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int n;
int solucao[100];
int total_solucoes = 0;
int solucoes_unicas[92][8];
int indice_unicas = 0;

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

int solucao_repetida(int nova_solucao[]) {
    int i, j;
    for (i = 0; i < indice_unicas; i++) {
        for (j = 0; j < n; j++) {
            if (nova_solucao[j] != solucoes_unicas[i][j]) {
                break;
            }
        }
        if (j == n) {
            return 1;
        }
    }
    return 0;
}

void busca(int linha) {
    int i;
    if (linha == n) {
        // encontrou uma solução
        int j;
        total_solucoes++;
        printf("Solucao número %d encontrada:\n", total_solucoes);
        for (i = 0; i < n; i++) {
            for (j = 0; j < solucao[i]; j++) {
                printf(". ");
            }
            printf("R ");
            for (j = solucao[i] + 1; j < n; j++) {
                printf(". ");
            }
            printf("\n");
        }
        printf("\n");
        // adiciona solução única
        int nova_solucao[8];
        for (i = 0; i < n; i++) {
            nova_solucao[i] = solucao[i];
        }
        if (!solucao_repetida(nova_solucao)) {
            for (i = 0; i < n; i++) {
                solucoes_unicas[indice_unicas][i] = nova_solucao[i];
            }
            indice_unicas++;
        }
        return;
    }
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        if (valido(linha, i)) {
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
    printf("Digite o número de threads: ");
    scanf("%d", &t);
    omp_set_num_threads(t);
    start = omp_get_wtime();
    busca(0);
    end = omp_get_wtime();
    printf("Tempo de execucao: %.2f segundos\n", end - start);
    printf("Total de soluções encontradas: %d\n", total_solucoes);
    printf("Total de soluções únicas encontradas: %d\n", indice_unicas);
    return 0;
}
