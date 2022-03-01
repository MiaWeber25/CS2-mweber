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

    public:
    void addPlant(Plant &p) {
        myPlot.push_back(p);

        //calculate availablSpace
        availableSpace = availableSpace - (p.getPlantSize()); 
        //cout << "AVAILABLE SPACE: " << availableSpace << endl;
        for (int i=0; i<myPlot.size(); i++) {
            //cout << "plant in myPlot: " << myPlot[i].getPlantName() << endl;
        }
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
    /*void addPlot(Plot &plot) {
        //totalPlots++; //increment totalPlots
        myGarden.push_back(plot);
    }*/
    public:
    Plot plot;
    void addPlot(Plot &plot) {
        myGarden.push_back(plot);
   //  cout << "myGarden Size from addPlot: " << myGarden.size() << endl;
        
    }
    //myGarden.push_back(plot);
    int addPlant(Plant &p) { //check if you can add a plant
    //loop through your plots, see if there is room for the plant in the plot 
        //plot.setAvailableSpace(16);
       // int difference = 0;
        for (int i=0; i<myGarden.size(); i++) {
            if (plot.getAvailableSpace() >= (p.getPlantSize())) { //room for the plant in the plot!
                cout << "available space = " << plot.getAvailableSpace() << "plant size = " << p.getPlantSize() << endl;
                plot.addPlant(p);
               // cout << "TOTAL PLOTS: " << myGarden.size() << endl;
                break;
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

              //  cout << "TOTAL PLOTS: " << myGarden.size() << endl;

                break;
            }
        }
    //cout << "TOTAL PLOTS: " << myGarden.size() << endl;
    return (myGarden.size());

  
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

    return 0;
}