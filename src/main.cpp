//
// Created by Shubham Bhokare on 11/3/18.
//

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
#include "functions.h"

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


using namespace std;
using namespace rapidxml;

vector <string> c_items;
vector <string> c_containers;
vector <triggers> c_triggers;
vector <string> c_creatures;
vector <string> c_inventory;

//Creating hash maps for all the different type of objects
map <string, room> rooms;
map <string, item> items;
map <string, container> containers;
map <string, creature> creatures;
map <string, triggers> trigs;


int main(int argc, char * argv[]) {

    //Error checking for inappropriate inputs or commands.
    //Only xml file should be an input
    if (argc != 2 ) {
        cout << "Error! Enter: a.out filename.xml" << endl;
        return 1;
    }

    //XML FILE PARSING that give an xml node
    file<> xmlFile(argv[1]); 			 	//Default template is char
    xml_document<> doc;						//XML doc parser
    doc.parse<0>(xmlFile.data()); 		 	//Default parse flag
    xml_node<> *node = doc.first_node(); 	//Map node (root)



    //TRAVERSE THROUGH THE Node initializing the objects
    xml_node<> *mapElement = node->first_node();
    while (mapElement != NULL){
        //cout << mapElement->name() << endl;
        string elementName = mapElement->name();

        //Create the appropriate object
        //Room Object
        if (elementName.compare("room") == 0){
            room r(mapElement);
            rooms.insert(make_pair(r.name, r));
        }
        //Item Object
        if (elementName.compare("item") == 0){
            item i(mapElement);
            items.insert(make_pair(i.name, i));
        }
        //Container Object
        if (elementName.compare("container") == 0){
            container c(mapElement);
            containers.insert(make_pair(c.name, c));
        }
        //Creature Object
        if (elementName.compare("creature") == 0){
            creature cr(mapElement);
            creatures.insert(make_pair(cr.name, cr));
        }

        //Iterations
        mapElement = mapElement->next_sibling();
    }

	
	//Gameplay Init
	room *c_room;
	char in[20];


    //TESTING
   	room *start_room = getRoom("Entrance",rooms);
	cout<<start_room->description<<endl;
	c_room = start_room;
	
	while(true)	{
		cout<<">";
		cin>>in;
		traverseRoom(in,c_room,rooms);


	}

}

void getNew(room *c_room, map <string, creature> creatures,map <string, item> items,map <string, container> containers)	{

	c_items.clear();
	c_items.insert(c_items.end(), c_room->items.begin(), c_room->items.end());

	c_containers.clear();
	c_containers.insert(c_containers.end(), c_room->containers.begin(), c_room->containers.end());
	for(int i=0; i < c_containers.size(); i++){
		container* c_container = getContainer(c_containers[i],containers);
		if(c_container->lock == 0){
			c_items.insert(c_items.end(), c_container->item.begin(), c_container->item.end());
		}
	}

	c_creatures.clear();
	if(c_room->creatures.size()>0){
		c_creatures.insert(c_creatures.end(), c_room->creatures.begin(), c_room->creatures.end());
	}

	c_triggers.clear();
	c_triggers.insert(c_triggers.end(), c_room->trigger.begin(), c_room->trigger.end());
	for(int i=0; i < c_items.size(); i++)	{
		item * c_item = getItem(c_items[i],items);
		c_triggers.insert(c_triggers.end(), c_item->trigger.begin(), c_item->trigger.end());
	}

	for(int i=0; i < c_containers.size(); i++){
		container * c_container = getContainer(c_containers[i],containers);
		c_triggers.insert(c_triggers.end(), c_container->trigger.begin(), c_container->trigger.end());
	}
	if(c_creatures.size()>0){
		for(int i=0; i < c_creatures.size(); i++){
			if(creatures.find(c_creatures[i]) != creatures.end()){
				creature * c_creature = getCreature(c_creatures[i],creatures);
				c_triggers.insert(c_triggers.end(), c_creature->trigger.begin(), c_creature->trigger.end());
			}

		}
	}

}

