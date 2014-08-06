//
//  Rule.h
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__Rule__
#define __Project2__Rule__

#include <iostream>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule{
    
public:
    
    Rule();
    ~Rule();
    void add_rule(Predicate rule_pred);
    string toString();
    void add_id(string id);
    string id;
    void clear();
    void add_head(Predicate head);
    string head;
    vector<Predicate> get_rule_body();
    Predicate get_rule_head();
    
private:
    
    Predicate rule_head;
    vector<Predicate> rule_body;

};

#endif /* defined(__Project2__Rule__) */
