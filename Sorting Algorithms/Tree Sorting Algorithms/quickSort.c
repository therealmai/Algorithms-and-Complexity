/*
* 1960
	Unstable algorithm
	In-place sorting
	Divide and conquer
	Comparison approach
Recursive
*Tony Hoare
*Time Complexity: Best (middle element) & Average (random) : O(nlogn) 
                  Worst(Pivot least/greatest) : O(n^2)
*Space Complexity: O(1) unstable partition
                   0(log n) tail recursion
*/
#include<stdio.h>
#include<string.h>
int SWAPS=0;
int ACCESSES=0;
int CALLS=0;

void display(int arr[], int size);
void quicksortv1(int arr[], int low, int high);
void quicksortv2(int arr[], int low, int high);
int partitionv1(int arr[], int low, int high);
int partitionv2(int arr[], int low, int high);
void medianOfThree(int *n1, int *n2, int *n3);
void insertionSort(int arr[], int low, int high);
void swap(int *x, int *y);
void createSorted(int *array, int *array2, int n);
void createShuffled(int *array, int *array2, int n);

int main(){
	
	/* TEST CASES */
//	int arr1[] = {23,44,2,2,34,56,1,9,-4,3,5,17,100,1,19,50}, size=16, Tcase=1;
//	int arr2[] = {23,44,2,2,34,56,1,9,-4,3,5,17,100,1,19,50};

//  int arr1[] = {7,7,6,6,9,9,10,10,5,5,1,1,0,0,2,2,16,16,33,33,18,18,7,7,20,20,19,19,-1,-1,4,4}, size=32, Tcase=2;
//	int arr2[] = {7,7,6,6,9,9,10,10,5,5,1,1,0,0,2,2,16,16,33,33,18,18,7,7,20,20,19,19,-1,-1,4,4};

    int size=500, arr1[size], arr2[size], Tcase=3;
    createSorted(arr1,arr2,size);

//  int size=500, arr1[size], arr2[size], Tcase=4;
//  createShuffled(arr1,arr2,size);
	
	printf("\nTEST CASE %d\n",Tcase);
	printf("\nOriginal array: ");
	display(arr1,size);
	
	/* VERSION 1*/
	quicksortv1(arr1,0,size-1);
	printf("\n\nVersion 1 (before improvements):");
	printf("\nSorted array: ");
	display(arr1, size);
	printf("\nTOTAL SWAPS: %d",SWAPS);
	printf("\nTOTAL COMPARISONS: %d",ACCESSES);
	printf("\nTOTAL CALLS: %d",CALLS);
	SWAPS=ACCESSES=CALLS=0;
	
	/* VERSION 2*/
	quicksortv2(arr2,0,size-1);
	printf("\n\nVersion 2 (After improvements):");
	printf("\nSorted array: ");
	display(arr2, size);
	printf("\nTOTAL SWAPS: %d",SWAPS);
	printf("\nTOTAL COMPARISONS: %d",ACCESSES);
	printf("\nTOTAL CALLS: %d",CALLS);
	
	return 0;
}

void display(int arr[], int size){
	int x;
	for(x=0; x<size; x++){
		printf("%d ",arr[x]);
	}	
}
void quicksortv1(int arr[], int low, int high){
	CALLS++;
	int pos;
	if(low < high) {
        pos = partitionv1(arr, low, high);
        quicksortv1(arr, low, pos-1);
        quicksortv1(arr, pos+1, high);
    }

}
void quicksortv2(int arr[], int low, int high){
	CALLS++;
	int pos;
	if(high - low < 8){
		insertionSort(arr, low, high);
	} else {
        pos = partitionv2(arr, low, high);
        quicksortv2(arr, low, pos-1);
        quicksortv2(arr, pos+1, high);
    }
}
int partitionv1(int arr[], int low, int high){
	int x, y, pivot;
    pivot = arr[high];
   //printf("\n%d %d",low,high);
    x = low;
    y = high;
    while (x < y) {
        for(; x < y && arr[x] < pivot; x++) {ACCESSES++;}
        for(; y > x && arr[y] >= pivot; y--) {ACCESSES++;}
        if(x < y){
            //printf("%d and %d ",arr[x],arr[y]);
            swap(&arr[x], &arr[y]);
            //printf("swapped,");
    	}
    };
 
    //printf("%d %d\n",x,high);
    swap(&arr[x], &arr[high]);
    //display(arr,16);
    return x;

}
int partitionv2(int arr[], int low, int high){
	int x, y, mid, pivot;
    
    mid = (low+high)/2;
    medianOfThree(&arr[low],&arr[mid],&arr[high]);
    pivot = arr[high];
 
    x = low;
    y = high;
    while (x < y) {
        for(; x < y && arr[x] < pivot; x++) {ACCESSES++;}
        for(; y > x && arr[y] >= pivot; y--) {ACCESSES++;}
        if(x < y){
        	swap(&arr[x], &arr[y]);
		}
    };
 
    swap(&arr[x], &arr[high]);
    return x;
}
void medianOfThree(int *x, int *y, int *z){ //we want smallest, largest, middle
    if (*x <= *y && *y <= *z){
        swap(y,z); 
    } else if (*x <= *z && *z <= *y) {
    	//do nothing
	} else if (*y <= *x && *x <= *z) {
		swap(x,y); 
		swap(y,z); 
	} else if (*y <= *z && *z <= *x) {
		swap(x,y); 
	} else if (*z <= *x && *x <= *y) {
		swap(x,z);
	} else {
		swap(y,z); 
		swap(x,y); 
	}
    
}
void insertionSort(int arr[], int low, int high){
	CALLS++;
	int i, j, temp;  
    for (i = low+1; i <= high; i++) {  
        temp = arr[i];
        for(j = i - 1; j>=0 && temp <= arr[j]; j--){ 
		    arr[j+1] = arr[j]; ACCESSES++;/* Move the elements greater than temp to one position ahead from their current position*/         
        }    
        arr[j+1] = temp; SWAPS++;   
    }  
}
void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
	SWAPS++;
}

void createSorted(int *array, int *array2, int n){
	int x = 0;
	for(x=0;x<n;x++){
		array[x]=x;
		array2[x]=x;
	}
}

void createShuffled(int *array, int *array2, int n){
	int x = 0;
	for(x=0;x<n;x++){
		array[x]=x;
	}
    if (n > 1) 
    {
        int i;
        for (i = 0; i < n - 1; i++) 
        {
          int j = (int)rand() % n;
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
    memcpy(array2,array,n*sizeof(int));
}

