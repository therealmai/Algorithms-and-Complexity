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

int main(){

    int data[SIZE] = {21,2,35,9,13,5,7,14};
    AVLTree T;

    initTree(&T);
    populateTree(&T, data);

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
    return 0;
}