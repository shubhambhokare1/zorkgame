//
// Created by Shubham Bhokare on 10/15/18.
//

#include "room.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;


room::~room(){

}

//PARAMETRIC CONSTRUCTOR
room::room(xml_node<> *roomObj) {
    xml_node<> *roomElement = roomObj->first_node();
    while (roomElement != NULL){
        //cout << roomElement->name() << endl;
        string elementName = roomElement->name();
        string elementValue = roomElement->value();

        //INSTANTIATE VALUES IN OBJECT
        if (elementName.compare("name") == 0){
            this->name = elementValue;
        }
        else if (elementName.compare("status") == 0){
            this->status = elementValue;
        }
        else if (elementName.compare("type") == 0){
            this->type = elementValue;
        }
        else if (elementName.compare("description") == 0){
            this->description = elementValue;
        }
        else if (elementName.compare("border") == 0){
            Border border;
            //Creating border object and initializing
            xml_node<> *borderElement = roomElement->first_node();
            while (borderElement != NULL){
                string borderName = borderElement->name();
                string borderValue = borderElement->value();
                if (borderName.compare("name") == 0){
                    border.name = borderValue;
                }
                else if (borderName.compare("direction") == 0){
                    border.direction = borderValue;
                }
                borderElement = borderElement->next_sibling();
            }
            this->borders.push_back(border);
        }
        else if (elementName.compare("container") == 0){
            this->containers.push_back(elementValue);
        }
        else if (elementName.compare("item") == 0){
            this->items.push_back(elementValue);
        }
        else if (elementName.compare("creature") == 0){
            this->creatures.push_back(elementValue);
        }
        else if (elementName.compare("trigger") == 0){
            triggers trig(roomElement);
            this->trigger.push_back(trig);
        }

        //Iterations
        roomElement = roomElement->next_sibling();
    }
}
