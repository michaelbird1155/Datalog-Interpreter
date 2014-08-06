//
//  Interpreter.cpp
//  Project3
//
//  Created by Michael Bird on 7/21/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Interpreter.h"

Interpreter::Interpreter() {};
Interpreter::~Interpreter() {};

void Interpreter::interpret(DataLog obj_, char* filename) {
    
    ofstream outputFile;
    outputFile.open(filename);
    
    DL_obj = obj_;
    queries_ = DL_obj.get_queries();
    rules_ = DL_obj.get_rules();
    
    add_relation();
    
    Relations_ = DAT.get_relations();
    
    convergance();

    eval_query();
    
    outputFile << ss.str();
    
    outputFile.close();
    
}

void Interpreter::add_relation() { // add a relation
    
    schemes_ = DL_obj.get_schemes();
    
    for (auto scheme: schemes_) {
        
        Scheme SC;
        
        for (auto parameter: scheme.get_parameters()) {
           
            for (auto value: parameter) {
               
               stringstream ss; ss << value;
               SC.push_back(ss.str());
               
            }
        }
        
        vector<Tuple> tuplevec = add_facts(scheme.get_id());
        DAT.create_new_relation(scheme.get_id(), SC, tuplevec);
        tuple_clear();
        
    }
}

vector<Tuple> Interpreter::add_facts(string id) {
    
    facts_ = DL_obj.get_facts(); // checks for tuples in the relation
    
    for (auto fact: facts_) {
        
        Tuple TU;
        
        if(id == fact.get_id()) {
            
            for (auto parameter: fact.get_parameters()) {
                TU.push_back(parameter);
                
            }
            
        tuple_vector.push_back(TU);
        
        }
    }
    
    return tuple_vector;
    
}

void Interpreter::tuple_clear() {
    
    tuple_vector.clear();

}

void Interpreter::eval_query() {
    

    for (auto query: queries_) {
        Relation RelTemp;
        RelTemp = Relations_[query.get_id()];
        
 
        ss << query.get_id() << "(";
        
        vector<string> parameters = query.get_parameters();

        for (unsigned int j=0; j < parameters.size(); j++) {
            
            ss << parameters[j];
            
            if (is_string(parameters[j]) == true) {
             
                RelTemp = RelTemp.select(j,parameters[j]);
                
            }
            else {
                
                for  (unsigned int k = (j+1); k < parameters.size(); k++) {
                    
                    if (parameters[k] == parameters[j]) {
                        RelTemp = RelTemp.select(k, j);
                    }
                }
                variable_pos.push_back(j);
                variable_name.push_back(parameters[j]);
            }
            if (j < (parameters.size()-1)) {
                 ss << ",";
            }
        }
        ss << ")?";
        set<Tuple> tupleset = RelTemp.get_tuples();
        ss << yes_no(tupleset);
        
        if(variable_pos.size() > 0)
            ss << RelTemp.project(variable_name, variable_pos);
        //cout << RelTemp.project(variable_name, variable_pos);
        //clear vector tables
        variable_pos.clear();
        variable_name.clear();
    }
}

void Interpreter::eval_rule() {
    
    for (auto rule_row: rules_) {
        
        Relation RelTemp;
        
        Predicate rule_head_predicate = rule_row.get_rule_head();
        vector<string> rule_head_scheme = rule_head_predicate.get_parameters();
        string rule_id = rule_head_predicate.get_id();
        
        vector<Predicate> rule_body = rule_row.get_rule_body();
        
        vector<Relation> all_relations;
        for (unsigned int i=0; i < rule_body.size(); i++) {
            
            Relation relpred1;
            Scheme scheme1;
            vector<string> predscheme = rule_body[i].get_parameters();
            for (auto param : predscheme) {
                scheme1.push_back(param);
            }
            relpred1.add_scheme(scheme1);
            set<Tuple> tupleset = DAT.get_tuples(rule_body[i].get_id());
            for (auto tuple : tupleset) {
                relpred1.add_tuple(tuple);
            }
            for (unsigned int i = 0; i < scheme1.size(); i++) {
                if (is_string(scheme1[i]) == true) {
                    relpred1 = relpred1.select(i,scheme1[i]);
                }
            }
            all_relations.push_back(relpred1);
        }
        
        for (unsigned int i = 0; i < rule_body .size(); i++) {
            vector<string> scheme = rule_body[i].get_parameters();
        }

        //join relations
        Relation r;

        r = bigjoin(r, all_relations);
        
        // find where to project on the new relation
        
        vector<string> scheme = r.get_scheme();
        
        pos = find_project_spots(scheme, rule_head_scheme);
        
        r = r.rule_project(pos, r);
        
        Relation relmap = Relations_[rule_id];
        
        r = r.unioning(r, relmap);
        DAT.update_map(rule_id,r);
        Relations_ = DAT.get_relations();
        pos.clear();
    }
    
}

vector<int> Interpreter::find_project_spots(vector<string> scheme, vector<string> rule_head_scheme) {
    
    for (unsigned int i = 0; i < rule_head_scheme.size(); i++) {
        for (unsigned int j = 0; j < scheme.size(); j++) {
            if (scheme[j] == rule_head_scheme[i]) {
                pos.push_back(j);
                //break;
            }
        }
    }
    return pos;
}

string Interpreter::yes_no(set<Tuple> set) {
    stringstream ss;
    if(set.size() >= 1)
        ss << " Yes(" << set.size() <<")\n";
    else
        ss << " No\n";

    return ss.str();
}

bool Interpreter::is_string(string param) {
    
    bool bvalue = false;
     
        if(isalpha(param.at(0)))
            bvalue = false;
        else
            bvalue = true;
    return bvalue;
}

void Interpreter::convergance() {
    int count = 0;
    bool size = true;
    
    while (size) {
        
        int before = DAT.get_tuple_size();
        eval_rule();
        count++;
        
        int after = DAT.get_tuple_size();
        if (before == after) {
            size = false;
        }
    }
    ss << "Converged after " << count << " passes through the Rules." << endl;
}
Relation Interpreter::bigjoin(Relation R, vector<Relation> all_relations) {
    
    R = all_relations[0];
    for (unsigned int i = 1; i < all_relations.size(); i++) {
        
        R = R.join(R, all_relations[i]);
        
    }
    
    return R;
}