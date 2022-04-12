#include <iostream>

using namespace std;

void printContents();
void printValue();


int main() {
  printContents();
  return 0;
}
    
    
    
    void printContents(/*string &fileName,*/) { //print the contents of the spreadhsheet
        int row, col;
        row = 3;
        col = 3;
        cout<<" ";
        int i=1,j;
        for(j = 0; j <= 4*col; j++){
            if (j%4==2)
              cout<<"   ";
        }
        cout<<endl;
        for(i = 0; i <= 2*row; i++){
            if(i%2!=0)
                //cout << " ";
                cout << (char)(i/2); 
            for(j = 0; j <= 2*col; j++){
            if(i%2==0)
            {
                if(j==0)
                    cout<<" ";
                if(j%2==0) {
                    cout<<" ";
                }
                else cout<<"---------";
            }
            else{

                if(j%2==0) {
                    cout<<"|";

                }
                //else cout<<"   Hi    "; //use if statements to check if row and col match desired
                  else printValue();
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



void printValue() {
  
}