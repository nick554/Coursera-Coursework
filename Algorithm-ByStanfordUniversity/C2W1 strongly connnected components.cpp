//
//  C2W1 strongly connnected components.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 30/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>

class Edge{
public:
    long head;
    long tail;
    Edge( long i, long j) : head(i),tail(j){
    }
    Edge reverse() {
        return Edge( tail, head);
    }
};

class AdjacentList{
private:
    std::vector< std::vector<Edge> > NodeList;
    long NodeCnt;
public:
    AdjacentList(std::vector<Edge> EdgeList, bool WantReverse) {
        // initialize
        NodeCnt = 0;
        std::vector<Edge> tmp;
        long CurrentSize = 8;
        std::vector< std::vector< Edge > > result( CurrentSize, tmp );
        
        //generate AdjacentList
        for(long i = 0; i< EdgeList.size(); i++){
            Edge CurrentEdge = WantReverse?  EdgeList[i].reverse() : EdgeList[i];
            long head = CurrentEdge.head;
            long tail = CurrentEdge.tail;
            if ( head > NodeCnt ) NodeCnt = head;
            if ( tail > NodeCnt ) NodeCnt = tail;

            if ( head >= CurrentSize ) {
                CurrentSize = CurrentSize * 2;
                result.resize( CurrentSize, tmp);
            }
            result[head].push_back( CurrentEdge );
        }
        result.resize( NodeCnt + 1 );
        NodeList = result;
    };
    std::vector<Edge> edgeToAdd( long i ) {
        return NodeList[ i];
    }
    long size() {
        return NodeCnt;
    }
};

class SCC {
    std::vector<long> elements;
    long length;
public:
    SCC () {
        std::vector<long> result;
        elements = result;
        length = 0;
    }
    void push ( long x ) {
        elements.push_back( x );
        length++;
    }
    long size() {
        return length;
    }
};

class MaxHeapForSCC{
    long capacity;
    long size;                  // first element start from index 1
    SCC** PriorityQueue;
public:
    MaxHeapForSCC( ) {
        size = 0;
        capacity = 1;
        PriorityQueue = NULL;
    }
    ~MaxHeapForSCC( ) {
        for (int i = 0; i < size - 1; i++) {
            delete [] PriorityQueue[i];
        }
        delete [] PriorityQueue;
    }
    void push( SCC& x) {
        size++;
        if ( size == capacity) {
            capacity *= 2;
            resize( capacity);
        }
        
        PriorityQueue[ size ] = &( x );
        swim( size );
    }
    SCC pop() {
        //read
        SCC result = top();

        //delete
        -- size;
        swap( 1, size);
        delete PriorityQueue[ size ];
        PriorityQueue[ size ] = nullptr;

        //resize
        if ( size + 1 < capacity / 4) {
            capacity /= 2;
            resize( capacity);
        }
        
        if ( size != 0) {
            sink( 1 );
        }
        
        return result;
    }
    SCC top() {
        return *( PriorityQueue[ 0 ] );
    }
private:
    void swap( long i, long j) {
        SCC* tmp = PriorityQueue[ i];
        PriorityQueue[ i] = PriorityQueue[ j];
        PriorityQueue[ j] = tmp;
    }
    long parent( long k) {
        return k / 2;
    }
    long child( long k) {
        // return left child
        return k*2;
    }
    void swim( long k) {
        // base case
        if ( k == 1 ) {
            return;
        }
        long target = parent( k );
        long size_k = PriorityQueue[ k ] -> size();
        long size_target = PriorityQueue[ target ] -> size();
        
        if ( size_k > size_target ) {
            swap( k, target );
            swim( target );
        }
    }
    void sink( long k) {
        // base case
        if ( child(k) >= size ) {
            return;
        }
        long target;
        long size_target;
        if ( child( k ) + 1 < size + 1 ) {
            long target_l = child(k);
            long target_r = target_l + 1;
            long size_target_l = PriorityQueue[ target_l ] -> size();
            long size_target_r = PriorityQueue[ target_r ] -> size();
            
            if ( size_target_l > size_target_r) {
                target = target_l;
                size_target = size_target_l;
            } else {
                target = target_r;
                size_target = size_target_r;
            }
        } else if ( child( k ) < size + 1 ) {
            target = child(k);
            size_target = PriorityQueue[ target ] -> size();
        } else {
            return;
        }
        
        long size_k = PriorityQueue[ k ] -> size();
        if ( size_k < size_target ) {
            swap( target, k );
            sink( target );
        }
    }
    void resize( long n) {
        SCC** newPQ = new SCC* [ n ];
        for ( long i = 1; i < size; i++ ) {
            newPQ[ i ] = PriorityQueue[ i ];
        }
        PriorityQueue = newPQ;
    };
};

