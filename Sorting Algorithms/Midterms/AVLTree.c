#include<stdio.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
}AVLTree;


void initTree(AVLTree* Tree);
void populateTree(AVLTree *Tree);

int main(){

    AVLTree T;

    initTree(&T);
    populateTree(&T);

    return 0;
}

void initTree(AVLTree* Tree){
    Tree->height = -1;
    Tree->left = NULL;
    Tree->right = NULL;
    Tree->data = 0;
}