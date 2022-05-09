/*
    Postfix Spreadsheet
    CSCI 112 
    05-06-2022
    Mia Weber
*/
//Future Optimizations: 
//read/write from a file to enable user to "save" and open existing spreadsheets
//automatically calculate the results of a formula cell and print out the result rather than the user needing to select calculate menu option
//better link together formula cells so that you can calculate a formula cell that contains a reference to another UNCALCULATED formula cell
//get calculate to work with negative numbers (currently identifies them as subtraction)

#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <algorithm> 
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

//FUNCTION PROTOTYPES
string getLocationInfo();

class Cell {
protected:
    bool isEmpty;
public:
    enum cellType {title='t', formula='f', value='v'};
   
    Cell(bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
    }

    void printCell() {  
		cout << getContents() << endl;
	}

    virtual void setContents(string value)=0;

    virtual string getContents()=0;
   
    bool getIsEmpty() {
        return isEmpty;
    }
};

class TitleCell: public Cell {
    string contents;
    cellType type;
public:
    TitleCell(string newContents="", bool newIsEmpty=false, cellType newType=title):Cell(newIsEmpty) {
        contents = newContents;
        type = newType;
    }

    void setContents(string newContents) {
        contents = newContents;
    }

    string getContents() {
        return contents;
    }
};

class FormulaCell: public TitleCell {  
    string contents;
    cellType type;
public:
    FormulaCell(string newContents="", bool newIsEmpty=false, cellType newType=formula):TitleCell(newContents,newIsEmpty) {
        contents = newContents;
        type = newType;
    }
 
    string getContents() { 
        return contents;
    }

    void setContents(string newContents) {
        contents = newContents;
        cout << "contents from F SET CONTENTS = " << contents << endl;
    }
};

class ValueCell: public Cell {
	double contents;
    cellType type;
public:
    ValueCell(double newContents=0.0, bool newIsEmpty=false, cellType newType=value):Cell(newIsEmpty) {
        contents = newContents;
        type = newType;
    }

    void setContents(string newContents) {
        contents = stod(newContents);  
    }
    
    string getContents() {
        return (to_string(contents));
    }  
};

class Sheet {
map<string, Cell*> sheet;
public:
    void updateValue(string &key, double value) { 
        sheet[key]->setContents(to_string(value));
    }

    void printSheet() {
        for (auto it = sheet.begin(); it!=sheet.end(); it++) {
            cout << it->first << " : "; 
            (*it->second).printCell(); 
            cout << endl;
        }
    }

    map<string, Cell*> getSheet() {
        return sheet;
    }
   
    void addCell(string key, Cell::cellType type, string userContents) {
        if (type == Cell::title) {
            sheet[key] = new TitleCell(userContents); //create a new title cell
        }
        else if (type == Cell::formula) {
            sheet[key] = new FormulaCell(userContents); //crete a new formula cell
        }
        else { //type is value cell
            sheet[key] = new ValueCell(stod(userContents)); //create a new value cell
        }
    }

   void editCell(string key, string newContents) { 
        map<string, Cell*>::const_iterator it;
        it = sheet.find(key);
        it->second->setContents(newContents);
    }

    void removeCell(string key) {
        //search through map and find the provided key, then delete the key-value pair
        sheet.erase(key);
    }

    double calculate(string &key) { 
        //parse the contents of the cell -> store substrings in vector called cellContents
        map<string, Cell*>::const_iterator it;
        string toParse;
        it = sheet.find(key);
        toParse = it->second->getContents();
        vector<string> cellContents;
        string intermediate;
        stringstream ss(toParse);
        while(getline(ss, intermediate, ' ')) {
            cellContents.push_back(intermediate);
        }
        //determine if each substring is a value, cell ID, or operator and perform appropriate tasks accordingly 
        stack<double> s;
        for (unsigned int i=0; i<cellContents.size(); i++) {
            if (isdigit(cellContents[i][0])) { //if the contents of the substring are a value - push onto stack
                s.push(stod(cellContents[i]));
            } else if (isalpha(cellContents[i][0])) { //if the contents of the substring are a CellID (if it contains ANY letters) - call find cell (and then push value onto stack from there) 
                if (Cell::value) { //cell ID reference to a value cell? go get the value and push onto stack
                    it = sheet.find(cellContents[i]);
                    s.push(stod(it->second->getContents()));
                } else if (Cell::formula) { //cell ID reference to a formula cell? go calculate contents of formula cell and push onto stack
                    cout << "FOUND A FORMULA CELL" << endl;
                    s.push(calculate(cellContents[i]));
                } else { //title cell
                    cerr << "attempted to compute title cell" << endl;
                }
            } else { //subtring is an opperator. which one?
                switch(cellContents[i][0]) {
                    case '+': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a+b); 
                        break; 
                        } 
                    case '-': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(b-a); 
                        break; 
                        }
                    case '*': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a*b);
                        break;
                         }
                    case '/': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(b/a); 
                        break; 
                    }
                }
            }
        }
        return s.top(); //return the last thing on the stack
    }  
};

