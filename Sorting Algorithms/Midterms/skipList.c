#include<stdio.h>
#include<stdlib.h>

#define LOW -9999
#define MAX 9999

#define SIZE 5
#define MAXLEVEL 7

typedef struct node{
    int data;
    struct node* next;
    struct node* below;
}*Node;

typedef struct skip{
    struct node root[MAXLEVEL];
    int level;
}SkipList;

void initSkipList(SkipList *s);
void displayList(SkipList s);

int main(){
    int arr[] = {3,2,1,4,5};
    SkipList s;
    initSkipList(&s);
    displayList(s);
    return 0;
}

void initSkipList(SkipList *s)
{
    s->level++;
    s->root[s->level-1] = (struct node*)malloc(sizeof(struct node));
    s->root[s->level-1]->data = LOW;
    s->root[s->level-1]->below = NULL;
    s->root[s->level-1]->next = (struct node*)malloc(sizeof(struct node));
    s->root[s->level-1]->next->data = MAX;
     
}

void insertNode(SkipList s, int elem)
{

}

int coinFlip()
{
    //srand(time(NULL));
    return rand() % 1;
}

void displayList(SkipList s)
{
    int i;
    for(i = s.level - 1; i >= 0; i--) {
        while(s.root[i] != NULL) {
            printf("%d ", s.root[i]->data);
            s.root[i] = s.root[i]->next;
        }
    }
}