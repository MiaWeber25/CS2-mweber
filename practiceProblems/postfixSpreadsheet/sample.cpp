#include <iostream> 
#include <math.h>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

template <class T>
class Cell {
protected:
    T contents;
    bool isEmpty;
private:
public:
    //CONSTRUCTOR
    void print() {} = 0; //pure virtual --> implemented in derived classes
    void calculateValue() {

    }
    T getContents() { //this might need to be more complicated for formula class...
        return contents;
    }
};


class TitleCell: public Cell<string> {
    
};

class FormulaCell: public Cell<string> {
public:
    void getContents() {
        //parse contents of the cell and get values contained within other cells that are referenced.
        //this will be complicated...
    }
};

class ValueCell: public Cell<double> {

};

class Sheet {
private:
    vector<vector<Cell<int>>> spreadSheet; //use array instead of vector so that I can keep the size constant?
    //can't use int!!!! we don't know what it will be... every Cell will have a different type... might need to template the vector too...
public:
    void printSheet() {

    }

    Cell<string> locate() {

    }
};


void createNew(Sheet &s);
char printMainMenu();
char printCellMenu();

int main() {
    Sheet s;
    Cell<int> c;
    c.print();
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            createNew(s);
            break;
        case '2': //open existing spreadsheet
            break;
        default:
            cout << "Please enter a valid choice." << endl;
    }

    switch(printCellMenu()) {
        case '1': {//create a title cell
            cout << "creating a title cell..." << endl;
            Cell<string> titleCell;
            break; }
        case '2': {//create a formula cell
            cout << "creating a formula cell..." << endl;
            Cell<string> formulaCell;
            break; }
        case '3': {//create a value cell
            cout << "creting a value cell..." << endl;
            Cell<double> valueCell;
            break; }
    }

return 0;
}

void createNew(Sheet &s) {

}

char printMainMenu() {
    char choice;
    cout << "WELCOME TO THE POSTFIX SPREADSHEET!" << endl;
    cout << "Please select a menu option: " << endl << "[1] Create a new spreadsheet" << endl;
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


/*       cout<<" ";
        int i=1,j;
        for(j = 0; j <= 4; j++){
            if (j%4==2)
                cout << i++; //cout the value of i to label the cols
            else cout<<"   ";
        }
        cout<<endl;
        for(i = 0; i <= 2; i++){
            if(i%2!=0)
                //cout << " ";
                cout << (char)(i/2 + 'A'); //cout the ASCII value to label the rows
            for(j = 0; j <= 2; j++){
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
            }
            }
            cout<<endl;
        }
        cout<<" ";
        for(j = 0, i = 1; j <= 4; j++){

            cout<<" ";
        }
        cout<<endl;
    }

};
*/