int triggerWithCommand(map <string, room> rooms, map <string, creature> creatures,map <string, item> items,map <string, container> containers){
	int flag = 0;
	for(int i=0; i < c_triggers.size(); i++){
		triggers trig = c_triggers[i];
		for(int i=0; i < trig.Cond.size(); i++){
			if(!trig.command.empty()){
				if(!trig.Cond[i].owner.has.empty()){
					if(trig.Cond[i].owner.owner.compare("inventory") == 0){
						if(find(c_inventory.begin(), c_inventory.end(), trig.Cond[i].owner.object) != c_inventory.end()){
							if(trig.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
							}
					    }
						else if(find(c_inventory.begin(), c_inventory.end(), trig.Cond[i].owner.object) == c_inventory.end()){
							if(trig.Cond[i].owner.has.compare("no") == 0){
								flag = 1;
							}				
						}
					}
					else{
						if(getItem(trig.Cond[i].owner.object,items) != 0 && getContainer(trig.Cond[i].owner.owner,containers) != 0){
							item *item = getItem(trig.Cond[i].owner.object,items);
							container *container = getContainer(trig.Cond[i].owner.owner,containers);
							if(find(container->item.begin(), container->item.end(), trig.Cond[i].owner.object) != container->item.end() && trig.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
							}
							else if(find(container->item.begin(), container->item.end(), trig.Cond[i].owner.object) == container->item.end() && trig.Cond[i].owner.has.compare("no") == 0){
								flag = 1;
							}
						}
						else if(getItem(trig.Cond[i].owner.object,items) != 0 && getRoom(trig.Cond[i].owner.owner,rooms) != 0){
							item *item = getItem(trig.Cond[i].owner.object,items);
							room *room = getRoom(trig.Cond[i].owner.owner,rooms);
							if(find(room->items.begin(), room->items.end(), trig.Cond[i].owner.object) != room->items.end() && trig.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
							}
							else if(find(room->items.begin(), room->items.end(), trig.Cond[i].owner.object) == room->items.end() && trig.Cond[i].owner.has.compare("no") == 0){
								flag = 1;
							}
						}
					}
				}
				else{
					if(getItem(trig.Cond[i].owner.object,items) != 0){
						item * item = getItem(trig.Cond[i].owner.object,items);
						if(item->status.compare(trig.Cond[i].status.status) == 0){
                    		flag = 1;
						}
					}
                    else if(getRoom(trig.Cond[i].owner.object,rooms) != 0){
						room * room = getRoom(trig.Cond[i].owner.object,rooms);
						if(room->status.compare(trig.Cond[i].status.status) == 0){
							flag = 1;
						}
					}
					else if(getContainer(trig.Cond[i].owner.object,containers) != 0){
						container * container = getContainer(trig.Cond[i].owner.object,containers);
						if(container->status.compare(trig.Cond[i].status.status) == 0){
							flag = 1;
						}
					}
					else if(getCreature(trig.Cond[i].owner.object,creatures) != 0){
						creature * creature = getCreature(trig.Cond[i].owner.object,creatures);
						if(creature->status.compare(trig.Cond[i].status.status) == 0){
							flag = 1;
						}
					}
				}
			}
		}
	}
	return flag;

}

