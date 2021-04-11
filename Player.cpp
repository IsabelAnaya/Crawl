#include "Player.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Player source file 

//constructor. maps must be added manually
Player::Player() {
    points = 0;
    charTurn = 0;
    srand(time(NULL));  //this ensures the random seed is only set once so it doesn't do weird things
    
    allMaps[0] = Map("forest.txt");
    allMaps[1] = Map("crypt.txt");
    allMaps[2] = Map("hideout.txt");
    //map list is hardcoded to only support 3 maps
}

//sets the playing map
void Player::setMap(int choice) {
    selectedMap = allMaps[choice];
    currentRoom = selectedMap.getCurrentRoom();
}

//sets the player's characters
void Player::setHeroes(Entity one, Entity two) {
    heroes[0] = one;
    heroes[1] = two;
}

//gets the name of the map through the player class. user won't have direct access to the map
string Player::getMapName(int i) {
    return allMaps[i].getID();
}

//gets the name of the player's hero through the player class
string Player::getHeroName(int i) {
    if (i > 1 || i < 0) {
        return "invalid hero index accessed";
    } else {
        return heroes[i].getName();
    }
}

//heal the heroes, show new health, show points
void Player::finishBattle() {
    heroes[0].heal();
    heroes[1].heal();
    
    cout << "Heroes healed once." << endl;
    cout << heroes[0].getName() << ": " << heroes[0].getHealth() << "/" << heroes[0].getMaxHealth() << endl;
    cout << heroes[1].getName() << ": " << heroes[1].getHealth() << "/" << heroes[1].getMaxHealth() << endl << endl;
    
    currentRoom.lootRoll();
}

//write final points, heroes, and map name to file
void Player::saveFinalStats() {
    string mapTheme;
    string heroType1;
    string heroType2;
    mapTheme = selectedMap.getTheme();
    heroType1 = heroes[0].getName();
    heroType2 = heroes[1].getName();
    
    cout << "Enter name of new save (ex. run1)" << endl;
    getline(cin, savefile);
    
    while (savefile == "crypt" || savefile == "hideout" || savefile == "forest") {
        cout << "Please enter a different name." << endl;
        getline(cin, savefile);
    }
    ofstream save(savefile + ".txt");
    save << "Map: " << selectedMap.getID() << endl;
    save << "Type: " << selectedMap.getTheme() << endl << endl;
    save << "Heroes: " << heroes[0].getName() << " and " << heroes[1].getName() << endl;
    save << "Points: " << points << endl;
    
    //extra flavor depending on if all rooms cleared
    if (selectedMap.checkClear() == true) {
        save << "Map cleared!" << endl << endl;
        
        //good ending
        if (mapTheme == "forest") {
            save << "The Goatman clan has been run out of the forest. The forest path became safe again for travelers, and trade between neighboring towns grew." << endl;
        } else if (mapTheme == "crypt") {
            save << "The Necromancers and their creations were driven from the crypt. Families could once again put their loved ones to rest without fear of dark magic taking them a second time." << endl;
        } else if (mapTheme == "dwelling") {
            save << "The Thieves were scared away from the area and all stolen items were returned. The people of the village were so grateful, they gave you some of the gold you returned." << endl;
        }
        
        //special ending if both heroes were the same
        if (heroType1 == heroType2) {
            if (heroType1 == "Priest") {
                save << "The priests' skills in healing became widely known. People would travel far to receive a blessing from them. Some say they were gods in disguise.";    
            }
            if (heroType1 == "Alchemist") {
                save << "The alchemists were able to open their own wildly successful shop together. Their potions and poisons are regarded as some of the strongest available.";
            }
            if (heroType1 == "Berserker") {
                save << "The berserkers continued to fight their way across the world. They were deadly in battle, and a strong pair of allies to anyone they met.";
            }
            if (heroType1 == "Trapper") {
                save << "The trappers continued adventuring. Their adventure ended when they were able to capture a terrifying elder dragon together. Sales from the dragon's hide meant they could retire comfortably.";
            } 
        
        //ending for each hero
        } else {
            for (int i = 0; i < 2; i++) {
                heroType1 = heroes[i].getName();
                if (heroType1 == "Priest") {
                    save << "The priest offered to heal anyone in need that they came across. Villages would celebrate when they came to visit." << endl;
                }
                if (heroType1 == "Alchemist") {
                    save << "The alchemist created new concotions from the loot they gathered. Sometimes the mixtures even worked, and could be sold for decent money." << endl;
                }
                if (heroType1 == "Berserker") {
                    save << "The berserker traveled to new lands, always searching for a stronger foe. Wherever they went, villages would send their strongest to learn from them." << endl;
                }
                if (heroType1 == "Trapper") {
                    save << "The trapper sold remains of enemies they had fought. Their materials are sought out by tailors and wizards alike." << endl;
                }
            }
        }
        
    //game lost/exited
    } else {
        //bad ending
        save << "Dungeon abandoned." << endl;
        if (mapTheme == "forest") {
            save << "The Goatman clan continues to grow. Merchants fear the forest path and pay steep prices for bodyguards.";
        } else if (mapTheme == "crypt") {
            save << "Dark magic taints the crypt. Villagers swear they can recognize the Ghouls that emerge to attack at night.";
        } else if (mapTheme == "dwelling") {
            save << "Precious belongings continue to go missing. The band of Thieves have control of the area.";
        }
    }
}

