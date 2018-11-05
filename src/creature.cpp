//
// Created by Shubham Bhokare on 11/3/18.
//

#include "creature.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;

creature::creature(){

}

creature::~creature(){

}

//PARAMETRIZED CONSTRUCTOR
creature::creature(xml_node<> * creatureObj){
    xml_node<> *creatureElement = creatureObj->first_node();
    while (creatureElement != NULL){
        //cout << creatureElement->name() << endl;
        string elementName = creatureElement->name();
        string elementValue = creatureElement->value();


        //INSTANTIATE VALUES IN OBJECT
        if (elementName.compare("name") == 0) {
            this->name = elementValue;
        }
        else if (elementName.compare("status") == 0) {
            this->status = elementValue;
        }
        else if (elementName.compare("vulnerability") == 0) {
            this->vulnerability.push_back(elementValue);
        }
        else if (elementName.compare("description") == 0) {
            this->description = elementValue;
        }
        else if (elementName.compare("attack") == 0) {

            Attack attack;
            //Creating turnOn object and initializing
            xml_node<> *attackElement = creatureElement->first_node();
            while (attackElement != NULL) {
                string attackName = attackElement->name();
                string attackValue = attackElement->value();
                if (attackName.compare("print") == 0) {
                    attack.print = attackValue;
                }
                else if (attackName.compare("condition") == 0) {
                    Condition condition;
                    xml_node<> *cond = attackElement->first_node();
                    string condName = cond->name();
                    string condVal = cond->value();

                    while (cond != NULL) {
                        if (condName.compare("has") == 0) {
                            attack.condition.owner.has = condVal;
                        }
                        if (condName.compare("object") == 0) {
                            attack.condition.owner.object = condVal;
                            attack.condition.status.object = condVal;
                        }
                        if (condName.compare("status") == 0) {
                            attack.condition.status.status = condVal;
                        }
                        if (condName.compare("owner") == 0) {
                            attack.condition.owner.owner = condVal;
                        }
                        cond = cond->next_sibling();

                    }

                }
                else if (attackName.compare("action") == 0) {
                    attack.actions.push_back(attackValue);
                }
                attackElement = attackElement->next_sibling();
            }
            this->attack = attack;
        }
        else if (elementName.compare("trigger") == 0) {
            triggers trig(creatureElement);
            this->trigger.push_back(trig);
        }

        //Iterations
        creatureElement = creatureElement->next_sibling();
    }
}