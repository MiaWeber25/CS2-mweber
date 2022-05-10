#include <iostream>
#include <cmath>

using namespace std;

//fib    = fib + fib
//	 n+1	  n		n-1
//  fib  =1
//     1
//  fib  =1
//	   2

int fib(int n) {
	if (n<=2) return 1;
	return fib(n-1)+fib(n-2);
}

double f(double x) {
  return x*sin(x)/exp(x);
}

double integrate(double a,double b,double epsilon=0.001) {
  double A2=0.5*(f(a)+f(b))*(b-a);
  double m=(a+b)/2.0;
  double A3=0.5*(f(a)+f(m))*(m-a)+
		    0.5*(f(m)+f(b))*(b-m);
  if (fabs(A2-A3)<epsilon) return A3;
  else return integrate(a,m,epsilon/2.0)+integrate(m,b,epsilon/2.0);
}

int main() {
	cout << integrate(1.,2.) << endl;
	return 0;
}
