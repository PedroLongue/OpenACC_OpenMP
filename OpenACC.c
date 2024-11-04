// OpenACC

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1300  // tamanho da matriz

void matrix_multiply_acc(float A, floatB, float C, int n) {
    #pragma acc data copyin(A[0:nn], B[0:nn]) copyout(C[0:nn])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            #pragma acc loop
            for (int j = 0; j < n; j++) {
                float sum = 0.0;
                for (int k = 0; k < n; k++) {
                    sum += A[i * n + k] * B[k * n + j];
                }
                C[i * n + j] = sum;
            }
        }
    }
}

int main() {
    float A = (float)malloc(N * N * sizeof(float));
    float B = (float)malloc(N * N * sizeof(float));
    float C = (float)malloc(N * N * sizeof(float));

    // Inicializar matrizes A e B com valores arbitrários
    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 1.0;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Multiplicação de matrizes com OpenACC
    matrix_multiply_acc(A, B, C, N);

    gettimeofday(&end, NULL);
    double time_taken = ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000000.0));
    printf("Tempo de execução com OpenACC: %.6f segundos\n", time_taken);

    free(A);
    free(B);
    free(C);
    return 0;
}
