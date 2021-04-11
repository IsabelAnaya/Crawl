#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include "Entity.h"
#include "Map.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Player header file 

#ifndef PLAYER_H
#define PLAYER_H

class Player {
    public:
        Player();
        void setMap(int choice);
        void setHeroes(Entity one, Entity two);
        string getMapName(int i);
        string getHeroName(int i);
        void finishBattle();
        void saveFinalStats();
        void dispMap();
        bool move(int dir);
        void currentRoomNarrate();
        bool inBattleRoom();
        Entity getEnemy(int i);
        void printStatus();
        void turn(int i);
        bool checkForDeath(bool enemy);
        bool checkClear();
        // void mapTemplate();
        // int validMap(string filename);
    
    private:
        Room currentRoom;
        Map allMaps[3];
        Map selectedMap;
        Entity heroes[2];
        Entity currentEnemies[2];
        double points;
        int charTurn;
        string savefile;
};

#endif