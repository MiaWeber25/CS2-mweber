#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

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
            //add values into gameBoard
            gameBoard.gameBoard[blockX][blockY] 
            cout << "Block X: " << blockX << " Block Y: " << blockY << endl;
            cout << "Space X: " << spaceX << " Space Y: " << spaceY << endl;
            cout << "Value: " << value << endl;
        }
        Block temp;
        for (int i=0;i<gameBoard.size(); i++) {
            for (int j=0; j<gameBoard.size(); j++) {
               temp = gameBoard[i][j]; //this is the location of a BLOCK
               for (int m=0; m<temp.block.size(); m++){
                   for (int n=0; n<temp.block.size(); n++) {
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