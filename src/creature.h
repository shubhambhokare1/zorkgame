//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_CREATURE_H
#define ZORKGAME_CREATURE_H

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


struct Attack {
	Condition condition;
	string print;
	vector <string> actions;
};

class creature{

public:

    //Attributes of the creature
    string name;
    string status;
    string description;
    vector <string> vulnerability;
    Attack attack;
    vector <triggers> trigger;

    //Functions performed by the creature
    creature();
    virtual ~creature();
    creature(xml_node<> *);
};

#endif //ZORKGAME_CREATURE_H
