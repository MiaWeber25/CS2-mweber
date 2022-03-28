//vocab: abstract, pure virtual (function or class), concrete

#include <iostream>
#include <math.h>
#include <queue>
//everything done recurssivly can also be done itteratively --> this shows that
using namespace std;

//function where everything is defined --> concrete class (constrast this with abstract class)
//vocab: concrete, abstract, pure virtual
class Functor {
public:
  virtual double f(double x) =0; //pure virtual function --> abstract class. class does not have a default implementation of function f
};


class IntegrationRequest {
  double a,b, epsilon;
  queue<IntegrationRequest *> sections;
public:
  void setParams(double newA, double newB, double newEpsilon) {
    a = newA;
    b = newB;
    epsilon = newEpsilon;
  }
  void copyFrom(IntegrationRequest other) {
    a=other->a;
    b=other->b;
    epsilon=other.epsilon;
  }

  double integrate(Functor *integrand) { //integrate f from a to b
    sections.push(*this);
    double sum=0.0;
    while (sections.size()>0) {
      copyFrom(sections.front());
      sections.pop();
      double fa=integrand->f(a);
      double fb=integrand->f(b);
      double A2=0.5*(fa+fm)*(b-a);
      double m=(a+b)/2.0;
      double fm=integrand->f(m);
      double A3=0.5*(f(a)+f(m))*(m-a) + 0.5*(f(m)+f(b))*(b-m);

      if (fabs(A2-A3)<epsilon) sum+=A3;
      else //return integrate(a,m,epsilon/2.0)+integrate(m,b, epsilon/2.0); //if they aren't equal, then we integrate smaller pieces
      {
        IntegrationRequest first;
        first.setParams(a,m,epsilon/2.0);
        sections.push(first);

        IntegrationRequest second;
        second.setParams(m,b,epsilon/2.0);
        sections.push(second);
      }
    }
    return sum;
}
};

class Easy:public Functor {
  double f(double x) {return x*x; }
  //line above is a concrete implementation of function f
};

class Hard:public Functor {
  double f(double x) {
    return x*sin(x)/exp(x);
  }
};

int main() {
  Easy e;
  IntegrationRequest result;
  result.setParams(0,1,0.001);

  cout << result.integrate(&e) << endl;
  return 0;
}
