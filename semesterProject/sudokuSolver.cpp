//CODE REFERENCE FOR PRINTBOARD(): https://stackoverflow.com/questions/48677066/printing-a-grid
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip>

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

    public:
    //constructor:
    Board(vector<vector<Block>> newGameBoard = {}) {
        gameBoard = newGameBoard;
    }

    void readGivens(string &fileName) {
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
            while(getline(ss, intermediate, ',')) { //parse with comma
                tokens.push_back(intermediate);
            }
        }
        for (int t=0; t<tokens.size(); t++) {
            stringstream sss(tokens[t]);
            while(getline(sss, intermediate2, ':')) { //parse with colon 
                tokens2.push_back(intermediate2);
            }
        }
        placeGivens(tokens2);        

    }
    void placeGivens(vector<string> & tokens2) {
        string blockX, blockY;
        string spaceX, spaceY;
        string value;
        for (int i=0; i<tokens2.size();) {
            blockX = tokens2[i];
            i++;
            blockY = tokens2[i];
            i++;
            //place in gameBoard
            //gameBoard[block[blockX][blockY]][block[blockX][blockY]];
            spaceX = tokens2[i];
            i++;
            spaceY = tokens2[i];
            i++;

            value = tokens2[i];
            i++;
            cout << "Block X: " << blockX << " Block Y: " << blockY << endl;
            cout << "Space X: " << spaceX << " Space Y: " << spaceY << endl;
            cout << "Value: " << value << endl;
        }
        for (int i=0;i<gameBoard.size(); i++) {
            for (int j=0; j<gameBoard.size(); j++) {
               //  temp = gameBoard[i][j]; //this is the location of a BLOCK
               
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

int main() {
    Board gameBoard;

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

