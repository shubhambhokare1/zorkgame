#pragma once
#include <iostream>
#include "rapidxml.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h> 

#ifndef __TRIGGERS_H__
#define __TRIGGERS_H__

using namespace std;

//STRUCTS FOR condition, status and owner
struct Status {
	string status;
	string object;
};

struct Owner {
	string object;
	string has;
	string owner;
};

struct Condition {
	Owner owner;
	Status status;
};



class triggers
{

	public:
		vector <Condition> Cond;
		string command;
		string type;
		string print;

};

#endif