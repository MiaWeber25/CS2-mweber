#include <iostream>

using namespace std;

#include "queue.h"
#include <stack>
#include <queue>

class Person {
  string first, last;
public:
  //need an empty parameter constructor in order for templated Queue class to compile
  Person(string newFirst="", string newLast="") {
    first = newFirst;
    last = newLast;
  }
  friend ostream & operator << (ostream &out, const Person &other) {
    return out << other.first << ", " << other.last << endl;
  }

};

int main() {
  Queue<Person> line; //because you templated the class --> tell it the data type
  Stack<Person> s; //implementation is the same for stacks and for queues
  Person karl("Karl", "Castleton"), kim("Kim", "Castleton"), john("John", "Doe");
  line.push(karl);
  s.push(karl);
  line.push(kim);
  s.push(kim);
  line.push(john);
  s.push(john);

  while(!line.isEmpty()) {
    Person p=line.pop();
    cout << p;
  }
  while (!s.isEmpty()) {
    Person p=s.pop();
    cout << p;
  }

  return 0;
}
