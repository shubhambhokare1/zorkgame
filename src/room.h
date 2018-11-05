//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_ROOM_H
#define ZORKGAME_ROOM_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

#include "item.h"
#include "container.h"
#include "creature.h"
#include "triggers.h"

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

//STRUCT FOR BORDER
struct Border {
    string name;
    string direction;
};


class room{

    public:

        //Components of the room
        string name;
        string status;
        string type;
        string description;
        vector <Border> borders;
        vector <string> containers;
        vector <string> items;
        vector <string> creatures;
        vector <triggers> trigger;

        //Commands applicable to root
        virtual ~room();
        room(xml_node<> * roomObj);

};

#endif //ZORKGAME_ROOM_H
