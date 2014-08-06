//
//  Database.h
//  Project2
//
//  Created by Michael Bird on 7/21/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__Database__
#define __Project2__Database__

#include <iostream>
#include <map>
#include "Relation.h"



using namespace std;

class Database {
    
public:
    
    Database();
    ~Database();
    
    void create_new_relation(string name, Scheme, vector<Tuple> tuplesvec);
    map<string, Relation> get_relations();
    set<Tuple> get_tuples(string key);
    void update_map(string id, Relation R);
    int get_tuple_size();
    
private:
    
    map<string, Relation> Relations;

    
    // key = name
    // val = relation
    
};


#endif /* defined(__Project2__Database__) */