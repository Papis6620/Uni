#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class BigInt{

public:
    BigInt(const string& number = "0"){
        value = number;
        delLeadingZeros();
        
    }

    BigInt& operator=(const BigInt& other){
        value = other.value;
        return *this;
    }

    BigInt add(const BigInt& other) const{
        
        string result;
        int carry = 0;
        int i = value.length() - 1;
        int j = other.value.length() - 1;

        while(i >= 0 || j >= 0 || carry != 0){
            int sum = carry;
            if(i >= 0){
                sum += value[i] - '0';
                i--;
            }
            if(j >= 0){
                sum += other.value[j] - '0';
                j--;
            }
            result.insert(0, 1, sum % 10 + '0');
            carry = sum / 10;
        }
        return BigInt(result);
    }
    void print() const{
        cout << value << endl;
    }
    BigInt substract(const BigInt& other) const{
        string result;
        if(isLessThan(other)){
            cout << "-";
            return other.substract(*this);
        }else{
            int borrow = 0;
            int diff;
            int i = value.length() - 1;
            int j = other.value.length() - 1;
            while(i >= 0 || j >= 0){
                diff = borrow;
                if(i >= 0){
                    diff += value[i] - '0';
                    i--;
                }
                if(j >= 0){
                    diff -= other.value[j] - '0';
                    j--;
                }
                if(diff < 0){
                    borrow = -1;
                    diff += 10;
                }else{
                    borrow = 0;
                }
                result.insert(0, 1, diff + '0');
            }
        }
        return BigInt(result);
    }
    bool isLessThan(const BigInt& other) const {
    if (value.length() < other.value.length()) {
        return true;
    } else if (value.length() > other.value.length()) {
        return false;
    } else {
        for (int i = 0; i < value.length(); i++) {
            if (value[i] < other.value[i]) {
                return true;
            } else if (value[i] > other.value[i]) {
                return false;
            }
        }
    }
    return false;
}
private:
    string value;

    void delLeadingZeros(){
        int i = 0;
        while(i < value.length()-1 && value[i] == '0'){
            i++;
        }
        value.erase(0, i);
    }
};

int main(){

    string num1, num2;
    int choice;
    cout << "Podaj 1. liczbe:" << endl;
    cin >> num1;
    cout << "Podaj 2. liczbe:" << endl;
    cin >> num2;
    BigInt a(num1);
    BigInt b(num2);
    cout << "1. Dodaj liczbe 1. do liczby 2" << endl;
    cout << "2. Odejmij liczbe 1. do liczby 2" << endl;
    cin >> choice;
    if(choice == 1){
        BigInt c = a.add(b);
        c.print();
    }
    else if(choice == 2){
        BigInt c = a.substract(b);
        c.print();
    }else{
        cout << "Podano złą liczbe";
        exit(1);
    }
    return 0;

}