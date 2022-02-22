//no return type
class Complex {
  double r,i;

  Complex(double newR=0.0, double newI=0.0) {
    r=newR;
    i=newI;
  }
  //constructor goes here (see above)
};

Complex() {
  r=0.0;
  i=0.0;
}
Complex (double newR, double newI) { //you can overload the function just need different arguments
  r=newR;
  i=newI;
}

//YOU CAN ALSO SET DEFAULT VALUES:
Complex(double newR=0.0, double newI=0.0) {
  r=newR;
  i=newI;
}

//OPERATOR OVERLOADING:

class Complex {
  private:
    double r,i;
  public:
    Complex(double newR=0.0, double newI=0.0) {
      r=newR;
      i=newI;
    }

    //will return a complex number.
    //use operator keyword to led computer know that you want to overload an operator
    Complex operator +(const Complex &other) const {
      return Complex(r+other.r,i+other.i); //the command to make a new complex number
    }

    void add(const Complex &other) { //can't put const here, because then you couldn't modify (*this)
      (*this)=(*this)+other; //*this is a pointer to the thing that you are currently manipulating
    }

    Complex operator *(const Complex &other) const {
      return Complex(r*other.r-i*other.i,r*other.i*r+other.r*i);
    }

    Complex operator *(double scalar) const { //you can overload the operator again //use const so that you don't change the other paramater that is getting passed from the function below
      return Complex(r*scalar, i*scalar);
    }

    //want to do the scalar first?
    //friend operator. Don't use *this, let the programmer tell you what the arguments are explicitly. override the default way of putting *this as the first argument
    friend Complex operator *(double scalar, const Complex &other) {
      return other*scalar; //just switch the order to user the operator function from the other * operator function above (line 52)
    }

    void multiply(const Complex &other) { //we can now write this function in terms of the other multiplication function
      (*this)=(*this)*other; //you don't want to modify the origional or the other therefore you need another pointer
    }

    double getReal() {
      return r;
    }
    void print(ostream &theStream = cout) {
      theStream << "r: " << r << "i: " << i << endl;
    }
}

int main() {
  Complex c;
  Complex b(M_PI);
  Complex d,e;

  d=c+Complex(1.0,1.0); //the address of c becomes the address that is passed to *this
  e=c*d;

  ofsteam out;
  out.open("MyFile.dat");

  c.print();
  b.print();

  b.print(out);
  c.print(out);

  out.close()
}