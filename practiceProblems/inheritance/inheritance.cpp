#include <iostream>
#include <vector>

using namespace std;

class Animal {
protected: //the protected status allows us to make these members available to derived classes as well (ie. Animal and Mannal)
  string commonName;
  string scientificName;
  vector<string> attributes; //make attribute a vector (or collection) of strings
public:
  Animal(string newCommonName = "", string newScientificName = "") { //you want to use this constructor for other classes as well (Java: super constructor)
    commonName = newCommonName;
    scientificName = newScientificName;
    attributes.push_back("Can Move");
  }

  friend ostream & operator <<(ostream &out, const Animal &animal) { //overload the ostream operator so that we can output an animal
      animal.output(out); //call the function below to only implement logic once
      return out;
  }

  void output(ostream &out) const {
    out << commonName << ": " << scientificName << endl;
    for (unsigned i=0; i<attributes.size(); i++) {
      out << " " << attributes[i] << endl;
    }
  }
};

class Mammal: public Animal {
public:
  Mammal(string newCommonName="mammal", string newScientificName="mammalia"):Animal(newCommonName, newScientificName) { //call the super class's constructor using this method
    //commonName = "mammal"; //SINCE YOU ARE CALLING SUPER CONSTRUCTOR, YOU CAN MOVE THESE ABOVE
    //scientificName = "mammalia";
    attributes.push_back("Has hair, live birth, warm blooded");
  }
};

//dog is an animal so a class of Dog would look a lot like a class of Animal
//we want the features from the Animal class to also be available to the Dog class
class Dog:public Mammal { //:public Mammal alllows you to classify a Dog as an Mammal (which is an Animal) as well as use the same members
public:
  Dog():Mammal("dog", "canis lupus familiaris") {
    attributes.push_back("Domesticated four legged animal");
  }

  void output(ostream &out) {
    Animal::output(out);
    Mammal::output(out); //you can also call Mammal output function using the ::
    out << commonName << ": " << scientificName << endl;
    for (unsigned i=0; i<attributes.size(); i++) {
      out << " " << attributes[i] << endl;
    }
  }
};

int main() {
  Dog d;
  Mammal m;
  Animal a("karl", "Human");
  //d.output(cout);
  cout << d << endl;
  cout << m << endl;
  cout << a << endl;
  return 0;
}