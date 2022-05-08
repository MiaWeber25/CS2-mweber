//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <map> 

using namespace std;

class Space {
    int value;
    vector<int> possibleVals;
    bool isGiven;
    bool isAttempted; //value is an attempted solution 
public:
    Space(int newValue=0, bool newIsGiven = false) { //constructor
        value = newValue;
        isGiven = newIsGiven;
    }

    void setPossibleVals(int newValue) {
        possibleVals.push_back(newValue);
    }
    vector<int> getPossibleVals() {
        return possibleVals;
    }

    void printPossibleVals() {
        cout << "size: " << possibleVals.size() << endl;
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

    void setIsGiven(bool theBool) {
        isGiven = theBool;
    }

    void setIsAttempted(bool theBool) {
        isAttempted = theBool;
    }
};

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
    /*Space* getSpaceLocation() {
        return spaceLocation;
    }*/

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

class Block {
   // vector<vector<Space>> block;
   vector<int> forbidBlockVals;
   //vector<int> rowValues;
   //vector<int> colValues;
public:
    vector<vector<Space>> block; //needs to be private
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

    bool isComplete() { //are there 9 values in the block?
        return (totalValues == 9);
    }


    vector<int> calculateBValues() { //function to calculate the values that are not allowed in a block
        for (int i=0; i<block.size(); i++) {
            for (int j=0; j<block.size(); j++) {
                if (block[i][j].getValue()!=0) //don't need to push back the 0 - insignificant for this... (just means no value is placed yet)
                    forbidBlockVals.push_back(block[i][j].getValue()); //use getter on line below instead...
            }
        }
        return forbidBlockVals;
    }
    vector<int> getCol(int sCol) { //get the values in the desired col (passed to function)
        vector<int> colValues;
        for (int i=0; i<3; i++) {
            colValues.push_back(block[i][sCol].getValue());
        }
        return colValues;
    }
    vector<int> getRow(int sRow) { //get the values in the desired row (passed to function)
        vector<int> rowValues;
        for (int i=0; i<3; i++) {
            rowValues.push_back(block[sRow][i].getValue());
        }
        return rowValues;
    }
};


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
            return true;
        }
        else if (checkColViolation(bCol, sCol, value)==true) {
            return true;
        }
        else {
            return false;
        }
    }
    
//start with iterativly, then make recurssive.
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
                        cout << "board[" << blockX << "][" << blockY << "] Block[" << spaceX << "][" << spaceY << "] =" << endl;
                        for (int k=1; k<=9; k++) {
                            if(!checkViolation(blockX, blockY, spaceX, spaceY, k)) { //no violation --> add to vector?
                                cout << k << endl;
                                board[blockX][blockY].block[spaceX][spaceY].setPossibleVals(k);                                
                                answers.push_back(k);
                            } else {
                                //cout << "tried " << k << " but DID VIOLATE!" << endl;
                            }
                        }
                        if (answers.size() ==1) {
                            board[blockX][blockY].block[spaceX][spaceY].setValue(answers[0]);
                            //change bool flag for guarrenteedValue -wait
                            //change update flag
                            cout << "would place a value here" << endl;
                            boardUpdate = true;
                        }
                    }
                }
            }
        }
        //outputBoard();
        secondSolve();
    }

    /*void outputBoard() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                int blockX = i/3;
                int blockY = j/3;
                int spaceX = i%3;
                int spaceY = j%3;
                cout << "board[" << blockX << "][" << blockY << "] Block[" << spaceX << "][" << spaceY << "] =" << endl;
                cout << board[blockX][blockY].block[spaceX][spaceY].getValue() << endl;
            }
        }*/
        void outputBoard() { 
            for (int r = 0; r < 9; r++){
                for (int c = 0; c < 9; c++) {
                    if(c == 3 || c == 6)
                        cout << " | ";
                        cout << board[r/3][c/3].block[r%3][c%3].getValue() << " ";
                        //cout << "9" << " ";
                    }
                    if(r == 2 || r == 5) {
                        cout << endl;
                        for(int k = 0; k<9; k++)
                            cout << "---";
                        }
                        cout << endl;
                    }

            }
//---------------------------------BELOW HERE IS STACK-------------------------------------------------------------------
    void secondSolve() {
        map<int, SpaceReference> line;
        int counter = 0;
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                int blockX = i/3;
                int blockY = j/3;
                int spaceX = i%3;
                int spaceY = j%3;
                //cout << "CURRENTLY CHECKING: board[" << blockX << "][" << blockY << "] block[" << spaceX << "][" << spaceY << "]" << endl;
                SpaceReference sr;
                sr.resetSR();

                sr.setBoardCol(blockY);
                sr.setBoardRow(blockX);
                sr.setSpaceCol(spaceY);
                sr.setSpaceRow(spaceX);
                sr.setSpaceLocation(&board[blockX][blockY].block[spaceX][spaceY]);
                if (board[blockX][blockY].block[spaceX][spaceY].getValue() == 0) {
                    line[counter] = sr;
                    cout << "size of line = " << line.size() << endl;
                }
            }
        }
        bool setCell = false;
        for (unsigned int k=0; k<line.size(); k++) {
            for (unsigned int n=line[k].getSpace().getValue(); n<=9; n++) {
                if (!checkViolation(line[k].getBoardRow(),line[k].getBoardCol(),line[k].getSpaceRow(),line[k].getSpaceCol(), n)) {
                    setCell = true;
                    line[k].getSpace().setValue(n);
                }
            }
            if (!setCell) {
                line[k].getSpace().setValue(0);
                k--;
            }
           
        }
    }
		    // In our discussion, I think you were just going to add all the cells with 0 value to the map.
		    // then, you can loop over the map and it makes moving back and forth much simpler. I think this
		    // logic will be a problem if you set the values BEFORE you have a reference to one a cell with 
		    // mulitple possible values (line 368). I would think about something like this pseudo code:
		    /*
		     
		       map multiValueCells;
		       int cellCounter=0;
		       for (...i ) {
		         for (...j ) {
			   spaceReference sr;
			   sr.setStuff(...)
			   multiValueCells.put(cellCounter++, sr);

			 }
		       }

		       then, AFTER you have all the cells in the map

		       bool setCell=false
		       for (int k=0; k<multiValueCells.length; k++) {

                         for (int n=multiValueCells.get(k).getValue(); n<=9; n++) {                            
                           if (!checkViolation(blockX, blockY, spaceX, spaceY, n)) {
			     setCell=true;
			     multiValueCells.get(k).setValue(n);
			   }
			 }
			 if (!setCell) {
			   didn't find a valid value so move back
			   multiValueCells.get(k).setValue(0)
			   k--;
			 }
		       }
		        


		    */

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
    gameBoard.outputBoard(); //**COMMENTED OUT FOR TESTING PURPOSES

    //cout << "best block value = " << gameBoard.findBestBlock().totalValues <<endl; //calling this here for testing purposes.
    return 0;
}
