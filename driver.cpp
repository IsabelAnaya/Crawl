#include <string>
#include <iostream>
#include "Player.h"
#include "Map.h"

using namespace std;

void selectMap(Player player);
// void createMap(Player player);
void selectHeroesFirst(Player player);
void selectHeroesSecond(Player player, Entity heroOne);
void game(Player player);
bool fight(Player *player); //pointer parameter
void room(Player player);

//map choosing menu
void selectMap(Player player) {
    cout << "Select a map:" << endl;
    cout << "1: " << player.getMapName(0) << endl;
    cout << "2: " << player.getMapName(1) << endl;
    cout << "3: " << player.getMapName(2) << endl;
    // cout << "4: External map" << endl; 
    string choice;
    string yn;
    getline(cin, choice);
    cout << endl;
    
    // bool mapCreator;
    
    if (isdigit(choice[0])) {
        if (stoi(choice) < 4 && stoi(choice) > 0) {
            player.setMap(stoi(choice) - 1);
            cout << "Selected " << player.getMapName(stoi(choice) - 1) << endl;
            selectHeroesFirst(player);
        // } else if (stoi(choice) == 4) {
        //     cout << "External maps must follow a specific format to be used. Consult template.txt for an example." << endl;
        //     player.mapTemplate();
        //     mapCreator = true;
            
        //     while (mapCreator) {
        //         cout << "Continue? [Y/N]" << endl;
        //         getline(cin, yn);
        //         cout << endl;
                
        //         if (yn == "Y" || yn == "y" || yn == "yes" || yn == "YES" || yn == "Yes") {
        //             createMap(player);
        //         } else if (yn == "N" || yn == "n" || yn == "no" || yn == "NO" || yn == "No") {
        //             cout << "Understood." << endl << endl;
        //             mapCreator = false;
        //             selectMap(player);
        //         } else {
        //             cout << "Response not understood." << endl;
        //         }
        //     }
        } else {
            cout << "Choice not in range." << endl << endl;
            selectMap(player);
        }
    } else {
        cout << "Enter a number." << endl << endl;
        selectMap(player);
    }
}

// //modding
// void createMap(Player player) {
//     string mapFile;
    
//     cout << "Enter name of map input file." << endl;
//     getline(cin, mapFile);
    
//     cout << player.validMap(mapFile);
// }

//first hero choosing menu
void selectHeroesFirst(Player player) {
    cout << "Select hero 1." << endl;
    cout << "1: Berserker" << endl;
    cout << "2: Alchemist" << endl;
    cout << "3: Priest" << endl;
    cout << "4: Trapper" << endl;
    string choice;
    getline(cin, choice);
    if (isdigit(choice[0])) {
        if (stoi(choice) < 5 && stoi(choice) > 0) {
            Entity heroOne;
            switch (stoi(choice)) {
                case 1:
                    heroOne.setType("berserker");
                    break;
                case 2:
                    heroOne.setType("alchemist");
                    break;
                case 3:
                    heroOne.setType("priest");
                    break;
                case 4:
                    heroOne.setType("trapper");
                    break;
            }
            selectHeroesSecond(player, heroOne);
        } else {
            cout << "Choice not in range." << endl;
            selectHeroesFirst(player);
        }
    } else {
        cout << "Enter a number." << endl;
        selectHeroesFirst(player);
    }
}

//second hero choosing menu (essentially same as first)
void selectHeroesSecond(Player player, Entity heroOne) {
    cout << "Select hero 2." << endl;
    cout << "1: Berserker" << endl;
    cout << "2: Alchemist" << endl;
    cout << "3: Priest" << endl;
    cout << "4: Trapper" << endl;
    string choice;
    getline(cin, choice);
    if (isdigit(choice[0])) {
        if (stoi(choice) < 5 && stoi(choice) > 0) {
            Entity heroTwo;
            switch (stoi(choice)) {
                case 1:
                    heroTwo.setType("berserker");
                    break;
                case 2:
                    heroTwo.setType("alchemist");
                    break;
                case 3:
                    heroTwo.setType("priest");
                    break;
                case 4:
                    heroTwo.setType("trapper");
                    break;
            }
            player.setHeroes(heroOne, heroTwo);
            cout << "Heroes selected: " << heroOne.getName() << " and " << heroTwo.getName() << endl;
            game(player);
        } else {
            cout << "Choice not in range." << endl;
            selectHeroesSecond(player, heroOne);
        }
    } else {
        cout << "Enter a number." << endl;
        selectHeroesSecond(player, heroOne);
    }
}

