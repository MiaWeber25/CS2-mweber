#include <iostream>

using namespace std;

class DOMNode {
  string name; //tag name
  vector<DOMNode *> children;
public:

};

class HeadTag: public DOMNode {

};

class BodyTag: public DOMNode {

};

int main() {

  return 0;
}
