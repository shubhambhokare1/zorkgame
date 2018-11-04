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
vector <string> c_triggers;
vector <string> c_creatures;


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


    //Creating hash maps for all the different type of objects
    map <string, room> rooms;
    map <string, item> items;
    map <string, container> containers;
    map <string, creature> creatures;
    map <string, triggers> trigs;


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