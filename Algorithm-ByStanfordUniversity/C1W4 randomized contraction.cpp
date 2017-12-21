//
//  C1W4 randomized contraction.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 27/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class edge {
    int x, y;
public:
    edge(int i,int j) {
        x = i;
        y = j;
    };
    int getHead() {
        return x;
    };
    int getTail() {
        return y;
    };
};

// get input
int getUndirctedGraph(std::vector< std::vector< int > >& VertexList, std::vector< edge >& edges){
    // load file
    std::ifstream file("/Users/chenxk/Desktop/kargerMinCut.txt", std::ios::in);
    if ( !file.is_open() ) {
        std::cout << "Wrong file!" << std::endl;
        exit(1);
    }
    
    std::string tmp;
    while ( std::getline(file, tmp) ) {
        // put line to sstream
        std::istringstream CurrentVertexInfo( tmp );
        
        // get No. of current vertex
        int vertex;
        CurrentVertexInfo >> vertex;
        // get edges head from current Vertex to others with large index
        int temp;
        std::vector< int > AdjacentNodes;
        while (CurrentVertexInfo >> temp) {
            if (temp > vertex) {
                AdjacentNodes.push_back( temp );
                edges.push_back( edge(vertex, temp) );
            }
        }
        
        // combine results
        VertexList.push_back( AdjacentNodes );
    }
    
    // close file
    file.close();
    
    return 0;
};

// generate a randomized sequence to pick up edges 
int* getRandomList(int size) {
    // initialzie List
    int* result = new int[ EdgesCnt ];

    srand( (unsigned)time(NULL) );
    for (int i = 0; i<size; i++) {
        int index = rand() % (i+1);
        result[i] = result[ index ];
        result[ index ] = i;
    }
    
    return result;
};

// A Class to Implememnt Union Find for Graph min cut
class Contraction{
    std::vector< int > Status;
public:
    int Uncontracted;
    Contraction(int n) {
    // initialize the class with no union
        for (int i = 0; i < n+1; i++) {
            Status.push_back(i);
        }
        Uncontracted = n;
    };

    int getRoot(int i) {
    // find the root of one element
        if (Status[i] == i) {
            return i;
        }
        // compress the path while finding the root
        return Status[i] = getRoot( List[i] );
    };
    void combine(int i,int j) {
    // make contration between two element
        int root_x = getRoot(i);
        int root_y = getRoot(j);
        // use the smaller element number
        if (root_x > root_y) {
            Status[root_x] = root_y;
            Status[i] = root_y;
        } else {
            Status[root_y] = root_x;
            Status[j] = root_x;
        }
        Uncontracted--;
    };
};

int main(){
    // initialize final result
    std::vector< edge > edges;
    std::vector< std::vector< int > > VertexList(1, std::vector< int >(1,0));
    
    // read input file
    getUndirctedGraph(VertexList, edges);
    // get the problem size
    int VertexCnt = VertexList.size()-1;
    int EdgesCnt = edges.size();
    
    // storage the answer of min cut crossing edges
    int count = std::numeric_limits< int >::max();
    
    time_t start,end;
    start = time(NULL);
    // repeat random contraction to find the min cut
    for (int n = 0; n< 50000; n++) {
        // generate sequences the edges are picked
        int* EdgeQueue = getRandomList( EdgesCnt );
        //for(int i = 0; i<EdgesCnt;i++) std::cout<<EdgeQueue[i]<<std::endl;

        // start contraction
        Contraction Attempt( VertexCnt );
        int ChosenEdgeCnt = 0;
        
        while (Attempt.Uncontracted > 2) {
            edge Current = edges[ EdgeQueue[ ChosenEdgeCnt++ ] ];
            int head = Current.getHead();
            int tail = Current.getTail();
            if (Attempt.getRoot( head ) != Attempt.getRoot( tail )){
                Attempt.combine(head, tail);
            }
        }
        
        // check for remaining self-loop
        int crossingEdge = 0;
        for (int i = 0; i< EdgesCnt-ChosenEdgeCnt; i++) {
            edge CurrentEdge = edges[ EdgeQueue[ ChosenEdgeCnt+i ] ];
            int head = CurrentEdge.getHead();
            int tail = CurrentEdge.getTail();
            if (Attempt.getRoot( head ) != Attempt.getRoot( tail )) {
                 crossingEdge++;
            }
        }
        
        count = count > crossingEdge? crossingEdge : count;
    }
    
    end = time(NULL);
    
    std::cout << "# of crossing edges in the min cut: " 
              << count << std::endl
              << "Use " << (end - start) << std::endl;
    
    return 0;
}
