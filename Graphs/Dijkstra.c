/*
worst time complexity : O(n^2);
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

int minimum(Vertex *D, Vertex *A){
    int x,y, min=SENTINEL, ret;

    
    for(x=1; x<SIZE; x++){
        if( (*A)[x] == 1){
          if((*D)[x] < min){
            min = (*D)[x];
            ret = x;
            }
        }
    }  
  return ret;
}

Vertex* difference(Vertex V, Vertex S){
    int x;
    Vertex *ret = (Vertex*)calloc(sizeof(Vertex),1);
    for(x=0; x<SIZE; x++){
        (*ret)[x] = V[x] & ~(S[x]);
    }
    return ret;
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

Vertex* dijkstra(Graph C, Vertex V){
    int x, w, y;
    Vertex S = {1,0,0,0,0}; //Set of Visited Vertices
    Vertex *D = (Vertex*)calloc(sizeof(Vertex),1); //Contains the smallest paths for every vertices
    Vertex *A = NULL; //Difference for getting unvisited vertices

    memcpy((*D), C[0], sizeof(int)*SIZE);
    (D)[0][0] = 0;

    // for(x=1; x<SIZE; x++){  //Blue colored statement
    //     (*D)[x] = C[0][x];
    // }

    for(x=1; x<SIZE-1; x++){
        A = difference(V, S);
        w = minimum(D,A);
        S[w] = 1;
        (*A)[w] = 0;

        for(y=1; y<SIZE; y++){
            if((*A)[y] == 1){
                (*D)[y] = ( (*D)[y] < ( (*D)[w] + C[w][y]) ) ? (*D)[y] : ( (*D)[w] + C[w][y]);
            }
        }
    }
    return D;
}

int main(){

    Graph C;
    Vertex V = {1,1,1,1,1};
    Vertex *D;
    initGraph(C);
    populateGraph(C);
    D = dijkstra(C,V);

    return 0;
}