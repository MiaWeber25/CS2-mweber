#include <iostream>
#include <fstream>

using namespace std;
//function prototype:
char printMainMenu();
void createNew(Sheet);
char printCellMenu();

class Sheet {
    //2D array of user specified type
    int row;
    int col;
public:
    //constructor:
    Sheet(int row = 2, int ccol =2) {

    }

    void printContents(/*string &fileName,*/) { //print the contents of the spreadhsheet
        cout<<" ";
        int i=1,j;
        for(j = 0; j <= 4*col; j++){
            if (j%4==2)
                cout << i++; //cout the value of i to label the cols
            else cout<<"   ";
        }
        cout<<endl;
        for(i = 0; i <= 2*row; i++){
            if(i%2!=0)
                //cout << " ";
                cout << (char)(i/2 + 'A'); //cout the ASCII value to label the rows
            for(j = 0; j <= 2*col; j++){
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

                else cout<<"   Hi    "; //use if statements to check if row and col match desired
            }
            }
            cout<<endl;
        }
        cout<<" ";
        for(j = 0, i = 1; j <= 4*col; j++){

            cout<<" ";
        }
        cout<<endl;
    }

    //setter
    void setSize(int &newRow, int &newCol) {
        row = newRow;
        col = newCol;
    }
};


int main() {
    Sheet s;
    //PRINT MAIN MENU
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
        int r, c;
        case '1': //create a new cell
            cout << "enter # of new rows, # of new cols: " << endl; //WAIT SHOULD THIS UPDATE ROW AND COL??
            cin >> r >> c;
            s.setSize(r,c);
            s.printContents();
            break;
        case '2': //edit an existing cell
            cout << "edit an existing cell" << endl;
            break;
        case '3': //delete a cell
            cout <<"delete a cell"<< endl;
            break;
        default:
            cout << "Please enter a valid choice." << endl; //should add looping stuff here so you don't have to start over...


    }
    return 0;
}

char printMainMenu() {
    char choice;
    cout << "WELCOME TO THE POSTFIX SPREADSHEET!" << endl;
    cout << "Plese select a menu option: " << endl << "[1] Create a new spreadsheet" << endl << "[2] Open an existing spreadsheet" << endl;
    cin >> choice;
    return (choice);
    
}

//function to create a new spreadsheet
void createNew(Sheet s) {
    //get info to save the spreadsheet
    string fileName;
    ofstream o;
    cout << "Please enter a file to save the spreadsheet to: ";
    cin >> fileName;
    o.open(fileName);
    //o << "print this information. will require overridding << opperator" << endl;
    o.close();

    int temp, temp2;
    cout << "Please enter the size of the spreadsheet. Row then Col. For 2x3 enter '2 3': " << endl;
    cin >> temp >> temp2;
    s.setSize(temp, temp2);
    s.printContents();
}

char printCellMenu() { //print the menu for actions on a cell
    char choice;
    cout << "[1] Create a new cell" << endl;
    cout << "[2] Edit an existing cell" << endl;
    cout << "[3] Delete a cell" << endl;
    cin >> choice;
    return (choice);
}