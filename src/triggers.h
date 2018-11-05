#pragma once

#ifndef __TRIGGERS_H__
#define __TRIGGERS_H__

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace rapidxml;

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
		bool tr;
		string type;
		string command;
		string print;
		vector <string> action;
		vector <Condition> Cond;

		//Functions related to the item
		triggers();
		virtual ~triggers();
		triggers(xml_node<> *);
};

#endif