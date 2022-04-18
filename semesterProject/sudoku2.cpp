//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <math.h>
//#include <iomanip> //MIGHT NEED THIS LATER FOR OUTPUT FORMATTING
#include <algorithm>
//include <iterator> //MIGHT NOT NEED THIS BECAUSE I FOUND A NEW WAY TO SEARCH FOR VALUES IN VECTORS

using namespace std;


class Space {
    int value;
    //vector<int> forbiddenValues;
    bool isGiven;
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
            return true; //might want to call another function here or something... it could be important to determine why this number can't go here? ie: what kind of violation to backtrace steps? or too much work for function later... idk
        }
        if (checkRowViolation(bRow, sRow, value)==true) {  
            return true;
        }
        else if (checkColViolation(bCol, sCol, value)==true) {
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
    
    void solve(/*Block inBlock*/) {
        //Board b;
        cout << "Solve was called" << endl << endl;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) { 
                for (int k=1; k<=9; k++) { //k=value
                    int blockX = i/3;
                    int blockY = j/3;
                    int spaceX = i%3;
                    int spaceY = j%3;
                    cout << "calling checkViolation() on: [" << blockX << "][" << blockY << "]  [" << spaceX << "][" << spaceY << "] with value =" << k << endl;
                    if (checkViolation(blockX, blockY, spaceX, spaceY, k) == false) { //there was no violation
                        //mark the number as a computer placement
                        //place the number in the space
                        //move onto the next space
                        cout << "no violation from solve()" << endl;
                    } else { //there was a violation!
                        //try the next k value --> recurssion
                        //solve();
                        cout << "violation from solve()" << endl;

                    }
                }
            }
        }
        //return b;
    }


        /*convert index to [0][0]-[8][8]
        int bRow, bCol, sRow, sCol, value;
        findBestBlock(); //somehow we need to acccess the index of best block...
        //loop over bestBlocks
        //loop over least forbidden values (?)
        //pass space(?) if checkViolation is false (the value can go there) --> move onto the next space. checkViolation is true, call yourself with the previous block's next possible value
        checkViolation(bRow,bCol,sRow,sCol,value);
        blockSolve(findBestBlock());
        //second method: pure recurssion: 
        
        int blockX;
        for (int i=0; i<board.size(); i++) {
            for (int j=0; j<board.size(); j++) {
                blockX = i / 3;
            }
        }*/

    /*void blockSolve(Block b) {
        //get index of b...
        for (int i=0; i<9; i++) {
            for (int j=0; j<9;j++) {
                for (int k=0; k<9; k++) {
                    if (checkViolation(0,0,i,j,k) == false) { //0,0 needs to be replaced with the index of b... (mod and divide stuff here??)
                        //place the number!
                    } else {
                        //don't place the number and try with the next k value...
                    }
                }
            }
        }
    }*/

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
    gameBoard.solve();
    
    cout << "best block value = " << gameBoard.findBestBlock().totalValues <<endl; //calling this here for testing purposes.
    return 0;
}



