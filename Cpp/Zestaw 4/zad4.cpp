#include <iostream>

using namespace std;
class A {
public:
    void foo() { cout << "Wypisane z klasy A" << endl; }
};
class TSmartPtr{
    A *fp { nullptr };
    A* fTable[5] { nullptr };
    int fUse { 0 };
    public:
        TSmartPtr(A* ptr = nullptr): fp(ptr) {}
        A* operator->(){
            fTable[fUse] = fp;
            fUse = (++fUse) % 5;
            return fp;
        }
        A& operator*(){
            return *(operator->());
        }
};

int main(){
    A obiekt;
    TSmartPtr ptr = &obiekt;
    ptr->foo();
    (*ptr).foo();
    return 0;

}