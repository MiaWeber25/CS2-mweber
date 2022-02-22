#include <iostream>
#include <math.h>
#include <fstream> 

using namespace std;

class Complex {
  private:
    double r,i;
  public:
    Complex(double newR=0.0, double newI=0.0) {
      r=newR;
      i=newI;
    }

    Complex operator +(const Complex &other) const {
      return Complex(r+other.r,i+other.i);
    }

    void add(const Complex &other) {
      (*this)=(*this)+other;
    }

    Complex operator *(const Complex &other) const {
      return Complex(r*other.r-i*other.i,r*other.i*r+other.r*i);
    }

    Complex operator *(double scalar) const {
      return Complex(r*scalar, i*scalar);
    }
    Complex operator /(double scalar) const {
      return Complex(r/scalar, i/scalar);
    }
    Complex operator -(const Complex &other) const {
      return Complex(r-other.r, i-other.i);
    }

    friend Complex operator *(double scalar, const Complex &other) {
      return other*scalar;
    }

    void multiply(const Complex &other) {
      (*this)=(*this)*other;
    }

    double getReal() {
      return r;
    }
    double getImaginary() {
      return i;
    }
    double magnitute() {
      return sqrt(r*r+i*i); //pythagorian
    }
    void print(ostream &theStream = cout) {
      theStream << "r: " << r << "i: " << i << endl;
    }
};

int main() {
  const int MAXPOINTS=100;
  const int MAXTRIES=100;
  Complex ul(-2.0,-2.0);
  Complex lr(2.0,2.0);
  Complex dp=(ul-lr)/MAXPOINTS;
  //dp is the change in the change in the real and the imaginary (change in point)
  for (int x=0; x<MAXPOINTS; x++) {
    for (int y=0; y<MAXPOINTS; y++) {
      Complex C=ul-Complex(dp.getReal()*x,dp.getImaginary()*y); //took the upperleft point and added x amount in the real direction and y amount in the imaginary direction
      Complex Z;
      int n; //change the scope of n
      for (n=0; n<MAXTRIES; n++) { //need to determine if the number escaped the set and ran to infinity (bound to 2 and -2)
        Z=Z*Z+C;
        if (Z.magnitude() >2.0) break; //using the bounds as -2 and 2 as the radius (see magnitude above)
      }
      //determine if the value escaped the set within the alloted number of MAXTRIES
      //this represents how many tries it took for the program to identify that the number has escaped the set
      if (n==MAXTRIES) cout << '#';
      else if (Z>=50) cout << '0';
      else if (Z>=25) cout << '""';
      else if (Z>=12) cout << '.';
      else cout << ' ';
    }
    cout << endl;
  }
}