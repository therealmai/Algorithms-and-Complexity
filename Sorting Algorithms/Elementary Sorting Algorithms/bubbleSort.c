#include<stdio.h>


void bubbleSort(int arr[],int size);

int main(){

    int arr[] = {13,9,1,3,2,13}, x;

    bubbleSort(arr,6);

    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }

    return 0;
}

void bubbleSort(int arr[], int size){
    int x,y,temp;

    for(x=0; x<size-1; x++){
        for(y=0 ; y<size-1; y++){
            if(arr[y] > arr[y+1]){
                temp = arr[y];
                arr[y] = arr[y+1];
                arr[y+1] = temp;
            }
        }
    }
}
