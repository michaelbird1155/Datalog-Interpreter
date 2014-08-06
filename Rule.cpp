//
//  Rule.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Rule.h"
#include <sstream>


Rule::Rule() {};
Rule::~Rule() {};

void Rule::add_head(Predicate head) {    
    rule_head = head;
}

void Rule::add_rule(Predicate rule_pred) {
    rule_body.push_back(rule_pred);
}

Predicate Rule::get_rule_head() {
    return rule_head;
}

string Rule::toString() {
    stringstream ss;
    ss << rule_head.toString() << " :- ";
    for(auto rule_pred: rule_body)
        ss << rule_pred.toString() << ",";
    string rule = ss.str();
    rule.pop_back(); // removes the last comma

    return rule;
}
void Rule::clear() {
    rule_head.clear();
    rule_body.clear();
}

vector<Predicate> Rule::get_rule_body() {
    return rule_body;
}