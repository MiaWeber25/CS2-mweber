//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip>

using namespace std;

//CLASS PROTOTYPES:
//class Board;
//class Block;
//class Space;
void welcomeToSudoku();
void readGivens(string&);
void printBoard();
//Block temp;



class Space {
    public:
    //bool isEmpty;
    int value;
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



class Block {
    public:
    vector<vector<Space>> block;
    vector<int> neededValues; //1-9 values

    //constructor: 
    Block() {
        vector<vector<Space>> newBlock;
        block = newBlock;
    }

    bool isComplete() {

        return false;
    }

};




class Board { //Board.gameBoard[i][j] = block???
    vector<vector<Block>> board;

    public:
    //constructor:
    Board(vector<vector<Block>> newGameBoard = {}) {
        board = newGameBoard;
    }

    void readGivens(string &fileName) {
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
        placeGivens(tokens2);        

    }
    void placeGivens(vector<int> & tokens2) {
        int blockX, blockY;
        int spaceX, spaceY;
        int value;
        Block aBlock;
        for (int i=0; i<tokens2.size();) {
            blockX = tokens2[i];
            i++;
            blockY = tokens2[i];
            i++;
            //place in gameBoard
            aBlock = board[blockX][blockY]; //THIS IS THE CORRECT BLOCK THAT THE SPACE IS IN
            //gameBoard[block[blockX][blockY]][block[blockX][blockY]];
            spaceX = tokens2[i];
            i++;
            spaceY = tokens2[i];
            i++;
            //could loop though here to see if the x and y values match, but that's more looping...
            aBlock.block[spaceX][spaceY]; //THIS SHOULD BE ON THE RIGHT PATH TO FINDING THE CORRECT SPACE WITHIN THE BLOCK
            /*for (int j=0; j<aBlock.block.size(); j++;) {
                if (aBlock.block[j][9].value == spaceX && aBlock.block[j][9].value == spaceY) {

                }
            */
            value = tokens2[i];
            i++;
            //place values in gameBoard
            //gameBoard.gameBoard[blockX][blockY] = temp;

            cout << "Block X: " << blockX << " Block Y: " << blockY << endl;
            cout << "Space X: " << spaceX << " Space Y: " << spaceY << endl;
            cout << "Value: " << value << endl;
        }
        //cout << "I GOT HERE" << endl;
        Block temp;
        cout << "GETTING HERE" << endl;
        cout << "gameBoard.size() = " << board.size() << endl;
        for (int i=0;i<board.size(); i++) {
            cout << "i FOR LOOP" << endl;
            for (int j=0; j<board.size(); j++) {
                cout << "j FOR LOOP" << endl;
               temp = board[i][j]; //this is the location of a BLOCK
               for (int m=0; m<temp.block.size(); m++){
                   cout << "m FOR LOOP" << endl;
                   for (int n=0; n<temp.block.size(); n++) {
                       cout << "n FOR LOOP" << endl;
                        temp.block[m][n].value = 9; //NEXT ISSUE
                        cout << "block at: " << m << ", " << n << temp.block[m][n].value << endl;
                   }
               }
            }
        }
    }

    void printBoard(int &row, int &col) {
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
    }

    
    bool isSolved() {

        return false;
    }
};



int main() {
    Board gameBoard;
    Block b;
    string fileName;
    cout << "Welcome To Sudoku Solver!!" << endl;
    cout << "Please enter the name of the file with givens: ";
    getline(cin, fileName);

    gameBoard.readGivens(fileName);
    int row = 9;
    int col = 9;
    gameBoard.printBoard(row,col);
    return 0;
}

