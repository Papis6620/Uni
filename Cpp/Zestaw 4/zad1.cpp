#include <iostream>
#include <compare>
using namespace std;

class TKlasa{
    public:
        TKlasa(const char* C): str(C) {} //definicja z inicjalizacją

        const char* operator[](const char* s) const{  // operator []
            size_t ptr = str.find(s);
            if(ptr == string::npos){
                return nullptr;
            }
            return str.c_str() + ptr;
        }
        auto operator<=>(const TKlasa& other) const{ // operator <=>
            return str <=> other.str;
        }
    private:
        string str;
};

int main(){

    TKlasa text("Lorem Ipsum is simply");
    TKlasa text2("Lorem Ipsum is dummy");
    const char* ptr = text["simply"];
    const char* ptr2= text2["simply"];
    if(ptr == nullptr){
        cout << "Nie znaleziono szukanego ciągu" << endl;
    }else{
        cout << "Znaleziony ciąg 'simply' "  << endl; 
    }
    if(ptr2 == nullptr){
        cout << "Nie znaleziono szukanego ciągu" << endl;
    }else{
        cout << "Znaleziono ciąg 'dummy' " << endl; 
    }

    auto wynik = text <=> text2;
    if(wynik < 0) cout << "text < text2"<< endl;
    else if(wynik == 0) cout << "text = text2"<< endl;
    else cout << "text > text2"<< endl;

    return 0;
}