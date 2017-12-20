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

class edge{
    int x, y;
public:
    edge(int i,int j){
        x = i;
        y = j;
    };
    int head(){return x;};
    int tail(){return y;};
};

// get input
int getUndirctedGraph(std::vector< std::vector<int>>& VertexList, std::vector<edge>& edges){
    // load file
    std::ifstream file("/Users/chenxk/Desktop/kargerMinCut.txt",std::ios::in);
    if(!file.is_open()) {std::cout<<"Wrong file!"<<std::endl; exit(1);}
    
    std::string tmp;
    while(std::getline(file,tmp)){
        // put line to sstream
        std::istringstream CurrentVertexInfo(tmp);
        
        // get No. of current vertex
        int vertex;
        CurrentVertexInfo >> vertex;
        
        // get edges head from current Vertex to others with large index
        int temp;
        std::vector<int> AdjacentNodes;
        while(CurrentVertexInfo >> temp){
            if(temp > vertex){
                AdjacentNodes.push_back(temp);
                edges.push_back(edge(vertex,temp));
            }
        }
        
        // combine results
        VertexList.push_back(AdjacentNodes);
    }
    
    // close file
    file.close();
    
    return 0;
};

// for shuffle edges
void swap(int* array,int i,int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
int randomList(int* List,int size){
    int Index;
    
    srand((unsigned)time(NULL));
    for(int i = 0; i<size;i++){
        Index = rand()%(i+1);
        swap(List,Index,i);
    }
    
    return 0;
};

// Union Find
class GraphMinCut{
    std::vector<int> List;
public:
    int Uncontracted;
    GraphMinCut(int n){
        for(int i = 0; i<n+1;i++) List.push_back(i);
        Uncontracted = n;
    };
    int Root(int i){
        if(List[i] == i) return i;
        return List[i] = Root(List[i]);
    };
    int Contraction(int i,int j){
        int root_x = Root(i);
        int root_y = Root(j);
        if(root_x > root_y) {
            List[root_x] = root_y;
            List[i] = root_y;
        }
        else{
            List[root_y] = root_x;
            List[j] = root_x;
        }
        
        return 0;
    };
};

int main(){
    // initialize final result
    std::vector<edge> edges;
    std::vector< std::vector<int> > VertexList(1, std::vector<int>(1,0));
    
    // read input file
    getUndirctedGraph(VertexList,edges);
    
    // get the problem size
    int VertexCnt = VertexList.size()-1;
    int EdgesCnt = edges.size();
    
    // storage the answer of min cut crossing edges
    int count = std::numeric_limits<int>::max();
    
    time_t start,end;
    start = time(NULL);
    // repeat random contraction to find the min cut
    for(int n = 0; n< 50000; n++){
        // generate records for one random contraction
        int EdgePickList [ EdgesCnt ];
        for(int i = 0; i<EdgesCnt;i++)
            EdgePickList[i] = i;

        // generate sequences the edges are picked
        randomList(EdgePickList,EdgesCnt);
        //for(int i = 0; i<EdgesCnt;i++) std::cout<<EdgePickList[i]<<std::endl;
        
        // start contraction
        GraphMinCut CntrctVtx (VertexCnt);
        int chosenEdgesCnt = 0;
        
        while(CntrctVtx.Uncontracted > 2){
            edge CurrentEdge = edges[EdgePickList[chosenEdgesCnt++]];
            int head = CurrentEdge.head(),tail = CurrentEdge.tail();
            if(CntrctVtx.Root(head) != CntrctVtx.Root(tail)){
                CntrctVtx.Contraction(head,tail);
                CntrctVtx.Uncontracted--;
            }
        }
        
        // check for remaining self-loop
        int crossingEdge = 0;
        for(int i = 0; i< EdgesCnt-chosenEdgesCnt;i++){
            edge CurrentEdge = edges[EdgePickList[chosenEdgesCnt+i]];
            int head = CurrentEdge.head(),tail = CurrentEdge.tail();
            if(CntrctVtx.Root(head) != CntrctVtx.Root(tail)) crossingEdge++;
        }
        
        count = count > crossingEdge? crossingEdge:count;
    }
    
    end = time(NULL);
    
    std::cout<<"# of crossing edges in the min cut: "<<count<<std::endl<<"Use "<<(end-start)<<std::endl;
    
    return 0;
}
