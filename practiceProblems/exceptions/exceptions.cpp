
#include <iostream>

using namespace std;

class StackException {
public:
  virtual void describe(ostream &out) { //subcalsses are allowed to rewrite this function (virtual keyword)
    out << "Stack Exception" << endl;
  }
};

class EmptyStackException: public StackException {
public:
  void describe(ostream &out) {
    out << "Empty Stack Exception" << endl;
  }
};

class StackOverflowException: public StackException {
public:
  void describe(ostream &out) {
    out << "Stack Overflow Exception" << endl;
  }
};

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
  bool isEmpty();
  bool isFull();
};

  bool Stack::isEmpty() {
    return position==MAXSTACK-1;
  }
  bool Stack::isFull() {
    return position==-1;
  }

//implementation of the class  (usually prototype and implementation are in seperate files)
//largest numbers are on the bottom. Lowest floor = largest index
Stack::Stack() {
  position = MAXSTACK-1; //start with the largest number. *element 999*
}

void Stack::push(double x) {
  if (!isFull()) {
    values[position] = x;
    position--; //put the new one right above it (stack the plates) *element 998*
  } else throw StackOverflowException();
}

double Stack::pop() {
  if (!isEmpty()) {
    position++;
    return values[position];
  }
  throw EmptyStackException();
  //return 0.0;//this is the motivation for exceptions. You want to return an error, but you have to return a double here...
  //instead of returning a 0, we want to throw an exception --> and then some part of the program has to catch it otherwise the program will terminate
}

double Stack::top() {
  return values[position+1]; //view the top available plate (it's a relative top)
}

int main() {
  Stack s;
  while (true) { //calculator implementation
    string input;
    cin >> input;
    try {
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
    } catch(StackException &e) { //because you added virtual above, you need to pass by reference (polymorphism)
        e.describe(cerr);
    }
  }
  return 0;
}
