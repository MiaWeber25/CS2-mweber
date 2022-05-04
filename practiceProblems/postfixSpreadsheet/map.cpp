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
    string contents;
    bool isEmpty;
   // Cell::cellType myType;
    
public:
    //constructor
    enum cellType {title='t', formula='f', value='v'};


    virtual void printCell()=0;

    string getContents() {
        return contents;
    }
};

class TitleCell: public Cell {
public:
    TitleCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
        cout << "contents from constructor: " << contents << endl;
    }
    void printCell() {
        cout << contents << endl;
    }
    string getContents() {
        return contents;
    }

};

class FormulaCell: public Cell {
public:
    FormulaCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void printCell() {
        cout << contents << endl;
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
    string getContents() {
        return contents;
    }
};

class ValueCell: public Cell {
public:
    ValueCell(string newContents, bool newIsEmpty=true) {
        isEmpty = newIsEmpty;
        contents = newContents;
    }
    void printCell() {
        cout << contents << endl;
    }
};

class Sheet {
map<string, Cell*> sheet;
public:
    void printSheet() {
        for (auto it = sheet.begin(); it!=sheet.end(); it++) {
            cout << "first: " << it->first << " second: "; // second: " << it->second << endl;
            (*it->second).printCell(); //will it know what kind of cell it is? YES! Enumeration type has already been called
            cout << endl;
        }
    }
    void addCell(string key, Cell::cellType cell) { //have the user provide the key and the cell type to create
        cout << "INSIDE ADDCELL" << endl;
        cout << "key from addCell() = " << key << endl;
        switch(cell) {
            case 't': {
                cout << "inside t case" << endl;
                sheet[key]= new TitleCell(setContents(), false); //delete later in code to prevent core dump
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
    void editCell(string key, /*Cell::cellType cell,*/ string newContents) { 
        map<string, Cell*>::const_iterator it;
        it = sheet.find(key);
        cout << "THE VALUE OF KEY TO EDIT: " << it->second->getContents() << endl; 
        //determine enum type of cell
        if (Cell::title) {
            cout << "identified cell as a value cell" << endl;
        } else if (Cell::value) { //seems to be identifing every cell as a value cell...
            cout << "identified cell as a title cell" << endl;
        } else if (Cell::formula) {
            cout << "identified cell as a formula cell" << endl;
        }
    }
    void removeCell(string key) {
        //search through map and find the provided key, then delete the key-value pair
        //map<string, Cell*>::const_iterator it;
        //it = sheet.find(key);
        sheet.erase(key);
    }

    double calculate(string &key) { //probably need a similar function in Cell class
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
                    cout << "FOUUND A VALUE CELL" << endl;
                    it = sheet.find(cellContents[i]);
                    s.push(stod(it->second->getContents()));
                } else if (Cell::formula) {
                    cout << "FOUUND A FORMULA CELL" << endl;
                    s.push(calculate(cellContents[i]));
                } else { //title cell
                    cerr << "attempted to compute title cell" << endl;
                }
            } else {
                switch(cellContents[i][0]) {
                    case '+': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a+b);
                        //break; 
                        } //want a break here? added before I added the other switch cases
                    case '-': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(b-a); //b-a or a-b???
                        //break; 
                        }
                    case '*': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(a*b);
                        //break;
                         }
                    case '/': {
                        double a = s.top();
                        s.pop();
                        double b = s.top();
                        s.pop();
                        s.push(b/a); //b/a or a/b
                        //break; 
                        }
                }
                 //if the contents of the substring are an operator - determine which operator and performing appropriate mathmatical functions on numbers in stack (numbers that you will need should already be on the stack...)
                //switch statement for which operator was used...?
                cout << "operator! call switch statement to determine which one" << endl;
            }
        }
    return s.top(); //return the last thing on the stack
    }
    
};


/*    if (input == "+") {
        double a = s.pop();
        double b = s.pop();
        s.push(a+b);

      } else if (input == "-") {
          double a = s.pop();
          double b = s.pop();
          s.push(b-a);

      } else if (input == "#") {
          cout << s.top() << endl;
      } else if (input == "*") { //*
          double a = s.pop();
          double b = s.pop();
          s.push(a*b);
      } else if (input == "/") { // /
          double a = s.pop();
          double b = s.pop();
          s.push(b/a);
      } else if (input == "sqrt") { // sqrt()
          double a = s.pop();
          s.push(sqrt(a)); */

//SHOULD THIS BE IN SHEET CLASS???
string setContents() { //will need to templatize so you can set a double for the value cell 
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
    //cout << "[2] Open an existing spreadsheet" << endl;
    cin >> choice;
    return choice;
}

/*char printCellMenu() {
    char choice;
    cout << "[1] Create a title cell" << endl;
    cout << "[2] Create a formula cell" << endl;
    cout << "[3] Create a value cell" << endl;
    cin >> choice;
    return choice;
}*/

char printActionsMenu() { //combine all menus into this one:
    char choice;
    cout << "[1] Create a title cell" << endl;
    cout << "[2] Create a formula cell" << endl;
    cout << "[3] Create a value cell" << endl;
    cout << "[4] Edit an existing cell" << endl;
    cout << "[5] Add an aditional cell" << endl;
    cout << "[6] Remove an existing cell" << endl;
    cout << "[7] Calculate a cell" << endl;
    cin >> choice;
    return choice;
}

void mainMenuSwitch(Sheet &s) {
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            //createNew();
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
        case '4': { //edit an existing cell --> WORKING (need to iron out details when value is a double)
            cout << "editing an existing cell..." << endl;
            string key;
            string contents;
            cout << "Please enter the location of the cell you want to edit A-J, 1-10: " << endl;
            cin >> key;
            cout << "Please enter the new contents of the cell: " << endl;
            cin.ignore();
            getline(cin, contents);
            s.editCell(key, contents);
            break; }
        case '5': { //add an additional cell --> WORKING (if time- edit and polish menu looping)
            cout << "adding an additional cell..." << endl;
            cellMenuSwitch(s);
            break; }
        case '6': { //remove an existing cell
            cout << "removing an existing cell..." << endl;
            //REMOVE CELL
            string key;
            cout << "Please enter the location of the cell you want to delete: " << endl;
            cin >> key;
            s.removeCell(key); //might want to use return value of this function call to alert user if cell doesn't exist...
        break; }
        case '7': { //calculate a cell
            string key;
            cout << "Please enter the location of the cell you wish to calculate: " << endl;
            cin >> key;
            cout << "RESULT = " << s.calculate(key) << endl;
        }
    }
}

int main() {
    Sheet s;
    mainMenuSwitch(s);

    bool cont = true;
    while (cont == true) {
        actionsMenuSwitch(s);
        char choice;
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

//SHOULD THIS BE IN SHEET CLASS?
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
