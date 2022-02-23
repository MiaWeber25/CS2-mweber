//make everything a class? vs just a space is a class...
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip>
//added a testing comment.

using namespace std;

//CLASS PROTOTYPES:
class Board;
class Block;
class Space;
void welcomeToSudoku();
void readGivens(string&);
void printBoard();

class Board {
    vector<vector<Block>> gameBoard;

    //constructor:
    Board(vector<vector<Block>> newGameBoard = {}) {
        gameBoard = newGameBoard;
    }
    
    bool isSolved() {

        return false;
    }
};

class Block {
    vector<vector<Space>> block;
    vector<int> neededValues; //1-9 values

    //constructor: 
    Block(vector<vector<Space>> newBlock = {}) {
        block = newBlock;
    }

    bool isComplete() {

        return false;
    }

};

class Space {
    //bool isEmpty;
    vector<int> possibleValues; //do I want to use possible valeus, or forbidden values?? 
   // int correctValue;

    //constructor: 
    

    void placeNumber() {

    }

    void switchNumber() {

    }

    void newPossibility() {

    }

};

int main() {
    welcomeToSudoku();
    printBoard();
    //initialize a gameBoard!
    //Board theGameBoard;
    return 0;
}

void welcomeToSudoku() { //welcomes the user, gets name of file with givens
    string fileName;
    cout << "Welcome To Sudoku Solver!!" << endl;
    cout << "Please enter the name of the file with givens: ";
    getline(cin, fileName);
    //cout << "File Name: " << fileName << endl; //GETLINE IS WORKING! 
    readGivens(fileName);
}

void readGivens(string &fileName) { //read in givens && add them to vector gameBoard //MIGHT NEED TO PASS IT GAMEOARD
    ifstream fin;
    string i;
    string token;
    string line;
    fin.open(fileName, ios::in);
    //istringstream ss(line); //stringstream or istringstream??
    stringstream lineStream(line);
    while(getline(ss,token,':')) {
        /* LOOP THROUGH GAMEBOARD USING "B" INDEX: */

        fin >> i;
       // i=i-'0';
        //cout << "token: " << token << endl;
    }
    /*
    while(!fin.eof()) { 
        fin.ignore();
        fin >> a >> b;
    }*/
    //cout << "token: " << token << endl;
    cout << "finished loop! i: " << i << endl;
 /*
    string line;
    int a = 0;
    int b = 0;
    istringstream ss(line);
    string token;
    while (getline(ss, token, ':')) {
        cout << token << endl;
        
       // if (!(ss >> a >>b)) {break;} 
    }
    //cout << "a: " << a << " " << "b: " << b << endl;*/
}

void printBoard() {    
   // setfill("-");   
    cout << setfill('-') << setw(10) << endl; 

}