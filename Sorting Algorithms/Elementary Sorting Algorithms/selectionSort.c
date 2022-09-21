/*
 * Notes:
 * Taking the smallest element to the front
 * When to use - when the size of the list small
 * Time Complexity - Best: O(n^2) Worst: O(n^2) Average: O(n^2)
 * Space Complexity - O(1)
 * In-place sort
 * Unstable sort??? mixed feelings sa internet
 */
#include<stdio.h>

void selectionSort(int arr[], int size);

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

    selectionSort(arr, size);
    printArray(arr,size);
    return 0;
}

void selectionSort(int arr[], int size){
    int x, temp, min,step;
    for(step = 0; step<size; step++){
        min = step;
        for(x= step+1; x<size; x++){
            if(arr[min] > arr[x]){
                min  = x;
            }
        }
        temp = arr[step];
        arr[step] = arr[min];
        arr[min] = temp;
    }
}