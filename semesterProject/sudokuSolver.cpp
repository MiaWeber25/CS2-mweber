//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
//#include <iomanip> //MIGHT NEED THIS LATER FOR OUTPUT FORMATTING
#include <algorithm>
//include <iterator> //MIGHT NOT NEED THIS BECAUSE I FOUND A NEW WAY TO SEARCH FOR VALUES IN VECTORS

using namespace std;


class Space {
    int value;
public:
    vector<int> forbiddenValues; //needs to be private!

    Space(int newValue=0) { //constructor
        value = newValue;
    }

    void setValue(int newValue) { //setter for value
        value = newValue;
    }
    int getValue() { //getter for value
        return value;
    }

    void placeNumber() {

    }

    void switchNumber() {

    }

    void newPossibility() {

    }

};



class Block {
public:
    vector<vector<Space>> block; //needs to be private
    vector<int> forbidBlockVals; //needs to be private
    vector<int> rowValues; //needs to be private
    vector<int> colValues; //needs to be private
    int totalValues; //needs to be private

    Block() { //constructor
        totalValues = 0;
        for (int i=0; i<3; i++) {
            vector<Space> newRow;
            for (int j=0; j<3; j++) {
                Space newSpace;
                newRow.push_back(newSpace);
            }
            block.push_back(newRow);
        }
    }

    Space getSpace(int x, int y) { //getter for the space at index [x][y]
        return (block[x][y]);
    }

    bool isComplete() { //are there 9 values in the block?
        return (totalValues == 9);
    }

    void printBlock() {
        
    }

    vector<int> calculateBValues() { //function to calculate the values that are not allowed in a block
        for (int i=0; i<block.size(); i++) {
            for (int j=0; j<block.size(); j++) {
               cout << "i = " << i << " " << "j = " << j << endl;
                if (block[i][j].getValue()!=0) //don't need to push back the 0 - insignificant for this... (just means no value is placed yet)
                    forbidBlockVals.push_back(block[i][j].getValue());
            }
        }
        cout << "FORBIDDEN BLOCK VALS: " << endl;
        for (int i=0; i<forbidBlockVals.size(); i++) {
            cout << forbidBlockVals[i] << endl;
        }
        return forbidBlockVals;
    }

    void getCol(int col) { //get the values in the desired col (passed to function)
        for (int i=0; i<3; i++) {
            colValues.push_back(block[i][col].getValue());
        }
        cout << "COL VALUES: " << endl;
        for (int i=0; i<colValues.size(); i++) {
            cout << colValues[i] << endl;
        }
    }

    void getRow(int row) { //get the values in the desired row (passed to function)
        for (int i=0; i<3; i++) {
            rowValues.push_back(block[row][i].getValue());
        }
        cout << "ROW VALUES: " << endl;
        for (int i=0; i<rowValues.size(); i++) {
            cout << rowValues[i] << endl;
        }
    }

};




class Board { 
    vector<vector<Block>> board;
public:
    vector<int> forbidRowVals; //needs to be private
    vector<int> forbidColVals; //needs to be private
    Board() { //constructor
        for (int i=0; i<3; i++) {
            vector<Block> newRow;
            for (int j=0; j<3; j++) {
                Block newBlock;
                newRow.push_back(newBlock);
            }
            board.push_back(newRow);
        }
    }

    Block getBlock(int x, int y) { //getter for a block at index [x][y]
        return (board[x][y]);
    }