//creates the map visual through the player class
void Player::dispMap() {
    selectedMap.displayMap();
}

//calls the move function from the map. if it succeeds, updates the current room
bool Player::move(int dir) {
    bool success = selectedMap.move(dir);
    
    if (success) {
        currentRoom = selectedMap.getCurrentRoom();
        if (currentRoom.enemiesAreAlive()) {
            currentEnemies[0] = currentRoom.getEnemy(0);
            currentEnemies[1] = currentRoom.getEnemy(1);
        }
    }
    
    //used for making the "move successful/you can't move there" messages
    return success;
}

//handles entering a room
void Player::currentRoomNarrate() {
    
    //for after winning a battle
    if (selectedMap.activeBattleRoom() == true) {
        double tempPoints = selectedMap.roomClear();
        points += tempPoints;
        cout << "Total points gained: " << tempPoints << endl;
        
        cout << "Now at " << points << " points." << endl << endl;
    }
    
    //description of room
    cout << "You found a" + currentRoom.getInteract() + "." << endl;
    
    if (selectedMap.unexploredRoom() == true) {
        
        //description of interaction
        cout << currentRoom.getDescription() << endl << endl;
        double pointsReceived = currentRoom.interact();
        points += pointsReceived;
        cout << "You got " << pointsReceived << " points." << endl;
        cout << "Now at " << points << " points." << endl << endl;
        
        //update room to explored
        selectedMap.updateCurrentRoomCode();
        
    //room has already been visited
    } else {
        cout << "You have already been in this room." << endl;
        cout << "Still at " << points << " points." << endl << endl;
    }
    
    
}

//check for if the current room has enemies
bool Player::inBattleRoom() {
    if (selectedMap.activeBattleRoom()) {
        return true;
    } else {
        return false;
    }
}

//used in fight function to get the names
Entity Player::getEnemy(int i) {
    return currentEnemies[i];
}

//printout for the statuses of all heroes and enemies
void Player::printStatus() {
    cout << "----BATTLE STATUS----" << endl;
    cout << heroes[0].getName() << ": " << heroes[0].getHealth() << "/" << heroes[0].getMaxHealth() << endl;
    cout << heroes[1].getName() << ": " << heroes[1].getHealth() << "/" << heroes[1].getMaxHealth() << endl;
    cout << currentEnemies[0].getName() << ": " << currentEnemies[0].getHealth() << "/" << currentEnemies[0].getMaxHealth() << endl;
    cout << currentEnemies[1].getName() << ": " << currentEnemies[1].getHealth() << "/" << currentEnemies[1].getMaxHealth() << endl;
    cout << "---------------------" << endl;
    cout << endl;
}

//used to check for battle/game ending conditions
bool Player::checkForDeath(bool enemy) {
    
    //enemies are dead check
    if (enemy == true) {
        if (currentEnemies[0].getHealth() <= 0 && currentEnemies[1].getHealth() <= 0) {
            return true;
        } else {
            return false;
        }
    
    //heroes are dead check    
    } else {
        if (heroes[0].getHealth() <= 0 && heroes[1].getHealth() <= 0) {
            return true;
        } else {
            return false;
        }
    }
}

