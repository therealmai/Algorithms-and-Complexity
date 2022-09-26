#include <stdio.h>
#include <stdlib.h>

int removeElement(int A[], int *size, int ndx){
    int element = A[ndx];
    int x;
    for(x = ndx + 1; x < *size; x++){
        A[x - 1] = A[x];
    }
    (*size)--;

    return element;
}

int *mergeADT(int A[], int B[], int *A_size, int *B_size){
    int *merged = (int*)calloc(*A_size + *B_size, sizeof(int));
    int A_trav, B_trav, M_trav;

    /* merge two array */
    for(A_trav = B_trav = M_trav = 0; A_trav < *A_size && B_trav < *B_size; M_trav++){
        merged[M_trav] = (A[A_trav] < B[B_trav]) ? A[A_trav++] : B[B_trav++];
    }

    // while there are elements in array A
    while(A_trav < *A_size){
        merged[M_trav++] = A[A_trav++];
    }

    // while there are elements in array B
    while(B_trav < *B_size){
        merged[M_trav++] = B[B_trav++];
    }
    
    (*B_size) = *A_size + *B_size;
    (*A_size) = 0;

    return merged;
}

int *strandSort(int A[], int size){
    int *sublist = (int*)calloc(size, sizeof(int));
    int *output = (int*)calloc(size, sizeof(int));
    int size_S = 0, size_O = 0, x;

    while(size > 0){
        /* insert the first element of the input array to the sublist */
        sublist[size_S++] = removeElement(A, &size, 0);

        /* insert element of the input array that are greater than the last inserted element in the sublist */
        for(x = 0; x < size; x++){
            if(sublist[size_S - 1] <= A[x]){
                sublist[size_S++] = removeElement(A, &size, x);
            }
        }

        output = mergeADT(sublist, output, &size_S, &size_O);
    }

    return output;
}

int main() {
  int arr[] = {10, 8, 2, 9, 1, 4, 9, 12, 1, -1};
  int size = sizeof(arr)/sizeof(arr[0]);

  int *A = strandSort(arr, size);

  //display sorted array
  int x;
  for(x = 0; x < size; x++){
    printf("%d ", A[x]);
  }
  return 0;
}
