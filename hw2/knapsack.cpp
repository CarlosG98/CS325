/********************************************************
 * Name: Carlos Gonzalez
 * Date: 4/22/2021
 * Program: knapsack.cpp
 * Description: analysis of the recursive and DP knapsack program
 * *****************************************************/


#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;


/************************************************
 * function: knapsack_r()
 * description: solves knapsack problem recursively
 * finds largest possible total value from set of items 
 * while meeting weight restrictions
 * ***********************************************/
int knapsack_r(int k, int W, int* kw, int*kval){

    if(k==0 || W ==0){
        return 0;
    }
    if( kw[k-1] > W){
        return knapsack_r(k-1, W, kw, kval);
    }else{
        return max((kval[k-1]+knapsack_r(k-1, W-kw[k-1], kw, kval)),knapsack_r(k-1, W, kw, kval));
        //return ((kval[k-1]+knapsack_r(k-1, W-kw[k-1], kw, kval)) > knapsack_r(k-1, W, kw, kval)) ? (kval[k-1]+knapsack_r(k-1, W-kw[k-1], kw, kval)):knapsack_r(k-1, W, kw, kval);
    }
}

/************************************************
 * function: knapsack_dp()
 * description: solves knapsack problem with a bottom up approach
 * fills table to find a max value
 * ***********************************************/
int knapsack_dp(int k, int W, int *kw, int *kval){
    
    //create table of k+1 x W + 1
    int table[ k + 1][W + 1];
    for(int i=0; i <= k; i++){
        for(int j=0; j <= W; j++){
            if(i==0 || j==0){
                table[i][j] = 0; //fill first row and first column with 0s
            }else if( kw[i-1] <= j){  //if item i is usable
                table[i][j] = max( kval[i-1]+
                                   table[i-1][j-kw[i-1]], 
                                   table[i-1][j]); //choose larger of two values
            }else{
                table[i][j] = table[i-1][j]; //else propagate last value
            }
        }
    }

    return table[k][W];

}

/************************************************
 * function: recknap()
 * description: records the run time of knapsack_r()
 * ***********************************************/
void recknap(int numItems, int maxWeight){
    int *weights = new int [numItems];
    int *vals = new int [numItems];

    //fill arrays with random values
    for(int i=0; i < numItems; i++){
        weights[i] = (rand()%45) +10;
        vals[i] = (rand()%19)+1; 
    }
    auto start = high_resolution_clock::now();
    int maxVal_rec = knapsack_r(numItems, maxWeight, weights, vals);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "N = " << numItems; 
    cout << " W = " << maxWeight;
    cout << " Rec time = " << duration.count() << "ms";
    cout << " max Rec = " << maxVal_rec << endl;
    

    delete [] weights;
    delete [] vals;
}

/************************************************
 * function: dpknap()
 * description: records run time of knapsack_dp()
 * ***********************************************/
void dpknap(int numItems, int maxWeight){
    int *weights = new int [numItems];
    int *vals = new int [numItems];

    for(int i=0; i < numItems; i++){
        weights[i] = (rand()%45) +10;
        vals[i] = (rand()%19)+1;
    }
    
    auto start = high_resolution_clock::now();
    int maxVal_dp = knapsack_dp(numItems, maxWeight, weights, vals);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "N = " << numItems; 
    cout << " W = " << maxWeight;
    cout << " DP time = " << duration.count() << "ms";
    cout << " max DP = " << maxVal_dp << endl;

    delete [] weights;
    delete [] vals;
}


int main(){

    srand(time(NULL));

    cout << "Recursive Knapsack: " << endl;
    for(int i = 300; i <= 400; i += 10){
        recknap(i, 50);
    }

    cout << "DP Knapsack: " << endl;
    for(int i=8000; i <= 10000; i += 200){
        dpknap(i, 150);
    }

return 0;   
}