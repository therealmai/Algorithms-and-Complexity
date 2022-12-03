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

int deleteMin(BinaryTree *Tree){
  BinaryTree *trav,temp;
  int ret;
  for(trav = Tree;(*trav)->left != NULL && *trav != NULL; trav = &(*trav)->left ){}
  if(*trav != NULL){
    temp = *trav;
    ret = temp->data;
    *trav = temp->right;
    free(temp);
  }
  return ret;
}

void deleteElem(BinaryTree *Tree, int data){
    BinaryTree *trav, temp;
    for (trav=Tree; *trav!=NULL && (*trav)->data != data;){
        trav = (data < (*trav)->data) ? &(*trav)->left : &(*trav)->right ;
    }
    if(*trav!=NULL){ //element found
        temp = *trav;
        if((*trav)->left != NULL || (*trav)->right != NULL){ // node has 2 children -> replace with predecessor (choose ONLY 1 between deleteMin or deleteMax)
             temp->data = deleteMin(&temp->right);
        } else if((*trav)->left == NULL || (*trav)->right != NULL) {  //node has at most 1 child
            *trav = (temp->left!=NULL) ? temp->left : temp->right;
            free(temp);
        }else{
        	*trav = NULL;
        	free(temp);
		}
    }else{
      printf("Element not found");  
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
    deleteElem(&BST, 5);
    printf("\n");
    preOrder(BST);
    return 0;
}
