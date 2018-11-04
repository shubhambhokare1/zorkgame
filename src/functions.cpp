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

void traverseRoom(string input,room *c_room,map <string, room> rooms)	{
	
	if(input.compare("n") == 0 || input.compare("s") == 0 || input.compare("w") == 0 || input.compare("e") == 0)	{	
		int dflag = 0;
		vector <Border> bord = c_room->borders;
		if(input == "n"){
			for(int i=0; i < bord.size(); i++){
				if(bord[i].direction == "north"){
					c_room = getRoom(bord[i].name,rooms);
					dflag = 1;
					cout<<c_room->description<<endl;
				}
			}
			if(dflag == 0){
				cout<<"Can't go that way!"<<endl;
			}
			cout<<"Your current room is "<<c_room->name<<endl;
		}
		else if(input == "s"){
			for(int i=0; i < bord.size(); i++){
				if(bord[i].direction == "south"){
					c_room = getRoom(bord[i].name,rooms);
					dflag = 1;
					cout<<c_room->description<<endl;
				}
			}
			if(dflag == 0){
				cout<<"Can't go that way!"<<endl;
			}
			cout<<"Your current room is "<<c_room->name<<endl;
		}
		else if(input == "e"){
			for(int i=0; i < bord.size(); i++){
				if(bord[i].direction == "east"){
					c_room = getRoom(bord[i].name,rooms);
					dflag = 1;
					cout<<c_room->description<<endl;
				}
			}
			if(dflag == 0){
				cout<<"Can't go that way!"<<endl;
			}
			cout<<"Your current room is "<<c_room->name<<endl;
		}
		else if(input == "w"){
			for(int i=0; i < bord.size(); i++){
				if(bord[i].direction == "west"){
					c_room = getRoom(bord[i].name,rooms);
					dflag = 1;
					cout<<c_room->description<<endl;
				}
			}
			if(dflag == 0){
				cout<<"Can't go that way!"<<endl;
			}
			cout<<"Your current room is "<<c_room->name<<endl;
		}
				
	}
	else{
		//dealItems
	}

}