#include<stdio.h>

void shellSort(int arr[], int size);
int main(){

    int arr[] = {13,9,1,3,2,13}, x;

    shellSort(arr, 6);
    for(x=0; x<6; x++){
      printf("%d ", arr[x]);
    }
    return 0;
}

void shellSort(int arr[], int size){
  int interval,x,y,temp;
  for(interval = size/2; interval > 0; interval /= 2){
    for(x=interval; x<size; x++){
      temp = arr[x];

      for(y=x; y>= interval && arr[y-interval] > temp; y-= interval){
        arr[y] = arr[y-interval];
      }
      arr[y] = temp;
    }
  }
}


/*
shellSort(array, size)
  for interval i <- size/2n down to 1
    for each interval "i" in array
        sort all the elements at interval "i"
end shellSort
*/