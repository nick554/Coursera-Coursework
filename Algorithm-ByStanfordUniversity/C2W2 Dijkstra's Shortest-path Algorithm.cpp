//
//  C2W2 Dijkstra's shortest-path algorithm.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 28/11/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Edge {
    int x;
    int y;
    long d;
public:
    Edge( int head, int tail, long distance ) {
        x = head;
        y = tail;
        d = distance;
    }
    int head() { return x; }
    int tail() { return y; }
    long distance() { return d; }
};

class AdjacencyList {
    std::vector< std::vector< Edge > > List;
public:
    AdjacencyList( std::vector< std::string > Input ) {
        std::vector< Edge > tmp;
        std::vector< std::vector< Edge > > result( Input.size() + 1, tmp);
        
        for ( int i = 0; i < Input.size(); i++ ) {
            std::istringstream CurrentLine( Input[ i ] );
            int index;
            CurrentLine>>index;
            while ( CurrentLine ) {
                int tail;
                long distance;
                CurrentLine >> tail >> distance;
                Edge Current( index, tail, distance );
                result[ index ].push_back( Current );
            }
        }
    }
};

class myPQ {
};

std::vector< std::string > getFileInLine( std::string FileName ) {
    std::vector< std::string > result;
    std::ifstream File( FileName, std::ios::in );
    if ( ! File.is_open() ) { std::cout<<"wrong file"<<std::endl; }
    
    std::string tmp;
    while( getline( File, tmp) ) {
        result.push_back( tmp );
    }
    
    File.close();
    return result;
}

int main() {
    // read input file line by line
    std::vector< std::string > InputInLines;
    std::string FileName = "/Users/chenxk/Desktop/SCC.txt";
    InputInLines = getFileInLine( FileName );
    
    // create adjacency list
    AdjacencyList Grph( InputInLines );
}
