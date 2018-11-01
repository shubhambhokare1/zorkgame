//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_CONTAINER_H
#define ZORKGAME_CONTAINER_H

#include <iostream>
#include <vector>

#include "item.h"

using namespace std;

class container{

public:

    //Components of the container
    string name;
    string status;
    string description;
    vector <string> accept;
    vector <item> item;
    vector <string> trigger;

    //Functions applicable to the container
    container();
    virtual ~container();
};

#endif //ZORKGAME_CONTAINER_H
