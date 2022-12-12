/*
Richard Bellman
1950s
-	Memoization is storing of answers to previously solved subproblems.
-	Basically recursion
Time Complexity
O(n2) - in all cases
Space Complexity
O(n2) + O(n) worst case
optimal = p(k) + optimal(i-k) where i is the max length and k is the iterating variable or current length we're dealing with
p(k) gets price at position/length k
base case: optimal(1) = 1
*/

#include<stdio.h>
#include<stdlib.h>

int rodCuttingMemoization(int price[], int length)
{
    static int * memo = NULL;
    if(memo == NULL) {
        memo = calloc(sizeof(int), 11);
    }

    int i, temp, value = 0;
    for(i = 1; i <= length; i++) {
        temp = !memo[i] ? price[i] + rodCuttingMemoization(price, length - i) : price[i] + memo[length - i];
        value = value < temp ? temp : value;
    }
    memo[length] = value;
    return value;
}

int main(){

    int price[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int memoization = {0};
    rodCuttingMemoization(price, 5);
    return 0;
    
}

