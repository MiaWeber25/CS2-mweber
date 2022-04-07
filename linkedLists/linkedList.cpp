#include <iostream>

using namespace std;

class Node {
    string data;
    Node *next;
    public:
    Node(string newData, Node *newNext = NULL) {
        data = newData;
        next = newNext;
    }
    void add(Node *item) { //currently, this is adding the new element directly after the head
        /*this would make it behave like a true stack
        string t=data;
        data=item->data;
        item->data=t; */
        item->next=next; 
        next=item;
    }
    void erase() { //currently deleting the second element after the head
        /*this is the stack implementation (pop off the top)
        if (next!=NULL) 
            data=next->data; */
        Node *p=next;
        /*if (next!=NULL) {
            next=next->next;
            delete p;
        }*/
        next=next->next;
        delete p;
        /* if (next == NULL) 
            data=""; */
    }
    void print(ostream &out) { //walk
        Node *p = this;
        while (p!=NULL) {
            out << p->data << endl; 
            p=p->next;
        }
    }
    /*bool operator ==(const Node &other) {
        return !(data!=other.data);
    }*/
    bool operator <(const Node &other) const { //just need the less operator in order to access the others
        return data<other.data;
    }
    /*bool operator >(const Node &other) {
        return other.data<data;
    }
    bool operator !=(const Node &other) {
        return (other.data<data || data<other.data);
    }*/
};

int main() {
    Node *head = new Node("Karl");
    Node *kim = new Node("Kim");
    head->add(kim);
    Node *emilee = new Node("Emilee");
    head->add(emilee);
    Node *kaleb = new Node("Kaleb");
    head->add(kaleb);
    head->print(cout); //head will be the instance variable this in the function
    cout << "AFTER ERASE: " << endl;
    head->erase();
    head->print(cout);
    return 0;
}