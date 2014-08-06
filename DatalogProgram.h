//
//  DatalogProgram.h
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__DatalogProgram__
#define __Project2__DatalogProgram__

#include <iostream>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <set>

class DataLog {
    
public:
    
    DataLog();
    ~DataLog();
    
    void add_to_schemes(Predicate &schemes);
    void add_to_facts(Predicate &facts);
    void add_to_rules(Rule &rules);
    void add_to_queries(Predicate &queries);
    void add_to_domains(string domain);
    string toString();
    
    vector<Predicate> get_schemes();
    vector<Predicate> get_facts();
    vector<Predicate> get_queries();
    vector<Rule> get_rules();
    
    
    
private:
    
    vector<Predicate> schemes_vector;
    vector<Predicate> facts_vector;
    vector<Predicate> queries_vector;
    vector<Rule> rules_vector;
    set<string> domains_list;

};

#endif /* defined(__Project2__DatalogProgram__) */
