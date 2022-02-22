//Garden Squares Practice Problem
//CSCI 112 01/Feb/2022
//Mia Weber
/*
Problem Statement: 
1. garden is divided into 4x4 squares.
2. different plants take up different size squares.
3. given a list of plants, I need to determine how many 4x4 squares are needed for those plants
4. ex: 4 carrots, 2 potatoes, 1 celery = ?? 4x4 squares. 
**use one class for the squares and one class for the plants
*/
#include <iostream> 
#include <math.h>
#include <vector> 


using namespace std;
//1. take data input (name of plant, how much space it occupies, how many plants there are)
    //2. determine if plant is 4x4
        //yes? --> 4 * #of plants = total number of plots needed
        //no? --> find plot with empty spaces. enough empty spaces for the plant? 
            //yes? --> great! place that plant there and either mark the plot as complete or keep marked as empty if still space
            //no? --> keep looking, if there isn't one with ENOUGH space for the plant, then create a new plot and plant the plant there. (remember that you may be able to place SOME of the plants in one plot and place the remainding plants in a new/another plants)
    
class Plant { //class to store information on the plants that is entered by the user
    string plantName = ""; //string variable to store name of the plant
    int plantSpace = 0; //integer variable to store how much space the plant occupies
    int plantNum = 0; //integer variable to store how many plants there are
    int neededSpace = 0; //integer variable to store calculated needed space value

    public:

    Plant(string newPlantName = "", int newPlantSpace = 0, int newPlantNum = 0) { //constructor to access plantName, plantSpace, and plantNum **NEED TO DETERMINE IF I ACTUALLY NEED THIS LATER...
        plantName = newPlantName;
        plantSpace = newPlantSpace;
        plantNum = newPlantNum;
    }
    void fourByFour(double &boxTotal) {
        boxTotal = 4 * plantNum; //if the plant occupies 4x4 then you need number of plants * 4 plots
    }

    void getFromUser() {
        cout << "What is the name of the plant?" << endl;
        cin >> plantName; 
        //cout << "PLANT NAME: " <<  plantName << endl;
        cout << "How much space does it occupy?" << endl;
        cin >> plantSpace;
        //cout << "PLANT SPACE: " << plantSpace << endl;
        cout << "How many do you have?" << endl; //switch statement to call appropriate classes/functions/methods
        cin >> plantNum;
        //cout << "PLANT NUM: " << plantNum << endl;

        //calculate the neededSpace:
        neededSpace = plantSpace * plantNum;
    }
/*
    void addThePlant(const Plant &currentBox) {
        for (int i=0; i<100; i++) {
            plots[i] = currentBox.plantName;
        }
    }*/

};

class Boxes {
    Plant plots[100]; //do I want this to be an array? I think that I do so that I can loop through and identify if there are any empty boxes... 
    int boxSpace = 4; //integer variable to represent how much open space is in the current box *WHAT SHOULD IT BE SET TO INITIALLY?? ***USING 4 FOR NOW... 
    int totalBoxes = 1; //integer variable to represent how many boxes we currently need  **SHOULD WE START WITH 1?  
    //int neededSpace = 0; //integer variable to store calculated needed space value THIS CAN'T GO HERE... 

    public: 

    void addPlant(const Plant &currentBox) { //there is room in the box! Now we need to add the plant to that box and update how much room is left! 
        if (locateSpace(currentBox)==true) { //Something like this???
            for (int i=0; i<100; i++) { //because plots.length() = 100 
                plots[i] = currentBox.plantName; 
            }
        }
    }

    bool locateSpace(const Plant &currentBox) { //is there room for these plants in an existing box or do we need to create a new box? 
        //neededSpace = currentBox.plantSpace * currentBox.plantNum; //how do I do this? 
        for (int i=0; i<totalBoxes; i++) { //use a for loop to check every existing box for space
            //if (boxSpace <= currentBox.neededSpace) {//check to see if there is enough space in boxSpace for the neededSpace. *how to access neededSpace? 
                //totalBoxes++;
                //might want to store the list of the plants that are in each box at some point... 
                if (boxSpace + currentBox.neededSpace == 4) {
                boxSpace = 0; //reset the boxSpace to 0 if the box is now full THERE'S NO MORE SPACE IN THAT BOX
                }
            return(boxSpace <= currentBox.neededSpace);
        }
    }
    void newBox() {

    }

    void printAnswer() {

    }


};
/*
//could use an array in order to determine which plants are going into which plots...
class Plots {
    double plantNum; //variable to store the number of plants desired to plant
    double plotTotal; //variable to store the total number of plots needed to plant desired plants
    double plotNeed; //variable to store the number of plots needed by 1 plant 
    public: 
    //function to compute plotNum for 4x4 plants
    void fourbyfour(double &plotTotal) { //do I need to pass plotNum if within the same class? Keep this in case I move it later
        plotTotal = 4 * plantNum;
    }
    void findPlots() {
        //subtract 4 until <= to 0 - then add up the number of times that 4 was subtracted
        cin >> plantNum >> plotNeed;
        double counter = 0;
        //int remainder = 0;
        int tempTotal = plantNum * plotNeed;
        while (tempTotal >=0) { //need a while loop because how many times you need to repeat = plotNum
            tempTotal = tempTotal-4;
            counter++;
        }
        cout << "counter: " << counter << endl;
    }
};
*/
int main() {
    Plant ex;
    ex.getFromUser();
   // ex.findPlots();

    return 0; 
}