/******************************************************
 * Name: Carlos Gonzalez
 * Date: 4/22/21
 * Program: shopping.cpp
 * Description: finds the max price a family can accumulate 
 *              from the items they select in a shopping spree.
 * ***************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std; 

/************************************************
 * function: searchKnap()
 * description: searches the table for items used to
 * calculate the max value
 * ***********************************************/
vector<int> searchKnap(int **table, int n, int W, int* weights){

    vector <int> v;
    int k = W;
    for(int i = n; i> 0; i--){
        if(table[i][k] != table[i-1][k]){ //if different values, item i was used
            v.push_back(i);
            k = k - weights[i-1]; //subtract weight of item i
        }
    }
    return v;
}

/************************************************
 * function: knapsack_dp()
 * description: bottom up approach to finding the max value
 * ***********************************************/
int** knapsack_dp(int k, int W, int *kw, int *kval){
    //create table of k+1 x W + 1
    int **table = new int *[k+1];
    for(int i=0; i < k+1; i++)
        table[i] = new int[W+1];

    for(int i=0; i <= k; i++){
        for(int j=0; j <= W; j++){
            if(i==0 || j==0){
                table[i][j] = 0; //fill first row and first column with 0s
            }else if( kw[i-1] <= j){ //if item i is usable
                table[i][j] = max( kval[i-1]+
                                   table[i-1][j-kw[i-1]], 
                                   table[i-1][j]); //choose larger of two values
            }else{
                table[i][j] = table[i-1][j]; //else propagate last value
            }
        }
    }
    return table;
}

/************************************************
 * function: printItems
 * description: prints the items used for each family member
 * ***********************************************/
void printItems(vector<int> list){
    if(list.size() > 0){
        for(int i= list.size()-1; i >= 0; i--){
            cout << " " << list.at(i); 
        }
    }
}

int main(){

    int Tcase, numItems, sizeFam;
    int *prices, *weights, *maxCarry;
    string c;
    fstream shopF;
    shopF.open("shopping.txt", ios::in);
    if(!shopF){
        cout << "No file found." << endl;
    }else{
        shopF >> c; //get num of test cases
        Tcase = stoi(c);
        for(int i=1; i <= Tcase; i++){
            cout << "Test Case " << i << endl;
            shopF >> c; //get num of items
            numItems = stoi(c);
            prices = new int [numItems];
            weights = new int [numItems];
            for(int j=0; j < numItems; j++){
                shopF >> c; //get jth item's price
                prices[j] = stoi(c);
                shopF >> c; //get jth item's weight
                weights[j] = stoi(c);
            }
            shopF >> c; //get num of family members
            sizeFam = stoi(c);
            maxCarry = new int [sizeFam];
            for(int j=0; j < sizeFam; j++){
                shopF >> c; //get jth member's max carring capacity
                maxCarry[j] = stoi(c);
            }
            int totalPrice = 0;
            int **V;
            vector<vector<int>> famItems; 
            for(int i=0; i < sizeFam; i++){
                V = knapsack_dp(numItems, maxCarry[i], weights, prices); //get max value for each family member
                totalPrice += V[numItems][maxCarry[i]]; //add to total
                famItems.push_back(searchKnap(V, numItems, maxCarry[i],weights));//find items used for this member
                for(int m =0; m <= numItems; m++){
                    delete [] V[m];
                }
                delete [] V;
            }
            cout << "Total Price: " << totalPrice << endl;
            for(int i =0; i < sizeFam; i++){
                cout << i+1 << ":";
                printItems(famItems.at(i));
                cout << endl;
            }
            cout << endl;
            delete [] prices;
            delete [] weights;
            delete [] maxCarry;
        }
    }
    shopF.close();
return 0;
}