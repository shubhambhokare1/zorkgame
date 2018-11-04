
#ifndef ZORKGAME_FUNCTIONS_H
#define ZORKGAME_FUNCTIONS_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <map>

#include "room.h"
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


room* getRoom(string name, map <string, room> rooms);

container* getContainer(string name,map <string, container> containers);

item* getItem(string name,map <string, item> items);

creature* getCreature(string name,map <string, creature> creatures);

#endif //ZORKGAME_FUNCTIONS_H