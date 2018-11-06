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

int endgame = 0;

room *c_room;
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

//FUNCTION DECLARATIONS
void gameCommands(string input);
void getNew(room *c_room);
void behindScenesCommands(string command);
int TriggerFunc(int ind);
void checkTrigger(string input);
void ParseInput(vector<string>& store, const string& userIn);


//FUNCTIONS TO TRAVERSE THROUGH MAP
room* getRoom(string name) {
    map <string, room>::iterator r;
    r = rooms.find(name);
    if(r != rooms.end()){
        return &(r->second);
    }
    else{
        return 0;
    }
}
container* getContainer(string name){
    map <string, container>::iterator c;
    c = containers.find(name);
    if(c != containers.end()){
        return &(c->second);
    }
    else{
        return 0;
    }
}
item* getItem(string name){
    map <string, item>::iterator i;
    i = items.find(name);
    if(i != items.end()){
        return &(i->second);
    }
    else{
        return 0;
    }
}
creature* getCreature(string name){
    map <string, creature>::iterator c;
    c = creatures.find(name);
    if(c != creatures.end()){
        return &(c->second);
    }
    else{
        return 0;
    }
}

//UTILITY FUNCTIONS
vector<string> ParseInput(string str, string delim)
{
    vector <string> result;
    while(str.size()){
        int index = str.find(delim);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+delim.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

void removeFromContainer(string item){
    for(int i=0; i < c_containers.size(); i++){
        container* ct = getContainer(c_containers[i]);
        if(find(ct->item.begin(), ct->item.end(), item) != ct->item.end()){
            std::vector<string>::iterator it;
            for(it = ct->item.begin(); it!=ct->item.end();it++){
                string it_name = *it;
                if(it_name.compare(item) == 0){
                    ct->item.erase(it);
                    break;
                }
            }
        }
    }
}

void removeFromInventory(string item){
    std::vector<string>::iterator it;
    for(it = c_inventory.begin(); it!=c_inventory.end();it++){
        string it_name = *it;
        if(it_name.compare(item) == 0){
            c_inventory.erase(it);
            break;
        }
    }
}


//GAME COMMANDS

//ROOM TRAVERSAL - n,s,w,e
void traverseRoom(string input)	{

    int dflag = 0;

        vector <Border> bord = c_room->borders;
        if(input == "n"){
            for(int i=0; i < bord.size(); i++){
                if(bord[i].direction == "north"){
                    c_room = getRoom(bord[i].name);
                    dflag = 1;
                    cout<<c_room->description<<endl;
                }
            }
            if(dflag == 0){
                cout<<"Invalid path!"<<endl;
            }
            cout<<"You are currently in "<<c_room->name<<endl;
        }
        else if(input == "s"){
            for(int i=0; i < bord.size(); i++){
                if(bord[i].direction == "south"){
                    c_room = getRoom(bord[i].name);
                    dflag = 1;
                    cout<<c_room->description<<endl;
                }
            }
            if(dflag == 0){
                cout<<"Invalid path!"<<endl;
            }
            cout<<"You are currently in "<<c_room->name<<endl;
        }
        else if(input == "e"){
            for(int i=0; i < bord.size(); i++){
                if(bord[i].direction == "east"){
                    c_room = getRoom(bord[i].name);
                    dflag = 1;
                    cout<<c_room->description<<endl;
                }
            }
            if(dflag == 0){
                cout<<"Invalid path!"<<endl;
            }
            cout<<"You are currently in "<<c_room->name<<endl;
        }
        else if(input == "w"){
            for(int i=0; i < bord.size(); i++){
                if(bord[i].direction == "west"){
                    c_room = getRoom(bord[i].name);
                    dflag = 1;
                    cout<<c_room->description<<endl;
                }
            }
            if(dflag == 0){
                cout<<"Invalid path!"<<endl;
            }
            cout<<"You are currently in "<<c_room->name<<endl;
        }
}


//INVENTORY DISPLAY - i
void displayInventory(){
    cout<<"Inventory: ";
    if(c_inventory.size() > 0){
        for(int i=0; i < c_inventory.size(); i++){
            cout<<c_inventory[i]<<" ";
        }
        cout<<""<<endl;
    }
    else{
        cout<<"empty"<<endl;
    }
}

//Changes item ownership from room or container to inventory - take
void takeItem(string input){
    vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 2){
        if(find(c_inventory.begin(), c_inventory.end(), words[1]) != c_inventory.end()){
            cout<<"Item exists in inventory"<<endl;
        }
        else if(find(c_items.begin(), c_items.end(), words[1]) != c_items.end()){
            c_inventory.push_back(words[1]);
            cout<<words[1]<<" added to inventory"<<endl;
            removeFromContainer(words[1]);
        }
        else{
            cout<<"Can't take "<<words[1]<<endl;
        }
    }
    else{
        cout<<"Incorrect command used"<<endl;
        cout<<"Enter: take (item)"<<endl;
    }
}

void openContainer(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 2){
        if(std::find(c_containers.begin(), c_containers.end(), words[1]) != c_containers.end()){
            container * ct = getContainer(words[1]);
            if(ct -> item.size() == 0){
                cout<<words[1]<<" is empty"<<endl;
            }
            else{
                ct->lock = 0;
                cout<<words[1]<<" contains: ";
                for(int i=0; i < ct-> item.size(); i++){
                    cout<<ct->item[i]<<" ";
                }
                cout<<" "<<endl;
            }
        }

        else if(containers.find(words[1]) != containers.end()){
            cout<<words[1]<<" is not present in this room"<<endl;
        }
        else{
            cout<<words[1]<<" is not a container"<<endl;
        }

    }
    else{
        cout<<"Incorrect command used"<<endl;
        cout<<"Enter: open (item)"<<endl;
    }
}

