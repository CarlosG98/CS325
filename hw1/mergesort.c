/***************************************************************************
 * Name: Carlos Gonzalez
 * Date: 4/12/2021
 * Description: This program reads lines from a text file containing an array of unsorted integers. 
 *              These integers are to be sorted using the merge sort algorithm. 
 * ************************************************************************/
#define _POSIX_C_SOURCE 200809L 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
 * Function: makeArr
 * Description: parses text line and creates a dynamic array of ints
 * *********************************************************************/
void makeArr(char* line){
    //parse line
    char* saveptr;
    char* token = strtok_r(line, " ", &saveptr);
    int NumItems = atoi(token); //first token tells us how many items
    int *numArr = malloc(NumItems*sizeof(int)); //allocate memory for array
    //fill array with items
    for(int i=0; i < NumItems; i++){
        token = strtok_r(NULL, " ", &saveptr);
        numArr[i] = atoi(token);
    }
 
    int *tempArr = malloc(NumItems*sizeof(int)); //temp array to hold sorted 
    merge_sort(0, NumItems-1, numArr, tempArr);
   
    for(int i = 0; i < NumItems; i++){
        printf("%d ", numArr[i]);
    }
    printf("\n");
    
    free(tempArr);
    free(numArr);
}

int main(){

    FILE* dataF = fopen("data-1.txt", "r");
    char* currLine = NULL;
    size_t len = 0;
    size_t nread; 
    
    //read file line-by-line
    while((nread = getline(&currLine, &len, dataF)) != -1){
        //printf(currLine);
        makeArr(currLine);
    }
    free(currLine);
    fclose(dataF);

    return 0;
}