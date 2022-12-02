/*
P.F. Windly, A.D. Booth, A.J.T Colin, T.N. Hibbard
1960
-    Non-balancing
-    Sorted Keys
-    Right > Root > Left

Time Complexity
Best = O(1) For Accessing, Searching, Inserting; O(log n) for deleting
Average = O(log n) in all cases
Worst = O(n) in all cases; skewed

Space Complexity
O(n) = Worst
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}*BinaryTree;

void initBST(BinaryTree* BST){
    *BST = NULL;
}

void insertRecur(BinaryTree* BST, int num){
    if(*BST == NULL){
        (*BST) = (BinaryTree)malloc(sizeof(struct node));
        (*BST)->data = num;
        (*BST)->left = NULL;
        (*BST)->right = NULL;
    }else if (num < (*BST)->data){
        insertRecur(&(*BST)->left, num);
    }else if (num > (*BST)->data){
        insertRecur(&(*BST)->right, num);
    }else{
        printf("Failed to insert data");
    }
}

void insert(BinaryTree* BST, int num){
    
    while(*BST != NULL){
        if((*BST)->data < num){
            BST = &(*BST)->right;
        }else if((*BST)->data > num){
            BST = &(*BST)->left;
        }else{
            printf("Error");
        }
    }
     (*BST) = (BinaryTree)malloc(sizeof(struct node));
    (*BST)->data = num;
    (*BST)->left = NULL;
    (*BST)->right = NULL;
}

void populateTree(BinaryTree* BST){
    insert(BST, 5);
    insertRecur(BST, 3);
    insert(BST, 9);
    insertRecur(BST, 1);
    insert(BST, 7);
    insert(BST, 8);
    insertRecur(BST, 2);
    insert(BST, 4);
}

void preOrder(BinaryTree BST){
    if(BST != NULL){
        printf("%d", BST->data);
        preOrder(BST->left);
        preOrder(BST->right);
    }
}

void postOrder(BinaryTree BST){
    if(BST != NULL){
        postOrder(BST->left);
        postOrder(BST->right);
        printf("%d", BST->data);
    }
}

void inOrder(BinaryTree BST){
    if(BST != NULL){
        inOrder(BST->left);
        printf("%d", BST->data);
        inOrder(BST->right);
    }
}

int isMember(BinaryTree BST, int data){
    while(BST != NULL && BST->data != data){
        if(data < BST->data){
            BST = BST->left;
        }else if(data > BST->data){
            BST = BST->right;
        }else{
            printf("Error");
        }
    }
    return (BST != NULL) ? 1 : 0;
}

int deleteMin(BinaryTree* BST){
    while((*BST) != NULL){
        BST = &(*BST)->left;
    }
    int ret = (*BST)->data;
    *BST = ((*BST)->right != NULL) ? (*BST)->right : NULL;
    return ret;
}

void deleteElem(BinaryTree *BST, int num){
    BinaryTree *temp;
     while( (*BST) != NULL && (*BST)->data != num ){
        if(num < (*BST)->data){
            BST = &(*BST)->left;
        }else{
            BST = &(*BST)->right;
        }
    }

    if((*BST)->left != NULL && (*BST)->right != NULL){
        (*BST)->data = deleteMin(&(*BST)->right);
    }else if((*BST)->left != NULL){
        *temp = *BST;
        (*BST) = (*BST)->left;
        free(temp);
    }else if( (*BST)->right != NULL){
        *temp = *BST;
        (*BST) = (*BST)->right;
        free(temp);
    }else{
        free(*BST);
        *BST = NULL;
    } 
}

int main(){
    BinaryTree BST;
    int result;
    initBST(&BST);
    populateTree(&BST);
    preOrder(BST);
    printf("\n");
    result = isMember(BST, 4);
    printf("%d", result);
    deleteElem(&BST, 7);
    printf("\n");
    preOrder(BST);
    return 0;
}