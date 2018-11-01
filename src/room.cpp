//
// Created by Shubham Bhokare on 10/15/18.
//

#include "room.h"
#include <iostream>
#include <vector>

using namespace std;

room::room(){

}

room::~room(){

}

//PARAMETRIC CONSTRUCTOR
room::room(string name, string status, string type, string description, vector <string> border,
           vector <container> container, vector <item > item, vector <creature> creature, vector <string> trigger) {
    this->name = name;
    this->status = status;
    this->type = type;
    this->description = description;
    this->border = border;
    this->container = container;
    this->item = item;
    this->creature = creature;
    this->trigger = trigger;
}
