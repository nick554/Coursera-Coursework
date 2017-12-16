//
//  C1W1 Karatsuba Multification.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 14/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <iostream>


void getInputData(std::string &num1, std::string &num2) {
    std::cout << "Type the first number:" << std::endl;
    std::cin >> num1;
    std::cout << "Type the second number:" << std::endl;
    std::cin >> num2;
}

int* convertStringToArray(std::string num) {
    int len= num.length();

    int *Var = new int[len];
    for(int i = 0; i < len; i++){
        Var[i] = num[i]-'0';
    }
    return Var;
}

int* addTwoHalf(int* a, int* b, int l) {
    int* result = new int[l];
    for (int i = 0; i < l; i++) {
        result[i] = a[i] + b[i];
    }
    return result;
}
int* addUp(int* a, int* b, int* c, int l) { 
    int* result = new int[2 * l];
    for (int i = 0; i < l; i++) {
        result[i] = a[i];
        result[i + l] = b[i]; 
    }
    int count = 0;
    for (int i = l-1; i > -1; i--) {
        int j = i + l/2;
        result[j] += c[i] - a[i] - b[i] + count;
        if (result[j] > 9) {
            count = 1;
            result -= 10;
        } else if (result[j] > 0) {
            count = 0;
        } else {
            count = -1;
            result += 10;
        }
    }
    return result;
}
int* KaratsubaMultiple(int * a, int * b, int la, int lb) {
    // assumption: the length of a/b are both 2^n

    // base case
    if(la == 1 || lb == 1){
        int* result = new int[la + lb];
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
    int* ah = addTwoHalf(a1, a2, la / 2);
    int* bh = addTwoHalf(b1, b2, lb / 2);

    // calculate a1b1 a2b2 (a1+b1)(a2+b2)                    //three multiple
    int* a1b1 = KaratsubaMultiple(a1,b1,la/2,lb/2);
    int* a2b2 = KaratsubaMultiple(a2,b2,la/2,lb/2);
    int* ahbh = KaratsubaMultiple(ah,bh,la/2,lb/2);

    //calculate final result
    int* result = addUp(a1b1, a2b2, ahbh, la);

    delete [] a1b1;
    delete [] a2b2;
    delete [] ahbh;
    delete [] ah;
    delete [] bh;
    return result;
}

int main(){
    // get input data in strings
    std::string num1,num2;
    getInputData(num1, num2);
    // store data into array
    int *Var1 = convertStringToArray( num1 );
    int *Var2 = convertStringToArray( num2 );

    // calculation of two numbers
    int *result = KaratsubaMultiple(Var1, Var2, num1.length(), num2.length());

    // output
    for(int i = 0; i < num1.length() + num2.length(); i++) {
	std::cout << result[i];
    }
    std::cout<<std::endl;

    // clear memory
    delete [] Var1;
    delete [] Var2;
    delete [] result;
    return 0;
}
