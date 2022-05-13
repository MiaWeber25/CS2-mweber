/*
    CSCI 112 Semester Project
    Sudoku Solver
    By: Mia Weber
    05-13-2022
*/
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <map> 

using namespace std;

//class for each individual Cell on the sudoku board
class Space {
    int value;
    vector<int> possibleVals;
    bool isGiven; //value in .txt
    bool isAttempted; //value is an attempted solution 
public:
    Space(int newValue=0, bool newIsGiven = false) { //constructor
        value = newValue;
        isGiven = newIsGiven;
    }

    void setPossibleVals(int newValue) { //setter for possible vals
        possibleVals.push_back(newValue);
    }

    vector<int> getPossibleVals() { //getter for possible vals
        return possibleVals;
    }

    void printPossibleVals() {
        for (int i=0; i<possibleVals.size(); i++) {
            cout << possibleVals[i] << endl;
        }
    }

    void setValue(int newValue) { //setter for value
        value = newValue;
    }

    int getValue() { //getter for value
        return value;
    }

    void setIsGiven(bool theBool) { //setter for isGiven
        isGiven = theBool;
    }

    void setIsAttempted(bool theBool) { //setter for isAttempted
        isAttempted = theBool;
    }
};

//class to save information of a space (used in secondSolve)
class SpaceReference {
    int boardRow, boardCol;
    int spaceRow, spaceCol;
    Space* spaceLocation;

    public:
    int getBoardRow() {
        return boardRow;
    }
    int getBoardCol() {
        return boardCol;
    }
    int getSpaceRow() {
        return spaceRow;
    }
    int getSpaceCol() {
        return spaceCol;
    }
    Space getSpace() {
        return *spaceLocation;
    }

    void setBoardRow(int& newBoardRow) {
        boardRow = newBoardRow;
    }
    void setBoardCol(int &newBoardCol) {
        boardCol = newBoardCol;
    }
    void setSpaceRow(int &newSpaceRow) {
        spaceRow = newSpaceRow;
    }
    void setSpaceCol(int &newSpaceCol) {
        spaceCol = newSpaceCol;
    }
    void setSpaceLocation(Space *newSpaceLocation) {
        spaceLocation = newSpaceLocation;
    }
    void resetSR() {
        boardRow = 0;
        boardCol = 0;
        spaceRow = 0;
        spaceCol = 0;
        spaceLocation = NULL; //should I be doing this? could cause problems later...
    }
};

//class for 3x3 grid of spaces
class Block {
   vector<int> forbidBlockVals;
   vector<int> rowValues;
   vector<int> colValues;
public:
    vector<vector<Space>> block; 
    int totalValues; 

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

    int getForbiddenBlockVals(int value) {
        return forbidBlockVals[value];
    }
    int getForbiddenBlockValsSize() {
        return forbidBlockVals.size();
    }

    bool isComplete() { //are there 9 values in the block?
        return (totalValues == 9);
    }

    vector<int> calculateBValues() { //function to calculate the values that are not allowed in a block
        forbidBlockVals.clear();
        for (int i=0; i<block.size(); i++) {
            for (int j=0; j<block.size(); j++) {
                if (block[i][j].getValue()!=0) //don't need 0 (0=empty space)
                    forbidBlockVals.push_back(block[i][j].getValue());
            }
        }
        return forbidBlockVals;
    }

    vector<int> getCol(int sCol) { //get the values in the desired col
        colValues.clear();
        for (int i=0; i<3; i++) {
            colValues.push_back(block[i][sCol].getValue());
        }
        return colValues;
    }
    vector<int> getRow(int sRow) { //get the values in the desired row
        rowValues.clear();
        for (int i=0; i<3; i++) {
            rowValues.push_back(block[sRow][i].getValue());
        }
        return rowValues;
    }
};

//class for 3x3 grid of blocks
class Board {
    vector<vector<Block>> board;
    vector<int> neededValues;
public:
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

    void addNeededValues(int &value) {
        neededValues.push_back(value);
    }

