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
    //Question: do I need seperate cases for each cell type?? Eventually I will because of double type in valueCell and need to evaluate a new formula cell
    void editCell(string key, Cell::cellType cell, string newContents) { //might not need to pass this in, but just identify it inside function...
        cout << "INSIDE EDITCELL()" << endl;
        cout << "key of cell to edit = " << key << endl;
        switch(cell) {
            case 't': {
                cout << "inside t case" << endl;
                //sheet[key] = newContents; want to be able to do this... syntax problem...
                break; }
            case 'f': {
                cout << "inside f case" << endl;
                //sheet[key] = newContents
                break; }
            case 'v': {
                cout << "inside v case" << endl;
                //sheet[key] = newContents;
                break; }
        }
    }
    void removeCell(string key) {
        //search through map and find the provided key, then delete the key-value pair
    }
};

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

char printCellMenu() {
    char choice;
    cout << "[1] Create a title cell" << endl;
    cout << "[2] Create a formula cell" << endl;
    cout << "[3] Create a value cell" << endl;
    cin >> choice;
    return choice;
}

char printActionsMenu() {
    char choice;
    cout << "[1] Edit an existing cell" << endl;
    cout << "[2] Add an aditional cell" << endl;
    cout << "[3] Remove an existing cell" << endl;
    cin >> choice;
    return choice;
}

void mainMenuSwitch(Sheet &s) {
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            //createNew();
            cout << "Create a new spreadsheet!" << endl;
            break;
        //case '2': //open an existing spreadsheet
         //   cout << "Open an existing spreadsheet!" << endl;
          //  break;
        default:
            cout << "Please enter a valid choice." << endl;
    }
}

void cellMenuSwitch(Sheet &s) {
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
}

void actionsMenuSwitch(Sheet &s) {
    switch(printActionsMenu()) {
        case '1': { //edit an existing cell
            cout << "editing an existing cell..." << endl;
            string key;
            string contents;
            cout << "Please enter the location of the cell you want to edit A-J, 1-10: " << endl;
            cin >> key;
            cout << "Please enter the new contents of the cell: " << endl;
            cin.ignore();
            getline(cin, contents);
            //s.editCell(key, /*cellType*/,contents); --> don't want to pass type of cell here, need to identify that in function in sheet class...
            break; }
        case '2': { //add an additional cell
            cout << "adding an additional cell..." << endl;
            cellMenuSwitch(s);
            break; }
        case '3': { //remove an existing cell
            cout << "removing an existing cell..." << endl;
            //REMOVE CELL
            string key;
            cout << "Please enter the location of the cell you want to delete: " << endl;
            cin >> key;
            s.removeCell(key);
        break; }
    }
}

int main() {
    Sheet s;
    mainMenuSwitch(s);

    bool cont = true;
    while (cont == true) {
        cellMenuSwitch(s);
        actionsMenuSwitch(s);
        char choice;
        cout << "Do you want to continue? [y][n] " << endl;
        cin >> choice;
        if (choice == 'y' || choice== 'Y') 
            cont = true;
        else 
            cont = false;
    }

    //print();
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