    vector<int> readGivens(string &fileName) { //function to read in givens from a file
        vector<string> line; 
        vector<string> tokens;
        vector<int> tokens2;
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
            while(getline(ss, intermediate, ',')) { //parse with comma
                tokens.push_back(intermediate);
            }
        }
        for (int t=0; t<tokens.size(); t++) {
            stringstream sss(tokens[t]);
            while(getline(sss, intermediate2, ':')) { //parse with colon
                tokens2.push_back(stoi(intermediate2));
            }
        }
        return (tokens2);       

    }
    void placeGivens(vector<int>  tokens2, Board &gameBoard) { //use the givens read in function above to populate the board
        int blockX, blockY;
        int spaceX, spaceY;
        int value;
        for (int i=0; i<tokens2.size();) {
            blockX = tokens2[i];
            i++;
            blockY = tokens2[i];
            i++;

            spaceX = tokens2[i];
            i++;
            spaceY = tokens2[i];
            i++;
        
            value = tokens2[i];
            i++;

            //cout << "Value: " << value << endl;
            board[blockX][blockY].block[spaceX][spaceY].setValue(value);
            board[blockX][blockY].totalValues++; //incremement tracker for totalValues
        }
    //cout << "value at Board[1][1]Block[1][0] which should be 8" << endl;
   // cout << board[1][1].block[1][0].getValue() << endl;
    }

    bool checkBoardCol(int col, int value) { //is the value I'm trying to place in a space already present in the col?
        for (int i=0; i<3; i++) {
            board[i][col].getCol(col);
            for (int k=0; k<board[i][col].colValues.size(); k++) {
                cout << "forbidden COL values: " << board[i][col].colValues[k] << endl;
                if (board[i][col].colValues[k] == value) {
                    //value is in the vector = VIOLATION!
                    return true;
                }
            }
        }
        return false;
    }

    bool checkBoardRow(int row, int value) { //is the value I'm trying to palce in a space already present in the row?
        for (int i=0; i<3; i++) {
            board[row][i].getRow(row); //returns a vector with the numbers in row for that block
            for (int k=0; k<board[row][i].rowValues.size(); k++) {
                cout << "forbidden ROW values: " << board[row][i].rowValues[k] << endl;
                if(board[row][i].rowValues[k] == value) {
                    //value is in the vector = VIOLATION!
                    return true;
                }
            }
        }
        return false;
    }

    bool checkForbidBlockVals(int i, int j, int value) { //is the value I'm trying to place in a space already present in the block?
        board[i][j].calculateBValues(/*i, j*/);
        for (int k=0; k<board[i][j].forbidBlockVals.size(); k++) {
            cout << "forbidden block values: " << board[i][j].forbidBlockVals[k] << endl;
            if (board[i][j].forbidBlockVals[k] == value) {
                //value is in the vector = VIOLATION!
                return true;
            }
        }
        return false;
    }

    bool checkViolation(int row, int col, int value) { //call the function above and determine if placing the value would violate game rules 
        if(checkForbidBlockVals(row, col, value)==true) {
            //VIOLATED! Cannot place a block here
            cout << "VIOLATED!" << endl;
            return true; //might want to call another function here or something... it could be important to determine why this number can't go here? ie: what kind of violation to backtrace steps? or too much work for function later... idk
        }
        if (checkBoardRow(row, value)==true) {
            cout << "VIOLATED!" << endl;
            return true;
        }
        if (checkBoardCol(col, value)==true) {
            cout << "VIOLATED!" << endl;
            return true;
        }
        cout << "NO VIOLATION!" << endl;
        return false;
    }

    /*void printBoard(int &row, int &col) {
        cout<<" ";
        int i=1,j;
        for(j = 0; j <= 4*col; j++){
            cout<<" ";
        }
        cout<<endl;
        for(i = 0; i <= 2*row; i++){
            if(i%2!=0)
                cout << " ";
            for(j = 0; j <= 2*col; j++){
            if(i%2==0)
            {
                if(j==0)
                    cout<<" ";
                if(j%2==0)
                    cout<<" ";
                else cout<<"---";
            }
            else{
                if(j%2==0)
                    cout<<"|";
                else cout<<"   ";
            }
            }
            cout<<endl;
        }
        cout<<" ";
        for(j = 0, i = 1; j <= 4*col; j++){

            cout<<" ";
        }
        cout<<endl;
    }*/

    void solve(int tryValue) {


    }

    bool isSolved() {

        return false;
    }

    Block findBestBlock() { //function to find the block with the fewest empty spaces. Which blocks should I solve first? this tells you that
        Block currentBest;
        int best = 0;
        for (int i=0; i<board.size(); i++) {
            for (int j=0; j<board.size(); j++) {
                if (board[i][j].totalValues > best && board[i][j].isComplete() == false) {
                    currentBest = board[i][j];
                    best = currentBest.totalValues;
                }
            }
        }
        return currentBest;
    }


};



int main() {
    Board gameBoard; //create a gameBoard
    //read in file information 
    string fileName;
    cout << "Welcome To Sudoku Solver!!" << endl;
    cout << "Please enter the name of the file with givens: ";
    getline(cin, fileName);

    //int row = 9; THIS IS ALL INFO ON BOARDPRINT FUNCTION WHICH NEEDS HELP LATER
    //int col = 9;
    //gameBoard.printBoard(row,col);

    //place the givens
    gameBoard.placeGivens(gameBoard.readGivens(fileName),gameBoard);
    gameBoard.checkViolation(2,0,2); //calling this here for testing purposes.
    cout << "best block value = " << gameBoard.findBestBlock().totalValues <<endl; //calling this here for testing purposes.

    return 0;
}



