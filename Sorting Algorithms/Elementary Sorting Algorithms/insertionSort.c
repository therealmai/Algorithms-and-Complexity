#include<stdio.h>

void insertionSort(int arr[], int size);

int main(){

    int arr[] = {13,9,1,3,2,13}, x;
    insertionSort(arr, 6);

    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }

    return 0;
}

void insertionSort(int arr[], int size){
   int step;
   for(step = 1; step < size; step++){
        int key = arr[step];
        int j = step - 1;

        while( j >= 0 && key < arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
   }
}

/*
insertionSort(array)
  mark first element as sorted
  for each unsorted element X
    'extract' the element X
    for j <- lastSortedIndex down to 0
      if current element j > X
        move sorted element to the right by 1
    break loop and insert X here
end insertionSort
*/