#include "functions.h"


room* getRoom(string name, map <string, room> rooms) {
	map <string, room>::iterator r;
	r = rooms.find(name);
	if(r != rooms.end()){
		return &(r->second);
	}
	else{
		return 0;
	}
}


container* getContainer(string name,map <string, container> containers){
	map <string, container>::iterator c;
	c = containers.find(name);
	if(c != containers.end()){
		return &(c->second);
	}
	else{
		return 0;
	}
}

item* getItem(string name,map <string, item> items){
	map <string, item>::iterator i;
	i = items.find(name);
	if(i != items.end()){
		return &(i->second);
	}
	else{
		return 0;
	}
}

creature* getCreature(string name,map <string, creature> creatures){
	map <string, creature>::iterator c;
	c = creatures.find(name);
	if(c != creatures.end()){
		return &(c->second);
	}
	else{
		return 0;
	}
}

