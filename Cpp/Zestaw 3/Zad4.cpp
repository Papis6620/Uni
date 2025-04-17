#include <iostream>
#include <cmath>
using namespace std;

int NWD(int a, int b){
    while(a != b){
        if(a > b){
            
            a -= b;
          
        }else{
            b -= a;
        }

    }
    return a;
}

int wykladnik(int a, int  b){
    int d = 1;
    while((d * a) % b != 1){
        d++;
    }
    return d;
}

int szyfrowanie(int n, int e, int liczba){
    int c = fmod(pow(liczba,e),n);
    return c;
}

int odszyfrowanie(int n, int d, int liczba){
    int wynik = 1;
    for(d; d > 0; d /= 2 )
    {
        if( d % 2 ) wynik = ( wynik * liczba ) % n;
        liczba = ( liczba * liczba ) % n; 
    }
    return wynik;
}

int main(){

    int p = 53, q = 71, liczba, d, wybor;
    int delta = (p-1) * (q-1);
    int n = p*q;
    int e = 2;

    do{
        cout << "1. Szyfrowanie liczby" << endl;
        cout << "2. Odszyfrowanie liczby" << endl;
        cin >> wybor;
    }while(wybor != 1 && wybor != 2);

    if(wybor == 1){
        cout << "Podaj liczbę do zaszyfrowania: " << endl;
        cin >> liczba;
        while(NWD(e,delta)!=1) e++;
        d = wykladnik(e, delta);
        liczba = szyfrowanie(n, e, liczba);
        cout << "Zaszyfrowana liczba: " << liczba << endl;
    }
    else{
        cout << "Podaj liczbę do zaszyfrowania: " << endl;
        cin >> liczba;
        while(NWD(e,delta)!=1) e++;
        d = wykladnik(e, delta);
        liczba = odszyfrowanie(n,d,liczba);
        cout << "Odszyfrowana liczba: " << liczba << endl;
    }
    return 0;
}