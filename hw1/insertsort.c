/***************************************************************************
 * Name: Carlos Gonzalez
 * Date: 4/12/2021
 * Description: This program reads lines from a text file containing an array of unsorted integers. 
 *              These integers are to be sorted using the insertion sort algorithm. 
 * ************************************************************************/
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
 
    //int *tempArr = malloc(NumItems*sizeof(int));
    insert_sort(numArr, NumItems);
   
    for(int i = 0; i < NumItems; i++){
        printf("%d ", numArr[i]);
    }
    printf("\n");
    
    //free(tempArr);
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