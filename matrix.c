#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t n;
    bool * data;
} Matrix;

Matrix * make_matrix(bool * arr, size_t n){
    Matrix * res = malloc(sizeof(Matrix));
    res->n = n;
    res->data = malloc(sizeof(bool) * n * n);
    memcpy(res->data, arr, sizeof(n*n));
    return res;
}

Matrix * mat_mult_bool(Matrix * a, Matrix * b){
    const size_t N = a->n;
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
    
    bool quick[N*N];
    Matrix * res = make_matrix(quick, N);
    int sum = 0; 
    int res_i = 0; 
    for (size_t i = 0; i<N; i++) {
        for (size_t j = 0; j<N; j++) { 
            sum = 0;
            for (size_t k = 0; k < N; k++) {
               sum += a->data[i*N + j] * a->data[j * N + k];
               res_i++;
            }

            if (!sum) res->data[res_i] = false;
            if (sum) res->data[res_i] = true;
        }
    }
   
    return res;  
   
}
