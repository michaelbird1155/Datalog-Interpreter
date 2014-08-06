//
//  Relation.h
//  Project2
//
//  Created by Michael Bird on 7/21/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__Relation__
#define __Project2__Relation__

#include <iostream>
#include <set>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include "Tuple.h"
#include "Scheme.h"
#include "Predicate.h"
#include <map>

using namespace std;

class Relation {
    
public:
    
    Relation();
    ~Relation();
    
    void add_tuple(vector<Tuple> tuple);
    void add_tuple(Tuple tuple);
    void add_scheme(Scheme);
    
    set<Tuple> get_tuples();
    Scheme get_scheme();
    Scheme join_scheme(Scheme S1, Scheme S2);
    Tuple join_tuple(Tuple T1, Tuple T2, vector<int> pos);
    vector<int> get_no_join_pos(Scheme S1, Scheme S2);
    
    Relation select(int pos, string value);
    Relation select(int pos1, int pos2);
    string project(vector<string> name, vector<int> pos);
    
    Relation rule_project(vector<int> pos, Relation r);
    Relation unioning(Relation R1, Relation R2);
    
    void rename();
    Relation join(Relation R1, Relation R2);
    bool can_join(Tuple T1, Tuple T2, Scheme S1, Scheme S2);
    

   
    
private:
    
    vector<Predicate> queries_;
    Scheme scheme;
    set<Tuple> tuples;
    
};



#endif /* defined(__Project2__Relation__) */