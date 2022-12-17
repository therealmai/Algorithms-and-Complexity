/*

*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
#define UNVISITED -2
#define VISITED -1

typedef struct node{
    int data;
    struct node* adjacent;
}*node;

typedef node Graph[SIZE];
typedef int vertex;

struct list{
  vertex vertices[SIZE];
  int count;
}mark, diffnum;


void initList(Graph L){
    int x;
    for(x=0; x<SIZE; x++){
        L[x] = NULL;
    }
}

void initDiffnum(){
  int x;
  diffnum.count = 1;
  for(x=0; x<SIZE; x++){
    diffnum.vertices[x] = UNVISITED;
  }
}

void initMark(){
    int x;
    mark.count = -1;
    for(x=0; x<SIZE; x++){
        mark.vertices[x] = UNVISITED;
    }
}

void insertVertex(vertex tail, vertex head, Graph L){
    int x;
    node *trav;
    for(trav = &(L[tail]); *trav != NULL && (*trav)->data != head; trav = &(*trav)->adjacent){}
    if(*trav == NULL){
        *trav = (node)calloc(sizeof(struct node), 1);
        (*trav)->data  = head;
    }
}

void populateList(Graph L){
    insertVertex(0, 1, L);
    insertVertex(0, 2, L);
    insertVertex(1, 2, L);
    insertVertex(1, 3, L);
    insertVertex(2, 0, L);
    insertVertex(3, 0, L);
    insertVertex(3, 2, L);
    insertVertex(4, 5, L);
    insertVertex(4, 6, L);
    insertVertex(5, 1, L);
    insertVertex(6, 3, L);
    insertVertex(6, 5, L);
}

void DFS(vertex start, Graph L){
    int x;
    vertex w;
    node trav;

    mark.vertices[start] = VISITED;

    for(trav=L[start]; trav != NULL ; trav = trav->adjacent){
        w = trav->data;
        if(mark.vertices[w] == UNVISITED){
            DFS(w, L);
        }
    }
}

void DFN(vertex start, Graph L){
    int x;
    vertex w;
    node trav;

    diffnum.vertices[start] = diffnum.count++;

    for(trav=L[start]; trav != NULL ; trav = trav->adjacent){
        w = trav->data;
        if(mark.vertices[w] == UNVISITED){
            DFN(w, L);
        }
    }
}

void display(struct list mark){
    int x;
    for(x=0; x<SIZE; x++){
        printf("%d ", mark.vertices[x]);
    }
}

int main(){
    int x;
    Graph L;
    initList(L);
    initMark();
    initDiffnum();
    populateList(L);
    DFS(0,L);
    DFN(4,L);

    display(mark);
    printf("\n");
    display(diffnum);
    for(x=0; x<SIZE; x++){
        if(mark.vertices[x] == UNVISITED){
            DFS(x, L);
        }
    }
    printf("\n");
    display(mark);

    return 0;
}