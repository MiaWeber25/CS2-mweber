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
    vector<string> line; 
    vector<string> tokens;
    vector<string> tokens2;
    string temp;

    ifstream fin;
    fin.open(fileName, ios::in);
    string intermediate;
    string intermediate2;

       while(!fin.eof()) {
        fin >> temp;
        line.push_back(temp);
    } 
    for (int t=0; t<line.size(); t++) {
        stringstream ss(line[t]);
        while(getline(ss, intermediate, ',')) {
            tokens.push_back(intermediate);
        }
    }
    for (int t=0; t<tokens.size(); t++) {
        stringstream sss(tokens[t]);
        while(getline(sss, intermediate2, ':')) {
            tokens2.push_back(intermediate2);
        }
    }

    for (int i=0; i<tokens2.size(); i++) {
        cout << tokens2[i] << endl;
    }
}

void printBoard() {    
   // setfill("-");   
    cout << setfill('-') << setw(10) << endl; 

}