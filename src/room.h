//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_ROOM_H
#define ZORKGAME_ROOM_H

#include <iostream>
#include <vector>

using namespace std;

class room{

    public:
        string name;
        string status;
        string type;
        string description;
        vector <string> border;
        vector <string> container;
        vector <string> item;
        vector <string> creature;
        vector <string> trigger;
};

#endif //ZORKGAME_ROOM_H
