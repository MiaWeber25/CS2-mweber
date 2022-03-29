#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
  vector<string> sampleInput;
  //sampleInput.push_back("9","X","7")


  Board gameBoard;
  Block b;
  gameBoard.addBlocks(b); //b would be the block in a board

  return 0;
}

class BlockID {
  public:
  int x, y;

};

class Board {
  public:
  vector<vector<Block>> board;
  void addBlocks(Block &b) {
    for (int i=0; i<board.size(); i++){
      for (int j=0; j<board.size(); j++) {
        board[i][j] = b; //b would be the block in a board
      }
    }
  }

  void addBlock(BlockID &blockID) {
    //board[blockID.x][blockID.y] = asdkljasdf;
    addValue(board[blockID.x][blockID.y]); //THIS IS WHAT I WANT TO GET TO WORK... or I could create a "new" block above... idk
  }



};

class Block {
  vector<vector<string>> block;
  void addValues() {
    for (int i=0; i<block.size(); i++) {
      for (int j=0; j<block.size(); j++) {
        block[i][j] = "9"; //9 would be the value in a cell (STRING)
      }
    }
  }

  void addValue(Board &board) {

  }
};       