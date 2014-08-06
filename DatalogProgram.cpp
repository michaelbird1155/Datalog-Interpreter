//
//  DatalogProgram.cpp
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "DatalogProgram.h"
#include <sstream>


DataLog::DataLog() {};

DataLog::~DataLog() {};

void DataLog::add_to_schemes(Predicate &schemes) {
    schemes_vector.push_back(schemes);
}
void DataLog::add_to_facts(Predicate &facts) {
    facts_vector.push_back(facts);
}
void DataLog::add_to_rules(Rule &rules) {
    rules_vector.push_back(rules);
}
void DataLog::add_to_queries(Predicate &queries) {
    queries_vector.push_back(queries);
}
void DataLog::add_to_domains(string domain) {
    domains_list.insert(domain);
}

// Geters for project 3

vector<Predicate> DataLog::get_schemes() {
    return schemes_vector;
}
vector<Predicate> DataLog::get_facts() {
    return facts_vector;
}
vector<Predicate> DataLog::get_queries() {
    return queries_vector;
}
vector<Rule> DataLog::get_rules() {
    return rules_vector;
}



string DataLog::toString() {
    stringstream final;
    final << "Success!" << endl;
    
    final << "Schemes(";
    final << schemes_vector.size() << "):" << endl;
    for(auto schemes : schemes_vector)
        final << "  " << schemes.toString() <<endl;
    
    final << "Facts(";
    final << facts_vector.size() << "):" << endl;
    for(auto facts : facts_vector)
        final << "  " << facts.toString() << endl;
    
    final << "Rules(";
    final << rules_vector.size() << "):" << endl;
    for(auto rules : rules_vector)
        final << "  " << rules.toString()<< endl;
    
    final << "Queries(";
    final << queries_vector.size() << "):" << endl;
    //queries_vector.pop_back();
    for(auto queries : queries_vector)
        final << "  " << queries.toString() <<endl;
    
    final << "Domain(";
    final << domains_list.size() << "):" << endl;
    for(auto domain : domains_list)
        final << "  '" << domain << "'" << endl;
    
    return final.str();
}

