#include <iostream>
#include <vector>

using namespace std;

class Plant;
class Plot;
class Garden;


class Garden { //ONLY KNOWS HOW MANY PLOTS ARE IN THE GARDEN && CAN ONLY ADD MORE PLOTS TO THE GARDEN
    int totalPlots;
    vector<Plot> myGarden;
    void addPlot() {
        totalPlots++; //increment totalPlots
    }

    public:
    void addPlant(Plant &p) { //check if you can add a plant
    //if...
    //then call addPlant from Plot
    }
    //getter
    vector<Plot> getMyGarden() {
        return myGarden;
    }
};

class Plot { //ONLY KNOWS IF THE PLOT HAS SPACE && WHAT PLANTS ARE IN THE PLOT
    int availableSpace = 16;
    vector<Plant> myPlot;

    public:
    int temporary;
    void addPlant(Plant &p) {
        myPlot.push_back(p);

        //calculate availablSpace
        temporary = p.getPlantSize();
        //availableSpace = availableSpace - (p.getPlantSize());
    }
    //getter
    int getAvailableSpace() {
        return availableSpace;
    }
};


class Plant {
     
    string plantName;
    int plantSize;

   public:
   /*
   Plant (string tempPlantName, int tempPlantSize) {
       plantName = tempPlantName;
       plantSize = tempPlantSize;
   }*/

    //getter
    string getPlantName() {
        return plantName;
    }
    int getPlantSize() {
        return plantSize;
    }
    //setter for plantName and plantSize
    void setPlantSize(int newPlantSize) {
        plantSize = newPlantSize * newPlantSize;
    }
    void setPlantName(string newPlantName) {
        plantName = newPlantName;
    }
    

};

int main() {
    Garden g;
   
    string tempPlantName;
    int tempPlantSize;
    int plantNum;
    int flag = 0;
        cout << "Welcome to The Garden Plot Calculator!" << endl;
        while (flag == 0) {
            Plant p;
            cout << "Enter name of the plant: ";
            cin >> tempPlantName;
            //SETTER
            p.setPlantName(tempPlantName);
            cout << "Enter size of the plant (enter \"1\" for 1x1, \"2\" for 2x2, etc): ";
            cin >> tempPlantSize;
            //SETTER
            p.setPlantSize(tempPlantSize);
            cout << "Enter number of plants: ";
            cin >> plantNum;
            for (int i=0; i<plantNum; i++) {
                //CREATE A NEW PLANT --> GIVE IT TO GARDEN

            }
            //p = new Plant(tempPlantName, tempPlantSize);
            cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
            cin >> flag;
        }

    return 0;
}







/*
    Plant temp;
    vector<Plant> sampleGarden;

    while (flag == 0) { //create a new plant each time the user enters plant data and then add it to the vector
        p.getFromUser(g);
        sampleGarden.push_back(p);
        
    }
     FOR TESTING: 
    cout << "plantName: " << p.plantName << endl;
    cout << "plantSize: " << p.plantSize << endl;
    for (int i=0; i<sampleGarden.size(); i++) {
        cout << "SampleGarden plantName: " << sampleGarden[i].plantName << endl;
        cout << "SampleGarden plantSize: " << sampleGarden[i].plantSize << endl;
    }
    //int plantNum;
    
    for (int i=0; i<sampleGarden.size(); i++) {
        int spaceNeeded = 0;
        //int newPlantNum = 0;
        //newPlantNum = g.getPlantNum();
        //cout << "newPlantNum: " << newPlantNum << endl;
      //  calculateSpaceNeeded(p,spaceNeedednewPlantNum); //call tryPlant or addPlant (from square class) with the value calculated FOR EACH PLANT HERE...
        calculateSpaceNeeded(sampleGarden[i], spaceNeeded);
    }

}

int calculateSpaceNeeded(Plant& p, int &spaceNeeded, int &plantNum) {
    spaceNeeded = (p.getPlantSize()) * (p.getPlantNum()); //doesn't even seem to matter is this is = or +=
    cout << "plantSize: " << p.getPlantSize() << endl << endl;
    cout << "plantNum: " << p.getPlantNum() << endl << endl;
    cout << "spaceNeeded: " << spaceNeeded << endl;
    return spaceNeeded;

}*/