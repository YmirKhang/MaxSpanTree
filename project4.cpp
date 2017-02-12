/*
Student Name: A. Emirhan Karagül
Student Number: 2013400057
Project Number: 4
Operating System: Cmpe250.ova
Compile Status:
Program Status:
Notes: Nothing right now

*/

#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <queue>
#include "vector"
#include "list"

using namespace std;


struct DistrictGraph{

    int size;

    vector<pair<int,int>> *adjListPair;

    int global;

    DistrictGraph(int n){
        size=n;
        adjListPair = new vector<pair<int,int>>[size];
    }
    int addEdges(int i, int j,int dist){
        this->adjListPair[i].push_back(make_pair(j,dist));
        this->adjListPair[j].push_back(make_pair(i,dist));
    }
    void deleteEdges(int i , int j);
    int cutShortestpath(int source, int target);


};

int DistrictGraph::cutShortestpath(int source, int target) {
    if(source==target){
        return 0;
    }
    queue<int> neigh;
    neigh.push(source);
    vector<int> visited;
    visited.push_back(source);
    string s = "";
    string temp ="";
    pair<int,pair<int,int>> shortpath;
    shortpath.first=INFINITY;
    for(auto itr=adjListPair[source].begin();itr!=adjListPair[source].end();itr++){

        temp = cutShortestpath(itr->first, target, visited, shortpath);
        if(temp.size()==0){

        }else{
            if(itr->second<shortpath.first){
                shortpath.first=itr->second;
                shortpath.second = make_pair(source,itr->first);
            }
            s = temp+ "-" + to_string(source);
        }
    }

    if(shortpath.second.first!=0||shortpath.second.second!=0){
        deleteEdges(shortpath.second.first,shortpath.second.second);
        return shortpath.first;
    }

    return 0;

}


void DistrictGraph::deleteEdges(int i, int j) {


    for (int k = 0; k <adjListPair[i].size() ; ++k) {
        if(j == adjListPair[i][k].first){
            this->adjListPair[i].erase(adjListPair[i].begin()+k);
            break;

        }
    }


    for (int l = 0; l <adjListPair[j].size() ; ++l) {
        if(i == adjListPair[j][l].first){
            this->adjListPair[j].erase(adjListPair[j].begin()+l);
            break;
        }
    }
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1[input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream infile(argv[1]);

    int size;
    infile>>size;
    int cutNumb;
    infile>>cutNumb;
    DistrictGraph graph(size);
    int j,k,dist;
    for(int i=1;i<size;i++){
        infile>>j;
        infile>>k;
        infile>>dist;
        graph.addEdges(j,k,dist);
    }

    int cutDistricts[cutNumb];
    int t;
    for(int i=0;i<cutNumb;i++){
        infile>>t;
        cutDistricts[i]=t;
    }

    int total =0;


    for (int l = 0; l <cutNumb ; ++l) {

        for (int z = l; z <cutNumb ; ++z) {

            total += graph.cutShortestpath(cutDistricts[l], cutDistricts[z]);
        }
    }


    cout<<to_string(total)<<endl;


    return 0;

}



