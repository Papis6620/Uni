#include <iostream>
using namespace std;

int main(){
    int error = 0;
    string str;
    cout << "Podaj tekst, żeby sprawdzić czy jest palindromem:" << endl;
    getline(cin,str); 

    for(int i = 0; i < str.length();i++){
        str[i] = tolower(str[i]);
    }
    int j = str.length()-1;
    for(int i = 0; i < j;i++){
        if(str[i] == ' ')i++;
        if(str[j] == ' ')j--;
        if(str[i] != str[j]){
            error = 1;
            cout << "podany tekst nie jest palindromem" << endl;
            break;
        }
        j--;
        }
    
    if(error == 0){
        cout << "podany tekst jest palindromem" << endl;
    }
    
    return 0;
}