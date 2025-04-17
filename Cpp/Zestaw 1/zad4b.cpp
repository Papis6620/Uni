#include <iostream>

using namespace std;

unsigned long long fib(int k){      //funkcja obliczająca wyraz ciągu Fibonnaciego iteracyjnie
    if(k <= 1) return k;
    if(k > 1){
        unsigned long long fib1 = 0;
        unsigned long long fib2 = 1;
        unsigned long long temp;
        for(int i = 2; i <= k; i++){
            temp = fib2;
            fib2 = fib1 + fib2;
            fib1 = temp;
        }
    return fib2;
    }
    return 0;
}

int main(){
    unsigned long long k = 50;
    for(unsigned long long i = 0; i<=k ; i++){
        cout << i << " wyraz ciągu = " << fib(i) << endl;
}
    return 0;
}   