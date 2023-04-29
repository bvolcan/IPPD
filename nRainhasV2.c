#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

int n;
int total = 0;
int solucao[100][100];

int valido(int linha, int coluna, int thread)
{
    int i;
    for (i = 0; i < linha; i++)
    {
        if (solucao[i][thread] == coluna || abs(i - linha) == abs(solucao[i][thread] - coluna))
        {
            return 0;
        }
    }
    return 1;
}

void busca(int linha, int thread)
{
    if (linha == n)
    {
        #pragma omp atomic
        total++;
    }
    for (int i = 0; i < n; i++)
    {
        if (valido(linha, i, thread))
        {
            solucao[linha][thread] = i;
            busca(linha + 1, thread);
        }
    }
}

void iniciaBusca(int current_rank)
{    
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        int current_thread = omp_get_thread_num();
        solucao[0][current_thread] = current_rank;
        if (valido(1, i, current_thread)) {
            solucao[1][current_thread] = i;
            busca(2, current_thread);
        }
    }
}

int main(int argc, char **argv)
{
    int t, rank, size;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Solução para %d rainhas\n", size);
        printf("Digite o numero de threads: ");
        scanf("%d", &t);
        while (t > omp_get_max_threads() || t < 1)
        {
            printf("Digite o numero de threads: ");
            scanf("%d", &t);
        }
    }

    n = size;

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&t, 1, MPI_INT, 0, MPI_COMM_WORLD);

    omp_set_num_threads(t);
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    iniciaBusca(rank);
    end = MPI_Wtime();

    int total_final = 0;
    MPI_Reduce(&total, &total_final, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        if (total_final > 0)
        {
            printf("Soluções encontradas: %d\n", total_final);
        }
        else
        {
            printf("Nao ha solução para N=%d\n", n);
        }
        printf("Tempo de execucao: %f segundos\n", end - start);
    }
    MPI_Finalize();
    return 0;
}
