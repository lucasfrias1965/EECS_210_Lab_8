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

Matrix * make_copy_matrix(Matrix * a){
    Matrix * res = malloc(sizeof(Matrix));
    res->n = a->n;
    res->data = malloc(sizeof(bool) * (a->n * a->n) );
    memcpy(res->data, a->data, sizeof(bool) * (a->n * a->n));
    return res;
}

Matrix * mat_or(Matrix * a, Matrix * b){
    const size_t N = a->n;
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
    printf("a->n = %zu\n", a->n);
    printf("b->n = %zu\n", b->n);
    
    bool quick[N*N];
    for (size_t i = 0; i<N*N; i++) quick[i] = a->data[i] || b->data[i];
   
    return make_matrix(quick, N);  
}


Matrix * mat_mult_bool(Matrix * a, Matrix * b){
    const size_t N = a->n;
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
    
    bool temp[N*N];
    int sum = 0; 
    int res_i = 0; 

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {

            int sum = 0;

            for (size_t k = 0; k < N; k++) {
                sum += a->data[i * N + k] *
                       b->data[k * N + j];
            }

            temp[i * N + j] = (sum != 0);
        }
    }   

    Matrix * res = make_matrix(temp, N);
    return res;  
   
}