void openExit(string input){
    if(c_room->type.compare("exit") == 0){
        cout<<"Game Over"<<endl;
        endgame = 1;
    }
    else{
        cout<<"Incorrect. Unable to exit. Try again"<<endl;
    }
}

void readItem(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 2){
        if(std::find(c_inventory.begin(), c_inventory.end(), words[1]) != c_inventory.end()){
            item * item = getItem(words[1]);
            if(item->writing.empty()){
                cout<<"Noting written on "<<item->name<<endl;
            }
            else{
                cout<<item->writing<<endl;
            }
        }
        else{
            cout<<"Take item in order to read it"<<endl;
        }
    }
    else{
        cout<<"Invalid command used"<<endl;
        cout<<"Enter: read (item)"<<endl;
    }
}

void dropItem(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 2){
        if(std::find(c_inventory.begin(), c_inventory.end(), words[1]) != c_inventory.end()){
            cout<<words[1]<<" dropped"<<endl;
            removeFromInventory(words[1]);
            room * room = getRoom(c_room->name);
            room->items.push_back(words[1]);
        }
        else{
            cout<<"No such item exists in inventory"<<endl;
        }
    }
    else{
        cout<<"Invalid command used"<<endl;
        cout<<"Enter: drop (item)"<<endl;
    }
}

void putItem(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 4){
        if(words[2].compare("in") == 0){
            item * it = getItem(words[1]);
            if(it == 0){
                cout<<"Item not exist"<<endl;
            }
            else if(std::find(c_containers.begin(), c_containers.end(), words[3]) == c_containers.end()){
                cout<<"Container not present in this room"<<endl;
            }
            else if(std::find(c_inventory.begin(), c_inventory.end(), words[1]) == c_inventory.end()){
                cout<<"No such item in exists in inventory"<<endl;
            }
            else{
                container * containers = getContainer(words[3]);
                if(containers->accept.size() == 0){

                    cout<<"Item "<<words[1]<<" added to "<<words[3]<<endl;
                    container * ct = getContainer(words[3]);
                    ct->item.push_back(words[1]);
                    removeFromInventory(words[1]);
                }else{
                    for(int i=0; i < containers->accept.size(); i++){
                        if(containers->accept[i].compare(it->name) == 0){
                            cout<<"Item "<<words[1]<<" added to "<<words[3]<<endl;
                            containers->item.push_back(words[1]);
                            removeFromInventory(words[1]);
                        }
                        else{
                            cout<<words[3]<<" doesn't accept "<<words[1]<<endl;
                        }
                    }
                }
            }
        }
        else{
            cout<<"Invalid command used"<<endl;
        }
    }
    else{
        cout<<"Invalid command used"<<endl;
        cout<<"Enter: put (item) in (container)"<<endl;
    }
}

