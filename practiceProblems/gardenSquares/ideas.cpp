#include <iostream>
#include <vector>

using namespace std;

void smallPlant(const vector<int>&);

int main() {
    string tempor;
    int temp;
    vector<string> plantName;
    vector<int> plantSize;
    vector<int> plantNum;

    int flag = 0;
    while (flag == 0) {
    cout << "enter plant name: ";
    cin >> tempor;
    plantName.push_back(tempor);

    cout << "enter size of plant: ";
    cin >> temp;
    plantSize.push_back(temp);

    cout << "enter number of plants: ";
    cin >> temp;
    plantNum.push_back(temp);

    cout << "do you want to continue? 0 yes, 1 no: ";
    cin >> flag;
    }
    //WHAT SIZE PLANT?
   
    for (int i=0; i<plantName.size(); i++) {
        if (plantSize[i] == 1) {
            smallPlant(plantNum);

        } else if (plantSize[i] == 2 || plantSize[i] == 3) {


        } else {

        }
    }
    /*
*/
    return 0;
}

void smallPlant(const vector<int> & plantNum) {
    int neededSpace;
    int availableSpace = 4;
    int boxesNeeded = 1;
    for (int i=0; i<plantNum.size(); i++) {
    neededSpace = plantNum[i];
        while (neededSpace > 0) {
            //determine if there is enough room in an existing box:
            if (availableSpace >= neededSpace) { //THERE IS ENOUGH ROOM
                //boxes[i].push_back((plantName[i], plantNum[i]));
                availableSpace -= neededSpace; //how much space is still available
                neededSpace = 0; //how much space is still needed
            } 
            else { //THERE IS NOT ENOUGH ROOM
                boxesNeeded++;
                availableSpace = 4; //how much space is available
                neededSpace -= availableSpace; //how much space is still needed
            }
         }     
    }  
    cout << "boxesNeeded: " << boxesNeeded << endl;
    cout << "availableSpace: " << availableSpace << endl;
    cout << "neededSpace: " << neededSpace << endl;
}