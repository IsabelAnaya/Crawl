#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Room.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Map header file 

#ifndef MAP_H
#define MAP_H

class Map {
    public:
        int split(string str, char delimiter, string newArray[], int length);
        Map();
        Map(string fileName);
        string getID();
        string getTheme();
        string getPos(int pos[2]);
        int getGridCode(int row, int col);
        void displayMap();
        void markExplored(int oldX, int oldY, int newX, int newY);
        void updateCurrentRoomCode();
        bool move(int dir);
        Room getCurrentRoom();
        bool checkClear();
        double roomClear();
        bool activeBattleRoom();
        bool unexploredRoom();
    
    private:
        string identifier;
        string theme;
        Room mapRooms[6][6];
        int mapGrid[6][6];
        int playerPosX;
        int playerPosY;
        int gridLength = 5;
};

#endif