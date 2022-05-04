//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
//#include <iomanip> //MIGHT NEED THIS LATER FOR OUTPUT FORMATTING
#include <algorithm>
#include <stack>
//include <iterator> //MIGHT NOT NEED THIS BECAUSE I FOUND A NEW WAY TO SEARCH FOR VALUES IN VECTORS

using namespace std;


class Space {
    int value;
    //vector<int> forbiddenValues;
    bool isGiven;
    bool isAttempted; //value is an attempted solution 
public:
    Space(int newValue=0, bool newIsGiven = false) { //constructor
        value = newValue;
        isGiven = newIsGiven;
    }

    void setValue(int newValue) { //setter for value
        value = newValue;
    }
    int getValue() { //getter for value
        return value;
    }

    void setIsGiven(bool theBool) {
        isGiven = theBool;
    }

    void setIsAttempted(bool theBool) {
        isAttempted = theBool;
    }

    /*void setForbiddenValue(int value) { //setter for forbiddenValue
        forbiddenValues.push_back(value);
    }
    int getForbiddenValue(int index) { //NOT USING EITHER OF THESE RIGHT NOW...
        return forbiddenValues[index];
    }*/

    void placeNumber() {

    }

    void switchNumber() {

    }

    void newPossibility() {

    }

};

class SpaceReference {
    int boardRow, boardCol;
    Space* spaceLocation;

    public:
    int getBoardRow() {
        return boardRow;
    }
    int getBoardCol() {
        return boardCol;
    }
    Space* getSpaceLocation() {
        return spaceLocation;
    }

    void setBoardRow(int& newBoardRow) {
        boardRow = newBoardRow;
    }
    void setBoardCol(int &newBoardCol) {
        boardCol = newBoardCol;
    }
    void setSpaceLocation(Space *newSpaceLocation) {
        spaceLocation = newSpaceLocation;
    }

};



class Block {
   // vector<vector<Space>> block;
   vector<int> forbidBlockVals;
   //vector<int> rowValues;
   //vector<int> colValues;
public:
    vector<vector<Space>> block; //needs to be private
    //vector<int> forbidBlockVals; //needs to be private
    //vector<int> rowValues; //needs to be private
    //vector<int> colValues; //needs to be private
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

    int getForbiddenBlockVals(int value) {
        return forbidBlockVals[value];
    }
    int getForbiddenBlockValsSize() {
        return forbidBlockVals.size();
    }

    /*int getRowValues(int value) {
        return rowValues[value];
    }
    int getRowValuesSize() {
        return rowValues.size();
    }

    int getColValues(int value) {
        return colValues[value];
    }
    int getColValuesSize() {
        return colValues.size();
    }*/

    bool isComplete() { //are there 9 values in the block?
        return (totalValues == 9);
    }

    void printBlock() {

    }

    vector<int> calculateBValues() { //function to calculate the values that are not allowed in a block
        for (int i=0; i<block.size(); i++) {
            for (int j=0; j<block.size(); j++) {
                if (block[i][j].getValue()!=0) //don't need to push back the 0 - insignificant for this... (just means no value is placed yet)
                    forbidBlockVals.push_back(block[i][j].getValue()); //use getter on line below instead...
            }
        }
        //cout << "FORBIDDEN BLOCK VALS: " << endl;
        //for (int i=0; i<forbidBlockVals.size(); i++) {
        //    cout << forbidBlockVals[i] << endl;
       // }
        return forbidBlockVals;
    }

    vector<int> getCol(int sCol) { //get the values in the desired col (passed to function)
        vector<int> colValues;
        for (int i=0; i<3; i++) {
            colValues.push_back(block[i][sCol].getValue());
        }
        //cout << "COL VALUES: " << endl;
        //for (int i=0; i<colValues.size(); i++) {
        //    cout << colValues[i] << endl;
        //}
        return colValues;
    }

    vector<int> getRow(int sRow) { //get the values in the desired row (passed to function)
        vector<int> rowValues;
        for (int i=0; i<3; i++) {
            rowValues.push_back(block[sRow][i].getValue());
        }
        //cout << "ROW VALUES: " << endl;
        //for (int i=0; i<rowValues.size(); i++) {
        //    cout << rowValues[i] << endl;
        //}
        return rowValues;
    }
};


class Board {
    vector<vector<Block>> board;
    vector<int> neededValues;
public:
    //vector<int> forbidRowVals; //needs to be private
   // vector<int> forbidColVals; //needs to be private
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

