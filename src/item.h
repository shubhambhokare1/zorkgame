//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_ITEM_H
#define ZORKGAME_ITEM_H

#include <iostream>
#include <vector>

using namespace std;

class item{

    public:
        string name;
        string status;
        string description;
        string writing;
        string turn_on;
        vector <string> trigger;
};

#endif //ZORKGAME_ITEM_H
