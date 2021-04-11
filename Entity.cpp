#include "Entity.h"
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Entity source file 

//makes an empty entity. use setType afterwards
Entity::Entity() {
    maxHealth = 0;
    health = 0;
    name = "";
    
    attackName = "";
    attackAmount = 0;
    healName = "";
    healAmount = 0;
}

//gives the entity object correct stats based on a given type. not a constructor so type can be assigned after construction
void Entity::setType(string type) {
    //heroes
    if (type == "berserker") {
        maxHealth = 25;
        name = "Berserker";
        attackName = "Axe Slash";
        attackAmount = 5;
        healName = "Battlecry";
        healAmount = 3;
    }
            
    if (type == "alchemist") {
        maxHealth = 20;
        name = "Alchemist";
        attackName = "Poison Vial";
        attackAmount = 5;
        healName = "Health Potion";
        healAmount = 4;
    }
            
    if (type == "priest") {
        maxHealth = 17;
        name = "Priest";
        attackName = "Holy Fire";
        attackAmount = 2;
        healName = "Bless";
        healAmount = 8;
    }
            
    if (type == "trapper") {
        maxHealth = 20;
        name = "Trapper";
        attackName = "Snare";
        attackAmount = 4;
        healName = "Bandage";
        healAmount = 5;
    }
            
    //enemies    
        if (type == "skeleton") {
            maxHealth = 18;
            name = "Skeleton";
            attackName = "Rusted Sword";
            attackAmount = 4;
            healName = "Rattle Bones";
            healAmount = 2;
        }
        if (type == "necromancer") {
            maxHealth = 22;
            name = "Necromancer";
            attackName = "Dark Spell";
            attackAmount = 3;
            healName = "Reconstruct";
            healAmount = 5;
        }
        if (type == "ghoul") {
            maxHealth = 27;
            name = "Ghoul";
            attackName = "Rip";
            attackAmount = 5;
            healName = "Rot";
            healAmount = -2;        
        }
            
        if (type == "goatman") {
            maxHealth = 21;
            name = "Goatman";
            attackName = "Spear";
            attackAmount = 4;
            healName = "Rage";
            healAmount = 1;        
        }
        if (type == "goatman shaman") {
            maxHealth = 18;
            name = "Goatman Shaman";
            attackName = "Curse";
            attackAmount = 3;
            healName = "Chant";
            healAmount = 4;        
         }
        if (type == "wolf") {
            maxHealth = 16;
            name = "Wolf";
            attackName = "Bite";
            attackAmount = 5;
            healName = "Lick Wounds";
            healAmount = 2;        
        }
            
        if (type == "bandit") {
            maxHealth = 19;
            name = "Bandit";
            attackName = "Shiv";
            attackAmount = 4;
            healName = "Bandage";
            healAmount = 2;        
        }
        if (type == "thief") {
            maxHealth = 23;
            name = "Thief";
            attackName = "Jab";
            attackAmount = 5;
            healName = "Stolen Medicine";
            healAmount = 4;        
        }
        if (type == "brawler") {
            maxHealth = 30;
            name = "Brawler";
            attackName = "Punch";
            attackAmount = 4;
            healName = "Blood Loss";
            healAmount = -3;        
        }
    
    //sets current health to max. no damage has been taken yet
    health = maxHealth;
}

//getter for attackAmount
double Entity::attack() {
    return attackAmount;
}

//heals character (increases health)
void Entity::heal() {
    double maxHeal = maxHealth - health;
    double maxHarm = 0 - health;
    
    //keep the character from overhealing
    if (healAmount > maxHeal) {
        health += maxHeal;
        
    //keeps the character from overkilling (some enemies have harms instead of heals)
    } else if (healAmount < maxHarm) {
        health = 0;
        
    //normal case
    } else {
        health += healAmount;
    }
}

//decrease health
void Entity::takeDamage(double dmg) {
    if (dmg > health) {
        health = 0;
    } else {
        health -= dmg;
    }
}

//getter for name/type
string Entity::getName() {
    return name;
}

//getter for current health
double Entity::getHealth() {
    return health;
}

//getter for maximum health
double Entity::getMaxHealth() {
    return maxHealth;
}

//getter for attack name
string Entity::getAttackName() {
    return attackName;
}

//getter for heal name
string Entity::getHealName() {
    return healName;
} 

//changes health outside of attacks and self heals
void Entity::changeHealth(double amount) {
    if (amount + health < 0) {
        health = 0;
    } else if (amount + health > maxHealth) {
        health = maxHealth;
    } else {
        health += amount;
    }
}

//gets the heal amount. used when heroes heal other heroes
double Entity::getHealAmount() {
    return healAmount;
}