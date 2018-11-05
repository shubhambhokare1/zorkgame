//
// Created by Shubham Bhokare on 10/15/18.
//

#include "item.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;

item::item(){

}

item::~item(){

}

//PARAMETERIZED CONSTRUCTOR
item::item(xml_node<> * itemObj){
    xml_node<> *itemElement = itemObj->first_node();
    while (itemElement != NULL){
        //cout << itemElement->name() << endl;
        string elementName = itemElement->name();
        string elementValue = itemElement->value();

        //INSTANTIATE VALUES IN OBJECT
        if (elementName.compare("name") == 0){
            this->name = elementValue;
        }
        else if (elementName.compare("status") == 0){
            this->status = elementValue;
        }
        else if (elementName.compare("writing") == 0){
            this->writing = elementValue;
        }
        else if (elementName.compare("description") == 0){
            this->description = elementValue;
        }
        else if (elementName.compare("turnon") == 0){

            turn_on turnOn;
            //Creating turnOn object and initializing
            xml_node<> *turnOnElement = itemElement->first_node();
            while (turnOnElement != NULL){
                string turnOnName = turnOnElement->name();
                string turnOnValue = turnOnElement->value();
                if (turnOnName.compare("print") == 0){
                    turnOn.print = turnOnValue;
                }
                else if (turnOnName.compare("action") == 0){
                    turnOn.actions.push_back(turnOnValue);
                }
                turnOnElement = turnOnElement->next_sibling();
            }
            this->turn = turnOn;
        }
        else if (elementName.compare("trigger") == 0){
            triggers trig(itemElement);
            this->trigger.push_back(trig);
        }

        //Iterations
        itemElement = itemElement->next_sibling();
    }
}