void turnOnItem(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 3){
        if(std::find(c_inventory.begin(), c_inventory.end(), words[2]) != c_inventory.end()){
            item * item = getItem(words[2]);
            cout<<"You activate the "<<words[2]<<endl;
            if(!item->turn.print.empty()){
                cout<<item->turn.print<<endl;
            }
            if(item->turn.actions.size()>0){
                for(int i=0; i < item->turn.actions.size(); i++){
                    behindScenesCommands(item->turn.actions[i]);
                }
            }
        }
        else{
            cout<<"No such item exists in inventory"<<endl;
        }
    }
    else{
        cout<<"Invalid game command"<<endl;
        cout<<"Enter: turn on (item)"<<endl;
    }
}

void attackCreature(string input){
    std::vector <string> words;
    words = ParseInput(input, " ");
    if(words.size() == 4){
        if(words[2].compare("with") == 0){
            if(getCreature(words[1]) == 0){
                cout<<"No such creature"<<endl;
            }
            else if(find(c_creatures.begin(), c_creatures.end(), words[1]) == c_creatures.end()){
                cout<<"Creature is not in this room"<<endl;
            }
            else if(getItem(words[3]) == 0){
                cout<<"Item does not exist"<<endl;
            }
            else if(std::find(c_inventory.begin(), c_inventory.end(), words[3]) == c_inventory.end()){
                cout<<"No such item exist in inventory"<<endl;
            }
            else{
                creature * creaturex = getCreature(words[1]);
                item * itemx = getItem(words[3]);
                string ob_status = creaturex->attack.condition.status.status;
                if(std::find(creaturex->vulnerability.begin(), creaturex->vulnerability.end(), itemx->name) != creaturex->vulnerability.end()) {
                    if (creaturex->attack.condition.owner.object.empty()) {
                        cout << "You assault the " << creaturex->name << " with " << itemx->name << endl;
                        cout << creaturex->attack.print << endl;
                        for (int i = 0; i < creaturex->attack.actions.size(); i++) {
                            behindScenesCommands(creaturex->attack.actions[i]);
                        }
                    }
                    else{
                        string ob_name = creaturex->attack.condition.owner.object;
                        if(getItem(ob_name) != 0){
                            item * item = getItem(ob_name);
                            if(item->status.compare(ob_status) == 0){
                                cout<<"You assault the "<<creaturex->name<<" with "<<item->name<<endl;
                                cout<<creaturex->attack.print<<endl;
                                for(int i=0; i < creaturex->attack.actions.size(); i++){
                                    behindScenesCommands(creaturex->attack.actions[i]);
                                }
                            }
                            else{
                                cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
                            }
                        }
                        else if(getCreature(ob_name) != 0){
                            creature * creature = getCreature(ob_name);
                            if(creature->status.compare(ob_status) == 0){
                                cout<<"You assault the "<<creaturex->name<<" with "<<creature->name<<endl;
                                cout<<creaturex->attack.print<<endl;
                                for(int i=0; i < creaturex->attack.actions.size(); i++){
                                    behindScenesCommands(creaturex->attack.actions[i]);
                                }
                            }
                            else{
                                cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
                            }
                        }
                        else if(getContainer(ob_name) != 0){
                            container * container = getContainer(ob_name);
                            if(container->status.compare(ob_status) == 0){
                                cout<<"You assault the "<<creaturex->name<<" with "<<creaturex->name<<endl;
                                cout<<creaturex->attack.print<<endl;
                                for(int i=0; i < creaturex->attack.actions.size(); i++){
                                    behindScenesCommands(creaturex->attack.actions[i]);
                                }
                            }
                            else{
                                cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
                            }
                        }
                        else if(getRoom(ob_name) != 0){
                            room * room = getRoom(ob_name);
                            if(room->status.compare(ob_status) == 0){
                                cout<<"You assault the "<<creaturex->name<<" with "<<itemx->name<<endl;
                                cout<<creaturex->attack.print<<endl;
                                for(int i=0; i < creaturex->attack.actions.size(); i++){
                                    behindScenesCommands(creaturex->attack.actions[i]);
                                }
                            }
                            else{
                                cout<<words[3]<<" is not activated to attack "<<words[1]<<endl;
                            }
                        }
                        else{
                            cout<<words[3]<<" can't attack "<<words[1]<<endl;
                        }
                    }

                }
                else{
                    cout<<words[3]<<" can't attack "<<words[1]<<endl;
                }

            }
        }
        else{
            cout<<"Invalid game command"<<endl;
            cout<<"Enter: attack (creature) with (item)"<<endl;
        }
    }
    else{
        cout<<"Invalid game command"<<endl;
        cout<<"Please enter: attack (creature) with (item)"<<endl;
    }
}

