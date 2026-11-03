#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>




typedef struct {
    


int main(){
    //first, we need to get the user inputted matrix
    printf("Enter your matrix: \n");
    // 1 <= n <= 10
    char buffer [50] = {0};
    bool matrix_buffer [1000] = {false};
    size_t previous_matrix_size_row = 0;
    size_t matrix_size_row = 0;
    size_t matrix_size_column = 0;
    for(;;){

       //first check to make sure we don't overflow the buffer
       if (fgets(buffer, sizeof(buffer), stdin) == NULL) perror("ERROR, input too large. Try again\n"), exit(1);
       
        //we don't overflow the buffer. now we need to parse the input 

       if (buffer[0] == '\n') break;
       //so its not "empty", we need to parse it
       for (size_t i = 0; i < 50; i++){
            
            if (buffer[i] == '\0') break;

            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == ',') continue;

            else if (buffer[i] == '0') matrix_buffer[i] = false;
            else if (buffer[i] == '1') matrix_buffer[i] = true;
            else printf("ERROR, invalid character %c\n", buffer[i]), exit(1);
            i++;
            matrix_size_row++;
       }

        //matrix size checking, by default on first run previous_matrix_size_row should be zero
        if (matrix_size_row != previous_matrix_size_row && previous_matrix_size_row != 0)perror("ERROR, inconsistent row sizes\n"), exit(1);
        else { previous_matrix_size_row = matrix_size_row; matrix_size_row = 0;} 

        matrix_size_column++;
        
    }
    //we broke from the loop. lets make sure our row and columns have the same space size
    if (previous_matrix_size_row != matrix_size_column) printf("ERROR, matrix is not NxN\n"), exit(1);
   
    //okay we already have our "matrix". we know that we can go from 0 to n^2 -1 within our boolean array and access ith and jth elements

    //now we need to implement the two algorithms: transitive closure and warshall's
    

     
 
    return 0; 
}
