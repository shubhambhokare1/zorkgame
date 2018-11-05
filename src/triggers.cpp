//
// Created by Shubham Bhokare on 11/3/18.
//

#include "triggers.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rapidxml;

triggers::triggers(){

}

triggers::~triggers(){

}

//PARAMETRIZED CONSTRUCTOR
triggers::triggers(xml_node<> * trigObj){
    xml_node<> *triggerElement = trigObj->first_node();
    this->tr = false;
    while (triggerElement != NULL){
        //cout << creatureElement->name() << endl;
        string elementName = triggerElement->name();
        string elementValue = triggerElement->value();


        //INSTANTIATE VALUES IN OBJECT
        if (elementName.compare("type") == 0) {
            this->type = elementValue;
        }
        else if (elementName.compare("command") == 0) {
            this->command = elementValue;
        }
        else if (elementName.compare("print") == 0) {
            this->print = elementValue;
        }
        else if (elementName.compare("action") == 0) {
            this->action.push_back(elementValue);
        }
        else if (elementName.compare("condition") == 0) {
            Condition condition;
            xml_node<> *cond = triggerElement->first_node();
            while (cond != NULL) {
                string condName = cond->name();
                string condVal = cond->value();

                if (condName.compare("has") == 0) {
                    condition.owner.has = condVal;
                }
                if (condName.compare("object") == 0) {
                    condition.owner.object = condVal;
                    condition.status.object = condVal;
                }
                if (condName.compare("status") == 0) {
                    condition.status.status = condVal;
                }
                if (condName.compare("owner") == 0) {
                    condition.owner.owner = condVal;
                }
                cond = cond->next_sibling();
            }

            this->Cond.push_back(condition);
        }

        //Iterations
        triggerElement = triggerElement->next_sibling();
    }
}