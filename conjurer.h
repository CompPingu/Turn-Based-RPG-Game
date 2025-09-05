#include "rpg.h"



class Conjurer : public Character{

protected:
    
    int ConjurerHealth;
    int mana;

    string lightningMeteor = "Lightning Meteor";
    int lightningMeteorDamage = 30;

    string lightningCloak = "Lightning Cloak";

    string twinLightningDragon = "Twin Lightning Dragon";
    int twinLightningDragonDamage = 40;

    bool doubleDamage = false;

public:
    Conjurer(string name, int maxHealth, int level, int damage, int stamina) : Character(name, maxHealth, level, damage, stamina), ConjurerHealth(maxHealth) , mana(stamina)
    {}

    void basicAttack(Character* target){
        bool attack = false;
        while(!attack)
        {
            if (stamina > 10 && mana > 5){
                cout << getName() << " used Lightning Blade" << endl;
                int damage = 15;
                if (isDoubleDamage()) {  // check if double damage flag is set
                    damage *= 2;  // double damage
                    setDoubleDamage(false);  // reset double damage flag
                }
                target->takeDamage(damage);
                stamina -= 10;
                mana-= 5;
                attack = true;
            }
            else{
                cout << "Not enough KI" << endl;
                cout << "Recharge?   y/n\n";
                char rest;
                cin >> rest;
                if (rest == 'y'){
                    stamina += 50;
                    mana += 50;
                    attack = true;
                }
                else{
                    attack = true;
                }
            }
        }
    }

    
    void useSpecialMove(Character& target){
        bool attack = false;
        while(!attack)
        {
            if (stamina > 15 && mana >= 10){
                cout << getName() << " used " << lightningMeteor << endl;
                if (isDoubleDamage()){
                    target.takeDamage(lightningMeteorDamage * 2);
                    stamina -=20;
                    mana -= 10;
                    attack = true;
                }
                target.takeDamage(lightningMeteorDamage);
                stamina -=20;
                mana -= 10;
                attack = true;
            }
            else{
                cout << "Not enought KI" << endl;
                cout << "Recharge?   y/n\n";
                char rest;
                cin >> rest;
                if (rest == 'y'){
                    stamina += 50;
                    mana += 50;
                    attack = true;
                }
                else{
                    attack = true;
                }
            }
        }
    }

    void useSpecialMove2(Character& target){
        bool attack = false;  // flag for double damage
        while(!attack)
        {
            if (mana > 20){
                cout << getName() << " used " << lightningCloak << endl;
                target.takeDamage(0);
                mana -= 10;
                doubleDamage = true;  // set flag for next attack
                attack = true;
            }
            else{
                cout << "Not enough KI" << endl;
                cout << "Recharge?   y/n\n";
                char rest;
                cin >> rest;
                if (rest == 'y'){
                    stamina += 50;
                    mana += 50;
                    attack = true;
                }
                else{
                    attack = true;
                }
            }
        }

        // check if next attack should deal double damage
        if (doubleDamage) {
            cout << "Next attack deals double damage!" << endl;
            setDoubleDamage(true);  // set flag for double damage on next attack
        }
    }

    void setDoubleDamage(bool flag) {
        doubleDamage = flag;
    }
    bool isDoubleDamage(){
        return doubleDamage;
    }



    void useSpecialMove3(Character& target){
        bool attack = false;
        while(!attack)
        {
            if (stamina > 20 && mana >= 30){
                cout << getName() << " used " << twinLightningDragon << endl;
                if (isDoubleDamage()){
                    target.takeDamage(twinLightningDragonDamage * 2);
                    stamina -=20;
                    mana -= 10;
                    attack = true;
                }
                target.takeDamage(twinLightningDragonDamage);
                stamina -=20;
                mana -= 10;
                attack = true;
            }
            else{
                cout << "Not enought KI" << endl;
                cout << "Recharge?   y/n\n";
                char rest;
                cin >> rest;
                if (rest == 'y'){
                    stamina += 50;
                    mana += 50;
                    attack = true;
                }
                else{
                    attack = true;
                }
            }
        }
    }

//Level Up Function
    virtual void levelUp(int XP)
    {
        int xpToLevUp = calXPGain(level);
        if (XP >= xpToLevUp){
            level ++;
            increaseStats();
            cout << getName() << " is now level " << getLevel() << endl;
            if (level == 10){
                addspecialMove(lightningMeteor);
                cout << getName() << " Unlocked a new move" << endl;
            }
            if (level == 15){
                addspecialMove(lightningCloak);
                cout << getName() << " Unlocked a new move" << endl;
            }
            if (level == 20){
                addspecialMove(twinLightningDragon);
                cout << getName() << " Unlocked a new move" << endl;
            }
        }
        

    } 
    virtual void increaseStats() {updatedHealth +=10; updateStamina +=5;}



    void trackHealth(){
        cout << "Current Health: " << ConjurerHealth << endl;
    }


};