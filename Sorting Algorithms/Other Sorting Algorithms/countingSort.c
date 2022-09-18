#include<stdio.h>
#include<stdlib.h>

void countingSort(int arr[], int size);
int main(){
    int arr[] = {13,9,1,3,2,13}, x;

    countingSort(arr, 6);

    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }
    return 0;
}

void countingSort(int arr[], int size){
    int x, max=0, *count, *output;
    for(x=0; x<size; x++){
        if(arr[x]> max){
            max = arr[x];
        }
    }
    count = (int*)calloc(sizeof(int), max+1);
    output = (int*)calloc(sizeof(int), size); 

    for(x=0; x<size; x++){
        count[arr[x]]++;
    }
    
    for(x=1; x<=max; x++){
        count[x] += count[x-1];
    }

    for(x = size - 1; x >= 0; x--){
        output[count[arr[x]] - 1] = arr[x];
        count[arr[x]]--;
    }

    for(x=0; x<size; x++){
        arr[x] = output[x];
    }
}


/*
countingSort(array, size)
  max <- find largest element in array
  initialize count array with all zeros
  for j <- 0 to size
    find the total count of each unique element and 
    store the count at jth index in count array
  for i <- 1 to max
    find the cumulative sum and store it in count array itself
  for j <- size down to 1
    restore the elements to array
    decrease count of each element restored by 1
*/