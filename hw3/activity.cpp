/*************************************************
 * Name: Carlos Gonzalez
 * Date: 5/7/21
 * Program: activity.cpp
 * Description: implement the last-to-start activity selection problem. use a greedy algorithm to 
 *              find an optimal solution. 
 * ************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/***************************************************************
 * Function: mergesort()
 * Description: merge sort sorting algorithm to sort the set
 *              of activities by start time in descending order. 
 * *************************************************************/
void mergesort(int **arr, int **sortedarr, int left, int right){
    if(right <= left){
        return;
    }
    int mid = (left+right)/2;

    //recursive merge sort subarrays
    mergesort(arr, sortedarr, left, mid);
    mergesort(arr, sortedarr, mid+1, right);

    int leftptr = left;
    int rightptr = mid+1;
    int k;

    for(k=left; k <= right; k++){
        if(leftptr == mid+1){ //if no more elements in left subarray
            sortedarr[k][0] = arr[rightptr][0];
            sortedarr[k][1] = arr[rightptr][1];
            sortedarr[k][2] = arr[rightptr][2];
            rightptr++;
        }else if(rightptr == right+1){ //if no more elements in right subarray
            sortedarr[k][0] = arr[leftptr][0];
            sortedarr[k][1] = arr[leftptr][1];
            sortedarr[k][2] = arr[leftptr][2];
            leftptr++;
        }else if(arr[leftptr][1] < arr[rightptr][1]){ //if right element has greater start time
            sortedarr[k][0] = arr[rightptr][0]; //copy values to temp arr
            sortedarr[k][1] = arr[rightptr][1]; 
            sortedarr[k][2] = arr[rightptr][2];
            rightptr++;
        }else{
            sortedarr[k][0] = arr[leftptr][0]; //else if left element has greater start time
            sortedarr[k][1] = arr[leftptr][1];
            sortedarr[k][2] = arr[leftptr][2];
            leftptr++;
        }
    }
    //copy values back to set
    for(k = left; k<= right; k++){
        arr[k][0] = sortedarr[k][0];
        arr[k][1] = sortedarr[k][1];
        arr[k][2] = sortedarr[k][2];
    }
}

/***************************************************************
 * Function: greedyAct()
 * Description: find the largest subset of mutually compatible 
 *              activities in the sorted set.  
 * *************************************************************/
vector<int> greedyAct(int** set, int n){
    vector<int> optSet;
    optSet.push_back(set[0][0]); //take first activity in sorted set
    int k = 0; //track current activity
    for(int i = 1; i < n; i++){
        if(set[i][2] <= set[k][1]){ //if activity i finishes before activity k starts
            optSet.push_back(set[i][0]); //place in vector
            k = i; //update current activity 
        }
    }
    return optSet;
}

int main(){
    
    int num_acts, currSet = 1;
    int **sets, **sortedset;
    string s;
    fstream actF;

    actF.open("act.txt", ios::in);
    if(!actF){
        cout << "No File Found." << endl;
    }else{
        while(!actF.eof()){
            
            actF >> s;
            if(actF.eof()){ break;}
            cout << "Set " << currSet << endl; 
            num_acts = stoi(s);
            sets = new int* [num_acts]; 
            sortedset = new int* [num_acts];

            for(int i=0; i < num_acts; i++){
                sets[i] = new int[3];
                sortedset[i] = new int[3];
                actF >> s; //read in activity number
                sets[i][0] = stoi(s);
                actF >> s; //read in activity's start time
                sets[i][1] = stoi(s);
                actF >> s; //read in activity's finish time
                sets[i][2]= stoi(s);
            }

            mergesort(sets, sortedset, 0, num_acts-1); //sort set
            vector<int> solution = greedyAct(sets, num_acts);
            cout << "Maximum number of activities = " << solution.size() << endl;
            for(int i = solution.size()-1; i >= 0 ; i--){
                cout << " " << solution.at(i);
            }
            cout << endl;
            cout << endl;

            currSet++;
            for(int i =0; i < num_acts; i++){
                delete [] sets[i];
                delete [] sortedset[i];
            }
            delete [] sets;
            delete [] sortedset;
        }
    }   
    actF.close();
return 0;
}