    bool checkNeededValues(int &value) {
        vector<int>::iterator it;
        it = find(neededValues.begin(), neededValues.end(), value);
        return (it != neededValues.end()); //true -> found the element
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
            board[blockX][blockY].block[spaceX][spaceY].setValue(value);
            board[blockX][blockY].totalValues++; //incremement tracker for totalValues
            board[blockX][blockY].block[spaceX][spaceY].setIsGiven(true);
        }
    }

    bool checkColViolation(int bCol, int sCol, int value) { //is the value I'm trying to place in a space already present in the col?
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][bCol].getCol(sCol)[j] == value) {
                    return true;
                }
            }
        }
        return false;
    }

   bool checkRowViolation(int bRow, int sRow, int value) { //is the value I'm trying to palce in a space already present in the row?
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[bRow][i].getRow(sRow)[j]==value) {
                    return true;
                }
            }
        }
        return false;
    }

    bool checkForbidBlockVals(int i, int j, int value) { //is the value I'm trying to place in a space already present in the block?
        board[i][j].calculateBValues();
        for (int k=0; k<board[i][j].getForbiddenBlockValsSize(); k++) {
            if (board[i][j].getForbiddenBlockVals(k)==value) {
                return true;
            }
        }
        return false;
    }

    //check a block row & col, and a space row & col for a value
    bool checkViolation(int bRow, int bCol, int sRow, int sCol, int value) { //call the function above and determine if placing the value would violate game rules
        if(checkForbidBlockVals(bRow, bCol, value)==true) {
            //VIOLATED! Cannot place a block here
            return true;
        }
        if (checkRowViolation(bRow, sRow, value)==true) {
            //cout << "Violated row val" << endl;
            return true;
        }
        else if (checkColViolation(bCol, sCol, value)==true) {
            //cout << "Violated col val" << endl;
            return true;
        }
        else {
            return false;
        }
    }
    
    void firstSolve() {
        bool boardUpdate = true;
        vector<int> answers;
        while(boardUpdate) {
            boardUpdate = false;
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                        int blockX = i/3; //row
                        int blockY = j/3;
                        int spaceX = i%3;
                        int spaceY = j%3;
                     if (board[blockX][blockY].block[spaceX][spaceY].getValue() == 0) { //empty space
                        answers.clear();
                        for (int k=1; k<=9; k++) {
                            if(!checkViolation(blockX, blockY, spaceX, spaceY, k)) { //no violation --> add to vector?
                                board[blockX][blockY].block[spaceX][spaceY].setPossibleVals(k);                                
                                answers.push_back(k);
                            } 
                        }
                        if (answers.size() ==1) {
                            board[blockX][blockY].block[spaceX][spaceY].setValue(answers[0]);
                            boardUpdate = true;
                        }
                    }
                }
            }
        }
        secondSolve();
    }

    void outputBoard() { 
        for (int r = 0; r < 9; r++){
            for (int c = 0; c < 9; c++) {
                if(c == 3 || c == 6)
                    cout << " | ";
                    cout << board[r/3][c/3].block[r%3][c%3].getValue() << " ";
            }
            if(r == 2 || r == 5) {
                cout << endl;
                for(int k = 0; k<9; k++)
                    cout << "---";
            }
            cout << endl;
        }
    }

    void secondSolve() {
        map<int, SpaceReference> line;
        int counter = 0;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                int blockX = i/3;
                int blockY = j/3;
                int spaceX = i%3;
                int spaceY = j%3;
                SpaceReference sr;
                
                if (board[blockX][blockY].block[spaceX][spaceY].getValue() == 0) {
                    sr.resetSR();
                    sr.setBoardCol(blockY);
                    sr.setBoardRow(blockX);
                    sr.setSpaceCol(spaceY);
                    sr.setSpaceRow(spaceX);
                    sr.setSpaceLocation(&board[blockX][blockY].block[spaceX][spaceY]);
                    line.insert({counter, sr}); 
                    counter++;
                }
            }
        }
        bool setCell = false;

        for (unsigned int k=0; k<line.size(); k++) {
            setCell = false;
            for (unsigned int n=line[k].getSpace().getValue()+1; n<=9 && !setCell; n++) { //could be an issue here with the reference to the sapce...
                if (!checkViolation(line[k].getBoardRow(),line[k].getBoardCol(),line[k].getSpaceRow(),line[k].getSpaceCol(), n)) {
                    setCell = true;
                    board[line[k].getBoardRow()][line[k].getBoardCol()].block[line[k].getSpaceRow()][line[k].getSpaceCol()].setValue(n);
                }
            }
            if (!setCell) { 
                board[line[k].getBoardRow()][line[k].getBoardCol()].block[line[k].getSpaceRow()][line[k].getSpaceCol()].setValue(0);
                k=k-2;
            }
        }
    }

    Block findBestBlock() { //function to find the block with the fewest empty spaces.
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

    //place the givens
    gameBoard.placeGivens(gameBoard.readGivens(fileName),gameBoard);
   
    cout << endl;
    gameBoard.outputBoard();
    cout << endl;
    
    gameBoard.firstSolve(); 
    cout << "*************Completed Sudoku Board*************" << endl << endl;
    gameBoard.outputBoard();

    return 0;
}
