#include <iostream>

using namespace std;

class BinaryNode {
  //pair<char, double> letterFrequency;
  char c;
  double position; //frequency of occurence of a letter
  BinaryNode *left, *right;
public:
  BinaryNode(char newC=' ', double newPosition=0.0, BinaryNode *newLeft=NULL, BinaryNode *newRight =NULL) {
    c = newC;
    position=newPosition;
    left=newLeft;
    right=newRight;
  }

  void insert(char newC, double newPosition) { //insert by frequency
    if (position < newPosition) { //update the right
        if (right!=NULL) {
          right->insert(newC, newPosition);
        } else{
          right = newBinaryNode(newC, newPosition);
        }
    } else if (newPosition<position) { //update the left
        if (left!=NULL) { //we actually have a tree to the left
          left->insert(newC, newPosition); //recurssion
        } else { //we have no tree to the left
            left = new BinaryNode(newC, newPosition); //there's no tree over there, go create a new one for this info
        }
    } else { //we are at the point we need to update
        c=newC;
    }
  }

  void printPre() {
    cout << c << ' ';
    if (left!=NULL) left->printPre();
    if (right!=NULL) right->printPre();
  } //# E I S H 5 4 V 3 U F (2) A R L (+) ...
  void printPost() {
    if (left!=NULL) left->printPost();
    if (right!=NULL) right->printPost();
    cout << c << ' ';
  }
  void printInfix() {
    if (left!=NULL) left->printInfix();
    cout << c << ' ';
    if (right!=NULL) right->printInfix();
  }

  //     +
  //   /   \
  //  5     6
  //pre order + 5 6
  //post order 5 6 +
  //infix order 5 + 6

};


int main() {
  BinaryNode root('#',0.5);
  root.insert('E', 0.25);
  root.insert('T', 0.75);
  root.insert('I', 0.125);
  root.insert('A', 0.375);
  root.insert('N', 0.625);
  root.insert('M', 0.875);

  cout << "PreFix Order" << endl;
  root.printPre();
  cout << endl << "PostFix Order" << endl;
  root.printPost();
  cout << endl << "InFix Order" << endl;
  root.printInFix();

  return 0;
}
