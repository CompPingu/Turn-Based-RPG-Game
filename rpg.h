#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


class Character
{
protected:
    string name;
    int maxHealth;
    int level;
    int damage;
    int stamina;
    vector<string> specialMoves;

    bool shield = false;

    int updatedHealth = 130;
    int updateStamina = 120;
    

public:
    Character(){
        name = "Default";
        maxHealth = 100;
        level = 5;
        damage = 0;
        stamina = 100;

    }

    Character(string name, int maxHealth, int level, int damage, int stamina) : name(name), maxHealth(maxHealth), level(level), damage(damage), stamina(stamina) {}

    
   void resetAfterBattle() 
    {
        maxHealth = updatedHealth;
        stamina = updateStamina;
        shield = false;
    }

//Level Up Function
    int calXPGain(int currentLevel) {return currentLevel * 2;}
    virtual void levelUp(int XP)
    {
        int xpToLevUp = calXPGain(level);
        if (XP >= xpToLevUp){
            level ++;
            increaseStats();
            cout << getName() << " is now level " << getLevel() << endl;
        }

    } 
    virtual void increaseStats() {updatedHealth +=10; updateStamina +=5;}
    void addspecialMove(string move)
    {
        if (find(specialMoves.begin(), specialMoves.end(), move) == specialMoves.end()) {
            specialMoves.push_back(move);
        }
    }


//Saving Game
    void saveGame1(string filename)
    {
        ofstream fout(filename);

        fout << "maxHealth=" << maxHealth << endl;
        fout << "stamina=" << stamina << endl;
        fout << "level=" << level << endl;

        // Load existing moves from file
        vector<string> existingMoves;
        ifstream fin("conjurer.txt");
        string line;
        while (getline(fin, line)) {
            if (line.substr(0, 13) == "specialMoves") {
                stringstream ss(line.substr(14));
                string move;
                while (getline(ss, move, ',')) {
                    existingMoves.push_back(move);
                }
                break;
            }
        }
        fin.close();

        // Add new moves
        for (int i = 0; i < specialMoves.size(); i++) {
            if (find(existingMoves.begin(), existingMoves.end(), specialMoves[i]) == existingMoves.end()) {
                fout << "specialMoves=" << specialMoves[i] << endl;
                existingMoves.push_back(specialMoves[i]);
            }
        }

        fout.close();

        // Display the moves
        for (int i = 0; i < existingMoves.size(); i++) {
            cout << i + 1 << ". " << existingMoves[i] << endl;
        }
    }

    
    void loadGame1(string filename)
    {
        ifstream fin(filename);
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string key, value;
            getline(ss, key, '=');
            getline(ss, value);
            if (key == "maxHealth") {
                maxHealth = stoi(value);
            } else if (key == "stamina") {
                stamina = stoi(value);
            } else if (key == "level") {
                level = stoi(value);
            } else if (key == "specialMoves") {
                specialMoves.push_back(value);
            }
        }
        fin.close();
    }
  

//Overwritten for shield
    void takeDamage(int num)
    {
        if (shield)
        {
            shield = false;
            cout << name << " blocked the attack" << endl;
        }
        else{
            maxHealth -= num;
            if (maxHealth < 0){
                maxHealth = 0;
            }
        }
    }


    

    virtual vector<string>& getSpecialMoves() { return specialMoves; }

    virtual string getName() {return name;}
    virtual int getHealth() {return maxHealth;}
    virtual int getLevel() {return level;}
    virtual int getDamage() {return damage;}
    virtual int getStamina() {return stamina;}

    void setHealth(int health){
        maxHealth = health;
    }
    
    virtual void basicAttack(Character* target) = 0;
    virtual void useSpecialMove(Character& target) = 0;
    virtual void useSpecialMove2(Character& target) = 0;
    virtual void useSpecialMove3(Character& target) = 0;


};

#endif
