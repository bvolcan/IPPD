## IPPD
Repositório para os trabalhos avaliados da cadeira de Introdução ao Processamento Paralelo e Distribuído do semestre 2022/2, realizada em 2023.

# Entrega 1: N-Rainhas com OpenMP

## Como compilar
Possuindo o compilador GCC devidamente instalado, no ubuntu basta rodar o seguinte comando:

```bash
gcc -fopenmp -o nRainhas nRainhas.c
```
## Como executar
Tendo o código fonte compilado, execute o seguinte comando:

```bash
./nRainhas
```

## Testes de performance
Todos os testes foram realizados numa mesma máquina e os dados foram reunidos e disponibilizados [neste docs](https://docs.google.com/document/d/1fp5Aj1WLLztMhEsa9X2j13sIljrbPa014t-5-pe28xA/edit?usp=sharing)

# Entrega 2: N-Rainhas com OpenMP e MPI

## Como compilar
Possuindo o compilador MPICC devidamente instalado, no ubuntu basta rodar o seguinte comando:

```bash
mpicc -fopenmp nRainhasV2.c -o nRainhasV2
```
## Como executar
Tendo o código fonte compilado, execute o seguinte comando:

```bash
mpirun -n <num_procs> ./nRainhasV2
```
Onde <num_procs> define o número de processos MPI e também o número de rainhas.

## Membros do grupo

<table>
  <tr>
   <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/58444261?v=4" width="100px;" alt="Foto do Bruno Volcan"/><br>
        <sub>
          <b>Bruno Volcan</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/35015195?v=4" width="100px;" alt="Foto do Gui Vahl"/><br>
        <sub>
          <b>Guilerme Vahl</b>
        </sub>
      </a>
    </td>
  </tr>
</table>
