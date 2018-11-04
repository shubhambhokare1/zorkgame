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
	lock = 1;
    while (containerElement != NULL){
        //cout << containerElement->name() << endl;
        string elementName = containerElement->name();
		string elementValue = containerElement->value();

		//INSTANTIATE VALUES IN OBJECT
		if (elementName.compare("name") == 0) {
			this->name = elementValue;
		}
		else if (elementName.compare("status") == 0) {
			this->status = elementValue;
		}
		else if (elementName.compare("accept") == 0) {
			this->accept.push_back(elementValue);
		}
		else if (elementName.compare("description") == 0) {
			this->description = elementValue;
		}
		else if (elementName.compare("trigger") == 0) {
			triggers trig(containerElement);
			this->trigger.push_back(trig);
		}
		else if (elementName.compare("item") == 0) {
			this->item.push_back(elementValue);
		}


        //Iterations
        containerElement = containerElement->next_sibling();
    }
}