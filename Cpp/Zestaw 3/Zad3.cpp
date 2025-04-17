#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    int i = 0;
    int j = 0;
    int A[25][25];
    int B[25][25];
    int C[25][25];
    string temp1, temp2, liczba;
    ifstream plik1("macierzA.txt");
    ifstream plik2("macierzB.txt");
    ofstream plik3("macierzC.txt");

    if(!plik1 || !plik2){
        cerr << "Nie ma plików" << endl;
        exit(1);
    }


    while(!plik1.eof()){
        j = 0;
        getline(plik1, temp1);
        for(int k = 0; k < temp1.length(); k++){
            liczba = "";
            while(temp1[k] != ' ' && temp1[k]!= '\n'){
                liczba += temp1[k];
                k++;
            }
            A[i][j] = stoi(liczba);
            j++;

        }
        i++;
    }
    int A_kol = j;
    int A_wiersz = i;
    i = 0;
    while(!plik2.eof()){
        j = 0;
        getline(plik2, temp2);
        for(int k = 0; k < temp2.length(); k++){
            liczba = "";
            while(temp2[k] != ' ' && temp2[k]!= '\n'){
                liczba += temp2[k];
                k++;
            }
            B[i][j] = stoi(liczba);
            j++;

        }
        i++;
    }
    int B_kol = j;
    int B_wiersz = i;
    if(A_kol != B_wiersz){
        cout << "Podano nieprawidołowe macierze" << endl;
        exit(1);
    }
    int suma;
    for(i = 0; i < A_kol; i++){
        for(j = 0; j < B_kol; j++){
            suma = 0;
            for(int k = 0; k < B_wiersz;k++){
               suma += A[i][k]*B[k][j];
            } C[i][j] = suma;
        }
    }

    for(i = 0; i < A_wiersz; i++){
        for(j = 0; j < B_kol; j++){
            plik3 << C[i][j] << " ";
        }
        plik3 << endl;
    }
    cout << "Zapisano wynik mnożenia macierzy A przez B do pliku" << endl;
    return 0;
}