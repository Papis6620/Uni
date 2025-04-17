#include<iostream>
#include<fstream>
using namespace std;

#define length = 100;

int main(){

    ifstream plik;
    string slowo, tekst;
    plik.open("plik.txt");
    if(!plik){
        cerr << "Nie znaleziono pliku!" << endl;
        exit(1);
    }

    while(!plik.eof()){
        
        getline(plik, slowo);
        tekst += slowo;
    }
    
    cout << tekst << endl;
    

}