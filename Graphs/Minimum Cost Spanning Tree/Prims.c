/*
*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 6
#define EMPTY 0
#define SEN 999

typedef int Graph[SIZE][SIZE];
typedef int SET[SIZE];

typedef struct {
    int u, v;
    int weight;
} edge;

typedef struct {
    edge edges[SIZE];
    int edgeCtr;
    int cost;
} edgeList;

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

    int x;
    for(x=0; x < list->edgeCtr; x++){
        printf("(%d, %d, %d) ", list->edges[x].u, list->edges[x].v, list->edges[x].weight);
    }
    printf("\nCost: %d", list->cost);
    
    return 0;
}

void initSet(SET set){
    int x;
    for(x=0; x<SIZE; x++){
        set[x] = EMPTY;
    }
}

void insertElemSet(SET visited, int vertex){
    visited[vertex] = 1; 
}

void difference(SET set, SET visited, SET diff){
    int x;
    for(x=0; x<SIZE; x++){
        diff[x] = set[x] & ~(visited[x]);
    }
}

edgeList* Prim(Graph G, int vertex){
    int u, v, x, y, z;

    edgeList * list = (edgeList*)calloc(sizeof(edgeList), 1);
    SET set, visited, diff;
    // diff[vertex] = vertex;

    initSet(set);
    initSet(visited);
    insertElemSet(visited, vertex);

    for(x=0; x<SIZE; x++){
        insertElemSet(set, x);
    }

    for(z=0; z < SIZE-1; z++){
        difference(set, visited, diff);
        u = 0;
        v = 0;
        for(x=0; x < SIZE; x++){
            if(!visited[x]){
              continue;  
            }
            for(y=0; y < SIZE; y++){
                if(!diff[y]){
                    continue;
                }
                if(G[x][y] < G[u][v]){
                    u = x;
                    v = y;
                }
            }
        }
        list->edges[z].u = u;
        list->edges[z].v = v;
        list->edges[z].weight = G[u][v];
        list->cost += list->edges[z].weight;
        list->edgeCtr++;
        insertElemSet(visited, v);
    }
    return list;
}