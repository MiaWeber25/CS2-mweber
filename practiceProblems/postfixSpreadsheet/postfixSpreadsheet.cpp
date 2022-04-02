#include <iostream>
#include <fstream>

using namespace std;
//function prototype:
char printMainMenu();
void createNew();

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
                    //cout << "Hi ";
                }
                else cout<<"---------";
            }
            else{
                //cout << "HI";
                if(j%2==0) {
                    cout<<"|";
                    //cout <<" HI   ";
                }
                //cout <<" HI   ";
               // else cout<<"         ";
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
    //PRINT MAIN MENU
    switch(printMainMenu()) {
        case '1': //create a new spreadsheet
            createNew();
            break;
        case '2': //open existing spreadsheet
            break;
        default: 
            cout << "Please enter a valid choice." << endl;
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
void createNew() {
    //get info to save the spreadsheet
    string fileName;
    ofstream o;
    cout << "Please enter a file to save the spreadsheet to: ";
    cin >> fileName;
    o.open(fileName);
    //o << "print this information. will require overridding << opperator" << endl;
    o.close();

    Sheet s;
    int temp, temp2;
    cout << "Please enter the size of the spreadsheet. Row then Col. For 2x3 enter '2 3': " << endl;
    cin >> temp >> temp2;
    s.setSize(temp, temp2);
    s.printContents();
}