#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/************************************************************************
 * Function: insert_sort()
 * Description: compares a value in the array to the values left of it.
 *              looks to the left until smaller value is found. proceeds
 *              to the next value on the right and repeats process until
 *              array is sorted in ascending order. 
 * *********************************************************************/
void insert_sort(int *arr, int n){

    int key, j;
    for(int i=1; i < n; i++){
        key = arr[i]; //store current value
        j = i -1;
        while(j >= 0 && arr[j] > key){ //shift left values that are greater than key to the right
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key; //place key in empty spot of array
    }
}

/************************************************************************
 * Function: insertTime()
 * Description: dynamically creates an integer array of size n and fills
 *              it with random ints ranging from 0-10,000. Records time to sort
 *              array. 
 * *********************************************************************/
void insertTime(int n){

    clock_t t;
    int *numArr;
    double runTime;

    numArr = malloc(n*sizeof(int)); 
    for(int i=0; i < n; i++){
        numArr[i] = rand() % 10000; //fill array
    }
    //record run time of insert_sort()
    t = clock();
    insert_sort(numArr, n);
    t = clock() - t;
    runTime = ((double)t)/CLOCKS_PER_SEC;
    printf("n = %d\trun time = %f\n", n, runTime);
    free(numArr);
}

int main(){

    // Measure run time of merge_sort with arrays of n items. 
    srand(time(NULL));

    insertTime(5000);
    insertTime(6000);
    insertTime(7000);
    insertTime(8000);
    insertTime(9000);
    insertTime(10000);
    insertTime(11000);
    insertTime(12000);
    insertTime(13000);
    insertTime(14000);

    return 0;
}