int triggersWithoutCommand(map <string, room> rooms, map <string, creature> creatures,map <string, item> items,map <string, container> containers){
	int flag = 0;

	for(int i=0; i < c_triggers.size(); i++){
		triggers trigger = c_triggers[i];
		for(int i=0; i < trigger.Cond.size(); i++){
			if(trigger.command.empty() && trigger.tr == false){
				if(trigger.Cond[i].owner.has.empty()){
					if(getItem(trigger.Cond[i].owner.object,items) != 0){
						item * item = getItem(trigger.Cond[i].owner.object,items);
						if(item->status.compare(trigger.Cond[i].status.status) == 0){
							flag = 1;
                            for(int i = 0; i < trigger.print.size(); i++) {
                                cout<<trigger.print[i]<<endl;
                            }
							if(trigger.type.compare("single") == 0){
								item->status = "go";
							}
						}
					}
                    else if(getRoom(trigger.Cond[i].owner.object,rooms) != 0){
						room * room = getRoom(trigger.Cond[i].owner.object,rooms);
						if(room->status.compare(trigger.Cond[i].status.status) == 0){
							flag = 1;
							if(trigger.type.compare("single") == 0){
								room->status = "go";
							}
						}
					}
					else if(getContainer(trigger.Cond[i].owner.object,containers) != 0){
						container * container = getContainer(trigger.Cond[i].owner.object,containers);
						if(container->status.compare(trigger.Cond[i].status.status) == 0){
							flag = 1;
						    if(trigger.type.compare("single") == 0){
								container->status = "go";
							}
						}
					}
					else if(getCreature(trigger.Cond[i].owner.object,creatures) != 0){
						creature * creature = getCreature(trigger.Cond[i].owner.object,creatures);
						if(creature->status.compare(trigger.Cond[i].status.status) == 0){
							flag = 1;
							if(trigger.type.compare("single") == 0){
								creature->status = "go";
							}
						}
					}

				}
				else{
					if(trigger.Cond[i].owner.owner.compare("inventory") == 0){
						if(find(c_inventory.begin(), c_inventory.end(), trigger.Cond[i].owner.object) != c_inventory.end()){
							if(trigger.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
								for(int i = 0; i < trigger.print.size(); i++) {
                                cout<<trigger.print[i]<<endl;
                                }
								for(int i=0; i < trigger.action.size(); i++){
									//hiddenCommands(trigger.action[i]); //Shubham see this
								}
							}
						}
						else if(find(c_inventory.begin(), c_inventory.end(), trigger.Cond[i].owner.object) == c_inventory.end()){
							if(trigger.Cond[i].owner.has.compare("no") == 0){
								flag = 0;
								for(int i = 0; i < trigger.print.size(); i++) {
                                cout<<trigger.print[i]<<endl;
                                }
								for(int i=0; i < trigger.action.size(); i++){
									//hiddenCommands(trigger.action[i]);
								}
							}
						}
					}
					else{
						if(getItem(trigger.Cond[i].owner.object,items) != 0 && getContainer(trigger.Cond[i].owner.owner,containers) != 0){
							item *item = getItem(trigger.Cond[i].owner.object,items);
							container *container = getContainer(trigger.Cond[i].owner.owner,containers);
							if(find(container->item.begin(), container->item.end(), trigger.Cond[i].owner.object) != container->item.end() && trigger.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
								for(int i = 0; i < trigger.print.size(); i++) {
                                cout<<trigger.print[i]<<endl;
                                }
								for(int i=0; i < trigger.action.size(); i++){
									//hiddenCommands(trigger.action[i]);
								}
							}
							else if(find(container->item.begin(), container->item.end(), trigger.Cond[i].owner.object) == container->item.end() && trigger.Cond[i].owner.has.compare("no") == 0){
								flag = 1;
								for(int i = 0; i < trigger.print.size(); i++) {
                                cout<<trigger.print[i]<<endl;
                                }
								for(int i=0; i < trigger.action.size(); i++){
									//hiddenCommands(trigger.action[i]);
								}
							}
					    }
						else if(getItem(trigger.Cond[i].owner.object,items) != 0 && getRoom(trigger.Cond[i].owner.owner,rooms) != 0){
							item *item = getItem(trigger.Cond[i].owner.object,items);
							room *room = getRoom(trigger.Cond[i].owner.owner,rooms);
							if(find(room->items.begin(), room->items.end(), trigger.Cond[i].owner.object) != room->items.end() && trigger.Cond[i].owner.has.compare("yes") == 0){
								flag = 1;
							}
							else if(find(room->items.begin(), room->items.end(), trigger.Cond[i].owner.object) == room->items.end() && trigger.Cond[i].owner.has.compare("no") == 0){
								flag = 1;
							}
						}
					}
				}
			}
		}
	}
	return flag;

}

void ParseInput(vector<string>& store, const string& userIn)
{
	string varStore;
	istringstream iss(userIn);

	iss >> noskipws;

	char delim;
	while (true) {
		if (iss >> varStore)
			store.push_back(varStore);
		else if (iss.eof())
			break;
		else
			store.push_back(string());
	}
}
