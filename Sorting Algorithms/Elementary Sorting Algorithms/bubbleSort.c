/*
 * Notes:
 * Largest element floats (hence why bubble)
 * When to use - when the size of the list small
 * Time Complexity - Best: O(n) Worst: O(n^2) Average: O(n^2)
 * Space Complexity - O(1)
 * In-place sort
 * Stable sort
*/
#include<stdio.h>

void bubbleSort(int arr[],int size);
void printArray(int arr[],int size);

int main(){
    int size;
    int arr[] = {5,6,8,9,1,2,5,0,6,8,6,4,3,0,5,4,7,6,9},x;
    size = sizeof(arr)/sizeof(arr[0]);

    bubbleSort(arr,size);
    printArray(arr,size);



    return 0;
}

void bubbleSort(int arr[], int size){
    int x, y, temp;

    for(x=0; x<size-1; x++){
        for(y=0; y<size-1; y++){
            if(arr[y] > arr[y+1]){
                temp = arr[y];
                arr[y] = arr[y+1];
                arr[y+1] = temp;
            }
        }
    }
}

void printArray(int arr[],int size){
    int x;

    for(x=0; x<size; x++){
        printf("%d ", arr[x]);
    }

}

