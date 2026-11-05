/*
Made 11/4/26 

    <@
    (KU//
      "
    EECS 210
    BY LUCAS FRIAS
    ROCK CHALK!!

Lab 08 - Transitive Closure Algorithm(s)
Description - Given a square NxN matrix representing a graph relationship,
makes it transitive using the transitive closure algorithm O(n^4)
and the Warshall Algorithm O(n^3) to compute the closed transitive relation
Single file, also has both algorithms split in a seperate thing
Enjoy!!!
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


//hi pardas this code is hard to read and harder to make so warning ya

typedef struct {
    size_t n;
    bool * data;
} Matrix;

//so basically, this is our matrix. we can make one, which just makes a heap allocted pointer to the size and the pointer to the pointer 

Matrix * make_matrix(bool * arr, size_t n){
    //create the sizeof struct
    Matrix * res = malloc(sizeof(Matrix));
    res->n = n;//set our n
    //makes the data the size of n^2 for the nxn matrix
    res->data = malloc(sizeof(bool) * n * n);
    //memcpy the array given to the data within our n size
    memcpy(res->data, arr, sizeof(bool) * n*n);
    return res;
}


Matrix * make_copy_matrix(Matrix * a){
    //make_copy_matrix -> given a matrix a,
    //copies the values and makes a new reference
    //and object with the same data

    Matrix * res = malloc(sizeof(Matrix));
    res->n = a->n;
    //malloc the size of our nxn
    res->data = malloc(sizeof(bool) * (a->n * a->n) );
    //copy the data from a to res
    memcpy(res->data, a->data, sizeof(bool) * (a->n * a->n));
    //return res
    return res;
}

Matrix * mat_or(Matrix * a, Matrix * b){
    //mat_or -> given our matrices a and b, ors every element given 
    //that they're the same size and returns a new matrix resulting from it

    const size_t N = a->n; //check n and see if it works
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
    
    bool quick[N*N]; //make a new bool matrix
    for (size_t i = 0; i<N*N; i++) quick[i] = a->data[i] || b->data[i]; //or every element
   
    return make_matrix(quick, N);  
}

/*Matrix * mat_and(Matrix * a, Matrix * b){
    const size_t N = a->n;
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
    
    bool quick[N*N];
    for (size_t i = 0; i<N*N; i++) quick[i] = a->data[i] && b->data[i];
   
    return make_matrix(quick, N);  
}*/



//mat_mult_bool
Matrix * mat_mult_bool(Matrix * a, Matrix * b){
    //given two matrices, does boolean multication, which is 
    //basically just this in boolean algebra notation
    // for some given row Mij
    // Ai1 * Bi1 + Ai2 * Bi2 .... Aij * Bij
    // so the result of the matrix is just like
    // easily computable because we can break early if
    //we get a 1 element because 1 OR X = 1 for all X values in boolean range

    const size_t N = a->n; //check N
    if (!(a->n == b->n)) printf("ERROR: matrixes are not same size"), exit(1);
   
    //make N arr 
    bool temp[N*N];
    int sum = 0; 
    int res_i = 0; 

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            //for every i, j
            int sum = 0; //calculating this row

            for (size_t k = 0; k < N; k++) {
                //sum add up parts

                sum += a->data[i * N + k] *
                       b->data[k * N + j];
                if (sum != 0) break; //break early
            }
            //the temp value at our row columns is equal to whether we have any new elements

            temp[i * N + j] = (sum != 0);
        }
    }   

    Matrix * res = make_matrix(temp, N);
    return res;  
   
}

    
void display_matrix(bool * arr, size_t n){
    //just a basic display functio not much here
    printf("|");
    for (size_t i = 0; i < n*n; i++){
        if (i != 0 && i % n == 0) printf("|\n|"); //break because of n that divides 
        if (arr[i]) printf(" 1 "); 
        if (!arr[i]) printf(" 0 ");
    }
    printf("|\n");
}



void transitive_closure(Matrix * user_matrix){

    //this is pretty much to a T from the algo
    //given but i'll annotate
    //A, B is a copy from the user_matrix

    Matrix * A = make_copy_matrix(user_matrix);
    Matrix * B = make_copy_matrix(user_matrix);

    const size_t N = user_matrix->n; //get N
    
    for (int i = 2; i <= N; i++) {
        
        //get A which is the product of A * the og matrix
        A = mat_mult_bool(A, user_matrix);

        B = mat_or(A, B); //B is A ^ B for all elements

    }

    display_matrix(B->data, B->n); //display the matrix from its elements
}

void warshie_my_beloved(Matrix * user_matrix){
    //user_matrix->n sets the value for N
    const size_t N = user_matrix->n;
    //make our iterator matrix
    Matrix * W = make_copy_matrix(user_matrix);
    //for all K,i, J
    for (int k = 0; k<N; k++){
        for (int i = 0; i<N; i++){
            for (int j = 0; j<N; j++){
                //do this crazy little statement, i trust you warshall, thanks for the slightly better time complexity
               W->data[i*N + j] = W->data[i*N+j] || (W->data[i*N+k] && W->data[k*N + j]);
            } 
        }
    }
    //display that thingy
    display_matrix(W->data, W->n);
}

int main(){
    //first, we need to get the user inputted matrix
    printf("Enter your matrix: \n");
    // 1 <= n <= 10
    char buffer [50] = {0};
    bool matrix_buffer [1000] = {false};
    //just initing some loop stuff
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
            //assign to the matrix buffer
            else if (buffer[i] == '0') matrix_buffer[matrix_index] = false;
            else if (buffer[i] == '1') matrix_buffer[matrix_index] = true;
            else printf("ERROR, invalid character %c\n", buffer[i]), exit(1);

            //if we got here and didnt err out increment up 
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


    if (matrix_size_column < 1 || matrix_size_column > 10) printf("N is not in input size 1 <= n <= 10"), exit(1);

    Matrix * user_matrix = make_matrix(matrix_buffer, matrix_size_column); 
    //display_matrix(user_matrix->data, user_matrix->n);

    //now we need to implement the two algorithms: transitive closure and warshall's
    
    //print trans closure
    printf("Algorithm 1, Transitive Closure\n");
    transitive_closure(user_matrix);    

    //print warshall
    printf("Algorithm 2, Warshall's Algorithm\n");
    warshie_my_beloved(user_matrix); 
 
    return 0; 
}
