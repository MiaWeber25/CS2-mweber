//future improvements: read/write from a file to enable user to "save" and open existing spreadsheets
//automatically calculate the results of a formula cell and print out the result rather than the user needing to select calculate menu option
#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <algorithm> 
#include <sstream>
#include <vector> //FOR PRINT TESTING PURPOSES
#include <stack>

using namespace std;

void print();
void samplePrint();
string getLocationInfo();
string setContents();

//Node to self: PLACES I HAVE PROBLEMS: Cell in map declaration (iterators too!) && Cell::____ 
template <class T>
class Cell {
protected:
    //string contents;
    T contents;
    bool isEmpty;
   // Cell::cellType myType;
    
public:
    /*Cell(string newContents="0", bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }*/
    Cell(T newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    Cell() = default;

    enum cellType {title='t', formula='f', value='v'};


    virtual void printCell()=0;
    virtual void setContents(string value)=0;

    string getContents() {
        return contents;
    }
    bool getIsEmpty() {
        return isEmpty;
    }
};

class TitleCell: public Cell<string> {
public:
    TitleCell(string newContents="0", bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void setContents(string newContents) {
        contents = newContents;
    }

    void printCell() {
        cout << contents << endl;
    }
    string getContents() {
        return contents;
    }

};

class FormulaCell: public Cell<string> {
public:
    void setContents(string newContents) {
        contents = newContents;
    }
    FormulaCell(string newContents="0", bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void printCell() {
        cout << contents << endl;
    }
    string getContents() {
        return contents;
    }
};

class ValueCell: public Cell<double> {
public:
    ValueCell(double newContents=0.0, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void setContents(double newContents) {
        contents = newContents;
    }
    void printCell() {
        cout << contents << endl;
    }
};

class Sheet {
map<string, Cell*> sheet;
public:
    void updateValue(string &key, double value) { //note to self: will need to be updated to a double (value)
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
    void addCell(string key, Cell::cellType cell) { //have the user provide the key and the cell type to create
        cout << "INSIDE ADDCELL" << endl;
        cout << "key from addCell() = " << key << endl;
        switch(cell) {
            case 't': {
                cout << "inside t case" << endl;
                sheet[key]= new TitleCell(setContents(), false); //note to self: delete later in code to prevent core dump
                break; }
            case 'f': {
                cout << "inside f case" << endl;
                 sheet[key] = new FormulaCell(setContents(), false);
                 break; }
            case 'v': {
                cout << "inside v case" << endl;
                sheet[key] = new ValueCell(setContents(), false); //getting an error here because it's no longer expecting a string but a double
                break; }
        }
    }
    void editCell(string key, string newContents) { 
        map<string, Cell*>::const_iterator it;
        it = sheet.find(key);
        cout << "THE VALUE OF KEY TO EDIT: " << it->second->getContents() << endl; 
       /*if ((*it->second).getIsEmpty() == false) {
           cerr << "Error. Please enter location of a valid cell..." << endl;
       }*/ //note to self: need to find a way to fix this ^^ - > throw an exception etc.
        //determine enum type of cell
        if (Cell::title) {
            cout << "identified cell as a value cell" << endl;
        } else if (Cell::value) { 
            cout << "identified cell as a title cell" << endl;
        } else if (Cell::formula) {
            cout << "identified cell as a formula cell" << endl;
        }
    }
    void removeCell(string key) {
        //search through map and find the provided key, then delete the key-value pair
        sheet.erase(key);
    }

    double calculate(string &key) { 
        cout << "GETTING IN CALCULATE FUNCTION" << endl;
        map<string, Cell*>::const_iterator it;
        string toParse;
        it = sheet.find(key);
        toParse = it->second->getContents();
        cout << "toParse = " << toParse << endl;
        //parse the string into operators, values, and cell IDs
        vector<string> cellContents;
        string intermediate;
        stringstream ss(toParse);
        while(getline(ss, intermediate, ' ')) {
            cellContents.push_back(intermediate);
        }
        stack<double> s;
        //determine if each substring is a value, cell ID, or operator and perform appropriate tasks accordingly
        for (unsigned int i=0; i<cellContents.size(); i++) {
            cout << "cellContents at 0: " << cellContents[i][0] << endl;
            cout << "cellContents @ " << i << " = " << cellContents[i] << endl;
            if (isdigit(cellContents[i][0])) { //if the contents of the substring are a value - push onto stack
                cout << "contents are digits!" << endl;
                s.push(stod(cellContents[i]));
            } else if (isalpha(cellContents[i][0])) { //if the contents of the substring are a CellID (if it contains ANY letters) - call find cell (and then push value onto stack from there) 
                cout << "contents contain a letter - cell ID" << endl;
                if (Cell::value) {
                    cout << "FOUND A VALUE CELL" << endl;
                    it = sheet.find(cellContents[i]);
                    s.push(stod(it->second->getContents()));
                } else if (Cell::formula) {
                    cout << "FOUND A FORMULA CELL" << endl;
                    s.push(calculate(cellContents[i]));
                } else { //title cell
                    cerr << "attempted to compute title cell" << endl;
                }
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
    return s.top(); //return the last thing on the stack
    }
    
};

//note to self: SHOULD THIS BE IN SHEET CLASS???
string setContents() { //note to self: will need to templatize so you can set a double for the value cell 
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
            //createNew(); //note to self: need this?
            cout << "Create a new spreadsheet!" << endl;
            break;
        default:
            cout << "Please enter a valid choice." << endl;
    }
}

void cellMenuSwitch(Sheet &s) {
    switch(printActionsMenu()) {
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
        default: 
            cout << "Please enter a valid choice." << endl;
    }
}

void actionsMenuSwitch(Sheet &s) {
    switch(printActionsMenu()) {
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
        case '4': { //edit an existing cell --> 
                    //note to self:  WORKING (need to iron out details when value is a double)
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
            s.removeCell(key); //note to self: might want to use return value of this function call to alert user if cell doesn't exist...
        break; }
        case '6': { //calculate a cell
            string key;
            cout << "Please enter the location of the cell you wish to calculate: " << endl;
            cin >> key;
            s.updateValue(key, s.calculate(key));
            cout << "at the end of case 7" << endl;
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