//BEHIND THE SCENES GAME COMMANDS

void addCommand(string command){
    std::vector <string> words;
    words = ParseInput(command, " ");
    if (words.size() == 4) {
        if (getItem(words[1]) != 0 && getContainer(words[3]) != 0) {
            item *item = getItem(words[1]);
            container *container = getContainer(words[3]);
            container->item.push_back(words[1]);
        } else if (getItem(words[1]) != 0 && getRoom(words[3]) != 0) {
            item *item = getItem(words[1]);
            room *room = getRoom(words[3]);
            room->items.push_back(words[1]);
        } else if (getContainer(words[1]) != 0 && getRoom(words[3]) != 0) {
            container *container = getContainer(words[1]);
            room *room = getRoom(words[3]);
            room->containers.push_back(words[1]);
        } else if (getCreature(words[1]) && getRoom(words[3]) != 0) {
            creature *creature = getCreature(words[1]);
            room *room = getRoom(words[3]);
            room->creatures.push_back(words[1]);
        }
    }
}

void delCommand(string command){
    std::vector <string> words;
    words = ParseInput(command, " ");
    if (words.size() == 2) {
        if (getItem(words[1]) != 0) {
            std::map<string, item>::iterator it;
            it = items.find(words[1]);
            items.erase(it);
        } else if (getContainer(words[1]) != 0) {
            std::map<string, container>::iterator it;
            it = containers.find(words[1]);
            containers.erase(it);
        } else if (getRoom(words[1]) != 0) {
            std::map<string, room>::iterator it;
            it = rooms.find(words[1]);
            rooms.erase(it);
        } else if (getCreature(words[1]) != 0) {
            std::map<string, creature>::iterator it;
            it = creatures.find(words[1]);
            creatures.erase(it);
        }
    }
}

void updateCommand(string command){
    std::vector <string> words;
    words = ParseInput(command, " ");
    if (words.size() == 4) {
        if (getItem(words[1]) != 0) {
            item *item = getItem(words[1]);
            item->status = words[3];
        }else if (getCreature(words[1]) != 0) {
            creature *creature = getCreature(words[1]);
            creature->status = words[3];
        }
        else if (getContainer(words[1]) != 0) {
            container *container = getContainer(words[1]);
            container->status = words[3];
        }
        else if (getRoom(words[1]) != 0) {
            room *room = getRoom(words[1]);
            room->status = words[3];
        }
    }
}