class maxPQ {
    long* arr;
    long size;
    long capacity;
public:
    maxPQ() : size(0), capacity(0) {
        arr = NULL;
    }
    ~maxPQ() {
        delete [] arr;
    }
    void add( long x ) {
        ++ size;
        if ( size > capacity ) {
            capacity *= 2;
            resize( capacity );
        }
        arr[ size ] = x;
        swim( size );
    }
    long top() {
        return arr[0];
    }
    long max() {
        long tmp = arr[0];
        swap( 0, size );
        sink( 0 );
        -- size;
        if ( size < capacity / 4 ) {
            capacity = capacity / 2;
            resize( capacity );
        }
        return tmp;
    }
private:
    void resize( long n ) {
        long* result = new long [n];
        for ( long i = 0; i < size; i++ ) {
            result[i] = arr[i];
        }
        delete [] arr;
        arr = result;
    }
    void swim( long i ) {
        
    }
    void sink( long i ) {
        
    }
    void swap( long i1, long i2 ) {
        
    }
};

std::vector<Edge> getEdgeList(){
    // open file
    std::ifstream file("/Users/chenxk/Desktop/SCC.txt",std::ios::in);
    if ( !file.is_open() ) {
        std::cout<<"Wrong file!"<<std::endl; exit(11);
    }
    
    //
    std::vector<Edge> EdgeList;
    std::string tmp;
    long n = 0;
    while( getline( file, tmp) ) {
        std::istringstream temp( tmp );
        long a,b;
        temp>>a; temp>>b;
        if(a>n) n = a;
        else if(b>n) n = b;
        Edge CurrentEdge(a,b);
        
        EdgeList.push_back( CurrentEdge );
    }
    
    return EdgeList;
}

std::stack<long> reverseLoop( AdjacentList rGrph ) {
    std::stack<long> result;
    
    // prepare
    long n = rGrph.size();
    std::stack<long> Stack;         //
    std::vector<long> VertexStatus( n + 1, 0);
    long FinishingTime = 1;
    long Beginning = 1;
    
    while ( FinishingTime != n + 1) {
        // find new unused vertex as the start of a DFS loop and put it in stack
        if ( Stack.size() == 0) {
            while( VertexStatus[ Beginning ] != 0) {
                ++Beginning;
            }
            Stack.push( Beginning );
            VertexStatus[ Beginning] = -1;
        }
        // add vertex being pointed to by the edge
        while( Stack.size() != 0) {
            long CurrentVertex = Stack.top();
            std::vector<Edge> EdgeToAdd = rGrph.edgeToAdd( CurrentVertex);
            
            long Cnt = 0;
            for ( long i = 0; i < EdgeToAdd.size() ; i++) {
                long VertexToAdd = EdgeToAdd[ i ].tail;
                if ( VertexStatus[ VertexToAdd ] == 0) {
                    ++Cnt;
                    Stack.push( VertexToAdd);
                    VertexStatus[ VertexToAdd ] = 1;
                }
            }
            if ( Cnt == 0) {
                ++ FinishingTime;
                result.push( CurrentVertex );
                Stack.pop();
            }
        }
    }
    
    return result;
}

MaxHeapForSCC Loop( AdjacentList Grph, std::stack<long> Sequence ) {
    MaxHeapForSCC result;
    
    long VertexCnt = Grph.size();
    std::vector<bool> VertexCheckList( VertexCnt + 1, 0);
    
    while ( Sequence.size() != 0) {
        // head of a new SCC
        long HeadOfSCC = Sequence.top();
        Sequence.pop();
        while ( VertexCheckList[ HeadOfSCC ] && Sequence.size() != 0 ) {
            HeadOfSCC = Sequence.top();
            Sequence.pop();
        }
        if ( VertexCheckList[ HeadOfSCC ] ) {
            return result;
        }
        
        // find the SCC by DFS-loop
        SCC NewSCC;
        std::stack<long> Stack;
        Stack.push( HeadOfSCC );
        VertexCheckList[ HeadOfSCC ] = true;
        while ( Stack.size() != 0 ) {
            // pop the checked vertex
            long Curr = Stack.top();
            Stack.pop();
                
            // add the checked vertex into current SCC
            NewSCC.push( Curr );
                
            // push the vertex newly discovered ( check if discovered before
            std::vector<Edge> EdgeToAdd = Grph.edgeToAdd( Curr );
            for ( long i = 0; i < EdgeToAdd.size() ; i++ ) {
                long VertexToAdd = EdgeToAdd[ i ].tail;
                if ( ! VertexCheckList[ VertexToAdd ] ) {
                    Stack.push( VertexToAdd );
                    VertexCheckList[ VertexToAdd ] = true;
                }
            }
        }
        
        // add the new SCC to result
        result.push( NewSCC );
    }
    return result;
}

int main(){
    // read data from file as a edge list
    std::vector<Edge> EdgeList = getEdgeList();

    // DFS-loop for reversed Graph
    // create adjacent list for the reversed graph
    AdjacentList rGrph( EdgeList, 1);
    // get finishing time for each node
    std::stack<long> FinishingSequence = reverseLoop( rGrph );
    
    // DFS-loop for the original graph
    // create adjacent list for the original graph
    AdjacentList Grph( EdgeList, 0);
    // prepare
    MaxHeapForSCC records = Loop( Grph, FinishingSequence );

    // result output
    for ( int i = 0; i< 5; i++) {
        std::cout<<records.pop().size()<<std::endl;
    }
    return 0;
}
