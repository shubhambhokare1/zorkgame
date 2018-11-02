//
// Created by Shubham Bhokare on 10/15/18.
//

#include "container.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;

container::container(){

}

container::~container(){

}

//PARAMETRIZED CONSTRUCTOR
container::container(xml_node<> * containerObj){
    xml_node<> *containerElement = containerObj->first_node();
    while (containerElement != NULL){
        //cout << containerElement->name() << endl;
        string elementName = containerElement->name();



        //Iterations
        containerElement = containerElement->next_sibling();
    }
}