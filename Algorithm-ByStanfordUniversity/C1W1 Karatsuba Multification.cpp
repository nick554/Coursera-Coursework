//
//  C1W1 Karatsuba Multification.cpp
//  Algorithm-Stanford-U
//
//  Created by S BRAIN on 14/10/2017.
//  Copyright © 2017 Xiaokong Chen. All rights reserved.
//

#include <iostream>

int* KaratsubaMultiple(int * a, int * b,int la, int lb){    //a,b length = 2^n
                                                            //can write a function to copy array
    int* result = new int[la+lb]();
    if(la == 1||lb ==1){
        if(a[0]*b[0]>9) {
            result[1] = a[0]*b[0]-10;
            result[0] = 1;}
        else{
            result[1] = a[0]*b[0];
            result[0] = 0;}
        
        return result;
    }
        
    // divide a,b into two half                             //can write a function to copy array
    int* a1 = new int[la/2];    for(int i = 0;i<la/2;i++) {a1[i] = a[i];std::cout<<a1[i];} std::cout<<std::endl;
    int* a2 = new int[la/2];    for(int i = 0;i<la/2;i++) a2[i] = a[i+la/2];
    int* b1 = new int[lb/2];    for(int i = 0;i<lb/2;i++) b1[i] = b[i];
    int* b2 = new int[lb/2];    for(int i = 0;i<lb/2;i++) b2[i] = b[i+lb/2];
    
    //calculate a1b1 a2b2 (a1+b1)(a2+b2)                    //three multiple
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

    delete [] a1;
    delete [] a2;
    delete [] b1;
    delete [] b2;
    delete [] a1b1;
    delete []  a1b2;
    delete []  a2b1;
    delete []  a2b2;
    return result;
}

int main(){         // write a class contain {array,array lenth}
// Input Data in strings
    std::string num1,num2;
    std::cout<<"Type the first number:"<<std::endl;
    std::cin>>num1;
    std::cout<<"Type the second number:"<<std::endl;
    std::cin>>num2;

//storage data in to array
    int len1= num1.length(),len2= num2.length();

    int *Var1 = new int[len1];
    for(int i = 0; i < len1; i++){
        Var1[i] = num1[i]-'0';
        std::cout<<Var1[i];
    }
    std::cout<<std::endl;
    
    int *Var2 = new int[len2];
    for(int i = 0; i < len2; i++){
        Var2[i] = num2[i]-'0';
        std::cout<<Var2[i];
    }
    std::cout<<std::endl;
    
//calculation of two numbers
    int *result = KaratsubaMultiple(Var1,Var2,len1,len2);
    
    for(int i = 0; i<len1+len2;i++) std::cout<<result[i];   // combine output in class
    std::cout<<std::endl;
    
    delete [] Var1;
    delete [] Var2;
    delete [] result;
    return 0;
}
