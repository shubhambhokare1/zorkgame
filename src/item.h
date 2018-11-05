//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_ITEM_H
#define ZORKGAME_ITEM_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

#include "triggers.h"

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


using namespace std;
using namespace rapidxml;

//STRUCT FOR TURNON ACTIONS
struct turn_on{
    string print;
    vector <string> actions;
};

class item{

    public:

        //Components of the item
        string name;
        string status;
        string description;
        string writing;
        turn_on turn;
        vector <triggers> trigger;

        //Functions related to the item
        item();
        virtual ~item();
        item(xml_node<> *);
};

#endif //ZORKGAME_ITEM_H
