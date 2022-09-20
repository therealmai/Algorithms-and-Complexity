#include<stdio.h>
#include<stdlib.h>

void radixSort(int arr[], int size);
int getMax(int arr[], int size);
void countingSort(int arr[], int size, int digit);

int main(){
    int arr[] = {131,99,100,3508,21,138}, x;

    radixSort(arr,6);

    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }

}

int getMax(int arr[],int size){
    int x, max=0;
    for(x=0; x<size; x++){
        if(max < arr[x])
            max = arr[x];
    }
    return max;
}

void radixSort(int arr[], int size){
    int max, digit;

    max = getMax(arr, size);


    for(digit = 1; max/digit > 0; digit *=10 ){
        countingSort(arr, size, digit);
    }
}

void countingSort(int arr[], int size, int digit){
    int x,*count, *output;

    output = (int*)malloc(size* sizeof(int));
    int max = (arr[0] / digit) % 10;

    for(x=0; x<size; x++){
        if(max < ((arr[x]/ digit)%10)){
            max = (arr[x]/digit)%10;
        }
    }
    count = (int*)calloc(sizeof(int), max+1);

    for(x=0; x<size; x++){
        count[(arr[x]/digit)%10]++;
    }

    for(x=1; x<=max; x++){
        count[x] += count[x-1];
    }

    for(x = size - 1; x >= 0 ; x--){
        output[ count[(arr[x]/digit)%10] - 1 ] = arr[x];
        count[(arr[x]/digit)%10]--;
    }

    for(x = 0; x<size; x++){
        arr[x] = output[x];
    }


}

/*
radixSort(array)
  d <- maximum number of digits in the largest element
  create d buckets of size 0-9
  for i <- 0 to d
    sort the elements according to ith place digits using countingSort

countingSort(array, d)
  max <- find largest element among dth place elements
  initialize count array with all zeros
  for j <- 0 to size
    find the total count of each unique digit in dth place of elements and
    store the count at jth index in count array
  for i <- 1 to max
    find the cumulative sum and store it in count array itself
  for j <- size down to 1
    restore the elements to array
    decrease count of each element restored by 1
*/