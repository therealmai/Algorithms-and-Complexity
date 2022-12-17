/*
time complexity = O(n^3)
*/
#include<stdio.h>
#include<stdlib.h>
#define SIZE 5
#define SENTINEL 999

typedef int Graph[SIZE][SIZE];
typedef int Vertex[SIZE]; //Bit vector implementation, can be computer word


void initGraph(Graph C){
    int x,y;
    for(x=0; x<SIZE; x++){
        for(y=0; y<SIZE; y++){
            C[x][y] = SENTINEL;
        }
    }
}

void populateGraph(Graph C){
    //Row 0
    C[0][1] = 10;
    C[0][3] = 30;
    C[0][4] = 100;

    //Row 1
    C[1][2] = 50;

    //Row 2
    C[2][0] = 20;
    C[2][4] = 10;

    //Row 3
    C[3][2] = 20;
    C[3][4] = 60;    
}

void Floyd(Graph A, Graph C){
    int x,y,z;

    //Copying the contents of Graph A to C
    for(x=0; x<SIZE;x++){
        for(y=0; y<SIZE; y++){
            A[x][y] = C[x][y];
        }
    }

    for(x=0; x<SIZE; x++){
        A[x][x] = 0;
    }

    for(z=0; z<SIZE; z++){
        for(x=0; x<SIZE; x++){
            for(y=0; y<SIZE; y++){
                if(A[x][z] + A[z][y] < A[x][y]){
                    A[x][y] = A[x][z] + A[z][y];
                }
            }
        }
    }
}

void display(Graph A){
    int x, y;

    for(x=0; x<SIZE; x++){
        for(y=0; y<SIZE; y++){
            printf("%d ", A[x][y]);
        }
        printf("\n");
    }
}

int main(){

    Graph C;
    Graph A;
    initGraph(C);
    populateGraph(C);
    Floyd(A, C);
    display(A);
    return 0;
}