string getUserContents() {  
    string temp;
    cout << "Please enter the contents for your cell: " << endl;
    cin.ignore();
    getline(cin, temp);
    string userContents; 
    userContents = temp;
    return userContents;
}

char printMainMenu() {
    char choice;
    cout << "WELCOME TO THE POSTFIX SPREADSHEET!" << endl;
    cout << "Please select a menu option: " << endl;
    cout << "[1] Create a new spreadsheet" << endl;
    cin >> choice;
    return choice;
}

char printActionsMenu() { 
    char choice;
    cout << "[1] Create a title cell" << endl;
    cout << "[2] Create a formula cell" << endl;
    cout << "[3] Create a value cell" << endl;
    cout << "[4] Edit an existing cell" << endl;
    cout << "[5] Remove an existing cell" << endl;
    cout << "[6] Calculate a cell" << endl;
    cin >> choice;
    return choice;
}

void mainMenuSwitch(Sheet &s) {
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            cout << "creating a new spreadsheet..." << endl;
            break;
        default:
            cout << "Please enter a valid choice." << endl;
    }
}



void actionsMenuSwitch(Sheet &s) {
    switch(printActionsMenu()) {
        case '1': { //create a title cell
            cout << "creating a title cell..." << endl;
            string key = getLocationInfo();
            string userContents = getUserContents();
            s.addCell(key,Cell::title, userContents);
            break; }
        case '2': { //create a formula cell
            cout << "creating a formula cell..." << endl;
            string key = getLocationInfo();
            string userContents = getUserContents();
            s.addCell(key, Cell::formula, userContents);
            break; }
        case '3': { //create a value cell
            cout << "creating a value cell..." << endl;
            string key = getLocationInfo();
            string userContents = getUserContents();
            s.addCell(key, Cell::value, userContents);
            break; }
        case '4': { //edit an existing cell --> 
            cout << "editing an existing cell..." << endl;
            string key;
            string contents;
            cout << "Please enter the location of the cell you want to edit A-J, 1-10: " << endl;
            cin >> key;
            map<string, Cell*>::const_iterator it;
            it = s.getSheet().find(key);
            if ((*it->second).getIsEmpty() == true) {
                cerr << "Error. Please enter the location of a valid cell..." << endl;
            } else {
                cout << "Please enter the new contents of the cell: " << endl;
                cin.ignore();
                getline(cin, contents);
                s.editCell(key, contents);
                break; }
            }
        case '5': { //remove an existing cell
            string key; 
            cout << "Please enter the location of the cell you want to delete: " << endl;
            cin >> key;
            s.removeCell(key); //here is a place to throw an exception if the cell attempting to be deleted doesn't exist
        break; }
        case '6': { //calculate a cell
            string key; 
            cout << "Please enter the location of the cell you wish to calculate: " << endl;
            cin >> key;
            s.updateValue(key, s.calculate(key));
            break; }   
        default: 
            cout << "Please enter a valid choice" << endl;   
    }
}

string getLocationInfo() {
    string key;
    cout << "Please enter the location for the new cell. A-J, 1-10: " << endl;
    cin >> key;
    return key;
}

int main() {
    Sheet s;
    mainMenuSwitch(s);
    bool cont = true;
    while (cont == true) {
        actionsMenuSwitch(s);
        char choice;
        s.printSheet();
        cout << "Do you want to continue? [y][n] " << endl;
        cin >> choice;
        if (choice == 'y' || choice== 'Y') 
            cont = true;
        else 
            cont = false;
    }
    s.printSheet();
    return 0;
}