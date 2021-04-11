#include "Room.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Homework #: source file 

//constructor that shouldn't be used but is still here just in case
Room::Room() {
    enemiesAlive = false;
    canInteract = false;
}

//constructor that sets up the room based on theme and if enemies exist
Room::Room(string theme, bool enemyRoom) {
    canInteract = true;
    
    //all the room objects and descriptions that are available
    forestInter = {" forest altar", " deer corpse", " tangled thorn bush", " twisted tree", " small clearing", " fallen log", " quiet stream", " lost traveler", " strange doe", " tree with crabapples", 
        " pile of leaves", " Goatman corpse", " tree stump with mushrooms", " deer skeleton", " traveling merchant", " featureless area"};
    cryptInter= {" sarcophagus", " slain adventurer", " forbidden tome", " ritual site", " hidden cask", " resting skeleton", " startled Necromancer", " ghost", " portrait of a wizard", "n intricate urn",
        "n opened coffin", "n unmarked casket", " bouquet of wilted flowers", " half of a Ghoul", " mummified cat"};
    dwellInter = {" stash of loot", " pile of weapons", " stolen throne", " gambling table", " torn map", " luxurious cape", " dropped wallet", " cat", " familiar face", " table with food on it",
        " loaf of stale bread", " bookshelf with strange books", " wolfskin rug", " taxidermied deer", " wheel of cheese"};
    
    forestItems = {"Gnarled staff", "Rare flower", "Animal skull", "Clothing scraps", "Fine fur", "Teeth", "Cracked bone", "Sparkling rock", "Forest runes", "Fresh berries",
        "Large mushroom", "Mouse bones", "Lost supplies", "Animal horn", "Large pebble", "Fresh apple", "Jagged rock", "Twisted stick", "Broken arrow", "Chunk of meat"
    };
    cryptItems = {"Ancient bone", "Tarnished jewelry", "Dark focus", "Heirloom", "Blessed sword", "Urn fragments", "Ring", "Tattered journal", "Holy scroll", "Pile of dust",
        "Faded paper", "Cryptic spellbook", "Burnt-out candle", "Sacrificial dagger", "Ritual herbs", "Cursed amulet", "Bone shards", "Old clothing", "Abandoned locket", "Silver coins"
    };
    dwellingItems = {"Gold coins", "Stolen painting", "Cursed amulet", "Fancy silverware", "King's ring", "Mysterious potion", "Ham", "Holy book", "Small dog", "Hair ribbon",
        "Knight's sword", "Stolen letters", "Wizard's grimoire", "Seer's writings", "Demon's bones", "Fresh bread", "Lockbox", "Stray key", "Bottle of wine", "Animal pelts"
    };
    
    forestDesc = {"You inspect the dried blood on the altar and take some of the ritual herbs.", "You scavenge some meat from the carcass.", "You hacked a way into the bush and found a stash of supplies.",
        "You take note of it to use as a landmark later.", "You rest for a minute in the peaceful area.", "You see a squirrel in the log. The sight of it gives you strength.", "You take a drink from the sparkling creek.",
        "They ask for directions. You point in a random direction. They thank you.", "It looks you in the eyes, and asks, \"Is this fun for you?\" You can't respond.", "Bitter.", 
        "In the leaves is a robin hatchling. You can't see its nest, and you have no room to take it with you. You look away.", "You feel like moving on.", "You consider eating them, but don't.",
        "It's been picked clean, the bones are gray with age.", "They're grateful for your attempt to restore peace to the forest, and offer to trade with you.", "You feel the void calling."
    };
    cryptDesc = {"You crack open the lid and see a petrified corpse.", "You pay your respects and take some of their supplies for yourself.", "You read a most unsettling passage. Stress increased by 10.", 
        "You put out the candles and scuff the marks on the floor.", "Smells like Amontillado. The wall nearby seems newer than the rest.", "The skeleton rattles at you but does nothing else.",
        "You ready your weapons, but the Necromancer says \"Wait I'm not ready to fight! I still need to finish this resurrection!\" You leave them alone.", "They give a solemn nod and wish you luck.",
        "It's definitely cursed.", "They made the right choice. The cremated can't be reanimated.", "There's nothing inside. Whoever it belongs to should go back to it.", 
        "You can't find a name or date on it, but it looks very old.", "Whoever they were meant for was dearly loved.", "It tries struggling towards you, but it's missing its legs.", 
        "You wish the Necromancers had brought this one back."
    };
    dwellDesc = {"You take handfuls of gold for yourself.", "You test a sword on a practice dummy nearby.", "You sit on it. You feel very important.", 
        "You look at the cards and switch some around in case the players come back.", "It looks like it could lead to treasure, but half of it's missing.", "You pet the fur. It's soft.",
        "You open it up. It has your name in it. You've never had a wallet like that.", "You spend at least 10 minutes petting the cat before it bites you and runs off.", 
        "You find out this is his house. \"Why are there so many thieves here?\" you ask. \"I don't lock my doors.\" he responds.", "You try some of the food for yourself. It's cold.", 
        "It's hard enough to break teeth on. You bite into it anyway and regret it.", "The books seem to be written in a language that isn't real with words that seem to change.",
        "Scary.", "It wasn't made very well. It looks like it was dropped a few times... off a tall building.", "It's more cheese than a party could eat, and unfortunately, you can't take it with you."
    };
    
    randomInteractable(theme);
    //set up interactable points
    
    if (enemyRoom) {
        enemiesAlive = true;
        randomEnemies(theme);
        randomLoot(theme);
        //cout << enemies[0].getName() << endl;
    } else {
        enemiesAlive = false;
        //no enemies, no loot
        //set loot points to 0
    }
}

