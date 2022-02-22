#include <iostream>
#include <vector>

using namespace std;

class Garden {
    vector<Box> theGarden;

    //boxesNeeded++;
};

class Box {
    int availableSpace;
    vector<int> plantNum;
    vector<Plant> thePlants;


    Box(int newAvailableSpace = 0) {
        availableSpace = newAvailableSpace;
    }

    bool foundSpace (const Plant &aPlant) {
        return (aPlant.getSize()<availableSpace);
    }

    void plantPlant() {

    }
};

class Plant {
    protected:

    vector<string> plantName;
   // vector<int> plantSize;
   int plantSize;
  
    //vector<string> boxes;

    //vector<int> neededSpace; //MIGHT NOT NEED THIS ONE...
    int neededSpace;
    int boxesNeeded;
    //available space might need to be a vector too..

    public:

    Plant(string newPlantName = "", int newPlantSize=0, int newPlantNum=0) {
        plantName.push_back(newPlantName);
        plantSize = newPlantSize;
       // plantNum.push_back(newPlantNum);
        //push_back() could get messy. Leave for now but there might be a better way to construct...
    }

    int getSize() {
        return plantSize;
    }
/*
    //overload >> and <<
    friend ostream & operator <<(ostream &out, const Plant &samplePlant) {
        samplePlant.output(out);
        return out;
    }
    void output(ostream &out) const {
        for (unsigned i=0; i<plantName.size(); i++) {
            out << " " << plantName[i]; //<< " " << plantSize[i] << " " << plantNum[i] << endl;
        }
    }
    friend istream & operator >>(/*const istream &in, Plant &samplePlant) {
        samplePlant.input(in);
        return in;
    }
    void input(istream &in) /*const {
        for (unsigned i=0; i<plantName.size(); i++) {
            in >> plantName[i];// >> plantSize[i] >> plantNum[i];
        }
    }
    */

    void getFromUser() {
        int flag = 0;
        int temp;
        string tempor;
        while(flag == 0) {
        //maybe implement a clearScreen function before this too...
        cout << "Please enter the following information about your garden!" << endl;
        cout << "name of the plant: ";
        cin >> tempor;
        plantName.push_back(tempor);
        cout << "size of the plant (enter \"1\" for 1x1, \"2\" for 2x2, etc): ";
        cin >> temp;
        plantSize.push_back(temp);
        cout << "number of plants: ";
        cin >> temp;
        plantNum.push_back(temp);
        
        cout << "do you want to continue? 0 for yes, 1 for no" << endl;
        cin >> flag;
                
        identifySize();
        }
    }
    void identifySize() {
        for (unsigned i=0;i<plantName.size(); i++) { //not sure if this will continue to work after istream is overloaded...
         //determine if that means it's a small, medium, or large plant...
            if (plantSize[i] == 1) {
                //SmallPlant.findSpace();
            }
            else if (plantSize[i] == 2 || plantSize[i] == 3) {
                //MediumPlant.findSpace();
            }
            else /*plant size is 4 */{
                //LargePlant.findSpace();
            }
        }
    
    }

};

class SmallPlant: public Plant {
    public:
    void findSpace() {
        availableSpace = 4;
        boxesNeeded = 1;
        for (int i=0; i<plantName.size(); i++) { //WHILE LOOP UNTIL NEEDEDSPACE = 0? 
        //calculate the total space needed
            neededSpace = plantNum[i]; //since they are 1x1 the needed space is the plantNum
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
    }
};

class MediumPlant: public Plant{
    public:
       void findSpace() {
        availableSpace = 4;
        boxesNeeded = 1;
        for (int i=0; i<plantName.size(); i++) { //WHILE LOOP UNTIL NEEDEDSPACE = 0? 
        //calculate the total space needed
          //***  neededSpace = plantNum[i]; //since they are 1x1 the needed space is the plantNum
        while (neededSpace > 0) {
        //determine if there is enough room in an existing box:
        if (availableSpace >= neededSpace) { //THERE IS ENOUGH ROOM
            //boxes[i].push_back((plantName[i], plantNum[i]));
            availableSpace -= neededSpace;
            neededSpace = 0;
        } 
        else { //THERE IS NOT ENOUGH ROOM
            boxesNeeded++;
            availableSpace = 4;
        }
        }
        }
    }
   
};

class LargePlant: public Plant {
    public:
        void findSpace() {
        availableSpace = 4;
        boxesNeeded = 1;
        for (int i=0; i<plantName.size(); i++) { //WHILE LOOP UNTIL NEEDEDSPACE = 0? 
        //calculate the total space needed
            neededSpace = plantNum[i]; //since they are 1x1 the needed space is the plantNum
        while (neededSpace > 0) {
        //determine if there is enough room in an existing box:
        if (availableSpace >= neededSpace) { //THERE IS ENOUGH ROOM
            //boxes[i].push_back((plantName[i], plantNum[i]));
            availableSpace -= neededSpace;
            neededSpace = 0;
        } 
        else { //THERE IS NOT ENOUGH ROOM
            boxesNeeded++;
            availableSpace = 4;
        }
        }
        }
    }
};



int main() {
    //get input from user
    Plant p;
    p.getFromUser();
    p.identifySize();
    //SmallPlant::p.findspace();

    return 0;
}