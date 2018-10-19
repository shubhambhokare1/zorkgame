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
		string owner;
		Status status;
	};
	struct Status {
		
	};
	
	struct Owner {
		
	};
public:
	vector <Condition> Cond;
	string command;
	string type; //single or permanent --> where does this information come from? XML?
	void print
}



#endif