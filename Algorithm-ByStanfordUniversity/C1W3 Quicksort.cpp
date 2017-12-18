//
//  C1W3 Quicksort.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 24/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <fstream>
#include <vector>
#include <iostream>

long count = 0;

std::vector<int> getOriginalArray(){
    // preallocation
    std::vector<int> result(20000);
    int n = 0;
    
    // read from file
    std::ifstream file;
    file.open("/Users/chenxk/Desktop/QuickSort.txt",std::ios::in);
    int temp = 0;
    while(file>>temp) result[n++] = temp;
    result.resize(n);
    
    // end of function
    file.close();
    return result;
};

// swap two element
void swap(std::vector<int> &nums, int i, int j){
    if(nums[i] == nums[j]) return;
    nums[i] ^= nums[j];
    nums[j] ^= nums[i];
    nums[i] ^= nums[j];
};

void quickSort(std::vector<int> &nums, int begin, int end, int method){
    //base case
    if(begin == end || begin == end + 1) return;
    
    // choose pivot
    int pivot;
    if(method == 1) pivot = nums[begin++];
    else{
        pivot = nums[end];
        swap(nums,begin++,end);
    }
    
    // partition
    int i = begin;
    for(int j = begin; j<end+1;j++)
        if(nums[j] < pivot) swap(nums,i++,j);
    
    // put pivot in the right place
    swap(nums,--begin,i-1);
    
    // count # of comparison
    count += end-begin;
    
    //for(int i = 0; i<nums.size();i++) std::cout<<nums[i]<<std::endl;

    // solve for subarray
        quickSort(nums,begin,i-2,method);
        quickSort(nums,i,end,method);
};

void quickSort(std::vector<int> &nums, int begin, int end){
    //base case
    if(begin == end||begin == end +1) return;
    
    // choose of pivot and swap the pivot with the first element
    int pivot, median = (begin+end)/2;
    if( (nums[median]-nums[begin])*(nums[median]-nums[end]) < 0)
        swap(nums, begin, median);
    else if( (nums[end]-nums[median])*(nums[end]-nums[begin]) <0)
        swap(nums, begin, end);
    pivot = nums[begin];

    // partition
    int i = begin+1;
    for(int j = begin+1; j<end+1;j++)
        if(nums[j] < pivot) swap(nums,i++,j);
    
    // put pivot in the right place
    swap(nums,begin,i-1);
    
    // count # of comparison
    count += end-begin;
    
    // solve for subarray
    quickSort(nums,begin,i-2);
    quickSort(nums,i,end);
    
};

int main(){
    // get file input
    std::vector<int> nums = getOriginalArray();
    
    int begin = 0, end = nums.size()-1;
    
    // choose method { method 1: use first element as pivot. method 2: use last element as pivot. method 3: use'median of three' as pivot}
    int method = 1;
    switch (method){
        case 1: std::cout<<"# of comparison using first element as a pivot: "<<std::endl; break;
        case 2: std::cout<<"# of comparison using last element as a pivot: "<<std::endl; break;
        case 3: std::cout<<"# of comparison using 'Median-of-three' element as a pivot: "<<std::endl; break;
        default: std::cout<<"Wrong method!"; goto endofprogram;
    }
    
    // sort by quicksort
    if(method != 3)
        quickSort(nums,begin,end,method);
    else
        quickSort(nums,begin,end);
    
    // print output
    std::cout<<"# of compare = "<<count<<std::endl;

endofprogram:
    return 0;
}
