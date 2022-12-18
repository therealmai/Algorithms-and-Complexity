/*

*/

#include<stdio.h>
#include<stdlib.h>
#define MAX 5
#define EMPTY -3
#define INF 999999

typedef int Graph[MAX][MAX];
typedef int SET[MAX];

typedef struct{
  int elem[MAX];
  int front;
  int rear;
}Queue;


void BFS(Graph G, int vertex);

int main(){

     Graph G = {
        {INF, 10, INF, 30, 100},
        {INF, INF, 50, INF, INF},
        {20, INF, INF, INF, 10},
        {INF, INF, 20, INF, 60},
        {INF, INF, INF, INF, INF}
    };

    BFS(G, 0);

    return 0;
}

void initQueue(Queue* q){
    q->front = 1;
    q->rear = 0;
}

void initSet(SET set){
    int x;
    for(x=0; x<MAX; x++){
        set[x] = EMPTY;
    }
}

int isFull(Queue Q){
   return (Q.front == (Q.rear+2) % MAX) ? 1 : 0;  
}

int isEmpty(Queue q) {
  return q.front == q.rear;
}

void insertElemSet(SET visited, int vertex){
    visited[vertex] = 1; 
}

void enqueue(Queue *Q, int elem){
  if(isFull(*Q) == 0){
  Q->rear = (Q->rear+1) % MAX;
  Q->elem[Q->rear] = elem;
  }
}


int front(Queue q){
    return q.elem[q.front];
}

void deQueue(Queue *Q){
  Q->front++;
}



void BFS(Graph G, int vertex){
    int u,x;
    Queue q;
    SET visited;

    initQueue(&q);
    initSet(visited);
    insertElemSet(visited, vertex);
    enqueue(&q, vertex);

    while(!isEmpty(q)){
        u = front(q);
        printf("%d ", u);
        deQueue(&q);

         for(x = 0; x < MAX; x++) {
            if(!visited[x] && G[u][x] != INF) {
                insertElemSet(visited, x);
                enqueue(&q, x);
            }
        }
    }
}