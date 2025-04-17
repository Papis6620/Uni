#include <iostream>
#include <cmath>
using namespace std;


class TComplex {
    public:
        TComplex(double re = 0, double im = 0) : re(re), im(im) {} // zamień na definicję z inicjalizacją

        TComplex operator()(double re, double im) const{
            return TComplex(re, im);
        }
        TComplex operator+(const TComplex& other) const{
            return TComplex(re + other.re, im + other.im);
        }
        TComplex operator-(const TComplex& other) const{
            return TComplex(re - other.re, im - other.im);
        }
        TComplex operator*(const TComplex& other) const{
            double temp_re = re * other.re - im * other.im;
            double temp_im = im * other.re + re * other.im;
            return TComplex(temp_re, temp_im);
        }
        TComplex operator/(const TComplex& other) const{
            double mianownik = other.re * other.re + other.im * other.im;
            double temp_re = (re * other.re + im * other.im) / mianownik;
            double temp_im = (im* other.re - other.im * re) / mianownik;
            return TComplex(temp_re, temp_im);
        }
        friend ostream& operator<<(ostream& os, const TComplex& a){
            os << "(" << a.re << ", " << a.im << ")";
            return os;
        }
        TComplex conj() const{
            return TComplex(re, -im);
        }
        double abs() const{
            return sqrt(sqrt(re) + sqrt(im));

        }
    private:
        double re{0}, im{0};
};

int main(){

    TComplex obiekt(2,3);
    TComplex obiekt2(4,1);
    double wartosc = obiekt.abs();
    cout << "Sprzężenie zespolone liczby " << obiekt << " = " << obiekt.conj() << endl;
    cout << "Wartosc liczby "<< obiekt << " = " << wartosc << endl;
    cout << obiekt << " * " << obiekt2 << " = " << obiekt * obiekt2 << endl;
    cout << obiekt << " / " << obiekt2 << " = " << obiekt / obiekt2 << endl;
    return 0;
}