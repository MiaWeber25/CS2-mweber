#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Plant;
class Plot;
class Garden;


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
        return plantSize*plantSize;
    }
    //setter for plantName and plantSize
    void setPlantSize(int newPlantSize) {
        plantSize = newPlantSize * newPlantSize;
    }
    void setPlantName(string newPlantName) {
        plantName = newPlantName;
    }
};

class Plot { //ONLY KNOWS IF THE PLOT HAS SPACE && WHAT PLANTS ARE IN THE PLOT
    int availableSpace = 16; //might be causing come problems
    vector<Plant> myPlot;
    bool can3 = true;
    bool can2 = true;

    public:
    bool checkPlants2() {
        cout << endl << "calling checkPlants2" << endl << endl;
        if (can2 == true) {
            return true;
        } else 
            return false;
    }
    bool checkPlants3() {
        cout << endl << "calling checkPlants3" << endl << endl;
        if (can3 == true)
            return true;
        else 
            return false;
    }
    
    void addPlant(Plant &p) {
        //is the plantSize == 3 or 2? (9 or 4)
        if (p.getPlantSize() == 9) {
            checkPlants3();
        } else if (p.getPlantSize() == 4) {
            checkPlants2();
        }
        //check to make sure that the plant is able to be placed (2x2 and 3x3 not in the same plot)
        if (p.getPlantSize() == 3 && can3 == true) {
            //go ahead and plant it!
            myPlot.push_back(p);
            availableSpace = availableSpace - (p.getPlantSize());
        } else if (p.getPlantSize() == 2 && can2 == true) {
            //go ahead and plant it!
            myPlot.push_back(p);
            availableSpace = availableSpace - (p.getPlantSize());
        } 


        myPlot.push_back(p);
        //calculate availablSpace
        availableSpace = availableSpace - (p.getPlantSize()); 
        //for (int i=0; i<myPlot.size(); i++) {
            //cout << "plant in myPlot: " << myPlot[i].getPlantName() << endl;
       // }
    }

    //getter
    int getAvailableSpace() {
        return availableSpace;
    }
    void setAvailableSpace(const int &newAvailableSpace) {
        availableSpace = newAvailableSpace;
    }
};

class Garden { //ONLY KNOWS HOW MANY PLOTS ARE IN THE GARDEN && CAN ONLY ADD MORE PLOTS TO THE GARDEN
    vector<Plot> myGarden;
   
    public:
    Plot plot;
    void addPlot(Plot &plot) {
        myGarden.push_back(plot);        
    }

    //myGarden.push_back(plot);
    void addPlant(Plant &p) { //check if you can add a plant
    //loop through your plots, see if there is room for the plant in the plot 
        for (int i=0; i<myGarden.size(); i++) {
            if (plot.getAvailableSpace() >= (p.getPlantSize())) { //room for the plant in the plot!
                //cout << "checkPlants3: " << plot.checkPlants3() << endl;
                //cout << "checkPlants2: " << plot.checkPlants2() << endl;
                if ((p.getPlantSize() == 9 && plot.checkPlants3() == false) /*|| (p.getPlantSize() == 2 && can2 == false)*/) {//double check that the plant doesn't violate the 3x3 and 2x2 rule!
                  //  cout << "getting here!" << endl;
                    Plot newPlot;
                    newPlot.setAvailableSpace(16);
                    addPlot(newPlot);
                    newPlot.addPlant(p);
                    break;
                }
                else if (p.getPlantSize() == 4 && plot.checkPlants2() == false) {
                    Plot newPlot;
                    newPlot.setAvailableSpace(16);
                    addPlot(newPlot);
                    newPlot.addPlant(p);
                    break;
                }
                else {
                    plot.addPlant(p);
                    break;
                }
            } else if (plot.getAvailableSpace() < p.getPlantSize()) { //not enough room for plant in the plot!
                //difference = p.getPlantSize() - plot.getAvailableSpace();
                //for (int j=0; j<difference; j++) {
                //    plot.addPlant(p);
                //}
                Plot newPlot;
                newPlot.setAvailableSpace(16);
                addPlot(newPlot); //add a plot
                //add plant to that new plot...
                newPlot.addPlant(p); //recursive 
                break;
            }
        }    
    }
    //getter
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
    g.addPlot(plot); //initialize the garden to 1 plot. You know that you need at least one plot in your garden. prevents myGarden.size() from starting at 0 for for loop...

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
                for (int i=0; i<plantNum; i++) {
                    //CREATE A NEW PLANT 
                    Plant p(tempPlantName, tempPlantSize);
                    //--> GIVE IT TO GARDEN
                    g.addPlant(p);
                    plantNum--;
                }
            }
            //p = new Plant(tempPlantName, tempPlantSize);
            cout << "do you want to continue? 0 for yes, 1 for no: " << endl;
            cin >> flag;
        }
        cout << "Congratulations! You will need " << g.getMyGarden().size() << " plots in your garden!" << endl;
        //iterate over the garden
        /*
        for (int i=0; i<g.getMyGarden().size(); i++) {
            for (int i=0; i<plot.size(); i++) {
                cout << "plant in myPlot: " << plot[i].getPlantName() << endl;
        }
        }*/
    return 0;
}