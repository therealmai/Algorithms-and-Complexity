#include<stdio.h>
#include<stdlib.h>
#define SIZE 20
#define MAX_INT 2147483647

void tournamentSort(int arr[]);
void findWinner(int arr[], int heap[], int n);
void printArray(int arr[]);

void main()
{
    int arr[] = {5,6,8,9,1,2,5,0,6,8,6,4,3,0,5,4,7,6,9,2};
    tournamentSort(arr);
    printArray(arr);
}

void tournamentSort(int arr[])
{
    int i, j, left, right, heap[SIZE*2] = {0}, output[SIZE];
    for(i = 0; i < SIZE; i++) { // initialize heap
        heap[i] = MAX_INT;
    }
    for(i = SIZE; i < SIZE*2; i++) { // initialize index of the element to the heap
        heap[i] = i-SIZE;
    }
    for(i = 0; i < SIZE; i++) {
        findWinner(arr, heap, 0);
        output[i] = arr[heap[0]];
        arr[heap[0]] = MAX_INT;
    }
    for(i = 0; i < SIZE; i++) {
        arr[i] = output[i];
    }
}

void findWinner(int arr[], int heap[], int n) // similar to heapify
{
    if(heap[n] == MAX_INT || arr[heap[n]] == MAX_INT) {
        int left = 2 * n + 1;
        int right = 2 * n + 2;
        int largest = n;
        if(left < SIZE*2) {
            findWinner(arr, heap, left);
            largest = left;
        }
        if(right < SIZE*2) {
            findWinner(arr, heap, right);
            if(arr[heap[right]] < arr[heap[largest]]) {
                largest = right;
            }
        }
        
        if(largest != n) {
            heap[n] = heap[largest];
        }
        
    }
}

void printArray(int arr[])
{
    int i;
    for(i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
