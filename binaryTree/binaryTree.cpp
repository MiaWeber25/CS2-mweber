#include <iostream>

using namespace std;

class BinaryNode {
  //pair<char, double> letterFrequency;
  char c;
  double frequency; //frequency of occurence of a letter
  BinaryNode *left, *right;
public:
  BinaryNode(char newC=' ', double newFrequency=0.0, BinaryNode *newLeft=NULL, BinaryNode *newRight =NULL) {
    c = newC;
    frequency=newFrequency;
    left=newLeft;
    right=newRight;
  }

  void insert(char newC, double newFrequency) { //insert by frequency
    if (frequency < newFrequency) { //update the right
        if (right!=NULL) {
          right->insert(newC, newFrequency);
        } else{
          right = newBinaryNode(newC, newFrequency);
        }
    } else if (newFrequency<frequency) { //update the left
        if (left!=NULL) { //we actually have a tree to the left
          left->insert(newC, newFrequency); //recurssion
        } else { //we have no tree to the left
            left = newBinaryNode(newC, newFrequency); //there's no tree over there, go create a new one for this info
        }
    } else { //we are at the point we need to update
        c=newC;
    }
  }

  void print() {
    cout << c << ' ';
    if (left!=NULL) left->print();
    if (right!=NULL) right->print();
  } //# E I S H 5 4 V 3 U F (2) A R L (+) ...


};


int main() {

  return 0;
}
