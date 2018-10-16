//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_CONTAINER_H
#define ZORKGAME_CONTAINER_H

#include <iostream>
#include <vector>

using namespace std;

class container{

public:
    string name;
    string status;
    string description;
    vector <string> accept;
    vector <string> item;
    vector <string> trigger;
};

#endif //ZORKGAME_CONTAINER_H
