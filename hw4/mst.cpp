/***************************************************
 * Name: Carlos Gonzalez
 * Date: 5/14/2021
 * Description: find the min spanning tree of a graph
 *              where the weights are determined by the
 *              Euclidean distance between vertices
 * **************************************************/

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Vertex{
    int x;
    int y;
};

/***************************************************************
 * function: buildMatrix()
 * Description: calculates the weight of an edge and returns the
 *              adjaceny matrix
 * ************************************************************/
void buildMatrix(int **am, Vertex* arr, int numV){

    for(int i = 0; i < numV; i++){
        for(int j =0; j < numV; j++){
            am[i][j] = nearbyint(sqrt(pow(arr[j].x - arr[i].x,2.0) + pow(arr[j].y - arr[i].y, 2.0)));
        }
    }
}

/***************************************************************
 * function: ExtractMin()
 * Description: finds the index of a vertex with the 
 *              smallest weight(key) that
 *              is not yet included in the MST
 * ************************************************************/
int ExtractMin(vector<int>keys, vector<bool>inMST, int numV){

    int min = 10000, idx;
    for(int i = 0; i < numV; i++){
        if( inMST.at(i) == false && (keys.at(i) < min)){
            min = keys.at(i);
            idx = i;
        }
    }
    return idx;
}

/***************************************************************
 * function: PrimMST()
 * Description: creates the MST of a graph and returns the weight
 * ************************************************************/
void PrimMST(int **graph, Vertex *arr, int numV){

    vector<int> keys(numV, 10000); //vector to hold the weights of each vertex
    vector<bool> inMST(numV, false); //boolean vect to determine if a vertex is in MST

    keys.at(0) = 0; //start at vertex 0

    for(int k = 0; k < numV - 1; k++){
        int u = ExtractMin(keys, inMST, numV); //find min vertex
        inMST.at(u) = true; //place vertex u in MST

        for(int i = 0; i < numV; i++){
            //weights are zero if u == i (same vertex)
            if( (u != i) && inMST.at(i) == false && graph[i][u] < keys.at(i)){
                keys.at(i) = graph[u][i]; //update weight of vertex i
            }
        }
    }
    //sum keys for MST weight
    int totalW = 0;
    for(int i =0; i < numV; i++){
        totalW += keys.at(i);
    }
    cout << "MST weight " << totalW << endl;
}

int main(){


    fstream treeF;
    string s;
    int cases, numV, ptX, ptY;
    int **adjM;
    Vertex *Varr;
    
    treeF.open("graph.txt", ios::in);
    if(!treeF){
        cout << "Unable to open file" << endl;
    }else{
        while(1){
            treeF >> s;
            if(treeF.eof()){break;}
            cases = stoi(s);
            for(int i =0; i < cases; i++){
                cout << "Test case " << i+1 << ": ";
                treeF >> s;
                numV = stoi(s);
                Varr = new Vertex [numV]; //create vertex array to hold vertices
                adjM = new int* [numV]; //use array to build adjency matrix
                for(int i = 0; i < numV; i++){
                    adjM[i] = new int [numV];
                }
                for(int j =0; j < numV; j++){
                    treeF >> s;
                    ptX = stoi(s);
                    treeF >> s;
                    ptY = stoi(s);
                    Varr[j].x = ptX;
                    Varr[j].y = ptY;
                }
                buildMatrix(adjM, Varr, numV);
                PrimMST(adjM, Varr, numV);
                cout << endl;
                

                //delete memory
                delete [] Varr;
                for(int j = 0; j < numV; j++){
                    delete [] adjM[j];
                }
                delete [] adjM;
            }
        }
    }
    treeF.close();
    return 0;
}