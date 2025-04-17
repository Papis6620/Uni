#include<iostream>
#include<filesystem>

using namespace std;

int main(){

    string path;
    int error = 1;
    do{
        cout << "Podaj scieżkę do katalogu" << endl;
        cin >> path;
        if(!filesystem::exists(path)){ 
            cout << "Podana ścieżka nie istnieje" << endl;
        }
    }
    while(!filesystem::exists(path));
    
    for(const auto& entry : filesystem::directory_iterator(path)){
        if(entry.is_regular_file()){
            cout << entry.path().filename() << " rozmiar: " << entry.file_size() << " B" << endl;
            error = 0;
        }
    }
    
    if(error){
        cout << "Brak normalnych plików w tym katalogu" << endl;
    }
    return 0;
}
    
