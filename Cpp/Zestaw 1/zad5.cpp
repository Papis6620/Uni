#include <iostream>

using namespace std;

unsigned long long fib(int n){
    unsigned long long tab[100];
    tab[0] = 0;
    tab[1] = 1;
    for(int i = 2; i <= n; i++){
        tab[i] = tab[i-1] + tab[i-2];
    }
    return tab[n];
}

auto main() -> int{

    unsigned long long k = 50;
    cout << fib(k) << endl;
    return 0;
}