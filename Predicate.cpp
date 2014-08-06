//
//  Predicate.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//
#include <sstream>

#include "Predicate.h"

Predicate::Predicate() {}

Predicate::~Predicate() {}

void Predicate::add_id(string _id) {
    id = _id;
}
string Predicate::get_id() {
    return id;
}
vector<string> Predicate::get_parameters() {
    return Par.get_values();
}

void Predicate::add_param(string param) {
    Par.add_param(param);
}

string Predicate::toString() {
    stringstream ss;
    ss << id << "(";
    ss << Par.toString();
    for(auto param : parameter)
        ss << "fdsa";
    ss << ")";
    return ss.str();
}

void Predicate::clear() {
    id = "";
    Par.clear();
}