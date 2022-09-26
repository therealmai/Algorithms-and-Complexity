/*
 * Notes:
 * heapsort is sometimes called tournament sort
 * When to use - similar to heapsort
 * Time Complexity - Best: O(n log n) Worst: O(n log n) Average: O(n log n)
 * Space Complexity - O(n)
 * Out-of-place sort
 * Unstable sort
 * Comparison sort
 * Alexander Stepanov
 * 2002
 */

#include<stdio.h>
#include<stdlib.h>

#define SIZE 20
#define MAX_INT 2147483647

void tournamentSort(int arr[]);
void findWinner(int arr[], int heap[], int n);

void tournamentSort_v2(int arr[]);
int winner_v2(int heap[], int left, int right);
void findWinner_v2(int heap[]);

void printArray(int arr[]);

void main()
{
    int arr[] = {5,6,8,9,1,2,5,0,6,8,6,4,3,0,5,4,7,6,9,2};
    //tournamentSort(arr);
    tournamentSort_v2(arr);
    printArray(arr);
}

void tournamentSort(int arr[])
{
    int i, j, left, right, heap[SIZE*2], output[SIZE];
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

void tournamentSort_v2(int arr[]) // using actual values in the heap; closer to the internet code
{
    int i, j = 0, k, left, right, heap[SIZE<<1];
    for(i = 0; i < SIZE; i++) { // initialize heap
        heap[i] = MAX_INT;
    }
    for(i = SIZE; i < SIZE*2; i++) { // initialize the element to the heap
        heap[i] = arr[i-SIZE];
    }
    for( i = SIZE*2-1; i > 1; i -=2) { // create the tournament heap
        left = i-1;
        right = i;
        k = i/2;
        heap[k] = winner_v2(heap, left, right);
    }
    arr[j++] = heap[heap[1]];
    heap[heap[1]] = MAX_INT;
    while(j < SIZE) {
        findWinner_v2(heap); // recreates tournament heap
        arr[j++] = heap[heap[1]];
        heap[heap[1]] = MAX_INT;
    }
}

int winner_v2(int heap[], int left, int right)
{
    int l = left >= SIZE ? left : heap[left];
    int r = right >= SIZE ? right : heap[right];
    return heap[l] <= heap[r] ? l : r;
}

void findWinner_v2(int heap[])
{
    int i, j;
    for(i = heap[1]; i > 0; i /= 2) {
        j = i%2==0?i+1:i-1;
        heap[i/2] = winner_v2(heap,i,j);
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
