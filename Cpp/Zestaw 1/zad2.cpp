#include <iostream>

using namespace std;

int main(){
    char ciag1[50];
    char ciag2[50];
    int error = 0;
    cout << "Podaj pierwszy ciąg znakow: \n"; 
    cin.getline(ciag1,100);
    cout << "Podaj drugi ciąg znakow: \n"; 
    cin.getline(ciag2,100);
   
    //zmienienie wszystkich liter na małe
    for(int i = 0; i < 100; i++){
        if(isalpha(ciag1[i]) && isalpha(ciag2[i])){
            ciag1[i] = tolower(ciag1[i]);
            ciag2[i] = tolower(ciag2[i]);
        }
    }
    //prównanie ciągów znaków
    for(int i = 0; i < 100; i++){
        if(!isalpha(ciag1[i]) && !isalpha(ciag2[i]) && ciag1[i]!= ' ' && ciag2[i]!= ' '){
            break;
        }else{
            if(ciag1[i] != ciag2[i]){
                cout << "ciagi nie sa takie same" << endl;
                error = 1;
                break;
        }
        } 
    }
    if(error == 0){
        cout << "ciagi sa takie same" << endl;
    }
    return 0;
}