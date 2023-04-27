#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int count = 0;

int is_valid(int *board, int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        if (board[i] == col || abs(i - row) == abs(board[i] - col)) {
            return 0;
        }
    }
    return 1;
}

void n_queens(int *board, int n, int row) {
    int i;
    if (row == n) {
        #pragma omp atomic
        count++;
    } else {
        for (i = 0; i < n; i++) {
            if (is_valid(board, row, i)) {
                board[row] = i;
                n_queens(board, n, row+1);
            }
        }
    }
}

int main() {
    int n, num_threads;
    double start_time, end_time;
    printf("Digite o valor de N: ");
    scanf("%d", &n);
    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);
    int *board = (int*) malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
        board[i] = -1;
    }
    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int *board_private = (int*) malloc(sizeof(int) * n);
        int j;
        for (j = 0; j < n; j++) {
            board_private[j] = -1;
        }
        #pragma omp for
        for (i = 0; i < n; i++) {
            board_private[0] = i;
            n_queens(board_private, n, 1);
        }
        free(board_private);
    }
    end_time = omp_get_wtime();
    printf("Número total de soluções possíveis: %d\n", count);
    printf("Tempo de execução: %f segundos\n", end_time - start_time);
    free(board);
    return 0;
}
