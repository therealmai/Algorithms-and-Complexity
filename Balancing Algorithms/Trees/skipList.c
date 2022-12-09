#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
#define maxLevel 2

typedef struct node{
    struct node **link;
    int data;
}*Node;

typedef struct {
    Node head;
    int level;
}SkipList;

void initList(SkipList *list);
void populateArr(SkipList* list, int arr[]);
void insertSkip(SkipList* list, int data);
Node updateInsert(Node head, int data, Node *update, int level);

int main(){
    
    int arr[] = {21,2,35,9,13,5,7,14,99,0};

    SkipList list;
    initList(&list);
    populateArr(&list, arr);


    return 0;
}

void initList(SkipList *list){
    list->level = 0;
    list->head = (struct node*)calloc(sizeof(struct node),1);

    // initialize data to INT_MIN
    list->head->data = -2147483647;
    // initalize pointer of arrays
    list->head->link = (struct node**)calloc(sizeof(struct node*),maxLevel+1); 
}

void insertSkip(SkipList *list, int data){
    Node *update = (struct node**)calloc(sizeof(struct node*), maxLevel+1);
    Node node = updateInsert(list->head, data, update, list->level); //traversal

    if(node == NULL || node->data != data){
        int newLevel = coinFlip();
    }
}

int coinFlip(){

}

int coinFlip(){
    int newLevel, coin;
    for(newLevel = 0, coin = rand() % 2; coin && newLevel < maxLevel; newLevel++, coin = rand() % 2) {}
    return newLevel;
}

Node updateInsert(Node head, int data, Node *update, int level){

    if(head == NULL || head->data >= data){
        return head;
    }
    update[level] = head;

    if(head->link[level] != NULL && data >= head->link[level]->data || level == 0){
        updateInsert(head->link[level], data, update, level); //move to the next link
    }else{
        updateInsert(head, data, update, level-1); //decrement level
    }
}

void populateArr(SkipList* list, int arr[]){
    int x;
    for(x=0; x<10; x++){
        insertSkip(list, arr[x]);
    }
}