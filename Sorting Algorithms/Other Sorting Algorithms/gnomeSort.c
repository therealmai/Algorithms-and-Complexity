#include<stdio.h>

void gnomeSort(int arr[], int size);
int main(){

     int arr[] = {13,9,1,3,2,13}, x;

     gnomeSort(arr, 6);

    return 0;
}

void gnomeSort(int arr[], int size){
    int step=0,temp;

    while(step < size){
        if(step == 0){
            step++;
        }
        if(arr[step] >= arr[step-1]){
            step++;
        }else{
            temp = arr[step];
            arr[step] = arr[step-1];
            arr[step-1] = temp;
            step--;
        }
    }
}