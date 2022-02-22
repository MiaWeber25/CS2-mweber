#include <iostream>
#include <math.h>

using namespace std;

//fib   = fib  + fib
//   n+1     n      n-1

//fib =1
//   1

//fib  =1
//   2
//needs a firm stopping point and needs to call itself (could call another function that calls it)
int fib(int n) {
  if(n<=1) return 1;
  return fib(n-1) + fib(n-2);

}

double f( double x) { //f(x)
  return x;
}

double integrate(double a, double b, double epsilon=0.001) { //integrate f from a to b
  double A2=0.5*(f(a))+f(b)*(b-a);
  double m=(a+b)/2.0;
  double A3=0.5*(f(a)+f(m))*(m-a) + 0.5*(f(m)+f(b))*(b-m);

  if (fabs(A2-A3)<epsilon) return A3;
  else return integrate(a,m,epsilon/2.0)+integrate(m,b, epsilon/2.0); //if they aren't equal, then we integrate smaller pieces
}

int main() {

  //cout << fib(4) << endl;
  cout << integrate(0.0,1.0);
  return 0;
}
