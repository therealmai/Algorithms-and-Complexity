#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}*nodePtr;

void bucketSort(int arr[], int size, int numBuckets);
void insertSortedLL(nodePtr* head, float num);

int main(){
    int arr[] = {13,9,50,9,42,0};
    int x;

    bucketSort(arr, 6, 5);
    for(x=0; x<6; x++){
        printf("%d ", arr[x]);
    }

    return 0;
}

void bucketSort(int arr[], int size, int numBuckets){
    int max, min, range, x;
    max = min = arr[0];

    for(x=0; x<size; x++){
        max = (max < arr[x]) ? arr[x] : max;
        min = (min > arr[x]) ? arr[x] : min;
    }
    range = (max - min) / numBuckets;

    nodePtr* buckets = (nodePtr*)calloc(sizeof(struct node), numBuckets);

    for(x=0; x<size; x++){
        int bucketNdx = (arr[x] - min) / range;
        insertSortedLL(&buckets[bucketNdx], arr[x]);
    }

    int ctr = 0;
    for(x=0; x<sizeof(buckets); x++){
        nodePtr trav;
        for(trav = buckets[x]; trav != NULL; trav = trav->link){
            arr[ctr++] = trav->data;
        }
    }
}

void insertSortedLL(nodePtr* head, float num){
    nodePtr *trav, temp;

    for(trav = head ; *trav != NULL && (*trav)->data < num; trav = &(*trav)->link){}
    temp = (nodePtr)calloc(1, sizeof(struct node));
    temp->data = num;
    temp->link = *trav;
    *trav = temp;
}



/*
bucketSort()
  create N buckets each of which can hold a range of values
  for all the buckets
    initialize each bucket with 0 values
  for all the buckets
    put elements into buckets matching the range
  for all the buckets 
    sort elements in each bucket
  gather elements from each bucket
end bucketSort
*/