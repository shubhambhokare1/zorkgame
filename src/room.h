//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_ROOM_H
#define ZORKGAME_ROOM_H

#include <iostream>
#include <vector>

#include "item.h"
#include "container.h"
#include "creature.h"

using namespace std;

class room{

    public:

        //Components of the room
        string name;
        string status;
        string type;
        string description;
        vector <string> border;
        vector <container> container;
        vector <item> item;
        vector <creature> creature;
        vector <string> trigger;

        //Commands applicable to room
        room();
        virtual ~room();
        //room(string name, string status, string type, string description, vector <string> border, vector <container> container, vector <item> item, vector <creature> creature, vector <string> trigger);


};

#endif //ZORKGAME_ROOM_H
