//
// Created by Shubham Bhokare on 10/15/18.
//

#include "room.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;

room::room(){

}

room::~room(){

}

//PARAMETRIC CONSTRUCTOR
room::room(xml_node<> * roomObj){
    xml_node<> *roomElement = roomObj->first_node();
    while (roomElement != NULL){
        cout << roomElement->name() << endl;
        string elementName = roomElement->name();



        //Iterations
        roomElement = roomElement->next_sibling();
    }
}
