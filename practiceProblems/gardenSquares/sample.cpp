#include <iostream>
#include <vector>

using namespace std;

class Plant;
class Square;
class Plot;
class Garden;


class Garden { //ONLY KNOWS HOW MANY PLOTS ARE IN THE GARDEN && CAN ONLY ADD MORE PLOTS TO THE GARDEN
    int totalPlots;
    vector<Plot> myGarden;

    public:
    void addPlot() {
        totalPlots++; //increment totalPlots
    }
    //getter
    vector<Plot> getMyGarden() {
        return myGarden;
    }

};

class Plot { //ONLY KNOWS IF THE PLOT HAS SPACE && WHAT PLANTS ARE IN THE PLOT
    //bool isFilled;
    int availableSpace;
    vector<vector<Square>> myPlots;

    public:
    //getter
    vector<vector<Square>> getMyPlots() {
        return (myPlots);
    }

};

class Square { //ONLY KNOWS IF THE SPACE IS EMPTY OR WHICH PLANT IS IN THE SPACE && CAN ONLY ADD A PLANT TO A SPACE
    bool isFilled = false;
    string whichPlant;
    vector<Plant> myPlants; //needs to be a vector? or just a plant? 

    public:

    bool isThereSpace() {
      //  Plot.getMyPlots();

    }
    void addPlant() {
        if (isFilled == false) { //square is empty!
            //place a plant here!
            //Plot.getMyPlots();
            //whichPlant = ______ //assign plantName to whichPlant for this space
        } else { //square is filled!
            //what do you do? 
        }

    }

};

class Plant {
    string plantName;
    int plantSize;

    public:
    void getFromUser() {
        int flag = 0;
        int temp;
        //while (flag == 0) {
            cout << "Enter name of the plant: ";
            cin >> plantName;
            cout << "Enter size of the plant (enter \"1\" for 1x1, \"2\" for 2x2, etc): ";
            cin >> plantSize;
            //cout << "do you want to continue? 0 for yes, 1 for no" << endl;
            //cin >> flag;
       // }
    }

};

int main() {
    Plant p;
    int flag = 0;
    Plant temp;
    vector<Plant> sampleGarden;

    cout << "Welcome to The Garden Plot Calculator!" << endl;
    while (flag == 0) { //create a new plant each time the user enters plant data and then add it to the vector
        p.getFromUser();
        sampleGarden.push_back(p);
        cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
        cin >> flag;
    }
    int plantNum;
    int spaceNeeded;

}