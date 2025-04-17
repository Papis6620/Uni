#include <iostream>
#include <iomanip>

using namespace std;

int main(){

    int bok_z;
    int bok_w;
    do{
        cout << "Podaj rozmiar zewnętrzny: " << endl;
        cin >> bok_z;
        cout << "Podaj rozmiar wewnętrzny: " << endl;
        cin >> bok_w;
        if((bok_z % 2) != (bok_w % 2)){
            cout << "Obie wartości muszą być parzyste lub nie parzyste" << endl;
        }else if(bok_z <= bok_w){
            cout << "Rozmiar zewnętrzny musi być większy od rozmiaru wewnętrznego" << endl;
        }
    }while(bok_z <= bok_w || bok_z < 1 ||(bok_z % 2) != (bok_w % 2));

    for(int i = 0; i < bok_z; i++){

        if(i < ((bok_z - bok_w)/2) || i >= (((bok_z - bok_w)/2)+bok_w)){
            cout << setfill('*') << setw(bok_z) << "" << endl;
        }else{
            cout << setfill('*') << setw((bok_z-bok_w)/2) << "" 
            << setfill(' ') << setw(bok_w) << "" 
            << setfill('*') << setw((bok_z-bok_w)/2) << "" << endl;
        }

    }



    return 0;

}