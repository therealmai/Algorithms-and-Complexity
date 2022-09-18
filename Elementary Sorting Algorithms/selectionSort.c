#include<stdio.h>

void selectionSort(int arr[], int size);
int main(){

    int arr[] = {13,9,1,3,2,13}, x;

    selectionSort(arr, 6);

    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }
    return 0;
}

void selectionSort(int arr[], int size){
    int min, step, x, temp;
    for(step = 0; step<size-1; step++){
        min = step;
        for(x= step+1 ; x<size; x++){
            if(arr[x] < arr[min]){
                min = x;
            }
        }
        temp = arr[step];
        arr[step] = arr[min];
        arr[min] = temp;
    }
}


/*
void selectionSort(int arr[], int size){
    int min, step, x, temp;

    for(step = 0; step<size - 1; step++){
        min = step;

        for(x=step+1; x<size; x++){
            if(arr[x] < arr[min] ){
              min = x;
            }
        }
          temp = arr[step];
          arr[step] = arr[min];
          arr[min] = temp;
    }
}

*/