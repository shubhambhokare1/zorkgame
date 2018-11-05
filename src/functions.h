
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



/*room* getRoom(string name, map <string, room> rooms);

container* getContainer(string name,map <string, container> containers);

item* getItem(string name,map <string, item> items);

creature* getCreature(string name,map <string, creature> creatures);

void traverseRoom(string input,room *c_room,map <string, room> rooms);

void displayInventory(vector <string> Inventory);



vector <string> removeFromInventory(string item, vector <string> Inventory);

void removeFromContainer(string item, vector <string> c_containers, map <string, container> containers);*/


#endif //ZORKGAME_FUNCTIONS_H