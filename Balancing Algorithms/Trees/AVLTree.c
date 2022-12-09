/*
Georgy Adelson-Velsky, Evgenii Landis
1962
-	Self-balancing
-	Sorted Keys
-	Right > Root > Left
- BEST CASE: O(log n) for Searching, Inserting, Deleting ; O(1) searching
- Average Case: O(log n) in all cases
- Worst Case: O(log n) in all cases
- Space Complexity: O(n) in all cases
*/

#include<stdio.h>
#include<stdlib.h>

#define SIZE 8

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}*AVLTree;


void initTree(AVLTree *T);
void populateTree(AVLTree *T, int data[]);
void insertNodeAVL(AVLTree node, AVLTree *T);
int getBalance(AVLTree T);
int getHeight(AVLTree T);
void leftRotation(AVLTree *T);
void rightRotation(AVLTree *T);
void displayTree(AVLTree T);
int findElem(int data, AVLTree node);
void removeNode(AVLTree *T, int data);

int main(){

    int data[SIZE] = {21,2,35,9,13,5,7,14};
    AVLTree T;

    initTree(&T);
    populateTree(&T, data);
    displayTree(T);
    printf("\n%d", findElem(2, T));
    removeNode(&T, 21);
    printf("\n");
    displayTree(T);


    return 0;
}

void initTree(AVLTree *T){
    *T = NULL;
}

void leftRotation(AVLTree *T)
{
    AVLTree temp = (*T)->right;
    AVLTree child = temp->left;
    temp->left = *T;
    (*T)->right = child;
    (*T) = temp;
}

void rightRotation(AVLTree *T){
    AVLTree temp = (*T)->left;
    AVLTree child = temp->right;
    temp->right = *T;
    (*T)->left = child;
    (*T) = temp;
}

void populateTree(AVLTree* T, int data[]){
    int x;
    AVLTree trav;
    for(x=0; x<SIZE; x++){
        AVLTree newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = data[x];
        newNode->left = NULL;
        newNode->right = NULL;
        insertNodeAVL(newNode, T);
        trav = *T;
        displayTree(trav);
        printf("\n");
    }
}

void insertNodeAVL(AVLTree newNode, AVLTree *node)
{
    if(*node == NULL) {
        *node = newNode;
    } else {
        if((*node)->data > newNode->data) {
            insertNodeAVL(newNode, &(*node)->left);
        } else {
            insertNodeAVL(newNode, &(*node)->right);
        }
    }

    int balance = getBalance(*node);
    if(balance > 1 && newNode->data <= (*node)->left->data){
        rightRotation(node);
    } else if(balance > 1 && newNode->data > (*node)->left->data) {
        leftRotation(&(*node)->left);
        rightRotation(node);
    } else if(balance < -1 && newNode->data > (*node)->right->data) {
        leftRotation(node);
    } else if(balance < -1 && newNode->data <= (*node)->right->data) {
        rightRotation(&(*node)->right);
        leftRotation(node);
    }
}

int getBalance(AVLTree node) {
    if(node == NULL) {
        return -1;
    }

    return getHeight(node->left) - getHeight(node->right);
}

int getHeight(AVLTree node) {
    if(node == NULL) {
        return 0;
    }

    int left = getHeight(node->left);
    int right = getHeight(node->right);
    return (left>right)?left+1:right+1;
}

void displayTree(AVLTree T){
    //Inorder
    if(T == NULL){
        return;
    }
    printf("%d ", T->data);
    displayTree(T->left);

    displayTree(T->right);
}

int findElem(int data, AVLTree node)
{
    int ret = 1;
    AVLTree trav;
    for(trav = node; trav != NULL && trav->data != data;){
        if(trav->data < data){
            trav = trav->right;
        }else{
            trav = trav->left;
        }
    }
    return (trav != NULL) ? 1 : 0;
}

AVLTree findMin(AVLTree T){
    while(T->left != NULL){
        T = T->left;
    }
    return T;
}

void removeNode(AVLTree *T, int data){

    if(*T == NULL){
        return;
    }else if ((*T)->data < data){
        removeNode(&(*T)->right, data);
    }else if ((*T)->data > data){
        removeNode(&(*T)->left, data);
    }else{
        AVLTree temp = *T;
        if(temp->left == NULL){
            *T = temp->right;
            free(temp);
        }else if(temp->right == NULL){
            *T = temp->left;
            free(temp);
        }else{
           AVLTree min = findMin(temp->right);
           (*T)->data = min->data;
           removeNode(&(*T)->right, min->data);
        }
    }

    int balance = getBalance(*T);
     if(balance > 1 && getBalance((*T)->left) >= 0){
        rightRotation(T);
    } else if(balance > 1 && getBalance((*T)->left) < 0) {
        leftRotation(&(*T)->left);
        rightRotation(T);
    } else if(balance < -1 && getBalance((*T)->right) >= 0) {
        leftRotation(T);
    } else if(balance < -1 && getBalance((*T)->right) < 0) {
        rightRotation(&(*T)->right);
        leftRotation(T);
    }
}
