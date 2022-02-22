//Contact Manager
#include <iostream>
#include <fstream>
#include <istream>
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

  //ADDITION FOR CIN:
  friend istream & operator >>(istream &in, Contact &other) {
    //read in to a single contact...
    char ch;
    //in >> other.add >> ch >> other.add;
    in >> other.name >> ch >> other.phone;
  //  cin >> other;

    return in;
  }

  bool operator ==(const Contact &other) const {
    return (name==other.name);
  }

  bool isEmpty() {
    return (name.length()==0 && phone.length()==0);
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

  //void getFromUser() {

  //}

  friend ostream &operator<<(ostream &out, const Contacts &list) { //take in an ostream and the list of contacts, and then return to the SAME ostream (that's why & is in front)
    for (int i=0;i<list.numContacts; i++) {
      out << list.contacts[i] << endl; //need to use list.numContacts and list.contacts because those are private associated with this and we are using a friend function so we need to access them through list
      //line above is attempting to output a SINGLE CONTACT, so you also need to implement a similar operator overloading function in order to output a single contact rather than contactS
    }
    return out;
}

//ADDITION FOR CIN:
  friend istream &operator>>(istream &in, Contacts &list) {
    //for (int i=0;i<list.numContacts; i++) {
    //  in >> list.contacts[i];
  //  }
  int contactsToAdd=0;
  cout << "Enter number of contacts: " << endl;
  cin >> contactsToAdd;
  cout << "contactsToAdd: " << contactsToAdd << endl;
  for (int i=0; i<contactsToAdd; i++) {
    Contact newContact;
    newContact.getFromUser(); //contacts[i].getFromUser();
    list.add(newContact);
  }
    return in;
  }

  Contact find(const Contact &c) {
    for (int i=0; i<numContacts; i++)
      if (c==contacts[i])
        return contacts[i];
    return Contact(); //if you can't find the contact, then just make an empty contact (using the contact constructor)
  }

  void remove(const Contact &c) {
    int offset=0;
    for (int i=0; i<numContacts; i++) {
      if (c==contacts[i]) { //remove this one. Need to overload == in Contact class so you can compare two contacts like this
        offset=1;
      }
      if (offset>0)
        contacts[i]=contacts[i+offset]; //shift everything up to effectivly remove a contact in the array
    }
    if (offset>0) {
      numContacts--;
    }
  }

};

int main() {

  Contact karl("Karl", "970-462-7280");
  Contact john("John", "970-258-1000");
  Contact james("James", "970-258-1000");
  Contact josh("Josh", "970-258-1000");
  Contact jacob("Jacob", "970-258-1000");

  Contacts phoneBook;

  phoneBook.add(karl); //you could overload the + to add a contact, but this is better readability
  phoneBook.add(john);
  phoneBook.add(james);
  phoneBook.add(josh);
  phoneBook.add(jacob);
/*
  Contact x=phoneBook.find(Contact("Karl"));
  cout << x << endl;
  Contact y=phoneBook.find(Contact("Karls Friend"));
  cout << y << endl;*/

  cin >> phoneBook; //YOU WANT TO BE ABLE TO OVERLOAD >> FOR CIN JUST LIKE WE DID FOR COUT
  cout << phoneBook << endl;
  //phoneBook.remove(Contact("John"));
  //cout << "After remove:" << endl << phoneBook << endl;
  return 0;
}