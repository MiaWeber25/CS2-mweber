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
        availableSpace = availableSpace - (p.getPlantSize()); //GETTING AN ERROR HERE...
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
   
   Plant(string tempPlantName, int tempPlantSize) {
       plantName = tempPlantName;
       plantSize = tempPlantSize;
   }

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
    Plant p(tempPlantName, tempPlantSize);
    int plantNum;
    int flag = 0;
        cout << "Welcome to The Garden Plot Calculator!" << endl;
        while (flag == 0) {
            
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
                Plant p(tempPlantName, tempPlantSize);

            }
            //p = new Plant(tempPlantName, tempPlantSize);
            cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
            cin >> flag;
        }

    return 0;
}