//The Real Fight Function
void Player::turn(int i) {
    
    //variables
    string input;
    int choice = 0;
    string input2;
    int choice2 = 0;
    bool moveSelecting = true;
    bool targetSelecting = true;
    
    printStatus();
    
    cout << "==============" << endl;

    switch (i) {
        
        //hero turns
        case 0:
        case 1:
            
            //check if hero is dead
            if (heroes[i].getHealth() <= 0) {
                cout << heroes[i].getName() << " is critically wounded." << endl;
                
            //hero survived
            } else {
                //options
                cout << heroes[i].getName() << "'s turn. (Hero " << i + 1 << ")" << endl;
                cout << "1. " << heroes[i].getAttackName() << endl;
                cout << "2. " << heroes[i].getHealName() << endl;
                
                //loop until valid input executed
                while (moveSelecting) {
                    getline(cin, input);
                    cout << endl;
                    
                    if (isdigit(input[0]) && (stoi(input) == 1 || stoi(input) == 2)) {
                        choice = stoi(input);
                        switch (choice) {
                            
                            //attack
                            case 1:
                                while(targetSelecting) {
                                    cout << "Choose target." << endl;
                                    cout << "1. " << currentEnemies[0].getName() << ": " << currentEnemies[0].getHealth() << "/" << currentEnemies[0].getMaxHealth() << endl;
                                    cout << "2. " << currentEnemies[1].getName() << ": " << currentEnemies[1].getHealth() << "/" << currentEnemies[1].getMaxHealth() << endl;
                                    getline(cin, input2);
                                    cout << endl;
                                    
                                    //valid target
                                    if (isdigit(input2[0]) && (stoi(input2) == 1 || stoi(input2) == 2)) {
                                        choice2 = stoi(input2);
                                        cout << heroes[i].getName() << " attacked " << currentEnemies[choice2 - 1].getName() << " with " << heroes[i].getAttackName() << "!" << endl;
                                        currentEnemies[choice2 - 1].takeDamage(heroes[i].attack());
                                        cout << currentEnemies[choice2 - 1].getName() << " took " << heroes[i].attack() << " damage." << endl;
                                        cout << currentEnemies[choice2 - 1].getName() << " is now at " << currentEnemies[choice2 - 1].getHealth() << "/" << currentEnemies[choice2 - 1].getMaxHealth() << endl;
                                        targetSelecting = false;
                                    
                                    //invalid input
                                    } else {
                                        cout << "Enter a number 1-2." << endl;
                                    }
                                }
                                break;
                                
                            //heal heroes
                            case 2:
                                while(targetSelecting) {
                                    cout << "Choose target." << endl;
                                    cout << "1. " << heroes[0].getName() << ": " << heroes[0].getHealth() << "/" << heroes[0].getMaxHealth() << endl;
                                    cout << "2. " << heroes[1].getName() << ": " << heroes[1].getHealth() << "/" << heroes[1].getMaxHealth() << endl;
                                    getline(cin, input2);
                                    cout << endl;
                                    
                                    //valid target
                                    if (isdigit(input2[0]) && (stoi(input2) == 1 || stoi(input2) == 2)) {
                                        choice2 = stoi(input2);
                                        
                                        if (choice2 == i + 1) { //self
                                            cout << heroes[i].getName() << " healed with " << heroes[i].getHealName() << "!" << endl;
                                            heroes[i].heal();
                                            cout << heroes[i].getName() << " recovered " << heroes[i].getHealAmount() << " health." << endl;
                                            cout << heroes[i].getName() << " is now at " << heroes[i].getHealth() << "/" << heroes[i].getMaxHealth() << endl;
                                            targetSelecting = false;
                                            
                                        } else { //the other one
                                            cout << heroes[i].getName() << " healed " << heroes[choice2 - 1].getName() << " with " << heroes[i].getHealName() << "!" << endl;
                                            heroes[choice2 - 1].changeHealth(heroes[i].getHealAmount());
                                            cout << heroes[choice2 - 1].getName() << " recovered " << heroes[i].getHealAmount() << " health." << endl;
                                            cout << heroes[choice2 - 1].getName() << " is now at " << heroes[choice2 - 1].getHealth() << "/" << heroes[choice2 - 1].getMaxHealth() << endl;
                                            targetSelecting = false;
                                        }
                                    
                                    //invalid input
                                    } else {
                                        cout << "Enter a number 1-2." << endl;
                                    }
                                }
                                break;
                                
                            //invalid input
                            default:
                                cout << "Enter a number 1-2." << endl;
                                break;
                        }
                        moveSelecting = false;
                        
                    //invalid input
                    } else {
                        cout << "Enter a number 1-2." << endl;
                    }
                }
            }
        break;
        
        //enemy turns
        case 2:
        case 3:
        
            //enemy is dead
            if (currentEnemies[i - 2].getHealth() <= 0) {
                cout << currentEnemies[i - 2].getName() << " is dead." << endl;
                
            //enemy is alive
            } else {
                cout << currentEnemies[i - 2].getName() << "'s turn." << endl;
                choice = (rand() % 5) + 1;  //+1 is actually completely arbitrary. makes a number between 1 and 5
                choice2 = rand() % 2;       //doesn't have + 1 because the arrays get weird with it
                
                // cout << "DEBUG: choice = " << choice << endl;
                // cout << "DEBUG: choice2 = " << choice2 << endl;
                
                //enemy is attacking
                if (choice < 5) { //80% chance of attacking
                    
                    //check if target is dead
                    if (heroes[choice2].getHealth() != 0) {
                        cout << currentEnemies[i - 2].getName() << " used " << currentEnemies[i - 2].getAttackName() << " on " << heroes[choice2].getName() << "!" << endl;
                        heroes[choice2].takeDamage(currentEnemies[i - 2].attack());
                        cout << heroes[choice2].getName() << " took " << currentEnemies[i - 2].attack() << " damage." << endl;
                        cout << heroes[choice2].getName() << " is now at " << heroes[choice2].getHealth() << "/" << heroes[choice2].getMaxHealth() << endl;
                        
                    //targets the other hero if first choice is dead
                    } else if (choice2 == 0) {
                        cout << currentEnemies[i - 2].getName() << " used " << currentEnemies[i - 2].getAttackName() << " on " << heroes[1].getName() << "!" << endl;
                        heroes[1].takeDamage(currentEnemies[i - 2].attack());
                        cout << heroes[1].getName() << " took " << currentEnemies[i - 2].attack() << " damage." << endl;
                        cout << heroes[1].getName() << " is now at " << heroes[1].getHealth() << "/" << heroes[1].getMaxHealth() << endl;
                    } else if (choice2 == 1) {
                        cout << currentEnemies[i - 2].getName() << " used " << currentEnemies[i - 2].getAttackName() << " on " << heroes[0].getName() << "!" << endl;
                        heroes[0].takeDamage(currentEnemies[i - 2].attack());
                        cout << heroes[0].getName() << " took " << currentEnemies[i - 2].attack() << " damage." << endl;
                        cout << heroes[0].getName() << " is now at " << heroes[0].getHealth() << "/" << heroes[0].getMaxHealth() << endl;
                    }
                
                //enemy used heal    
                } else if (choice == 5) { //20% chance of healing
                    cout << currentEnemies[i - 2].getName() << " used " << currentEnemies[i -2].getHealName() << "!" << endl;
                    currentEnemies[i - 2].heal();
                    
                    if (currentEnemies[i - 2].getHealAmount() < 0) {
                        cout << currentEnemies[i - 2].getName() << " lost " << abs(currentEnemies[i - 2].getHealAmount()) << " health." << endl;
                    } else {
                        cout << currentEnemies[i - 2].getName() << " restored " << currentEnemies[i - 2].getHealAmount() << " health." << endl;
                    }
                    
                    cout << currentEnemies[i - 2].getName() << " is now at " << currentEnemies[i - 2].getHealth() << "/" << currentEnemies[i - 2].getMaxHealth() << endl;
                }
                break;
            }
    }   
    cout << endl;
}

