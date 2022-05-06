/*
    This file includes all the notes from karl about sheet.cpp (comments located in MWsheet.cpp)
    The goal of this file is to get the calculatle function working (or at least outlined and compiling)
    I still have a segFault with creating Formula cells - and this file is not aimed at resolving that. 
    Instead of putting all of the logic for calculate in the formula cell - it will reside in the sheet class...

*/


//future improvements: read/write from a file to enable user to "save" and open existing spreadsheets
//automatically calculate the results of a formula cell and print out the result rather than the user needing to select calculate menu option
#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <algorithm> 
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

void print();
void samplePrint();
string getLocationInfo();
string getUserContents();

class Cell {
protected:
    bool isEmpty;    
public:
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
    bool checkContents() { //returns true if cell is a value cell and false if it's a formula cell (or contains letters)
        map<string, Cell*>::const_iterator it;
        string toParse;
        vector<string> cellContents;
        string intermediate;
        stringstream ss(toParse);
        while(getline(ss, intermediate, ' ')) {
            cellContents.push_back(intermediate);
        }
        if (isdigit(cellContents[0][0])) {
            cout << "contents are digits!" << endl;
            return true;
        } else {
            cout << "contents are not digits" << endl;
            return false;
        }
    }
};

class TitleCell: public Cell {
    string contents;
public:
    TitleCell(string newContents="", bool newIsEmpty=true):Cell(newIsEmpty) {
        contents = newContents;
    }

    void setContents(string newContents) {
        contents = newContents;
    }

    string getContents() {
        return contents;
    }

};

class FormulaCell:public TitleCell {
    double result;
public:
    FormulaCell(string newContents="0", bool newIsEmpty=true):TitleCell(newContents, newIsEmpty) {
        
    }
   
    //issue: I don't want to take parameters because it would differ from the prototype in Cell class, but I think I have to...
    //DO THE STACK EVAL HERE!!