            //cout << "Value: " << value << endl;
            board[blockX][blockY].block[spaceX][spaceY].setValue(value);
            board[blockX][blockY].totalValues++; //incremement tracker for totalValues
            board[blockX][blockY].block[spaceX][spaceY].setIsGiven(true);
        }
    //cout << "value at Board[1][1]Block[1][0] which should be 8" << endl;
   // cout << board[1][1].block[1][0].getValue() << endl;
    }

    bool checkColViolation(int bCol, int sCol, int value) { //is the value I'm trying to place in a space already present in the col?
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[i][bCol].getCol(sCol)[j] == value) {
                    //cout << "Violation from checkColViolation()";
                    return true;
                }
            }

        }
        //cout << "No violation from checkColViolation()";
        return false;
    }

   bool checkRowViolation(int bRow, int sRow, int value) { //is the value I'm trying to palce in a space already present in the row?
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (board[bRow][i].getRow(sRow)[j]==value) {
                   // cout << "Violation from checkRowViolation()" << endl;
                    return true;
                }
            }

        }
        //cout << "No violation from checkRowViolation()" << endl;
        return false;
    }

    bool checkForbidBlockVals(int i, int j, int value) { //is the value I'm trying to place in a space already present in the block?
        board[i][j].calculateBValues();
        for (int k=0; k<board[i][j].getForbiddenBlockValsSize(); k++) {
            if (board[i][j].getForbiddenBlockVals(k)==value) {
                //value is in the vector = VIOLATION!
                return true;
            }
        }
        return false;
    }

    //check a block row & col, and a space row & col for a value
    bool checkViolation(int bRow, int bCol, int sRow, int sCol, int value) { //call the function above and determine if placing the value would violate game rules
   //cout << "bRow = " << bRow << endl;
    //cout << "bCol = " << bCol << endl;
    //cout << "sRow = " << sRow << endl;
   // cout << "sCol = " << sCol << endl;
   // cout << "value = " << value << endl;
        if(checkForbidBlockVals(bRow, bCol, value)==true) {
            //VIOLATED! Cannot place a block here
            //cout << "violated forbidden block vals" << endl;
            return true; //might want to call another function here or something... it could be important to determine why this number can't go here? ie: what kind of violation to backtrace steps? or too much work for function later... idk
        }
        if (checkRowViolation(bRow, sRow, value)==true) {
            //cout << "violated forbidden row vals" << endl;
            return true;
        }
        else if (checkColViolation(bCol, sCol, value)==true) {
            //cout << "violated forbidden col vals" << endl;
            return true;
        }
        else {
            //cout << "NO VIOLATION FROM CHECKVIOLATION()" << endl;
            return false;
        }

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


    /*void printBoard() {
        vector<int> tRow;
        vector<int> mRow;
        vector<int> bRow;
        for (int i=0; i<board.size(); i++) {
            for (int j=0; j<board.size(); j++) {
                for (int k=0; k<3; k++) {
                    tRow.push_back(board[i][j].block[0][k].getValue());
                    mRow.push_back(board[i][j].block[1][k].getValue());
                    bRow.push_back(board[i][j].block[2][k].getValue());            }
                }
        }

        cout << "tRow.size() = " << tRow.size() << endl;
        for (int i=0; i<tRow.size(); i++) {
            cout << "tRow @ " << i << " = " << tRow[i] << endl;
        }

        for (int count=0; count<tRow.size();) {
            for (int i=count; i<tRow.size(); i++) {
                cout << tRow[i] << " ";
                if (i==2 || i==5) {
                    cout << "  ";
                }
            }
            cout << endl;

            for (int i=count; i<tRow.size(); i++) {
                cout << mRow[i] << " ";
                if (i==2 || i==5) {
                    cout << "  ";
                }
            }
            cout << endl;

            for (int i=count; i<tRow.size(); i++) {
                cout << bRow[i] << " ";
                if (i==2 || i==5) {
                    cout << "  ";
                }
            }
            cout << endl << endl;
            count = count+8;
        }
    }*/
//start with iterativly, then make recurssive.
    void firstSolve(/*Block inBlock*/) {
        bool boardUpdate = true;
        //Board b;
        vector<int> answers;
        cout << "Solve was called" << endl << endl;
        while(boardUpdate) {
            boardUpdate = false;
            for (int i=0; i<9; i++) {
                for (int j=0; j<9; j++) {
                        int blockX = i/3;
                        int blockY = j/3;
                        int spaceX = i%3;
                        int spaceY = j%3;
                    if (getBlock(blockX, blockY).getSpace(spaceX, spaceY).getValue() == 0) { //empty space!
                        ///////cout << "empty space @ [" << blockX << "][" << blockY << "] [" << spaceX << "][" << spaceY << "] " << endl;
                        answers.clear();
                        for (int k=1; k<=9; k++) {
                            if(!checkViolation(blockX, blockY, spaceX, spaceY, k)) { //no violation --> add to vector?
                                /////////cout << "no violation! adding " << k << " to the vector" << endl;
                                answers.push_back(k);
                            }
                        }
                        if (answers.size() ==1) {
                            board[blockX][blockY].block[spaceX][spaceY].setValue(answers[0]);
                            //change bool flag for guarrenteedValue -wait
                            //change update flag
                            boardUpdate = true;
                        }
                    }
                }
            }
        }
        secondSolve();
    }

    void outputBoard() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                int blockX = i/3;
                int blockY = j/3;
                int spaceX = i%3;
                int spaceY = j%3;
                cout << "board[" << blockX << "][" << blockY << "] Block[" << spaceX << "][" << spaceY << "] =" << endl;
                cout << board[blockX][blockY].block[spaceX][spaceY].getValue() << endl;
            }
        }
    }

    void secondSolve() {
        //use a stack!
        stack<SpaceReference> myLine;
        cout << "board.size() = " << board.size() << endl;
        for (int i=0; i<board.size(); i++) {
            cout << "I VALUE = " << i << endl;
            for (int j=0; j<board.size(); j++) {
                cout << "J VALUE = " << j << endl;
                SpaceReference sr;
                int blockX = i/3;
                int blockY = j/3;
                int spaceX = i%3;
                int spaceY = j%3;
                cout << "CURRENTLY CHECKING: board[" << blockX << "][" << blockY << "] block[" << spaceX << "][" << spaceY << "]" << endl;
                for (int k=1; k<=9; k++) {
                    if (board[blockX][blockY].block[spaceX][spaceY].getValue() == 0) { //only ever passes this check the first time... once you assign a value in here it doesn't work...
                        if (!checkViolation(blockX, blockY, spaceX, spaceY, k)) {
                            cout << "checked k value: " << k << " and it didn't violate" << endl;
                            sr.setBoardCol(blockY);
                            sr.setBoardRow(blockX);
                            sr.setSpaceLocation(&board[blockX][blockY].block[spaceX][spaceY]);
                            board[blockX][blockY].block[spaceX][spaceY].setValue(k);
                            cout << "set the value to " << k << endl;
                            board[blockX][blockY].block[spaceX][spaceY].setIsAttempted(true);
                            cout << "marked the cell as attempted" << endl;
                            myLine.push(sr);
                            cout << "pushed space reference info on the stack" << endl;
                        }
                    } else {
                        cout << "current space is already completed" << endl;
                    }    
                } 
                //here! still in i j loop - out of k loop
                cout << "out of k looping structure." << endl;
                    if (board[blockX][blockY].block[spaceX][spaceY].getValue() == 0) { //if the value of the space is still 0
                        cout << "contents of current space is still 0" << endl;
                        if (myLine.empty()) {
                            cout << "myLine is empty" << endl;
                        } else {
                            cout << "top of stack boardCol: " << myLine.top().getBoardCol() << ' ';
                            cout << "boardRow:" << myLine.top().getBoardRow() << ' ';
                            cout << "spaceLocation: " << myLine.top().getSpaceLocation() << endl;
                            //go back to the previous block and try the next possible value
                            //myLine.top().getSpaceLocation().getValue(); //ok wait another issue... say you go back a space and pop it off and try the next value, you could still have a problem later... you can't remove it from the stack ever right???
                            //problems here: how to use [] notation since spaceLocation is a pointer
                            //it doesn't know what the next available value is, so it either needs to recalculate it or I need to include some recurssion...
                        }
            }
        }
            }
    }
       // cout << "COMPLETED ALL LOOPING. EXITING FUNCTION" << endl;
    //}
     //Block currentBlock[blockX][blockY].Block[spaceX][spaceY];
                    //need to make sure that it doesn't violate the game rules && that it isn't a given or already placed value
                    //if (board[blockX][blockY].block[spaceX][spaceY].getValue()==0 && !checkViolation(blockX, blockY, spaceX, spaceY, k)) { //if the value doesn't violate && doesn't reduce another space's possible values to 0
                        //update the spaceLocation into
                        //cout << "THE K VALUE OF: " << k << "DOESN'T VIOLATE" << endl;
                        //sr.setBoardCol(blockY);
                        //sr.setBoardRow(blockX);
                        //sr.setSpaceLocation(&board[blockX][blockY].block[spaceX][spaceY]);
                        //board[blockX][blockY].block[spaceX][spaceY].setValue(k);
                        //cout << "board[" << blockX << "][" << blockY << "] block[" << spaceX << "][" << spaceY << "] = " << board[blockX][blockY].block[spaceX][spaceY].getValue() << endl;

                        //cout << "SPACE REFERENCE INFO: " << endl;
                        //cout << "board col: " << sr.getBoardCol() << " board row: " << sr.getBoardRow() << " space location: " << sr.getSpaceLocation() << endl;
                        //mark the space as a questionValue
                        //board[blockX][blockY].block[spaceX][spaceY].setIsAttempted(true);
                        //myLine.push(sr); //push the space ID onto the stack

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



    //place the givens
    gameBoard.placeGivens(gameBoard.readGivens(fileName),gameBoard);
    //gameBoard.checkViolation(1,0,1,1,3); //pass bRow, bCol, sRow, sCol, value
    gameBoard.firstSolve(); 
    cout << "BACK IN MAIN. CALLING OUTPUTBOARD()" << endl;
  //gameBoard.outputBoard(); //**COMMENTED OUT FOR TESTING PURPOSES

    cout << "best block value = " << gameBoard.findBestBlock().totalValues <<endl; //calling this here for testing purposes.
    return 0;
}
