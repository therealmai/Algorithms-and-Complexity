/*
*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 6
#define EMPTY -3
#define UNVISITED -2
#define VISITED -1
#define SEN 999

typedef int Graph[SIZE][SIZE];
typedef unsigned int SET[SIZE];

typedef struct {
    int u, v;
    int weight;
}edge;

typedef struct {
    edge edges[SIZE];
    int edgeCtr;
}edgeList;

edgeList* Prim(Graph G, int vertex);

int main(){
    Graph G = {
        {SEN, 1, 5, 4, 6, 5},
        {1, SEN, 5, SEN, SEN, 6},
        {5, 5, SEN, 2, SEN, SEN},
        {4, SEN, 2, SEN, 1, SEN},
        {6, SEN, SEN, 1, SEN, 3},
        {5, 6, SEN, SEN, 3, SEN}
    };

    edgeList* list = Prim(G, 0);
    
    return 0;
}

void initSet(SET set){
    int x;
    for(x=0; x<SIZE; x++){
        set[x] = EMPTY;
    }
}

edgeList* Prim(Graph G, int vertex){
    int u, v, x, y, z;

    edgeList *list = (edgeList)calloc(sizeof(edgeList),1);
    SET set, visited, diff;
    
    initSet(set);
    
}