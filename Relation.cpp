//
//  Relation.cpp
//  Project2
//
//  Created by Michael Bird on 7/21/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Relation.h"

Relation::Relation() {}
Relation::~Relation() {}

void Relation::add_tuple(vector<Tuple> tuple) {
    for(auto tuple_item : tuple) {
        tuples.insert(tuple_item);
    }
}
void Relation::add_tuple(Tuple tuple) {
    tuples.insert(tuple);
}
void Relation::add_scheme(Scheme scheme_in) {
    
    scheme = scheme_in;
    
}
Relation Relation::select(int pos, string value) {
    
    Relation R;
    for (auto tuple : tuples ) {
       if(tuple[pos] == value ){
           R.add_tuple(tuple);
           R.add_scheme(scheme);
        }
    }
    
    return  R;
}

Relation Relation::select(int pos1, int pos2) {
    Relation R;
    for (auto tuple : tuples ) {
        if(tuple[pos1] == tuple[pos2] ){
            R.add_tuple(tuple);
        }
    }
    R.add_scheme(scheme);
    return  R;
    
}
string Relation::project(vector<string> name, vector<int> pos) {
    
    stringstream ss;
    
    //if(!tuples.empty())
    for (auto tuple : tuples) {
        for (unsigned int i = 0; i < name.size(); i++) {
            if(i == 0){
                ss << "  "<<name[i] << "=" << tuple[pos[i]];
            }
            else { 
                ss << ", "<<name[i] << "=" << tuple[pos[i]];
            }
        }
        ss << "\n";
    }
    return ss.str();
}

set<Tuple> Relation::get_tuples() {
    return tuples;
}

Scheme Relation::get_scheme() {
    return scheme;
}

Relation Relation::join(Relation R1, Relation R2) {
    
    
    Scheme S1 = R1.get_scheme();
    Scheme S2 = R2.get_scheme();
    vector<int> pos = get_no_join_pos(S1,S2);
    Scheme SC = join_scheme(S1, S2);

    
    
    Relation R;
    R.add_scheme(SC);
    
    
    set<Tuple> TS1 = R1.get_tuples();
    set<Tuple> TS2 = R2.get_tuples();
    
    for (auto tuple1 : TS1) {
        for (auto tuple2 : TS2) {
            if ((can_join(tuple1, tuple2, S1, S2) == true)) {
                Tuple t = R.join_tuple(tuple1, tuple2, pos);
                R.add_tuple(t);
            }
        }
    }
        /*make the scheme s for the result relation
     (combine r1's scheme with r2's scheme)
     
     make a new empty relation r using scheme s
     
     for each tuple t1 in r1
     for each tuple t2 in r2
     
     if t1 and t2 can join
     join t1 and t2 to make tuple t
     add tuple t to relation r
     end if
     
     end for
     end for*/
    
    return R;
    
}

Relation Relation::rule_project(vector<int> pos, Relation R) {
    
    Relation rtemp;
    
    for (auto tuple : R.get_tuples()) {
        Tuple ttemp;
        for (unsigned int i = 0; i < pos.size(); i++) {
            ttemp.push_back(tuple[pos[i]]);
        }
        rtemp.add_tuple(ttemp);
    }
    rtemp.add_scheme(scheme);
    return rtemp;
}


Scheme Relation::join_scheme(Scheme S1, Scheme S2) {
    
    Scheme tempSC;
    
    for (unsigned int i = 0; i < S1.size(); i++) {
        for (unsigned int y = 0; y < S2.size(); y++) {
            if (S1[i] == S2[y]) {
                S2.erase(remove(S2.begin(), S2.end(), S1[i]));
            }
        }
        tempSC.push_back(S1[i]);
    }
    for (auto scheme : S2) {
        tempSC.push_back(scheme);
    }
    return tempSC;
}

vector<int> Relation::get_no_join_pos(Scheme S1, Scheme S2) {
    vector<int> pos;
    for (unsigned int i = 0; i < S1.size(); i++) {
        for (unsigned int y = 0; y < S2.size(); y++) {
            if (S1[i] == S2[y]) {
                pos.push_back(y);
            }
        }
    }
    return pos;
}

bool Relation::can_join(Tuple T1, Tuple T2, Scheme S1, Scheme S2) {
    
    bool bvalue = true;
    
    for (unsigned int i = 0; i < S1.size(); i++) {
        string value1 = T1[i];
        string name1 = S1[i];
        for (unsigned int y = 0; y < S2.size(); y++) {
            string value2 = T2[y];
            string name2 = S2[y];
            if ((name1 == name2) && (value1 != value2)) {
                bvalue = false;
            }
        }
    }
    
    /*
     
     value1 in tuple1
     foreach name1 in scheme2
     value2 in tupe2
     foreach name2 in scheme2
     if(name1 == name2 && value1 != value2)
     return false (not joinable)
     }
     return true (joinable)
     */
    
    
    return bvalue;
}

Tuple Relation::join_tuple(Tuple T1, Tuple T2, vector<int> pos) {
    
    Tuple tupleTemp;
    
    for (auto param : T1) {
        tupleTemp.push_back(param);
    }
    
    for (unsigned int i = 0; i < T2.size(); i++) {
        unsigned int count = 0;
        for (unsigned spot : pos) {
            if (spot != i) {
                count++;
            }
        }
        if (count == pos.size()) {
            tupleTemp.push_back(T2[i]);
        }
        //T2.erase(remove(T2.begin(), T2.end(), T2[spot]));
    }
    
    return tupleTemp;
}

Relation Relation::unioning(Relation R1, Relation R2) {
    
    set<Tuple> tupleset1 = R1.get_tuples();
    set<Tuple> tupleset2 = R2.get_tuples();
    
    for (auto tuple : tupleset2) {
       R1.add_tuple(tuple);
    }
    return R1;
}

