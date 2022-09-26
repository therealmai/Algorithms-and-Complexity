/*
if root = index 0
parent = child - 1 / 2
left = 2(parent) +1
right = 2(parent) + 2
___________

if root = index 1
parent = child  / 2
left = 2(parent)
right = 2(parent) + 1
*/

/*
 * Notes:
 * Slightly slower than merge sort and quick sort on largest lists; think of an improved selection sort; recursive
 * When to use - more efficient than elementary sorting algo; can be used to deal with priority trees
 * Time Complexity - Best: O(n log n) Worst: O(n log n) Average: O(n log n)
 * Space Complexity - O(1)
 * In-place sort
 * Unstable sort
 * Comparison sort
 * J. W. J. Williams (1964)
 */

#include<stdio.h>

#define SIZE 20

void heapSort(int arr[]);
void heapify(int arr[], int n, int node);
void printArray(int arr[]);

void main()
{
    int arr[] = {5,6,8,9,1,2,5,0,6,8,6,4,3,0,5,4,7,6,9,2};
    heapSort(arr);
    printArray(arr);
}

void heapSort(int arr[])
{
    int i, temp;
    for(i = SIZE/2-1; i >= 0; i--) {
        heapify(arr, SIZE, i);
    }

    for(i = SIZE-1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int node) // max heapify
{
    int largest = node, left = 2 * largest + 1, right = 2 * largest + 2, temp;
    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if(largest != node) {
        temp = arr[largest];
        arr[largest] = arr[node];
        arr[node] = temp;

        heapify(arr, n, largest);
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
