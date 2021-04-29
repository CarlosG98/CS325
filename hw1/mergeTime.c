#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/************************************************************************
 * Function: merge_sort()
 * Description: takes in a filled array,temp empty array, array start index and end index. 
 *              recursively breaks down array into subarrays until array of length 1.
 *              Then array is sorted and merge with other subarray and sorted again.
 *              Repeats until fully sorted.
 * *********************************************************************/
void merge_sort(int startindex, int endindex, int *numArr, int* numArrSorted){

    //if size of array is 1 or less
    if(endindex <= startindex){
        return;
    }
    int mid = (startindex + endindex) / 2;  //get middle index to split array into two

    //recursively break down arrays into subarrays
    merge_sort(startindex, mid, numArr, numArrSorted); 
    merge_sort(mid + 1, endindex, numArr, numArrSorted);

    int leftPointer = startindex; //left subarray
    int rightPointer = mid + 1;   //right subarray

    for(int i = startindex; i <= endindex; i++){
        if(leftPointer == mid + 1){ //if no more items in left subarray
            numArrSorted[i] = numArr[rightPointer]; //sorted array gets right subarray items
            rightPointer++;
        }
        else if( rightPointer == endindex + 1){ //if no more items in right subarray
            numArrSorted[i] = numArr[leftPointer]; //sorted array gets left subarray items
            leftPointer++;
        }
        else if( numArr[leftPointer] < numArr[rightPointer]){ //if left item greater than right item
            numArrSorted[i] = numArr[leftPointer]; //add left item to sorted array
            leftPointer++;
        }
        else{
            numArrSorted[i] = numArr[rightPointer]; //else add right item
            rightPointer++;
        }
    }
    for(int i = startindex; i <= endindex; i++){
        numArr[i] = numArrSorted[i];
    }

}

/************************************************************************
 * Function: mergeTime()
 * Description: dynamically creates an integer array of size n and fills
 *              it with random ints ranging from 0-10,000. Records time to sort
 *              array. 
 * *********************************************************************/
void mergeTime(int n){

    clock_t t;
    int *numArr;
    int *tempArr;
    double runTime;

    numArr = malloc(n*sizeof(int)); //unsorted array 
    tempArr = malloc(n*sizeof(int)); //temp array for sorted
    for(int i=0; i < n; i++){
        numArr[i] = rand() % 10000; //fill unsorted array w/ rand ints
    }
    //time merge_sort
    t = clock();
    merge_sort(0, n-1, numArr, tempArr);
    t = clock() - t;
    runTime = ((double)t)/CLOCKS_PER_SEC;
    printf("n = %d\trun time = %f\n", n, runTime);
    free(numArr);
    free(tempArr);
}

int main(){

    // Measure run time of merge_sort with arrays of n items. 
    srand(time(NULL));

    mergeTime(125000);
    mergeTime(150000);
    mergeTime(175000);
    mergeTime(200000);
    mergeTime(225000);
    mergeTime(250000);
    mergeTime(275000);
    mergeTime(300000);
    mergeTime(325000);
    mergeTime(350000);
    return 0;
}