//gets the map clear check from the map
bool Player::checkClear() {
    return selectedMap.checkClear();
}

// //generate mapTemplate.txt
// void Player::mapTemplate() {
//     ofstream writer("mapTemplate.txt");
//     writer << "Map Name" << endl;
//     writer << "map theme" << endl;
//     for (int i = 0; i < 5; i++) {
//         writer << "#.#.#.#.#" << endl;
//     }
    
//     writer << endl << endl << endl;
//     writer << "Premade themes are forest, crypt, and dwelling" << endl;
//     writer << "Replace #'s with numbers 0-3" << endl;
//     writer << "0: wall (unpassable)" << endl;
//     writer << "1: empty room" << endl;
//     writer << "2: room with enemies" << endl;
//     writer << "3: player start room (ONLY HAVE 1)" << endl;
//     writer << endl;
//     writer << "Maps not following proper formatting are not supported. Use at own risk.";
// }

// //modding?
// int Player::validMap(string filename) {
//     string identifier;
//     string theme;
//     string linecheck;
//     bool playerStart = false;

//     ifstream file;
//     file.open(filename);
    
//     if (file.is_open() == false) {
//         return -1;
//     }
    
//     if (!getline(file, identifier)) {
//         return -2;
//     }
    
//     if (!getline(file, theme)) {
//         return -3;
//     }
    
//     for (int i = 0; i < 5; i++) {
//         getline(file, linecheck);
//         for (int j = 0; j < 9; j++) {
//             if ((i % 2) == 0) {
//                 if (linecheck[i] != '0' && linecheck[i] != '1' && linecheck[i] != '2' && linecheck[i] != '3') {
//                     cout << linecheck[i];
//                     return -4;
//                 } else {
//                     if (linecheck[i] == '3' && playerStart == true) {
//                         return -5;
//                     } else if (linecheck[i] == '3' && playerStart == false) {
//                         playerStart = true;
//                     }
//                 }
//             } else if ((i % 2) == 1) {
//                 if (linecheck[i] != '.') {
//                     return -6;
//                 }
//             }
//         }
//     }
    
//     return 7;
// }