//GAME RUN THROUGH
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

    char in[100];
    //TESTING
   	room *start_room = getRoom("Entrance");
	cout<<start_room->description<<endl;
	c_room = start_room;

    while(!endgame)	{
		cout<<">";
		cin.getline(in, 100);
		getNew(c_room);
        if(TriggerFunc(0) == 0){//has command
            gameCommands(in);
            TriggerFunc(1);
        }
        else{
            checkTrigger(in);
            TriggerFunc(1);
        }
	}
}

void getNew(room *c_room)
{
	c_items.clear();
	c_items.insert(c_items.end(), c_room->items.begin(), c_room->items.end());

	c_containers.clear();
	c_containers.insert(c_containers.end(), c_room->containers.begin(), c_room->containers.end());
	for(int i=0; i < c_containers.size(); i++){
		container* c_container = getContainer(c_containers[i]);
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
		item * c_item = getItem(c_items[i]);
		c_triggers.insert(c_triggers.end(), c_item->trigger.begin(), c_item->trigger.end());
	}

	for(int i=0; i < c_containers.size(); i++){
		container * c_container = getContainer(c_containers[i]);
		c_triggers.insert(c_triggers.end(), c_container->trigger.begin(), c_container->trigger.end());
	}
	if(c_creatures.size()>0){
		for(int i=0; i < c_creatures.size(); i++){
			if(creatures.find(c_creatures[i]) != creatures.end()){
				creature * c_creature = getCreature(c_creatures[i]);
				c_triggers.insert(c_triggers.end(), c_creature->trigger.begin(), c_creature->trigger.end());
			}

		}
	}
}

//TRIGGER FUNCTIONS
void checkTrigger(string input){
    for(int i=0; i < c_triggers.size(); i++){
        triggers trigger = c_triggers[i];
        if(!trigger.command.empty()){//command exist
            if(trigger.command.compare(input) == 0){
                if(TriggerFunc(1) == 0){
                    cout<<trigger.print<<endl;
                    for(int i=0; i < trigger.action.size(); i++){
                        behindScenesCommands(trigger.action[i]);
                    }
                }
            }
            else{
                gameCommands(input);
            }

        }

    }
}

