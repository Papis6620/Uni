#include<iostream>
#include<string>
using namespace std;
string arab_rzym(int liczba){
    int arab[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string rzym[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string wynik = "";
    int i = 0;
    while(liczba != 0){
        while(liczba >= arab[i]){
            wynik += rzym[i];
            liczba -= arab[i];
        }
        i++;
    }
    return wynik;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout << "Nie podano liczby jako parametr wywołania programu" << endl;
        exit(1);
    }
    int liczba = stoi(argv[1]);
    if(liczba > 3999 || liczba < 1){
        cout << "Podano złą liczbę" << endl;
        exit(1);
    }
    
    cout << "Liczba rzymska: " << arab_rzym(liczba) << endl;
    return 0;
}