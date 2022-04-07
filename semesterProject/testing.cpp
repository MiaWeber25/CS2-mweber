#include <iostream>
#include <math.h>

using namespace std;

void printSpace(int &, int &);
void printSpaceValue();
void printBoard();
void printBlock();

int main() {
  printBoard();
  //printSpace(row,col);
  return 0;
}

void printSpace(int &row, int &col) {
  for (int m=0; m<=row; m++) {
    cout << "beginning m: " << m << endl;
    for (int n=0; n<=col; n++) {
      cout << "beginning n: " << n << endl;
      cout<<" ";
      int i=1,j;
      for(j = 0; j <= 4*n; j++){ //4*col
        cout<<" ";
      }
      cout<<endl;
      for(i = 0; i <= 2*m; i++){ //2*row
        if(i%2!=0)
        cout << " ";
        for(j = 0; j <= 2*n; j++){ //2*col
          if(i%2==0) {
            if(j==0)
              cout<<" ";
            if(j%2==0)
              cout<<" ";
            else cout<<"---";
          }
          else{
            if(j%2==0)
              cout<<"|";
            //else cout<<" 6 "; //THIS IS THE SPACE FOR THE VALUE
            else printSpaceValue();
          }
        }
        cout<<endl;
      }
      cout<<" ";
      for(j = 0, i = 1; j <= 4*n; j++){ //4*col
        cout<<" ";
      }
      cout<<endl;
      }
  }
}

void printSpaceValue() {
  cout <<" 6 ";
}


void printBlock(int &row, int &col) {
  printSpace(row,col);
}

void printBoard() {
  int row, col;
  row = 3;
  col =3;
  printBlock(row, col);
}