int TriggerFunc(int ind){
    int flag = 0;
    if(ind == 0){
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
    							else{
	    						    flag = 0;
    							}
    					    }
		    				else if(find(c_inventory.begin(), c_inventory.end(), trig.Cond[i].owner.object) == c_inventory.end()){
		    					if(trig.Cond[i].owner.has.compare("no") == 0){
		    						flag = 1;
		    					}
		    					else{
		    					    flag = 0;
		    					}
	    					}
	    				}
		    			else{
		    				if(getItem(trig.Cond[i].owner.object) != 0 && getContainer(trig.Cond[i].owner.owner) != 0){
		    					item *item = getItem(trig.Cond[i].owner.object);
			    				container *container = getContainer(trig.Cond[i].owner.owner);
		    					if(find(container->item.begin(), container->item.end(), trig.Cond[i].owner.object) != container->item.end() && trig.Cond[i].owner.has.compare("yes") == 0){
		    						flag = 1;
		    					}
		    					else if(find(container->item.begin(), container->item.end(), trig.Cond[i].owner.object) == container->item.end() && trig.Cond[i].owner.has.compare("no") == 0){
		    						flag = 1;
		    					}
                               else{
                                   flag = 0;
                               }
		    				}
		    				else if(getItem(trig.Cond[i].owner.object) != 0 && getRoom(trig.Cond[i].owner.owner) != 0){
		    					item *item = getItem(trig.Cond[i].owner.object);
		    					room *room = getRoom(trig.Cond[i].owner.owner);
			    				if(find(room->items.begin(), room->items.end(), trig.Cond[i].owner.object) != room->items.end() && trig.Cond[i].owner.has.compare("yes") == 0){
		    						flag = 1;
		    					}
                                else if(find(room->items.begin(), room->items.end(), trig.Cond[i].owner.object) == room->items.end() && trig.Cond[i].owner.has.compare("no") == 0){
                                    flag = 1;
			    				}
                                else{
                                    flag = 0;
                                }
					    	}
				    	}
			    	}
			    	else{
			    		if(getItem(trig.Cond[i].owner.object) != 0){
			    			item * item = getItem(trig.Cond[i].owner.object);
			    			if(item->status.compare(trig.Cond[i].status.status) == 0){
			    			    flag = 1;
			    			}
                            else{
                                flag = 0;
                           }
			    		}
                       else if(getRoom(trig.Cond[i].owner.object) != 0){
		    				room * room = getRoom(trig.Cond[i].owner.object);
		    				if(room->status.compare(trig.Cond[i].status.status) == 0){
		    					flag = 1;
		    				}
                            else{
                            flag = 0;
                            }
			    		}
			    		else if(getContainer(trig.Cond[i].owner.object) != 0){
			    			container * container = getContainer(trig.Cond[i].owner.object);
			    			if(container->status.compare(trig.Cond[i].status.status) == 0){
			    				flag = 1;
			    			}
                            else{
                                flag = 0;
                            }
			    		}
			    		else if(getCreature(trig.Cond[i].owner.object) != 0){
			    			creature * creature = getCreature(trig.Cond[i].owner.object);
			    			if(creature->status.compare(trig.Cond[i].status.status) == 0){
			    				flag = 1;
			    			}
                            else{
                                flag = 0;
                            }
					    }
				    }
			    }
		    }
	    }
    }
    else {

	    for(int i=0; i < c_triggers.size(); i++){
		    triggers trigger = c_triggers[i];
		    for(int i=0; i < trigger.Cond.size(); i++){
			    if(trigger.command.empty() && !trigger.tr){
				    if(trigger.Cond[i].owner.has.empty()){
					    if(getItem(trigger.Cond[i].owner.object) != 0){
						    item * item = getItem(trigger.Cond[i].owner.object);
						    if(item->status.compare(trigger.Cond[i].status.status) == 0){
							    flag = 1;
                                cout<<trigger.print<<endl;
							    if(trigger.type.compare("single") == 0){
								    item->status = "go";
							    }
						    }
                            else{
                                flag = 0;
                            }
					    }
                        else if(getRoom(trigger.Cond[i].owner.object) != 0){
						    room * room = getRoom(trigger.Cond[i].owner.object);
						    if(room->status.compare(trigger.Cond[i].status.status) == 0){
							    flag = 1;
							    if(trigger.type.compare("single") == 0){
								    room->status = "go";
							    }
						    }
                            else{
                                flag = 0;
                            }
					    }
					    else if(getContainer(trigger.Cond[i].owner.object) != 0){
						    container * container = getContainer(trigger.Cond[i].owner.object);
						    if(container->status.compare(trigger.Cond[i].status.status) == 0){
							    flag = 1;
						        if(trigger.type.compare("single") == 0){
								container->status = "go";
							    }
						    }
                            else{
                                flag = 0;
                            }
					    }
					    else if(getCreature(trigger.Cond[i].owner.object) != 0){
						    creature * creature = getCreature(trigger.Cond[i].owner.object);
						    if(creature->status.compare(trigger.Cond[i].status.status) == 0){
							    flag = 1;
							    if(trigger.type.compare("single") == 0){
								    creature->status = "go";
							    }
						    }
                            else{
                                flag = 0;
                            }
					    }

				    }
				    else{
					    if(trigger.Cond[i].owner.owner.compare("inventory") == 0){
						    if(find(c_inventory.begin(), c_inventory.end(), trigger.Cond[i].owner.object) != c_inventory.end()){
							    if(trigger.Cond[i].owner.has.compare("yes") == 0){
								    flag = 1;
                                cout<<trigger.print<<endl;
								    for(int i=0; i < trigger.action.size(); i++){
                                        behindScenesCommands(trigger.action[i]);
								    }
							    }
                                else{
                                    flag = 0;
                                }
						    }
						    else if(find(c_inventory.begin(), c_inventory.end(), trigger.Cond[i].owner.object) == c_inventory.end()){
							    if(trigger.Cond[i].owner.has.compare("no") == 0){
								    flag = 0;
                                    cout<<trigger.print<<endl;
								    for(int i=0; i < trigger.action.size(); i++){
                                        behindScenesCommands(trigger.action[i]);
								    }
							    }
                                else{
                                    flag = 1;
                                }
						    }
					    }
					    else{
						    if(getItem(trigger.Cond[i].owner.object) != 0 && getContainer(trigger.Cond[i].owner.owner) != 0){
							    item *item = getItem(trigger.Cond[i].owner.object);
							    container *container = getContainer(trigger.Cond[i].owner.owner);
							    if(find(container->item.begin(), container->item.end(), trigger.Cond[i].owner.object) != container->item.end() && trigger.Cond[i].owner.has.compare("yes") == 0){
								    flag = 1;
                                    cout<<trigger.print<<endl;
								    for(int i=0; i < trigger.action.size(); i++){
                                        behindScenesCommands(trigger.action[i]);
								    }
							    }
							    else if(find(container->item.begin(), container->item.end(), trigger.Cond[i].owner.object) == container->item.end() && trigger.Cond[i].owner.has.compare("no") == 0){
								    flag = 1;
                                    cout<<trigger.print<<endl;
								    for(int i=0; i < trigger.action.size(); i++){
                                        behindScenesCommands(trigger.action[i]);
								    }
							    }
                                else{
                                    flag = 0;
                                }
					        }
						    else if(getItem(trigger.Cond[i].owner.object) != 0 && getRoom(trigger.Cond[i].owner.owner) != 0){
							    item *item = getItem(trigger.Cond[i].owner.object);
							    room *room = getRoom(trigger.Cond[i].owner.owner);
							    if(find(room->items.begin(), room->items.end(), trigger.Cond[i].owner.object) != room->items.end() && trigger.Cond[i].owner.has.compare("yes") == 0){
								    flag = 1;
							    }
							    else if(find(room->items.begin(), room->items.end(), trigger.Cond[i].owner.object) == room->items.end() && trigger.Cond[i].owner.has.compare("no") == 0){
								    flag = 1;
							    }
                                else{
                                    flag = 0;
                                }
						    }
					    }
				    }
			    }
		    }
	    }
    }

    return flag;

}

