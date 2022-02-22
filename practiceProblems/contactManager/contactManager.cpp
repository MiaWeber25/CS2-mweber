//Contact Manager
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class Contact {
  string name;
  string phone;

public:
  Contact(string newName="", string newPhone="") { //constructor
    name=newName;
    phone=newPhone;
  }
  void getFromUser() {
    cout << "Enter name and phone: " << endl;
    cin >> name >> phone; //DO THE SAME FOR INPUTS!!
  }

  friend ostream & operator <<(ostream &out, const Contact &other) { //same template as below. This function allows you to output a single contact (which we do below)
    out << other.name << ", " << other.phone << endl; //again, you need to use other.name and other.phone, because you don't have direct access to name and phone
    return out;
  }

};

//const int MAXCONTACTS=100; //NOT BEING USED YET... WARNING
class Contacts {
  int numContacts;
  Contact contacts[100];

public:
  Contacts() { //constructor
    numContacts=0;
  }

  void add(const Contact &other) {
    contacts[numContacts]=other; //you know that the last element in the array is empty, so you can add a contact there
    numContacts++;
  }

  void getFromUser() {
    cout << "Enter number of contacts: " << endl;
    cin >> numContacts;
    for (int i=0; i<numContacts; i++) {
      contacts[i].getFromUser();
    }
  }

  friend ostream& operator <<(ostream &out, const Contacts &list) { //take in an ostream and the list of contacts, and then return to the SAME ostream (that's why & is in front)
    for (int i=0;i<list.numContacts; i++) {
      cout << list.contacts[i] << endl; //need to use list.numContacts and list.contacts because those are private associated with this and we are using a friend function so we need to access them through list
      //line above is attempting to output a SINGLE CONTACT, so you also need to implement a similar operator overloading function in order to output a single contact rather than contactS
    }
    return out;
}

};

int main() {

  Contact karl("Karl", "970-462-7280");
  Contact john("John", "970-258-1000");
  Contacts phoneBook;
  phoneBook.add(karl); //you could overload the + to add a contact, but this is better readability
  phoneBook.add(john);

  cout << phoneBook << endl; //it would be nice to do this, but you can't cout an entire array
  //cin >> phoneBook; //YOU WANT TO BE ABLE TO OVERLOAD >> FOR CIN JUST LIKE WE DID FOR COUT
  return 0;
}