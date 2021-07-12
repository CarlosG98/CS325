/**************************************
 * Name: Carlos Gonzalez
 * Date: 6/5/2021
 * Program: Traveling Salesman
 * **************************************/


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>


using namespace std;

struct City{

    int ID;
    int x;
    int y;
    bool visited = false;
};


/***************************************************
 * Function: makeGraph()
 * Description: creates an adjacency matrix based on the cities xy coordinates
 * *************************************************/
vector<vector<int>> makeGraph(vector<struct City> cities, int numC){
    vector<vector<int>> Graph;
    int dist;

    for(int i = 0 ; i < numC; i++){
        vector<int> temp;
        for(int j = 0; j < numC; j++){
            dist = nearbyint(sqrt(pow(cities[i].x - cities[j].x, 2.0) + pow(cities[i].y - cities[j].y,2.0)));
            temp.push_back(dist);
        }
        Graph.push_back(temp);
    }

return Graph;
}

/***************************************************
 * Function: NextCity()
 * Description: Given a starting position/city, finds the
 *              closest city.
 * *************************************************/
void NextCity(vector<vector<int>> Graph, vector<struct City> *cities, vector<int> *path, int *currCity, int *cost){

    int min_dist = 999999; //initially inf
    int closest_city = -1;
    for(int i = 0; i < (*cities).size(); i++){
        if( (min_dist > Graph[*currCity][i]) && (*cities)[i].visited == false ){ //if new closest city and not already visisted
            min_dist = Graph[*currCity][i]; //update shortest distance
            closest_city = i; //store city id
        }
    }
    (*path).push_back(closest_city); //place closest city in path
    (*cities)[closest_city].visited = true; //set visited to true
    (*cost) += min_dist; //update total dist travelled

}

/***************************************************
 * Function: NearestNeighbor()
 * Description: 
 * *************************************************/
int NearestNeighbor(vector<vector<int>> Graph, vector<struct City> *cities, vector<int> *path, int numC){

    
    int currCity = 0; //choose arbitrary city to start at
    (*path).push_back(currCity);  //place in path
    (*cities)[currCity].visited = true; //set visited to true
    int total_dist = 0;

    while((*path).size() < numC){ //visit every city
        currCity = (*path).back(); //for current city
        NextCity(Graph, cities, path, &currCity, &total_dist); //find closest city  
    }

    total_dist += Graph[(*path)[0]][(*path).back()]; //distance to get back to start position

    return total_dist;
}


int main(int argc, char** argv){

    fstream tspF;
    string s;

    int numC;
    vector<struct City> cities;

    tspF.open(argv[1], ios::in);
    if(!tspF){
        cout << "Could not open file: " << argv[1] << endl;
    }else{
         while(!tspF.eof()){

            tspF >> s;
            if(tspF.eof()){break;}
            numC = stoi(s);
            for(int i = 0; i < numC; i++){ //get city data
                City c;
                tspF >> s;
                c.ID = stoi(s);
                tspF >> s;
                c.x = stoi(s);
                tspF >> s;
                c.y = stoi(s);
                cities.push_back(c);
            }
        }
        tspF.close();
        vector<vector<int>> G = makeGraph(cities, numC); //create adjacency matrix
        vector<int> path; 
        int total = NearestNeighbor(G, &cities, &path, numC); //total travel distance

        string outfile = argv[1];
        outfile.append(".tour");
       
       fstream newFile;
       newFile.open(outfile, ios::trunc | ios::out);

        //write to file
       if(!newFile){
           cout << "Could not open/create file " << outfile << endl;
       }else{
           newFile << total << endl;
           for(int i=0; i < path.size(); i++){
               newFile << path[i] << endl;
           }
       }

       newFile.close();
    }

return 0;
}