/*
William Worthingon Pugh Jr.
“Bill” Pugh
1989
-	Randomized Balancing
-	Sorted Keys
-	O (log n) levels
Time complexity
- O (log n) Average in all cases;
- O (n) Worst in all cases;
Space Complexity
- O(n log n) Worst Case;
*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10
#define MAXLEVEL 2

typedef struct node{
    struct node **link;
    int data;
}*Node;

typedef struct {
    Node head;
    int level;
}SkipList;

void initList(SkipList *list);
void insertData(SkipList *list, int data);
Node updateInsert(Node head, int data, Node update[], int level);
int coinFlipLevel();
void populateList(SkipList *list, int arr[]);
Node searchData(Node head, int level, int data);
void deleteData(SkipList *list, int data);
Node updateDelete(Node head, int data, Node *update, int level);
void displayList(SkipList list);

void main()
{
    //srand(time(NULL));
    int arr[] = {21,2,35,9,13,5,7,14,99,0};

    SkipList list;
    initList(&list);
    
    printf("\nPopulate:");
    populateList(&list, arr);
    displayList(list);

    int key = 5;
    printf("\n\nSearch: %d", key);
    Node get = searchData(list.head, list.level, key);
    printf("\nFound key: %d", get != NULL && get->data == key ? get->data: -2147483647);

    key = 3;
    printf("\n\nDelete: %d", key);
    deleteData(&list, key);
    displayList(list);

    key = 3;
    printf("\n\nInsert: %d", key);    
    insertData(&list, key);
    displayList(list);
}

/********** INITIALIZE **********/

void initList(SkipList *list)
{
    list->level = 0;
    list->head = (struct node*)calloc(sizeof(struct node),1);

    // initialize data to INT_MIN
    list->head->data = -2147483647;
    // initalize pointer of arrays
    list->head->link = (struct node**)calloc(sizeof(struct node*),MAXLEVEL+1); 
}

/********** INSERTION **********/

void insertData(SkipList *list, int data)
{
    // initialize update array
    Node *update = (struct node**)calloc(sizeof(struct node*),MAXLEVEL+1);
    Node node = updateInsert(list->head, data, update, list->level);

    if(node == NULL || node->data != data) {
        // Generate random level
        int nlevel = coinFlipLevel();
        // Create new node
        Node newNode = (struct node*)calloc(sizeof(struct node),1);
        newNode->data = data;
        newNode->link = (struct node**)calloc(sizeof(struct node*),nlevel+1);
        int i;
        for(i = list->level+1; i <= nlevel; i++) {
            update[i] = list->head;
            list->level = i;
        }
        // insert node by rearranging pointers
        for(i = 0; i <= nlevel; i++) {
            newNode->link[i] = update[i]->link[i];
            update[i]->link[i] = newNode;
        }
    }

    free(update);
}

Node updateInsert(Node head, int data, Node *update, int level) // recursive
{
    if(head == NULL || head->data >= data ) {
        return head;
    }

    update[level] = head;

    if (head->link[level] != NULL && data >= head->link[level]->data || level == 0) {
        updateInsert(head->link[level], data, update, level);
    } else {
        updateInsert(head, data, update, level-1);
    }
}

int coinFlipLevel()
{
    int newLevel, coin;
    for(newLevel = 0, coin = rand() % 2; coin && newLevel < MAXLEVEL; newLevel++, coin = rand() % 2) {}
    return newLevel;
}

/*********** SEARCH ***********/

Node searchData(Node head, int level, int data) // recursive
{
    if(head == NULL || head->data >= data ){
        return head;
    }
    
    if (head->link[level] != NULL && data >= head->link[level]->data || level == 0) {
        searchData(head->link[level], level, data);
    } else {
        searchData(head, level-1, data);
    }
}

/********** DELETION ***********/

void deleteData(SkipList *list, int data)
{
    Node *update = (struct node**)calloc(sizeof(struct node*),MAXLEVEL+1);

    Node node = updateDelete(list->head, data, update, list->level);

    if(node != NULL && node->data == data) {
        int i;
        for(i = 0; i <= list->level && update[i]->link[i] == node; i++) {
            update[i]->link[i] = node->link[i];
        }
        for(; list->level > 0 && list->head->link[list->level] == NULL; list->level--) {}
        free(node);
    }

    free(update);
}

Node updateDelete(Node head, int data, Node *update, int level) // recursive
{ 
    if(head == NULL || head->data >= data){
        return head;
    }

    update[level] = head;

    if (head->link[level] != NULL && data > head->link[level]->data || level == 0) {
        updateDelete(head->link[level], data, update, level);
    } else {
        updateDelete(head, data, update, level-1);
    }
}

/************ MISC *************/

void populateList(SkipList *list, int arr[])
{
    int i;
    for(i = 0; i < SIZE; i++) {
        insertData(list, arr[i]);
    }
}

void displayList(SkipList list)
{
    int i;
    Node trav;
    for(i = list.level; i >= 0; i--) {
        printf("\nlevel %d: ", i);
        for(trav = list.head->link[i]; trav != NULL; trav = trav->link[i]) {
            printf("%d ", trav->data);
        }
    }
}