//updates the room data for defeating enemies and returns the points won.
double Room::noEnemiesLeft() {
    enemiesAlive = false;   //not actually used after initial map setup
    return (lootPoints[0] + lootPoints[1] + lootPoints[2]);
}

//gets points from interactable and disables it. if it's already interacted, does nothing
double Room::interact() {
    if (canInteract == true) {
        canInteract = false;
        return interactPoints;
    } else {
        return 0;
    }
}

//sets up random enemies related to theme (called if room has enemies)
void Room::randomEnemies(string theme) {
    int enemyInt[2] = {rand() % 3, rand() % 3};
    Entity temp;
    
    if (theme == "forest") {
        //forest enemies
        for (int i = 0; i < 2; i++) {
            switch (enemyInt[i]) {
                case 0:
                    temp.setType("goatman");
                    enemies[i] = temp;
                    break;
                case 1:
                    temp.setType("goatman shaman");
                    enemies[i] = temp;
                    break;
                case 2:
                    temp.setType("wolf");
                    enemies[i] = temp;
                    break;
            }
        }
        
    } else if (theme == "crypt") {
        //crypt enemies
        for (int i = 0; i < 2; i++) {
            switch (enemyInt[i]) {
                case 0:
                    temp.setType("skeleton");
                    enemies[i] = temp;
                    break;
                case 1:
                    temp.setType("necromancer");
                    enemies[i] = temp;
                    break;
                case 2:
                    temp.setType("ghoul");
                    enemies[i] = temp;
                    break;
            }
        }
        
    } else if (theme == "dwelling") {
        //dwelling enemies
        for (int i = 0; i < 2; i++) {
            switch (enemyInt[i]) {
                case 0:
                    temp.setType("bandit");
                    enemies[i] = temp;
                    break;
                case 1:
                    temp.setType("thief");
                    enemies[i] = temp;
                    break;
                case 2:
                    temp.setType("brawler");
                    enemies[i] = temp;
                    break;
            }
        }
        
    } else {
        //default. shouldn't be called unless it's really broken
        for (int i = 0; i < 2; i++) {
            switch (enemyInt[i]) {
                case 0:
                    temp.setType("goatman");
                    enemies[i] = temp;
                    break;
                case 1:
                    temp.setType("goatman shaman");
                    enemies[i] = temp;
                    break;
                case 2:
                    temp.setType("wolf");
                    enemies[i] = temp;
                    break;
            }
        }
        cout << "ERROR IN MAP THEME" << endl;
    }
}
        
//sets up random loot for a room (called if it has enemies)        
void Room::randomLoot(string theme) {
    for (int i = 0; i < 3; i++) {
        if (theme == "forest") {
            lootFlavor[i] = forestItems[rand() % forestItems.size()];
            lootPoints[i] = (rand() % 15) + 1;
        } else if (theme == "crypt") {
            lootFlavor[i] = cryptItems[rand() % cryptItems.size()];
            lootPoints[i] = (rand() % 15) + 1;
        } else if (theme == "dwelling") {
            lootFlavor[i] = dwellingItems[rand() % dwellingItems.size()];
            lootPoints[i] = (rand() % 15) + 1;
        }
    
    //cout << lootFlavor[i] << ": " << lootPoints[i] << " points" << endl; //for testing results
    }
}

//sets up the description of the room (object of interest and relevant description) based on theme
void Room::randomInteractable(string theme) {
    //these blocks are all the same. they just access different description banks
    if (theme == "forest") {
        int rndm = rand() % forestInter.size();
        //cout << "forest rndm: " << rndm << endl;
        interactable = forestInter[rndm];
        description = forestDesc[rndm];
    } else if (theme == "crypt") {
        int rndm = rand() % cryptInter.size();
        //cout << "crypt rndm: " << rndm << endl;
        interactable = cryptInter[rndm];
        description = cryptDesc[rndm];
    } else if (theme == "dwelling") {
        int rndm = rand() % dwellInter.size();
        //cout << "dwelling rndm: " << rndm << endl;
        interactable = dwellInter[rndm];
        description = dwellDesc[rndm];
    }
    interactPoints = (rand() % 11) + 5;
    //cout << interactable << endl; //testing
}

//returns enemy
Entity Room::getEnemy(int i) {
    return enemies[i];
}

//shows each piece of loot and corresponding points
void Room::lootRoll() {
    cout << "You found loot." << endl;
    for (int i = 0; i < 3; i++) {
        if (lootPoints[i] != 1) {
            cout << lootFlavor[i] << ": " << lootPoints[i] << " points" << endl;
        } else {
            cout << lootFlavor[i] << ": " << lootPoints[i] << " point" << endl;
        }
    }
}

//return the interactable (main description)
string Room::getInteract() {
    return interactable;    
}   

//return description of interaction (first visit to room)
string Room::getDescription() {
    return description;
}

//returns if enemies are still alive. might not actually work?
bool Room::enemiesAreAlive() {
    return enemiesAlive;
}