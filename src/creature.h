//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_CREATURE_H
#define ZORKGAME_CREATURE_H

#include <iostream>
#include <vector>

using namespace std;

class creature{

public:

    //Attributes of the creature
    string name;
    string status;
    string description;
    vector <string> vulnerability;
    string attack;
    vector <string> trigger;

    //Functions performed by the creature
    creature();
    virtual ~creature();
};

#endif //ZORKGAME_CREATURE_H
