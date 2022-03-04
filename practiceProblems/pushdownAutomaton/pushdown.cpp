//pushdown Automaton && post fix calculator (rpn)
//stack first in first out
//que last in last out

#include <iostream>

using namespace std;

//prototype for the class
class Stack { //need some type (ex: double)
  const static int MAXSTACK = 1000;
  double values[MAXSTACK];
  int position;
public:
  Stack(); //just prototype your member functions here - would implementation in another file
  void push(double x);
  double pop();
  double top();
};

//implementation of the class  (usually prototype and implementation are in seperate files)
//largest numbers are on the bottom. Lowest floor = largest index
Stack::Stack() {
  position = MAXSTACK-1; //start with the largest number. *element 999*
}

void Stack::push(double x) {
  values[position] = x;
  position--; //put the new one right above it (stack the plates) *element 998*
}

double Stack::pop() {
  position++;
  return values[position];
}

double Stack::top() {
  return values[position+1]; //view the top available plate (it's a relative top)
}

int main() {
  Stack s;
  while (true) { //calculator implementation
    string input;
    cin >> input;
    if (input == "+") {
      double a = s.pop();
      double b = s.pop();
      s.push(a+b);

    } if (input == "-") {
        double a = s.pop();
        double b = s.pop();
        s.push(b-a);

    } else if (input == "#") {
        cout << s.top() << endl;
    }

    else {
      try {
        double x = stod(input); //will throw an exception. Need to implement a catch too (below) google to find exception name
        s.push(x); //if it's a number, add it to the stack
      } catch(exception &e) { //you want exceptions for operators, dividing by 0s, etc.
    }
    }
  }
  return 0;
}
