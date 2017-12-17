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


int merge(int* array, int* helper, int n) {
    int l = 0;
    int r = n/2;
    int i = 0;
    int count = 0;
    while (l < n/2 && r < n) {
        if (array[l] <= array[r]) {
            helper[i++] = array[l++];
        } else {
            helper[i++] = array[r++];
            count += n/2 - l;
        }
    }
    while (l < n/2) {
        helper[i++] = array[l++];
    }
    for (int j = i-1; j >= 0; j--) {
        array[j] = helper[j];
    }
    return count;
}
int countInversionsByMergesort(int* array, int* helper, int n) {
    // base case
    if (n <= 1)  return 0;
    
    // split into two subproblem
    int count_left = countInversionsByMergesort(array, helper, n/2);
    int count_right = countInversionsByMergesort(array + n/2, helper, n - n/2);
    
    // merge back to one
    int count = merge(array, helper, n);

    return (count + count_left + count_right);
};

std::vector< int > getOriginalInput() {
    // assumption: input size < 200000
    std::ifstream file;
    file.open( "/Users/chenxk/Desktop/IntegerArray.txt", std::ios::in);
    std::cout << file.is_open();
    
    std::vector< int > result(200000);
    
    int n = 0;
    int temp;
    while (file >> temp) {
        result[n] = temp;
        n++;
    }
    result.resize(n);
    file.close();
    return result;
};

int* convertToArray(std::vector< int > array) {
    int n = array.size();
    int* result = new int[n];
    for (int i = 0; i < n; i++) {
        result[i] = array[i];
    }
    return result;
};

int main() {
    // get input array
    std::vector< int > OriginalArray = getOriginalInput();
    int n = OriginalArray.size();
    std::cout << "input success with " << n << " lines" << std::endl;
    int* array = convertToArray( OriginalArray );
    
    // count inversions using mergesort
    int* helper = new int[n];
    int count = countInversionsByMergesort(array, helper, n);
    std::cout << count << std::endl;

    delete [] array;
    delete [] helper;
    return 0;
};
