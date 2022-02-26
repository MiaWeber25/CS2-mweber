#include <iostream>
using namespace std;

void printGrid(int &userRows, int &userColumns){
  cout<<" ";
  int i=1,j;
  for(j = 0; j <= 4*userColumns; j++){
    cout<<" ";
  }
  cout<<endl;
  for(i = 0; i <= 2*userRows; i++){
    if(i%2!=0)
        cout << " ";
    for(j = 0; j <= 2*userColumns; j++){
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
  for(j = 0, i = 1; j <= 4*userColumns; j++){

    cout<<" ";
  }
  cout<<endl;
}

int main() {
  int userRows, userColumns;
  cout << "Enter the number of rows -> ";   
  cin >> userRows;   
  cout << "Enter the number of columns -> ";
  cin >> userColumns; 
  printGrid(userRows, userColumns);
  return 0;
}