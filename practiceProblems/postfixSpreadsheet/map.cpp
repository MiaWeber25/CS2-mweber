#include <iostream>
#include <map>
#include <math.h>
#include <stack>

#include <vector> //FOR PRINT TESTING PURPOSES

using namespace std;

void print();
void samplePrint();
string getLocationInfo();
string setContents();

class Cell {
protected:
    string contents;
    bool isEmpty;
public:
    //constructor
    enum cellType {title='t', formula='f', value='v'};


    virtual void printCell()=0;
};

class TitleCell: public Cell {
public:
    TitleCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
        cout << "contents from constructor: " << contents << endl;
    }
    void printCell() {
        //cout << first << endl;
        cout << contents << endl;
    }

};

class FormulaCell: public Cell {
public:
    FormulaCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void printCell() {

    }

    void calculate() { //double calculate()
        if (isEmpty == false) { //calculate the value
            //parse the string contents: ignore the =, identify if value or cell ID, push on stack, calculate, pop off stack, call print function

        }
        else {
            //the cell is empty...
            cout << "This cell is empty. Please select another." << endl;
            //throw exception???
        }
    }
};

class ValueCell: public Cell {
public:
    ValueCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void printCell() {

    }
};

class Sheet {
map<string, Cell*> sheet;
public:
    void printSheet() {
        for (auto it = sheet.begin(); it!=sheet.end(); it++) {
            cout << "first: " << it->first << " second: "; // second: " << it->second << endl;
            (*it->second).printCell(); //will it know what kind of cell it is? 
            cout << endl;
        }
    }
    void addCell(string key, Cell::cellType cell) { //have the user provide the key and the cell type to create
        cout << "INSIDE ADDCELL" << endl;
        cout << "key from addCell() = " << key << endl;
        switch(cell) {
            case 't': {
                cout << "inside t case" << endl;
                sheet[key]= new TitleCell(setContents(), false); 
                break; }
            case 'f': {
                cout << "inside f case" << endl;
                 sheet[key] = new FormulaCell(setContents(), false);
                 break; }
            case 'v': {
                cout << "inside v case" << endl;
                sheet[key] = new ValueCell(setContents(), false);
                break; }
        }
    }
};

string setContents() { //will need to templatize so you can set a double for the value cell
    string userContents;
    cout << "Please enter the contents for your cell: " << endl;
    cin >> userContents;
    return userContents;
}

char printMainMenu() {
    char choice;
    cout << "WELCOME TO THE POSTFIX SPREADSHEET!" << endl;
    cout << "Please select a menu option: " << endl;
    cout << "[1] Create a new spreadsheet" << endl;
    cout << "[2] Open an existing spreadsheet" << endl;
    cin >> choice;
    return choice;
}

char printCellMenu() {
    char choice;
    cout << "[1] Create a title cell" << endl;
    cout << "[2] Create a formula cell" << endl;
    cout << "[3] Create a value cell" << endl;
    cin >> choice;
    return choice;
}


int main() {
    Sheet s;
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            //createNew();
            cout << "Create a new spreadsheet!" << endl;
            break;
        case '2': //open an existing spreadsheet
            cout << "Open an existing spreadsheet!" << endl;
            break;
        default:
            cout << "Please enter a valid choice." << endl;
    }
    switch(printCellMenu()) {
        case '1': { //create a title cell
            cout << "creating a title cell..." << endl;
            s.addCell(getLocationInfo(), Cell::title);
            break; }
        case '2': { //create a formula cell
            cout << "creating a formula cell..." << endl;
            s.addCell(getLocationInfo(), Cell::formula); 
            break; }
        case '3': { //create a value cell
            cout << "creating a value cell..." << endl;
            s.addCell(getLocationInfo(), Cell::value);
            break; }
    }
    //get Location Info: (key):

    //print();
    s.printSheet();
    return 0;
}


string getLocationInfo() {
    string key;
    cout << "Please enter the location for the new cell. A-J, 1-10: " << endl;
    cin >> key;
    return key;
}

void print() {
    cout<<" ";
        int i=1,j;
        for(j = 0; j <= 40; j++){
            if (j%4==2)
                cout << i++; //cout the value of i to label the cols
            else cout<<"   ";
        }
        cout<<endl;
        for(i = 0; i <= 20; i++){
            if(i%2!=0)
                //cout << " ";
                cout << (char)(i/2 + 'A'); //cout the ASCII value to label the rows
            for(j = 0; j <= 20; j++){
            if(i%2==0)
            {
                if(j==0)
                    cout<<" ";
                if(j%2==0) {
                    cout<<" ";
                }
                else cout<<"---------";
            }
            else{

                if(j%2==0) {
                    cout<<"|";

                }
                //else if

                else cout<<"   HI    "; //use if statements to check if row and col match desired
                //else samplePrint();
            }
            }
            cout<<endl;
        }
        cout<<" ";
        for(j = 0, i = 1; j <= 40; j++){

            cout<<" ";
        }
        cout<<endl;
}

//CREATES AN INFINATE LOOP....


void samplePrint() {
    vector<vector<string>> sample;
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            sample[i][j].push_back('9');
            sample[i][j].push_back('3');
            sample[i][j].push_back('A');
            cout << "   " << sample[i][j] << "    ";
        }
    }
    
}
