//
//  C1W2 No. Invertion.cpp
//  Algorithm-Stanford-Univ
//
//  Created by S BRAIN on 19/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

long count = 0;

std::vector<int> getOriginalInput(){
    std::ifstream file;
    file.open("/Users/chenxk/Desktop/IntegerArray.txt",std::ios::in);
    std::cout<<file.is_open();
    

    std::vector<int> result(200000);
    
    int n = 0,temp;
    while(file>>temp){
        result[n] = temp;
        n++;
        //if(n == vol)
        //    result.resize(vol *=2);
    }
    result.resize(n);
    file.close();
    return result;
};

std::vector<int> CountInversionsByMergesort(std::vector<int> nums){
    // base case
    if(nums.size() ==  1)  return nums;
    
    // split into two subproblem
    std::vector<int> LeftPart,RightPart;
    LeftPart.assign(nums.begin(),nums.begin()+nums.size()/2);
    RightPart.assign(nums.begin()+nums.size()/2,nums.end());
    LeftPart = CountInversionsByMergesort(LeftPart);
    RightPart = CountInversionsByMergesort(RightPart);
    
    // merge back to one
    for(int i = 0, l = 0, r = 0; i<nums.size(); i++){
        if(l == LeftPart.size() && r != RightPart.size())
            nums[i] = RightPart[r++];
        else if(r == RightPart.size())
            nums[i] = LeftPart[l++];
        else if(LeftPart[l]>RightPart[r]){
            nums[i] = RightPart[r++];
            count += LeftPart.size()-l;
        }
        else
            nums[i] = LeftPart[l++];
    }
        
        return nums;
};

int main(){
    // get input array
    std::vector<int> OriginalArray   = getOriginalInput();
    std::cout<<"input success with "<<OriginalArray.size()<<" lines"<<std::endl;
    
    // count inversions using mergesort
    std::vector<int> TotalInversions = CountInversionsByMergesort(OriginalArray);
    std::cout<<count<<std::endl;
    
    return 0;
}
