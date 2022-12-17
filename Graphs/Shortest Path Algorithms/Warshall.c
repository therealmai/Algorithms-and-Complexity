/*

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
            C[x][y] = 1;
        }
    }
}

void populateGraph(Graph C){
    //Row 0
    C[1][0] = 0;
    C[2][0] = 0;
    C[3][0] = 0;
    C[4][0] = 0;
}

void Warshall(Graph A, Graph C){
    int x, y, z;
    for(x=0; x<SIZE; x++){
        for(y=0; y<SIZE; y++){
            A[x][y] = C[x][y];
        }
    }

    for(z=0; z<SIZE; z++){
        for(x=0; x<SIZE; x++){
            for(y=0; y<SIZE; y++){
                if(A[x][y] == 0){
                    A[x][y] = A[x][z] && A[z][y];
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
    Warshall(A, C);
    display(A);
    return 0;
}