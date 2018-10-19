#pragma once
#include <iostream>
#include "rapidxml.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h> 

#ifndef __TRIGGERS_H__
#define __TRIGGERS_H__

using namespace std;

class Triggers 
{
	
	struct Condition {
		Owner owner;
		Status status;
		
	};
	struct Status {
		Status status;
		string object;
	};
	
	struct Owner {
		string object;
		string has;
		Owner owner;
	};
public:
	vector <Condition> Cond;
	string command;
	string type; //single or permanent --> where does this information come from? XML?
	void print




}



#endif