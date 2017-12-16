//
//  C1W1 Karatsuba Multification.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 14/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <iostream>

int* KaratsubaMultiple(int * a, int * b, int la, int lb) {
    // assumption: the length of a/b are both 2^n

    int* result = new int[la + lb]();

    // base case
    if(la == 1 || lb == 1){
        if(a[0] * b[0] > 9) {
            result[1] = a[0] * b[0] - 10;
            result[0] = 1;
        } else {
            result[1] = a[0] * b[0];
            result[0] = 0;
        }

        return result;
    }
        
    // divide a,b into two half
    int* a1 = a;
    int* a2 = a + la / 2;
    int* b1 = b;
    int* b2 = b + lb / 2;

    // calculate a1b1 a2b2 (a1+b1)(a2+b2)                    //three multiple
    int* a1b1 = KaratsubaMultiple(a1,b1,la/2,lb/2);
    int* a2b2 = KaratsubaMultiple(a2,b2,la/2,lb/2);
    int* a1b2 = KaratsubaMultiple(a1,b2,la/2,lb/2);
    int* a2b1 = KaratsubaMultiple(a2,b1,la/2,lb/2);

    //calculate final result
    for(int i = 0; i < (la+lb)/2; i++){                     // need a function to add array
        result[i] += a1b1[i];
        result[i+(la+lb)/2] += a2b2[i];
        result[i+la/2] += a1b2[i] + a2b1[i];
    }
    for(int i = la+lb-1, count = 0; i>-1; i--) {
        result[i] += count;
        if(result[i]>9){
            count = result[i]/10;
            result[i] %= 10;
        }
        else count = 0;
    }

    delete [] a1b1;
    delete [] a1b2;
    delete [] a2b1;
    delete [] a2b2;
    return result;
}

int main(){         // write a class contain {array,array lenth}
    // get input data in strings
    std::string num1,num2;
    getInputData(num1, num2);
    // store data into array
    int *Var1 = convertStringToArray( num1 );
    int *Var2 = convertStringToArray( num2 );

    // calculation of two numbers
    int *result = KaratsubaMultiple(Var1, Var2, num1.length(), num2.length());

    // output
    for(int i = 0; i<len1+len2;i++) std::cout<<result[i];   // combine output in class
    std::cout<<std::endl;

    // clear memory
    delete [] Var1;
    delete [] Var2;
    delete [] result;
    return 0;
}

void getInputData(std::string &num1, std::string &num2) {
    std::cout<<"Type the first number:"<<std::endl;
    std::cin>>num1;
    std::cout<<"Type the second number:"<<std::endl;
    std::cin>>num2;
}
int* convertStringToArray(std::string num) {
    int len= num.length();

    int *Var = new int[len];
    for(int i = 0; i < len; i++){
        Var[i] = num[i]-'0';
    }
    return Var;
}

