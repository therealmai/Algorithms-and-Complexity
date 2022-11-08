//https://github.com/Frooge/3102N_Repo/blob/master/002midterm/001AVL.c
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
int balance(AVLTree T);
int getHeight(AVLTree T);
void leftRotation(AVLTree *T);
void rightRotation(AVLTree *T);
void displayTree(AVLTree T);
int findElem(AVLTree T, int elem);

int main(){

    int data[SIZE] = {21,2,35,9,13,5,7,14};
    AVLTree T;

    initTree(&T);
    populateTree(&T, data);
    findElem(T,6);
    displayTree(T);

    return 0;
}

void initTree(AVLTree *T){
    *T = NULL;
}

void populateTree(AVLTree* T, int data[]){
    int x;
    for(x=0; x<SIZE; x++){
        AVLTree newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = data[x];
        newNode->left = NULL;
        newNode->right = NULL;
        insertNodeAVL(newNode, T);
    }
}

void insertNodeAVL(AVLTree node, AVLTree *T){
    int balance;
    if(*T == NULL){
        *T = node;
    }else{
        if((*T)->data > node->data){
            insertNodeAVL(node, &(*T)->left);
        }else{
            insertNodeAVL(node, &(*T)->right);
        }
    }

    balance = getBalance(*T);

    if(balance > 1 && node->data <= (*T)->left->data){
        rightRotation(T);
    } else if(balance > 1 && node->data > (*T)->left->data) {
        leftRotation(&(*T)->left);
        rightRotation(T);
    } else if(balance < -1 && node->data > (*T)->right->data) {
        leftRotation(node);
    } else if(balance < -1 && node->data <= (*T)->right->data) {
        rightRotation(&(*T)->right);
        leftRotation(T);
    }
}

int balance(AVLTree T){
    if(T == NULL){
        return -1;
    }

    return getHeight(T->left) - getHeight(T->right);
}

int getHeight(AVLTree T){

    if(T == NULL){
        return 0;
    }

    int left = getHeight(T->left);
    int right = getHeight(T->right);
    return (left > right) ? left+1 : right+1;
}

void leftRotation(AVLTree *T)
{
    AVLTree temp = (*T)->right;
    AVLTree child = temp->left;
    (*T)->right->left = *T;
    (*T)->right = child;
    (*T) = temp;
}

void rightRotation(AVLTree *T){
    AVLTree temp = (*T)->left;
    AVLTree child = temp->right;
    (*T)->left->right = *T;
    (*T)->left = child;
    (*T) = temp;
}

void displayTree(AVLTree T){
    //PreOrder display
    printf("%d", T->data);
    displayTree(T->left);
    displayTree(T->right);
}

int findElem(AVLTree T, int elem){
    int dataExist = 0;
    if(T->data != elem){
        dataExist = 1;
    }
    else if (T->data < elem){
        findElem(T->right, elem);
    }else{
        findElem(T->left, elem);
    }
    return dataExist;
}

