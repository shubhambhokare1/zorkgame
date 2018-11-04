//
// Created by Shubham Bhokare on 10/15/18.
//

#ifndef ZORKGAME_CONTAINER_H
#define ZORKGAME_CONTAINER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

#include "triggers.h"
#include "item.h"

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;


class container{

public:

    //Components of the container
    string name;
    string status;
    string description;
    vector <string> accept;
    vector <string> item;
    vector <triggers> trigger;
    int lock;

    //Functions applicable to the container
    container();
    virtual ~container();
    container(xml_node<> *);
};

#endif //ZORKGAME_CONTAINER_H