    string getContents() { //need to know: key and sheet
        stack<double> s;
        map<string, Cell*>::const_iterator it;
        //parse the string into operators, values, and cell IDs
        string toParse;
        vector<string> cellContents;
        string intermediate;
        stringstream ss(toParse);
        while(getline(ss, intermediate, ' ')) {
            cellContents.push_back(intermediate);
        }
        //determine if each substring is a value, cell ID, or operator and perform appropriate tasks accordingly
        for (unsigned int i=0; i<cellContents.size(); i++) {
            cout << "cellContents at 0: " << cellContents[i][0] << endl;
            cout << "cellContents @ " << i << " = " << cellContents[i] << endl;
            if (isdigit(cellContents[i][0])) { //if the contents of the substring are a value - push onto stack
                cout << "contents are digits!" << endl;
                s.push(stod(cellContents[i]));
                cellContents[i].checkContents();
            } 
            
            
            
            else if (isalpha(cellContents[i][0])) { //if the contents of the substring are a CellID (if it contains ANY letters) - call find cell (and then push value onto stack from there) 
                cout << "contents contain a letter - cell ID" << endl;
                //it = sheet.find(cellContents[i]);
              //if (Cell::value) { //Cell ID for a value cell? 
                    cout << "FOUND A VALUE CELL" << endl;
                    //it = sheet.find(cellContents[i]);
                    s.push(stod(it->second->getContents()));
                }/* else if (Cell::formula) { //cell ID for another formula cell?
                    cout << "FOUND A FORMULA CELL" << endl;
                    s.push(calculate(cellContents[i]));
                } else { //title cell
                    cerr << "attempted to compute title cell" << endl;
                }*/
            } else {
                switch(cellContents[i][0]) {
                    case '+': {
                        cout << "FOUND AN ADDITION" << endl;
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a+b); 
                        break; 
                        } 
                    case '-': {
                        cout << "FOUND A SUBTRACTION" << endl;
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(b-a); 
                        break; 
                        }
                    case '*': {
                        cout << "FOUND A MULTIPLICATION" << endl;
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a*b);
                        break;
                        }
                    case '/': {
                        cout << "FOUND A DIVISION" << endl;
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
    result = s.top(); //return the last thing on the stack
    return (to_string(result));
    }
};

//class ValueCell: public Cell<double> {
class ValueCell: public Cell {
    double contents;
public:
    ValueCell(double newContents=0.0, bool newIsEmpty=true):Cell(newIsEmpty) {
        contents = newContents;
    }
    void setContents(string newContents) {
        //contents = stod(newContents); //THIS PART IS A LITTLE UGLY. MIGHT NEED TO FIX LATER...
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
   
    void addCell(char type) {
        cout << "inside add cell!" << endl;
        string key = getLocationInfo();
        if (type == 't') {
            sheet[key] = new TitleCell(getUserContents(), false);
            //MAYBE I CHANGE THIS LATER TO BE LIKE: 
            //sheet[key] = new TitleCell.addCell(getUserContents(), false); 
            //make it so that I can move all addCell() functions into each individual Cell class and then I can call those functions directly from switch statement
            //I can't right now because s[key] isn't working... needs to be from sheet class... 
        }
        else if (type == 'f') {
            cout << "before new FormulaCell statement" << endl;
            sheet[key] = new FormulaCell(getUserContents(), false);
            cout << "after new FormulaCell statement" << endl;
        }
        else { //type is v 
            sheet[key] = new ValueCell(stod(getUserContents()), false);
            cout << "after last addCell() statement..." << endl;
        }
    }

    void editCell(string key, string newContents) { 
        map<string, Cell*>::const_iterator it;
        it = sheet.find(key);
        cout << "THE VALUE OF KEY TO EDIT: " << it->second->getContents() << endl; 
        it->second->setContents(newContents);
    }
    void removeCell(string key) {
        //search through map and find the provided key, then delete the key-value pair
        sheet.erase(key);
    }

    double calculateCell(string &key) {
        double result;
        map<string, Cell*>::const_iterator it;
        it = sheet.find(key);
        it->second->getContents(); //potential problem: how will it know which cell to call getContents for? it's a formula cell...
        return result;
    }
};

string getUserContents() {  
    string temp;
    cout << "Please enter the contents for your cell: " << endl;
    cin.ignore();
    getline(cin, temp);
    string userContents; //note to self: template? could cause problems with double value cells later...
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

void mainMenuSwitch(Sheet &s) {
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            //createNew(); //note to self: need this?
            cout << "Create a new spreadsheet!" << endl;
            break;
        default:
            cout << "Please enter a valid choice." << endl;
    }
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

void actionsMenuSwitch(Sheet &s) {
    switch(printActionsMenu()) {
        char type;
        case '1': { //create a title cell --> WORKING SO FAR
            type = 't';
            cout << "creating a title cell..." << endl;
            cout << "about to call addCell()" << endl;
            s.addCell(type);
            //WHAT I WANT TO DO: 
            //s.getSheet()[getLocationInfo()] = new TitleCell(getUserContents(), false);
            cout << "got to after addCell() call" << endl;
            break; }
        case '2': { //create a formula cell --> SEG FAULT (here or Case 3?)
            type = 'f';
            cout << "creating a formula cell..." << endl;
            s.addCell(type);
            cout << "BACK IN SWITCH STATEMENT AFTER ADDCELL WAS CALLED" << endl;
            //seg faulting here?
            break; }
        case '3': { //create a value cell --> SEEMS TO BE WORKING (could be contributing to the seg fault)
            type = 'v';
            cout << "creating a value cell..." << endl;
            s.addCell(type);
            break; }
        case '4': { //edit an existing cell --> WORKING SO FAR 
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
        case '5': { //remove an existing cell --> WORKING SO FAR
            string key;
            cout << "Please enter the location of the cell you want to delete: " << endl;
            cin >> key;
            s.removeCell(key); //note to self: might want to use return value of this function call to alert user if cell doesn't exist...
        break; }
        case '6': { //calculate a cell --> I WOULD ASSUME NOT WORKING b/c of SEG FAULT
            string key;
            cout << "Please enter the location of the cell you wish to calculate: " << endl;
            cin >> key;
            s.getSheet()[key]->getContents(); //call getContents() --> which is the initial calculate logic on user entered cell
            s.calculateCell(key); 
            break; }   
        default: 
            cout << "Please enter a valid choice" << endl;   
    }
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

//note to self: SHOULD THIS BE IN SHEET CLASS?
    string getLocationInfo() {
        string key;
        cout << "Please enter the location for the new cell. A-J, 1-10: " << endl;
        cin >> key;
        return key;
    }