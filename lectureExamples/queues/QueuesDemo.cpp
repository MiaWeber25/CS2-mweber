#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#include "Queue.h"
#include "Stack.h"

class Person {
	string first,last;
	public:
	Person(string newFirst="",string newLast="") {
		setInfo(newFirst,newLast);
	}
	void setInfo(string newFirst="",string newLast="") {
		first=newFirst;
		last=newLast;
	}
	friend ostream & operator << (ostream &out,const Person &other) {
		return out << other.first << ',' << other.last<<endl;
	} 
};


int main() {
  Queue<Person> line;
  queue<Person> line2;
  Stack<Person> s;
  Person karl("Karl","Castleton"),kim("Kim","Castleton"),john("John","Doe");
  line.push(karl);
  line.push(karl);
  s.push(karl);
  line.push(kim);
  s.push(kim);
  line.push(john);
  s.push(john);
  while (!line.isEmpty()) {
	  Person p=line.pop();
	  cout << p;
  }
  while (!s.isEmpty()) {
	  Person p=s.pop();
	  cout << p;
  }
  return 0;
}
