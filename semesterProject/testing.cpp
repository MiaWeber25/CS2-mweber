#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;
/*This code is an attempt to read in from file and then parse it.*/
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
}