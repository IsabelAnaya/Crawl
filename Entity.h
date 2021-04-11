#include <iostream>
#include <string>
using namespace std;

//CSCI 1300 Fall 2019
//Author: Isabel Anaya
//Recitation: 105 - Michael Bradshaw
//Project 3: Entity header file 

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    public:
        Entity();
        void setType(string type);
        void heal();
        double attack();
        void takeDamage(double dmg);
        string getName();
        double getHealth();
        double getMaxHealth();
        string getAttackName();
        string getHealName();
        void changeHealth(double amount);
        double getHealAmount();
    
    private:
        double maxHealth;
        double health;
        string name;
        string attackName;
        double attackAmount;
        string healName;
        double healAmount;
};

#endif