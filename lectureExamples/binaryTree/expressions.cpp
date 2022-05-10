//read a string like ( 3 + 5 ) * ( 6 + 7 ) and output PostFix 3 5 + 6 7 + *

#include <iostream>

using namespace std;


class ParseTree {
  ParseTree *left, *right;
  char value;
public:
  ParseTree(char newValue, ParseTree *newLeft = NULL, ParseTree *newRight = NULL) {
    value = newValue;
    left = newLeft;
    right = newRight;
  }

  void postFix(ostream &out=cout) {
    if (left!=NULL) left->postFix(out);
    if (right!=NULL) right->postFix(out);
    out << value;
  }

};

bool isOperator(char c) {
  return (c=='+' || c=='-' || c=='/' || c=='*');
}

//recurssive desent parser
ParseTree *parse(string s, unsigned &pos) {
  if (isdigit(s[pos])) {
    ParseTree *l = new ParseTree(s[pos]); //left and right are defaulted to NULL
    //peak ahead to see if there is an expression coming
    if (pos+1<s.size()) //is there another char follwing digit?
      if (isOperator(s[pos+1])) {  //is that char an operator (and therefore an expression)
        if (pos+2<s.size()) { //second character following the operator? --> create a leaf node
          if (isdigit(s[pos+2])) {
            unsigned opIndex=pos+1;
            ParseTree *r = new ParseTree(s[pos+2]);
            pos+=3;
            return new ParseTree(s[opIndex],l,r); //return a new node with the 2 digits and the operator
        } else if (s[pos+2]=='(') {
          unsigned pos2=pos+3;
          ParseTree *r=parse(s,pos2);
          unsigned opIndex=pos+1;
          pos=pos2;
          return new ParseTree(s[opIndex],l,r);
        }
      }
    }
      pos++;
      return l; //if it's just a lone digit (not part of an expression) just return the leaf node with the digit
  } else if (s[pos]=='(') {
    unsigned pos2=pos+1;
    ParseTree *sub=parse(s, pos2);
    if (s[pos2]==')') {
      pos=pos2+1;
      return sub;
    } else {
      cerr << "Expected ) at " << pos2 << endl;
    }
  }
  return NULL;
}
int main() {
  string expression;
  cout << "enter the expression: " << endl;
  cin >> expression;
  unsigned pos = 0;
  ParseTree *t = parse(expression, pos);
  t->postFix();
  cout << endl;
  return 0;
}
