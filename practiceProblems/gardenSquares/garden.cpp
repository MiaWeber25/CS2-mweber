#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Plant;
class Plot;
class Garden;

//PLANT CLASS - ONLY KNOWS ABOUT EACH INDIVIDUAL PLANT
class Plant {
    string plantName;
    int plantSize;
public:
    Plant(string tempPlantName, int tempPlantSize) {
       plantName = tempPlantName;
       plantSize = tempPlantSize;
    }
    //getters
    string getPlantName() {
        return plantName;
    }
    int getPlantSize() {
        return plantSize*plantSize;
    }
    //setters
    void setPlantSize(int newPlantSize) {
        plantSize = newPlantSize * newPlantSize;
    }
    void setPlantName(string newPlantName) {
        plantName = newPlantName;
    }
};

//PLOT CLASS - ONLY KNOWS AVAILABLE SPACE AND WHAT PLANTS ARE IN THE PLOT
class Plot { 
    int availableSpace = 16; //might be causing come problems
    vector<Plant> myPlot;
public:
    void addPlant(Plant &p) {
        myPlot.push_back(p);
        //calculate availablSpace
        availableSpace = availableSpace - (p.getPlantSize()); 
    }

    bool violate23Rule(Plant &p) {
        if (p.getPlantSize() == 9) {
            //are there any size 2 plants in the plot?
            for (int i=0; i<myPlot.size(); i++) {
                if (myPlot[i].getPlantSize() == 4) {
                    return true; //yes! the rule was violated
                } else {
                    return false; //no! the rule was not violated
                }
            }
        } 
        if (p.getPlantSize() == 4) {
        //are there any size 3 plants in the plot?
            for (int i=0; i<myPlot.size(); i++) {
                if (myPlot[i].getPlantSize() == 9) {
                    return true; //yes! the rule was violated
                } else {
                    return false; //no! the rule was not violated
                }
            }
        } 
        return false;
    }

    void print() {
        cout << "plot contains: ";
        for (int i=0; i<myPlot.size(); i++) {
            cout << myPlot[i].getPlantName() << ", ";
        }
        cout << endl;
    }
    //getters
    int getAvailableSpace() {
        return availableSpace;
    }
    //setters
    void setAvailableSpace(const int &newAvailableSpace) {
        availableSpace = newAvailableSpace;
    }
};

//GARDEN CLASS - ONLY KNOWS HOW MANY PLOTS ARE IN THE GARDEN && CAN ONLY ADD MORE PLOTS TO THE GARDEN
class Garden { 
    vector<Plot> myGarden;
public:
    void addPlot(Plot &plot) {
        myGarden.push_back(plot);        
    }

    void addPlant(Plant &p) { //check if you can add a plant
    //loop through your plots, see if there is room for the plant in the plot 
        for (int i=0; i<myGarden.size(); i++) {
            //there is room and doesn't violate so PLANT THE PLANT
            if (myGarden[i].getAvailableSpace() > p.getPlantSize() && !myGarden[i].violate23Rule(p)) {
                myGarden[i].addPlant(p);
                return;
            }
        }
        //make a new plot
        Plot newPlot;
        newPlot.setAvailableSpace(16);
        newPlot.addPlant(p); 
        addPlot(newPlot);        
    }
   
    //getters
    vector<Plot> getMyGarden() {
        return myGarden;
    }
};

int main() {
    Garden g;
    Plot plot;

    string tempPlantName;
    int tempPlantSize=0;
    Plant p(tempPlantName, tempPlantSize);
    g.addPlot(plot);
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
        while (plantNum >0) {
            //CREATE A NEW PLANT 
            Plant p(tempPlantName, tempPlantSize);
            //--> GIVE IT TO GARDEN
            g.addPlant(p);
            plantNum--;    
        }
        cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
        cin >> flag;
    }
    cout << "You will need " << g.getMyGarden().size() << " plots in your garden!" << endl;
    for (int i=0; i<g.getMyGarden().size(); i++) { //will loop through the plots
        cout << "Plot # " << i+1 << endl;
        (g.getMyGarden()[i]).print(); //for an individual plot, print the contents
    }
    return 0;
}