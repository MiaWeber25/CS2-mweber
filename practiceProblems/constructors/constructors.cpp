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

//encapsolution/seperation of concerns
  //allows you to hide elements in a class to avoid making mistakes with your data

class Complex {
  private:
    double r,i; //sets a new scope for these variables to within the {}
  public:
    Complex(double newR=0.0, double newI=0.0) {
      r=newR;
      i=newI;
    }
    void add(const Complex &other) { //set a rule for how to add complex numbers (add real values and then add imaginary values)
      //pass by reference (not because you need to modify other), but because you don't want to have to copy a bunch of data
      //you add const so that you cant't modify other, but you still don't have to copy data
      r+=other.r;
      i+=other.i; //you can access r and i even though they are private because anyone's r and i are available because they are in scope Complex
    }
    void multiply(const Complex &other) {
      //FOIL
      double tr=r*other.r-i*other.i; //modifying r so you want a temp value so line 47 doesn't use the wrong r value
      i=r*other.i+other.r*i;
      r = tr;
    }

    double getReal() { //getter
      return r;
    } //line 42: not using ofstream because it's at a higher level where you can output to a stream of any kind. INHERITENCE is the keyword here
    void print(ostream &theStream = cout) { //if you want to modify the steam then you need to pass by reference not making another copy
      //=cout would set the default stream as cout
      theStream << "r: " << r << "i: " << i << endl;
    }
};
  //getters and setters as well (members in class)
  //sometimes you won't even see private: because private is the default so you only need to specify public

  //print to another stream too: IN MAIN, assuming a print member of Complex class
int main() {
  Complex c;
  Complex b(M_PI);


  ofsteam out;
  out.open("MyFile.dat");

  c.print(); //this would print to the console (because it's the default when no argument passed)
  b.print();

  b.print(out); //this would print to the file (because you are passing out as an argument)
  c.print(out);

  c.add(Complex(1.0, 1.0));
  c.multiply(b);

  out.close()
}