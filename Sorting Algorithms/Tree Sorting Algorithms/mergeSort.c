/*
	Stable algorithm
	Out-of-place sorting
	Divide and conquer algorithm
	Comparison approach
	recursive
John von Neumann
1945
Time Complexity: O(n log n) in all cases
Space Complexity : O(n)
POSTORDER
*/

#include<stdio.h>
#include<stdlib.h>

int recursion = 0;
int mergeSort(int arr[], int size);
void merge(int A[], int L[], int R[], int Lsize, int Rsize);

void printArray(int arr[], int size){
    int x;
    for(x=0; x<size; x++){
        printf("%d ", arr[x]);
    }
    printf("Recursion %d", recursion);
}

int main(){

    int arr[] = {12,0,98,5,46,10,21};
    int size = sizeof(arr)/sizeof(arr[0]);

    mergeSort(arr, size);
    printArray(arr, size);

    return 0;
}



int mergeSort(int arr[], int size){
    recursion++;
  if(size < 2)
    return 0;
    
  int mid = size / 2;
  int ndx = 0, Lndx = 0, Rndx = 0;
  
  //MergeSort Left
  int *L = (int*)calloc(mid, sizeof(int));
  while(ndx < mid){
    L[Lndx++] = arr[ndx++];
  }
  mergeSort(L, mid);
  //MergeSort Right
  int *R = (int*)calloc(size - mid, sizeof(int));
  while(ndx < size){
    R[Rndx++] = arr[ndx++];
  }
  mergeSort(R, size - mid);

  //Merge
  merge(arr, L, R, mid, size - mid);
}

void merge(int A[], int L[], int R[], int Lsize, int Rsize){

    int Andx = 0, Lndx, Rndx;

    for(Lndx = 0, Rndx = 0; Lndx < Lsize && Rndx < Rsize;){
        if(L[Lndx] < R[Rndx]){
            A[Andx++] = L[Lndx++];
        } else {
            A[Andx++] = R[Rndx++];
        }
    }

    //if right array finishes first
    while(Lndx < Lsize){
        A[Andx++] = L[Lndx++];
    }
  //if left array finishes first
    while(Rndx < Rsize){
        A[Andx++] = R[Rndx++];
    }

}
