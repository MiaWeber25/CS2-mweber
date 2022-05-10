#include "Queue.h"

#include <iostream>

using namespace std;

void Exception::describe(ostream &out) {
	  out << "Storage Exception" << endl;
  }


  void EmptyException::describe(ostream &out) {
	  out << "Empty Storage Exception" << endl;
  }


  void OverflowException::describe(ostream &out) {
	  out << "Storage Overflow Exception" << endl;
  }

// Karl's To-Do
//template <class T>
//	bool Stack<class T>::isFull(){
//	  return position==-1;
//	}
