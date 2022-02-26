/* PARSING FILE INPUT STREAM
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;
This code is an attempt to read in from file and then parse it.
int main() {
    vector<string> line; 
    vector<string> tokens;
    vector<string> tokens2;
    string temp;

    string inFile;
    cout << "enter file name: ";
    cin >> inFile;
    
    ifstream fin;
    fin.open(inFile, ios::in);
    string intermediate;
    string intermediate2;

    while(!fin.eof()) {
        fin >> temp;
        line.push_back(temp);
    } 
    for (int t=0; t<line.size(); t++) {
        stringstream ss(line[t]);
        while(getline(ss, intermediate, ',')) {
            tokens.push_back(intermediate);
        }
    }
    for (int t=0; t<tokens.size(); t++) {
        stringstream sss(tokens[t]);
        while(getline(sss, intermediate2, ':')) {
            tokens2.push_back(intermediate2);
        }
    }

    for (int i=0; i<tokens2.size(); i++) {
        cout << tokens2[i] << endl;
    }
    return 0;
}*/

#include <iostream>
using namespace std;

void printGrid(int row, int col){
  //cout<<endl;
  //cout<<" ";
  int i=1,j;
  for(j = 0; j <= 4*col; j++){
    //if(j%4==2)
     //   cout<<i++;
   // cout<<" ";
  }
  cout<<endl;
  for(i = 0; i <= 2*row; i++){
   // if(i%2!=0)
    //  cout<<(char)(i/2 +'A');
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
   // if(i%2!=0)
    //  cout<<(char)(i/2 +'A');
    cout<<endl;
  }
  cout<<" ";
  for(j = 0, i = 1; j <= 4*col; j++){
   // if(j%4==2)
        //cout<<i++;
   // cout<<" ";
  }
  cout<<endl;
}

int main() {
  printGrid(9, 9);
  return 0;
}