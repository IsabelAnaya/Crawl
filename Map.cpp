#include "Map.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Homework #: source file 

//used in reading data from file
int Map::split(string str, char delimiter, string newArray[], int length) {
    int starter = 0;
    int currentArrayIndex = 0;
    int splitPieces = 0;
    string temp;
    
    if (str == "") {
        return 0;
    }
    
    str = str + delimiter;
    
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delimiter && temp != "") {
            newArray[currentArrayIndex] = temp;
            splitPieces++;
            currentArrayIndex++;
            temp = "";
        } else if (str[i] != delimiter) {
            temp = temp + str[i];
            if (currentArrayIndex + 1 > length) {
                return -1;
            }
        }
    }
    return splitPieces;
} 

//constructor for empty map
Map::Map() {
    identifier = "";
    theme = "";
    playerPosX = 0;
    playerPosY = 0;
}

//constructor based on file
Map::Map(string fileName) {
    
    //open file. players shouldn't touch this so it's fine if it breaks without correct file
    ifstream file;
    file.open(fileName);
    getline(file, identifier);
    getline(file, theme);
    
    string gridRow;
    string rowCodes[5];
    
    //start going through the map grid [row by row]
    for (int i = 0; i < gridLength; i++) {  //rows
        getline(file, gridRow);
        
        //check that input is a room code
        if (isdigit(gridRow[0])) {
            split(gridRow, '.', rowCodes, 5);
            
            //start going through the columns in the row
            for (int j = 0; j < gridLength; j++) {  //columns
                mapGrid[i][j] = stoi(rowCodes[j]);
                /*cout << mapGrid[i][j];*/ //this displays the room code. used in testing 
                
                //sets player position to the room marked with "3"
                if (mapGrid[i][j] == 3) {
                    playerPosX = j;
                    playerPosY = i;
                }
                
                //determining if the room has enemies. room code of "2" is an enemy room
                bool enemyRoom = false;
                if (mapGrid[i][j] == 2) {
                    enemyRoom = true;
                }
                
                //also adds the room to the array of rooms
                Room newRoom(theme, enemyRoom);
                mapRooms[i][j] = newRoom;
            }
        }
    }
}

//getter for map name/identifier. in written file
string Map::getID() {
    return identifier;
}

//getter for map theme. used to determine enemies and room descriptions
string Map::getTheme() {
    return theme;
}

//testing function. referenced in driver
string Map::getPos(int pos[2]) {
    string x = to_string(playerPosX);
    string y = to_string(playerPosY);
    pos[0] = playerPosX;
    pos[1] = playerPosY;
    return (x + ", " + y);
}

//test for available rooms
int Map::getGridCode(int x, int y) {
    //segfault check
    if (y < 0 || x < 0 || y > 5 || x > 5) {
        return -1;
    }
    
    return mapGrid[y][x]; //swapped around because rows are y, columns are x
}

//used to display map
void Map::displayMap() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            switch (mapGrid[i][j]) {
                case 0:
                    //leave an unpassable space "   "
                    cout << "   ";
                    break;
                case 1:
                    //show an unvisited room with object  "[?]"
                    cout << "[?]";
                    //cout << "[1]";
                    break;
                case 2:
                    //show an unvisited room with object and enemies   "[?]"
                    cout << "[?]";
                    //cout << "[2]";
                    break;
                case 3:
                    //show the player in a room with uninteracted object "[@]"
                    cout << "[@]";
                    //cout << "[3]";
                    break;
                case 4:
                    //show a visited empty room   "[ ]"
                    cout << "[ ]";
                    //cout << "[4]";
                    break;
                case 5:
                    //show a visited room with an object    "[O]"
                    cout << "[O]";
                    //cout << "[5]";
                    break;
                case 6:
                    //show a visited room with unfought enemies and an object "[O]"
                    cout << "[O]";
                    //cout << "[6]";
                    break;
                case 7:
                    //show the player's current room, empty "[@]"
                    cout << "[@]";
                    //cout << "[7]";
                    break;
                case 8:
                    //show the player's current room w/ uninteracted object and enemies "[@]"
                    cout << "[@]";
                    //cout << "[8]";
                    break;
            }
        }
        cout << endl;
    }
}

//updates map codes after movement
void Map::markExplored(int oldX, int oldY, int newX, int newY) {
    
    //updates current room ([@] room) to a visited room
    switch (mapGrid[oldY][oldX]) {
        //unexplored room
        case 3:
            mapGrid[oldY][oldX] = 5;
            break;
        
        //explored room
        case 7:
            mapGrid[oldY][oldX] = 4;
            break;
            
        //unexplored room (enemies)
        case 8:
            mapGrid[oldY][oldX] = 6;
            break;
    }
    
    //updates room to a current room
    switch (mapGrid[newY][newX]) {
        //unvisited room
        case 1:
            mapGrid[newY][newX] = 3;
            break;
            
        //unvisited room (enemies)
        case 2:
            mapGrid[newY][newX] = 8;
            break;
            
        //explored room
        case 4:
            mapGrid[newY][newX] = 7;
            break;
            
        //visited, unexplored room
        case 5:
            mapGrid[newY][newX] = 3;
            break;
            
        //visited, unexplored room (enemies)
        case 6:
            mapGrid[newY][newX] = 8;
            break;
    }

    //updates position
    playerPosX = newX;
    playerPosY = newY;
}

