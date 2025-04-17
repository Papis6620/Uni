#include <iostream>

using namespace std;

class A{
    int i;
    public:
        A(int n=0) : i(n) {}
        A operator+(){
            return *this;
        }
        A operator-(){
            return A(-i);
        }
        A operator+ (const A& a) const {
            return A(i + a.i);
        }
        A operator- (const A& a) const {
            return A(i - a.i);
        }
        A& operator++(){
            ++i;
            return *this;
        }
        A operator++(int){
            A temp(*this);
            ++i;
            return temp;
        }
        A& operator--(){
            --i;
            return *this;
        }
        A operator--(int){
            A temp(*this);
            --i;
            return temp;
        }


        friend ostream& operator<<(ostream& os, const A& a){
                os << a.i;
                return os;
        }
};


int main(){

    A a(4);
    A b(10);

    cout << "Wartość początkowa: " << a << endl;
    cout << "wartość używająć a++: ";
    cout << a++ << endl;
    a = 4;
    cout << "wartość używająć ++a: ";
    cout << ++a << endl;
    cout << "a + b = ";
    cout << a + b << endl;
    cout << "a - b = ";
    cout << a - b << endl;
    cout << "-a = ";
    cout << -a << endl;
    cout << "+a = ";
    cout << +a << endl;
}