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

class Cell {
protected:
    bool isEmpty;

public:
    enum cellType {title='t', formula='f', value='v'};
    /*Cell(string newContents="0", bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }*/
    Cell(/*T newContents,*/ bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        //contents = newContents;
    }
    //Cell() = default;

    


    void printCell(){  // KJC No need to make this virtual really make the 
		// function that gets you the contents virtual instead
		cout << getContents() << endl;
	}
    virtual void setContents(string value)=0;
    virtual string getContents()=0;
    // {
   //     return contents;
   // }
    bool getIsEmpty() {
        return isEmpty;
    }
};

class TitleCell: public Cell {
    string contents;
    cellType type;
public:
    TitleCell(string newContents="", bool newIsEmpty=true, cellType newType=title):Cell(newIsEmpty) {
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

class FormulaCell: public TitleCell {  // KJC Derive from TitleCell because you store a string
	double result;
public:
  /*  void setContents(string newContents) {
        contents = newContents;
    }*/
    FormulaCell(string newContents="0", bool newIsEmpty=true):TitleCell(newContents,newIsEmpty) {
    }
 /*   void printCell() {
        cout << getContent() << endl;
    }*/
    string getContents() {  // KJC This is where there is an interesting difference between TitleCell and a Formula Cell
		// DO STACK EVAL HERE store double in result
        return to_string(result);
    }
};

class ValueCell: public Cell {
	double contents;
public:
    ValueCell(double newContents=0.0, bool newIsEmpty=true):Cell(newIsEmpty) {
        /*isEmpty = newIsEmpty;*/
        contents = newContents;
    }
    void setContents(string newContents) {
        contents = stod(newContents);  // This is a little ugly to match the virtual function prototype
    }
    /*void printCell() {
        cout << contents << endl;
    }*/
    string getContents() {
        return (to_string(contents));
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
    /*void addCell(string key, Cell *cellref) { //have the user provide the key and the cell type to create
        cout << "INSIDE ADDCELL" << endl;
        cout << "key from addCell() = " << key << endl;
        sheet[key]=cellref;
    }*/
       void addCell(string key, Cell::cellType type, string userContents) {
        if (type == Cell::title) {
            sheet[key] = new TitleCell(userContents); //pass it contents
        }
        else if (type == Cell::formula) {
            sheet[key] = new FormulaCell(userContents);
        }
        else { //type is v 
            sheet[key] = new ValueCell(stod(userContents));
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

    double calculate(string &key) { 
        cout << "GETTING IN CALCULATE FUNCTION" << endl;
        map<string, Cell*>::const_iterator it;
        string toParse;
        it = sheet.find(key);
        toParse = it->second->getContents();
        cout << "toParse = " << toParse << endl;
        //parse the string into operators, values, and cell IDs
        // KJC this to the END KJC should be in the formulaCell class
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



void actionsMenuSwitch(Sheet &s) {
    string key = getLocationInfo();
    string userContents = getUserContents();
    switch(printActionsMenu()) {
        case '1': { //create a title cell
            cout << "creating a title cell..." << endl;
            
            s.addCell(key,Cell::title, userContents);
            break; }
        case '2': { //create a formula cell
            s.addCell(getLocationInfo(), Cell::formula, userContents);
            break; }
        case '3': { //create a value cell
            cout << "creating a value cell..." << endl;
            s.addCell(getLocationInfo(), Cell::value, userContents);
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
