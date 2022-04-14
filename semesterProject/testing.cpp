#include <iostream>
#include <iomanip>

using namespace std;
//prototypes:
void printNewLine();


void printSpace() {
    cout << setw(1) << "--"; 


}


void printBlock() {
    for (int i=0; i<3; i++) {
        printNewLine();
        for (int j=0; j<3; j++) {
            printSpace();
        }
    }

}


void printBoard() {
    for (int i=0; i<3; i++) { //might want a seperate function to print a new line that I can call between the two loops...? This makes it just print a block seperatly form a space...
        printNewLine();
        for (int j=0; j<3; j++) {
            printBlock();
        }
    }
}

void printNewLine() {
    cout << endl;
}

int main() {
    printBoard();


    return 0;
}