//game loop
void game(Player player) {
    cout << endl << endl << "Entering dungeon..." << endl;
    bool dungeonActive = true;  //game is being played
    bool dungeonClear = false;  //map is fully explored
    while (dungeonActive) {
        cout << "++++++MAP++++++" << endl;
        player.dispMap();   //print out map
        cout << "+++++++++++++++" << endl;
        
        if (dungeonClear) {
            cout << "All rooms clear. The dungeon has been completed." << endl;
        }
        
        //ask for input (move rooms, go into rooms)
        cout << endl;
        cout << "Choose where to go." << endl;
        cout << "1. Into current room" << endl;
        cout << "2. North" << endl;
        cout << "3. East" << endl;
        cout << "4. South" << endl;
        cout << "5. West" << endl;
        cout << "6. Exit dungeon" << endl;
        
        //move rooms
        //show valid directions
        //ask for input
        //move rooms correctly
        //loop back to top
        
        //keeping it out of the switch case or it'll break
        string choice;
        getline (cin, choice);
        
        bool moveSuccess = false;
        bool inRoom = false;
        
        if (isdigit(choice[0])) {
            switch(stoi(choice)) {
            
                //room interaction
                case 1:
                    /*go into rooms
                     *if enemy room, fight (separate function)
                     *go into room
                     *interact with random item if not already done
                     *ask if user wants to exit room
                     *loop back to top*/
                
                    cout << "Went into room." << endl;
                    
                    if (player.inBattleRoom() == true) {
                        
                        //both heroes die
                        if (fight(&player) == false) {  //the & symbol is to pass the pointer to the function. using pointers makes hero damage persistent
                            dungeonActive = false;
                            break;
                            
                        //heroes lived    
                        } else {
                            cout << "****Battle won!****" << endl;
                            player.finishBattle();
                        }
                    }
                    
                    //room flavor text and points
                    player.currentRoomNarrate();
                    inRoom = true;
                    cout << "1. Leave room" << endl;
                    while (inRoom) {
                        getline (cin, choice);
                        if (isdigit(choice[0]) && stoi(choice) == 1) {
                            cout << "Leaving room." << endl;
                            inRoom = false;
                        } else {
                            cout << "Please enter 1 when ready." << endl;
                        }
                    }
                    
                    //when leaving check to see if everything's explored
                    dungeonClear = player.checkClear();
                    
                    break;
            
                //directional movement
                case 2:
                case 3:
                case 4:
                case 5:
                    moveSuccess = player.move(stoi(choice));
                    if (moveSuccess) {
                        cout << "Move successful." << endl;
                    } else {
                        cout << "You can not move in that direction." << endl;
                    }
                    break;
                    
                //exit game
                case 6:
                    cout << "Ending game." << endl;
                    player.saveFinalStats();
                    cout << "Tale written. Goodbye" << endl;
                    dungeonActive = false;
                    break;
                
                //invalid number
                default:
                    cout << "Invalid choice." << endl;
            }
        } else {
            //non-numerical input
            cout << "Please enter a number 1-5." << endl;
        }
        
        cout << endl;
    }
}

bool fight(Player *player) {    //modifies the actual player
    bool battle = true;
    
    cout << endl;
    cout << "You were ambushed by " << player->getEnemy(0).getName() << " and " << player->getEnemy(1).getName() << "!" << endl << endl;
    //functions from a pointer object need a -> symbol instead of a .
    
    while (battle) {
        //player->printStatus();
        
        for (int i = 0; i < 4; i++) {
            //go through a turn
            player->turn(i);
            
            //check for both heroes dead. if true, end game (game lost)
            if (player->checkForDeath(false)) {
                battle = false;
                cout << "**Your party has died.**" << endl;
                cout << "This is the end of your journey." << endl;
                player->saveFinalStats();
                cout << "Tale written. May your next adventure fare better." << endl;
                return false;
                break;
            }
            
            //check for both enemies dead. if true, end battle (won battle)
            if (player->checkForDeath(true)) {
                battle = false;
                return true;
                break;
            }
        }
    }
}

int main() {
    Player p;
    
    //testing stuff. uncomment to see maps
    // Map forest("forest.txt");
    // Map crypt("crypt.txt");
    // Map thieves("hideout.txt");
    
    // cout << "Name: " << forest.getID() << endl;
    // cout << "Theme: " << forest.getTheme() << endl;
    // //cout << "Position: " << forest.getPos() << endl;
    // forest.displayMap();
    // cout << endl;
    
    // cout << "Name: " << crypt.getID() << endl;
    // cout << "Theme: " << crypt.getTheme() << endl;
    // //cout << "Position: " << crypt.getPos() << endl;
    // crypt.displayMap();
    // cout << endl;
    
    // cout << "Name: " << thieves.getID() << endl;
    // cout << "Theme: " << thieves.getTheme() << endl;
    // //cout << "Position: " << thieves.getPos() << endl;
    // thieves.displayMap();
    // cout << endl;
    
    cout << endl << "Adventurers are needed to secure the surrounding area." << endl << endl;
    selectMap(p);
    
    return 0;
}