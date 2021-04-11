#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Entity.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Room header file 

#ifndef ROOM_H
#define ROOM_H

class Room {
    public:
        Room();
        Room(string theme, bool enemyRoom);
        double noEnemiesLeft();
        double interact();
        void randomEnemies(string theme);
        void randomLoot(string theme);
        void randomInteractable(string theme);
        Entity getEnemy(int i);
        void lootRoll();
        string getInteract();
        string getDescription();
        bool enemiesAreAlive();
        
    
    private:
        string lootFlavor[3];
        double lootPoints[3];
        string description;
        string interactable;
        double interactPoints;
        bool canInteract;
        bool enemiesAlive;
        Entity enemies[2];
        
        vector<string> forestItems;
        vector<string> cryptItems;
        vector<string> dwellingItems;
        vector<string> forestInter;
        vector<string> cryptInter;
        vector<string> dwellInter;
        vector<string> forestDesc;
        vector<string> cryptDesc;
        vector<string> dwellDesc;
};

#endif