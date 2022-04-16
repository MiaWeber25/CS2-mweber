#include <iostream>

using namespace std;

class DLNode {
  double data;
  DLNode *prev, *next;
public:
  double getData() const {
    return data;
  }

  DLNode * getNext() const {
    return next;
  }

  DLNode(double newData, DLNode *newPrev = NULL, DLNode *newNext = NULL) {
    data = newData;
    prev = newPrev;
    next = newNext;
  }


  void forwardWalk(ostream &out) {
    DLNode *p = this;
    while (p!=NULL) {
      out << p->data << endl;
      p=p->next;
    }
    /*out<<data << endl;
    //if (next != NULL) { //iterate through until at the end of the list (recurssivly)
    //  next->forwardWalk(out);
    }*/
  }

  void backwardWalk(ostream &out) {
    DLNode *p = this;
    while (p!=NULL) {
      out << p->data << endl;
      p=p->prev;
    }
  }

  void insert(DLNode *item) {
    item->next = this->next;
    item->prev = this;
    this->next = item;
    if (item->next!=NULL)
      item->next->prev = item;
  }

  DLNode *end() {
    DLNode *p=this;
    while(p->next!=NULL) p=p->next;
    return p;
  }

  void cleanUp() { //need this function for the deconstructor for Queue
    DLNode *p=this;
    while(p->next!=NULL) p=p->next;
      p=p->next;
    delete p->prev;
  }

  bool remove(double d) {
    DLNode *p=this;
    while(p!=NULL) {
      if (p->data == d) {
        DLNode *dead=p;
        if (p->prev!=NULL) p->prev->next=p->next;
        if (p->next!=NULL) p->next->prev=p->prev;
        p=p->next;
        delete dead;
        return true;
      } else
          p=p->next; //still have to increment even if it doesn't match
    }
    return false;
  }

};

class Queue {
  DLNode *head, *tail;
public:
  class Iterator { //class inside Queue class so that we can do as many iterations over the class at a time as we want to.
    DLNode *current;
  public:
    Increment increment() {
      current=current->getNext(); //increment current
      return *this;
    }

    Iterator operator ++() {
      return increment();
    }

    Iterator(DLNode *newCurrent) {
      current = newCurrent;
    }

  };

  Queue() {
    head = NULL;
    tail = NULL;
  }

  //the copy constructor:
  Queue(const Queue &other) { //I want to make a copy (shallow vs deep copy. Shallow copy would end up deleting both Queues)
    //THIS IS A SHALLOW COPY - > it is the default.
    //head = other.head;
    //tail=other.tail
    head = NULL;
    tail = NULL;
    //cout << hex << other.head << endl; //THIS IS A HELPFUL TOOL WHEN USING COUT TO DEBUGG
    //copy constructor: (like type casting a variable. that's also a copy constructor)

    //this is the deep copy. creates new houses for the values. shallow copies just create pointers to the origional houses
    DLNode *p=other.head;
    while (p!=NULL) { //while not at the end of the list
      push(p->getData());
      p=p->getNext();
    }
  }

  Iterator* begin() {
    return new Iterator(head);
  }
  Iterator* end() {
    return NULL;
  }

  void pop() {
    DLNode *temp = head;
    head=head->getNext();
    delete temp;
  }

  double front() {
    if (!empty())
      return head->getData();
    else
      return 0.0; //typically will want to throw an exception
  }
  void push(double data) {
    if (empty()) {
      head = new DLNode(data);
      tail = head;
    } else {
      DLNode *nTail = new DLNode(data); //you need this line to avoid using this and breaking encapuslation
      tail->insert(nTail);
      tail=nTail;
    }
    //don't have to use delete here because you still have the same number of pointers
  }
  void emplace(double data) {
    push(data);

  }
  bool empty() {
    return (head == NULL);
  }
  ~Queue() {
    //deconstructor to free up the data. Gets invoked once the members are no longer in scope
    //destructor also gets invoked when you go to delete an object (this means that you don't want to delete AND have it go out of scope --> copy type important here)
    //if (!empty()) p->cleanUp();
    while (!empty())
      pop();
  }

};


int main() {



  //string k("Karl");
  //for (auto it=k.rbegin(); it!=k.rend(); it++) {
  //  cout << *it << ' ';
  //}
  Queue *q = new Queue;
  //Queue *p = new Queue(*q); //this is explicitly calling the copy constructor (after dereferencing q)
  Queue p;

  q->push(10.0);
  q->push(12.0);
  p=*q; //calls copy constructor implicitly
  q->pop();
  cout << q->front() << endl;
  //delete p; can't delete p when implicitly calling copy constructor
  q->pop();
  delete q; //can still delete q
  cout << p.front() << endl;

//  q.pop();


  /*DLNode head(10.0);
  head.insert(new DLNode(3.14159));
  head.insert(new DLNode(1.414));
  head.forwardWalk(cout);
  head.end()->backwardWalk(cout); //find the end, and use that as the start to walk backwards*/
  return 0;
}
