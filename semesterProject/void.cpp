
/*
    //all the code above does is read data into temp and then add temp to line vector
    //code below attempts to then parse that data... doesn't work, and still doesn't account for ','
    for(int i=0; i<line.size(); i++) {
        stringstream ss(line[i]);
        while(getline(ss,intermediate, ':')) {
            tokens.push_back(intermediate);
        }
    }

     This code seems to be working when the data values are assigned to input rather than read from a file. 
    Attempt to combine this logic with file input is above

    vector<string> firstValue;
    vector<string> secondValue;

    string input = "1:1, 2:2, 3:3";
    istringstream ss(input);
    string token;

    while (getline(ss, token, ',')) {
        while(getline(ss, token, ':'))
            cout << token << endl;
    }*/

    return 0;
}


/*This code is working to read in from a file in form "2:3" or "1:2"*/
int readFromFile() {
    string inFile;
    vector<string> line;
    string temp;
    cout << "enter name of file to read from: ";
    cin >> inFile;
    ifstream fin;
    fin.open(inFile, ios::in);
    while(!fin.eof()) {
        fin >> temp;
        line.push_back(temp);
    }
    for (int i=0; i<line.size(); i++)
        cout << "line: " << line[i] << endl;
    return 0; 
}
/*
int main()
{
    //file io into a vector then use stringstream to parse each string in the vector?
    string inFile;
    vector<string> line;
    string temp;
    string the;
    string token;
    cout << "enter the name of the file to read from: ";
    cin >> inFile;
    ifstream fin;
    fin.open(inFile, ios::in);
    istringstream theStream(the); //put the vector in place of the?
    while(!fin.eof()) {
        line.push_back(temp);
    }
    for (int i=0; i<line.size();i++) {
        cout << "line: " << line[i] << endl;
    }

    while(!cin.eof()) {
        string line;
        getline(cin,line);
        stringstream lineStream(line);

        string word;
        while(!lineStream.eof()) {
            getline(lineStream, word, ',');
            cout << "[" << word << "]" << endl;
        }
    }
    return 0;
}*/




/*
int main() {
    string inFile;
    cout << "enter name of file to read from: ";
    cin >> inFile;
    ifstream fin;
    fin.open(inFile, ios::in);
    
    string line;
    stringstream lineStream(line);
    string temp;
    while(!lineStream.eof()) {
        getline(lineStream, temp, ':');
        cout << temp;
    }

    return 0;
}*/


