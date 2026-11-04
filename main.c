#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "matrix.c"



    
void display_matrix(bool * arr, size_t n){
    printf("|");
    for (size_t i = 0; i < n*n; i++){
        if (i != 0 && i % n == 0) printf("|\n|");
        if (arr[i]) printf(" 1 ");
        if (!arr[i]) printf(" 0 ");
    }
    printf("|\n");
}





void transitive_closure(Matrix * user_matrix){
    Matrix * A = make_copy_matrix(user_matrix);
    Matrix * B = make_copy_matrix(user_matrix);

    const size_t N = user_matrix->n;
    
    for (int i = 2; i <= N; i++) {

        A = mat_mult_bool(A, user_matrix);

        B = mat_or(A, B);

    }

    display_matrix(B->data, B->n);
}

void warshie_my_beloved(Matrix * user_matrix){
    const size_t N = user_matrix->n;
    Matrix * W = make_copy_matrix(user_matrix);
    for (int k = 1; k<N; k++){
        for (int i = 1; i<N; i++){
            for (int j = 1; j<N; j++){
               W->data[i*N + j] = W->data[i*N+j] || (W->data[i*N+k] && W->data[k*N + j]);
            } 
        }
    }
}

int main(){
    //first, we need to get the user inputted matrix
    printf("Enter your matrix: \n");
    // 1 <= n <= 10
    char buffer [50] = {0};
    bool matrix_buffer [1000] = {false};
    size_t previous_matrix_size_row = 0;
    size_t matrix_size_row = 0;
    size_t matrix_size_column = 0;
    size_t matrix_index = 0;
    for(;;){

       //first check to make sure we don't overflow the buffer
       if (fgets(buffer, sizeof(buffer), stdin) == NULL) perror("ERROR, input too large. Try again\n"), exit(1);
       
        //we don't overflow the buffer. now we need to parse the input 

       if (buffer[0] == '\n') break;
       //so its not "empty", we need to parse it
       for (size_t i = 0; i < 50; i++){
            
            if (buffer[i] == '\0') break;

            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == ',') continue;

            else if (buffer[i] == '0') matrix_buffer[matrix_index] = false;
            else if (buffer[i] == '1') matrix_buffer[matrix_index] = true;
            else printf("ERROR, invalid character %c\n", buffer[i]), exit(1);
            
            matrix_size_row++, matrix_index++;
       }

        //matrix size checking, by default on first run previous_matrix_size_row should be zero
        if (matrix_size_row != previous_matrix_size_row && previous_matrix_size_row != 0)printf("ERROR, inconsistent row sizes\n"), exit(1);
        else { previous_matrix_size_row = matrix_size_row; matrix_size_row = 0;}

        matrix_size_column++;

    }
    //we broke from the loop. lets make sure our row and columns have the same space size
    if (previous_matrix_size_row != matrix_size_column) printf("ERROR, matrix is not NxN\n"), exit(1);

    //display_matrix(matrix_buffer, matrix_size_column*matrix_size_column);

    if (previous_matrix_size_row != matrix_size_column) printf("ERROR, matrix is not NxN\n"), exit(1);
    Matrix * user_matrix = make_matrix(matrix_buffer, matrix_size_column); 
    //display_matrix(user_matrix->data, user_matrix->n);

    //now we need to implement the two algorithms: transitive closure and warshall's
    transitive_closure(user_matrix);    

     
 
    return 0; 
}
