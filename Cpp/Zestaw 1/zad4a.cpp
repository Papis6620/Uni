#include <iostream>

using namespace std;

unsigned long long fib(int k){    //funkcja obliczająca wyraz ciągu Fibonnaciego rekurencyjnie
    if(k == 0) return 0;
    if(k == 1) return 1;
    if(k > 1) return fib(k-1) + fib(k-2);
    return 0;
}

int main(){
    unsigned long long k = 30;
    for(unsigned long long i = 0; i<=k ; i++){
        cout << i << " wyraz ciągu = " << fib(i) << endl; 
    }
    return 0;
}   