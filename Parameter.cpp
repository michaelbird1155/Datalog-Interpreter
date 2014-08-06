//
//  Parameter.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Parameter.h"
#include <sstream>

Parameter::Parameter() {}
Parameter::~Parameter() {}

void Parameter::add_param(string param) {
    domains.push_back(param);
}
vector<string> Parameter::get_values() {
    return domains;
}

string Parameter::toString() {
    stringstream ss;
    for(auto domain : domains)
        ss << domain;
   // cout << ss.str();
    return ss.str();
}
void Parameter::clear() {
    domains.clear();
}