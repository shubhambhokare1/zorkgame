//
// Created by Shubham Bhokare on 10/15/18.
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



        //Iterations
        creatureElement = creatureElement->next_sibling();
    }
}
