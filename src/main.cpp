//
// Created by Shubham Bhokare on 10/15/18.
//

#include "room.h"
#include "item.h"
#include "container.h"
#include "creature.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>

using namespace std;
using namespace rapidxml;

int main(int argc, char * argv[]) {
    rapidxml::file<> xmlFile("input/*.xml"); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<>(xmlFile.data());

}