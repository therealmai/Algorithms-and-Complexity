/*
 * Notes:
 * Shifting sort (like how you sort your cards)
 * When to use - when the size of the list small
 * Time Complexity - Best: O(n) Worst: O(n^2) Average: O(n^2)
 * Space Complexity - O(1)
 * In-place sort
 * Stable sort
 */

#include<stdio.h>

void insertionSort(int arr[], int size);

void printArray(int arr[],int size){
    int x;

    for(x=0; x<size; x++){
        printf("%d ", arr[x]);
    }
}

int main(){
    int size;

    int arr[] = {5,6,8,9,1,2,5,0,6,8,6,4,3,0,5,4,7,6,9,2};
    size = sizeof(arr)/sizeof(arr[0]);

    insertionSort(arr, size);
    printArray(arr, size);

    return 0;
}

void insertionSort(int arr[], int size){
  int step,x,key,temp;
  for(step = 1; step<size; step++){
    key = arr[step];
    x = step - 1;

    while(key< arr[x] && x >= 0){
      arr[x+1] = arr[x];
      x--;
    }
    arr[x+1] = key;
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