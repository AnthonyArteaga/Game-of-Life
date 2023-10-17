#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

#include "life.h"

int numberOfNeighbors(int row, int col, char matrix[26][82]);
bool isAliveNextGen(int row, int col, char matrix[26][82]);
void printMatrixNoBorder(char matrixWithX[26][82]);
void moveCellToNextGenMatrix(int matrixNum, int row, int col, char matrix[26][82]);

//global variables
char grids[2][26][82];


/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */
int main(int argc, char *argv[]){
    if(argc <=  2 || argc > 3){
        printf("ERROR\n");
        return -1;
    }
    else{
        
        char **parsedFile = parse_life(argv[1]); //array of contents of each gridy

        if(parsedFile == NULL){
            printf("ERROR\n");
            return -1;
        } else{
            
            

            for(int i=0; i <= 25; i++){
                for(int j=0; j <= 81; j++){
                    if(i == 0 || i == 25){  //border supposed to be here
                        grids[0][i][j] = ' ';              
                    } else{
                        if(j == 0 || j == 81){  //border supposed to be here
                            grids[0][i][j] = ' ';
                        }
                        else{
                            grids[0][i][j] = parsedFile[i-1][j-1];
                        }
                    }
                }
            }

            //code above makes grids usable

/*            
            printMatrixNoBorder(grids[0]);
            //gen 0 is populated as it should be at this point

            printf("=====\n");

            for(int i = 1; i <= 24; i++){
                    for(int j = 1; j <= 80; j++){
                        moveCellToNextGenMatrix ( 1 , i, j, grids[0]);
                    }
            }

            printMatrixNoBorder(grids[1]);

            printf("=====\n");

            for(int i = 1; i <= 24; i++){
                for(int j = 1; j <= 80; j++){
                    moveCellToNextGenMatrix ( 0 , i, j, grids[1]);
                }
            }

            printMatrixNoBorder(grids[0]);
*/                    

            /* KINDA ISH WORKING CODE BELOW
            int genNum = atoi(argv[2]);
            int current = 0;
            
            for(int k = 0; k <= (int)(genNum/2); k++){  //(int)(genNum/2) swaps will ocurr with even genNum at grid[0] and odd at grid[1]

                for(int i = 1; i <= 24; i++){
                    for(int j = 1; j <= 80; j++){
                        moveCellToNextGenMatrix( (current+1)%2 , i, j, grids[current]);  
                    } 
                }
                
                current = (current+1)%2;
            }*/

            /*
            //will be printing the final gen
            //if gen is even return grid[0] if odd grid[1]
            if(genNum%2 == 0){
                printMatrixNoBorder(grids[0]);
            } else {
                printMatrixNoBorder(grids[1]);
            } 
            */

            int genNum = atoi(argv[2]);
            int k=0;
                for(int current = 0; k<genNum; current = (current+1)%2 ){
                
                for(int i = 1; i <= 24; i++){
                    for(int j = 1; j <= 80; j++){
                        moveCellToNextGenMatrix ( (current+1)%2 , i, j, grids[current]);
                    }
                }
                k++;
            }



            //will be printing the final gen
            //if gen is even return grid[0] if odd grid[1]
            if(genNum%2 == 0){
                printMatrixNoBorder(grids[0]);
            } else {
                printMatrixNoBorder(grids[1]);
            } 
            
            return 0;
        }
    }
}

int numberOfNeighbors(int row, int col, char matrix[26][82]){ 
    int sum = 0;

    for(int i = row-1; i<= row+1; i++){
        for(int j = col-1; j <= col+1; j++){
            if(i==row && j==col){
            }else{
                if(matrix[i][j] == 'X'){
                    sum++;
                }
            }
        }
    }

    return sum;
}

bool isAliveNextGen(int row, int col, char matrix[26][82]){//param
    bool output = false;
    int neighbors = numberOfNeighbors(row, col, matrix);
    char currCell = matrix[row][col];
    
    if(currCell == ' ' && neighbors == 3){
        output = true;
    }else if(currCell == 'X' && (neighbors == 2 || neighbors == 3) ){
        output = true;
    }else if(currCell == 'X' && neighbors > 3){
        output = false;
    }
    else if(currCell == 'X' && neighbors < 2){
        output = false;
    }
     
    return output;
}


//make method to check if is alive or dead and add to other matrix respectively (must have param for either grid[0] or grid[1], row, col, and the matrix)
void moveCellToNextGenMatrix(int matrixNum, int row, int col, char matrix[26][82]){    //matrixNum is the matrix the cell will be moving to, matrix is the current matrix the cell is in at row col

    if(isAliveNextGen(row, col, matrix)){
        grids[matrixNum][row][col] = 'X';
    } else{
        grids[matrixNum][row][col] = ' ';
    }
      
}

void printMatrixNoBorder(char matrixWithX[26][82]){

    for(int i = 1; i <= 24; i++){
        for(int j = 1; j <= 80; j++){
            printf("%c",matrixWithX[i][j]);
        }
        printf("\n");
    }

    return;
}