//returns if movement in the direction is possible, and does stuff if it is
bool Map::move(int dir) {
    switch (dir) {
        case 2: //north
            // TESTING BLOCK
            // cout << "X: " << playerPosX << endl;
            // cout << "Y: " << playerPosY << endl;
            // cout << "Room code: " << getGridCode(playerPosX, playerPosY - 1) << endl;
            // cout << "Target X: " << playerPosX << endl;
            // cout << "Target Y: " << playerPosY - 1 << endl;
            
            if (getGridCode(playerPosX, playerPosY - 1) > 0) {
                markExplored(playerPosX, playerPosY, playerPosX, playerPosY - 1);
                return true;
            } else {
                return false;
            }
            break;
            
        case 3: //east
            // TESTING BLOCK
            // cout << "X: " << playerPosX << endl;
            // cout << "Y: " << playerPosY << endl;
            // cout << "Room code: " << getGridCode(playerPosX + 1, playerPosY) << endl;
            // cout << "Target X: " << playerPosX + 1 << endl;
            // cout << "Target Y: " << playerPosY << endl;
            
            if (getGridCode(playerPosX + 1, playerPosY) > 0) {
                markExplored(playerPosX, playerPosY, playerPosX + 1, playerPosY);
                return true;
            } else {
                return false;
            }
            break;
            
        case 4: //south
            // TESTING BLOCK
            // cout << "X: " << playerPosX << endl;
            // cout << "Y: " << playerPosY << endl;
            // cout << "Room code: " << getGridCode(playerPosX, playerPosY + 1) << endl;
            // cout << "Target X: " << playerPosX << endl;
            // cout << "Target Y: " << playerPosY + 1 << endl;
            
            if (getGridCode(playerPosX, playerPosY + 1) > 0) {
                markExplored(playerPosX, playerPosY, playerPosX, playerPosY + 1);
                return true;
            } else {
                return false;
            }
            break;
            
        case 5: //west
            // TESTING BLOCK
            // cout << "X: " << playerPosX << endl;
            // cout << "Y: " << playerPosY << endl;
            // cout << "Room code: " << getGridCode(playerPosX - 1, playerPosY) << endl;
            // cout << "Target X: " << playerPosX - 1 << endl;
            // cout << "Target Y: " << playerPosY << endl;
            
            if (getGridCode(playerPosX - 1, playerPosY) > 0) {
                markExplored(playerPosX, playerPosY, playerPosX - 1, playerPosY);
                return true;
            } else {
                return false;
            }
            break;
            
        default:
            return false;
            break;
    }
}

//player needs to access current room
Room Map::getCurrentRoom() {
    return mapRooms[playerPosY][playerPosX];
}

//used when player enters a room
void Map::updateCurrentRoomCode() {
    switch (mapGrid[playerPosY][playerPosX]) {
        case 3:
            //uninteracted object to empty room
            mapGrid[playerPosY][playerPosX] = 7;
            break;
        case 8:
            //uninteracted object and enemies to empty room
            mapGrid[playerPosY][playerPosX] = 7;
            break;
    }   
}

//checks for any unexplored rooms
bool Map::checkClear() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            //cout << mapGrid[j][i];
            if (mapGrid[j][i] != 4 && mapGrid[j][i] != 7 && mapGrid[j][i] != 0) { //4 is empty room, 7 is empty current room
                // cout << "Uncleared room at (" + to_string(j) + ", " + to_string(i) + ")" << endl;
                // cout << "Current position is (" + to_string(playerPosX) + ", " + to_string(playerPosY) + ")" << endl;
                return false;
            }
        }
    }
    return true;
}

//returns the points from the loot. also switches the battle room bool but that's deprecated
double Map::roomClear() {
    //cout << "Room cleared at (" + to_string(playerPosX) + ", " + to_string(playerPosY) + ")" << endl;
    return mapRooms[playerPosY][playerPosX].noEnemiesLeft();
}

//check for if enemies are alive (works without pointer by looking at map's data instead of room)
bool Map::activeBattleRoom() {
    if (mapGrid[playerPosY][playerPosX] != 8) {
        return false;
    } else {
        return true;
    }
}

//checks if room has been explored
bool Map::unexploredRoom() {
    if (mapGrid[playerPosY][playerPosX] != 8 && mapGrid[playerPosY][playerPosX] != 3) {
        return false;
    } else {
        return true;
    }
}
