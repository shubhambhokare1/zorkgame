//
// Created by Shubham Bhokare on 10/15/18.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "room.h"
#include "item.h"
#include "container.h"
#include "creature.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"


using namespace std;
using namespace rapidxml;

int main(int argc, char * argv[]) {
	
	if (argc != 1 ) { //error checking for innappropriate inputs or commands.  only xml file should be an input
		cout << "Error! Enter: a.out filename.xml" << endl;
		return 1;
		}


    //file<> xmlFile(argv[1]); // Default template is char
    //xml_document<> doc;
    //doc.parse<0>(xmlFile.data()); //default parse flag?

	//xml_node<> *node = doc.first_node(); //map node (root)


}