//HIDDEN COMMAND FUNCTIONS

void behindScenesCommands(string command) {
    if (command.find("Add") != string::npos) {
        addCommand(command);
    }
    else if (command.find("Delete") != string::npos) {
        delCommand(command);
    }
    else if (command.find("Update") != string::npos) {
        updateCommand(command);
    }
    else if (command.compare("Game Over") == 0) {
        cout << "Victory!" << endl;
        endgame = 1;
    }
    else {
        gameCommands(command);
    }
}


//GAME COMMAND FUNCTIONS

void gameCommands(string input){
    if(input.compare("n") == 0 || input.compare("s") == 0 || input.compare("w") == 0 || input.compare("e") == 0){
        traverseRoom(input);
    }
    else if(input.compare("i") == 0){
        displayInventory();
    }
    else if(input.find("take") != string::npos){
        takeItem(input);
    }
    else if(input.find("drop") != string::npos){
        dropItem(input);
    }
    else if(input.find("put") != string::npos){
        putItem(input);
    }
    else if(input.find("open exit") != string::npos){
        openExit(input);
    }
    else if(input.find("open") != string::npos){
        openContainer(input);
    }
    else if(input.find("read") != string::npos){
        readItem(input);
    }
    else if(input.find("turn on") != string::npos){
        turnOnItem(input);
    }
    else if(input.find("attack") != string::npos){
        attackCreature(input);
    }
    else{
        cout<<"Invalid game command"<<endl;
    }
}
