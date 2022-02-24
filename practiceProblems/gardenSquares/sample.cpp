#include <iostream>
#include <vector>

using namespace std;

class Plant;
class Square;
class Plot;
class Garden;
int calculateSpaceNeeded(Plant&, int &/*, int &*/);


class Garden { //ONLY KNOWS HOW MANY PLOTS ARE IN THE GARDEN && CAN ONLY ADD MORE PLOTS TO THE GARDEN
    int totalPlots;
    int plantNum;
    vector<Plot> myGarden;

    public:
    void addPlot() {
        totalPlots++; //increment totalPlots
    }
    //getter
    vector<Plot> getMyGarden() {
        return myGarden;
    }
    /*
    int getPlantNum() {
        cout << "plantNum from garden: " << plantNum << endl;
        return plantNum;
    }
    //setter
    int setPlantNum(int newPlantNum) {
        plantNum = newPlantNum;
        cout << "plantNum from setter in garden: " << plantNum << endl;
    }*/

};

class Plot { //ONLY KNOWS IF THE PLOT HAS SPACE && WHAT PLANTS ARE IN THE PLOT
    //bool isFilled;
    int availableSpace;
    vector<Plant> myPlot;

    public:
    //getter
    vector<vector<Square>> getMyPlots() {
        return (myPlots);
    }

};
/*
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
*/
class Plant {
     
    string plantName;
    int plantSize;
    int plantNum; //maybe fix later...

   public:
    void getFromUser(Garden &g) {
        //int temp;
        cout << "Enter name of the plant: ";
        cin >> plantName;
        cout << "Enter size of the plant (enter \"1\" for 1x1, \"2\" for 2x2, etc): ";
        cin >> plantSize;
        cout << "Enter number of plants: ";
        cin >> plantNum;
        //cin >> temp;
       // g.setPlantNum(temp);

    }
    //getter
    string getPlantName() {
        return plantName;
    }
    int getPlantSize() {
        return plantSize;
    }
    int getPlantNum() {
        return plantNum;
    }

};

int main() {
    Garden g;
    Plant p;
    int flag = 0;
    Plant temp;
    vector<Plant> sampleGarden;

    cout << "Welcome to The Garden Plot Calculator!" << endl;
    while (flag == 0) { //create a new plant each time the user enters plant data and then add it to the vector
        p.getFromUser(g);
        sampleGarden.push_back(p);
        cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
        cin >> flag;
    }
    /* FOR TESTING: 
    cout << "plantName: " << p.plantName << endl;
    cout << "plantSize: " << p.plantSize << endl;
    for (int i=0; i<sampleGarden.size(); i++) {
        cout << "SampleGarden plantName: " << sampleGarden[i].plantName << endl;
        cout << "SampleGarden plantSize: " << sampleGarden[i].plantSize << endl;
    }*/
    //int plantNum;
    
    for (int i=0; i<sampleGarden.size(); i++) {
        int spaceNeeded = 0;
        //int newPlantNum = 0;
        //newPlantNum = g.getPlantNum();
        //cout << "newPlantNum: " << newPlantNum << endl;
      //  calculateSpaceNeeded(p,spaceNeeded/*newPlantNum*/); //call tryPlant or addPlant (from square class) with the value calculated FOR EACH PLANT HERE...
        calculateSpaceNeeded(sampleGarden[i], spaceNeeded);
    }

}

int calculateSpaceNeeded(Plant& p, int &spaceNeeded/*, int &plantNum*/) {
    spaceNeeded = (p.getPlantSize()) * (p.getPlantNum()); //doesn't even seem to matter is this is = or +=
    cout << "plantSize: " << p.getPlantSize() << endl << endl;
    cout << "plantNum: " << p.getPlantNum() << endl << endl;
    cout << "spaceNeeded: " << spaceNeeded << endl;
    return spaceNeeded;

}