//
//  parser.cpp
//  Project2
//
//  Created by Michael Bird on 7/10/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "parser.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


parser::parser() {}

parser::~parser() {}

void parser::parse(vector<Token> tokenlist_) {
    
    tokenlist = tokenlist_;
    
    //get_token();
    //current_token_value = tokenlist[index].get_token_value();
    //current_token_type = tokenlist[index].get_token_type();
    
    
    try {
        
        update_token();
        match("SCHEMES");
        match("COLON");
        schemelist();
        match("FACTS");
        match("COLON");
        update_token();
        factlist();
        match("RULES");
        match("COLON");
        rulelist();
        match("QUERIES");
        match("COLON");
        querylist();
        match("ENDFILE");
        
        if(index > tokenlist.size()) {
            error();
        }
        //cout << D.toString() << endl;
        
        //outputFile << D.toString();

    }
    catch (string e){
        //outputFile << "Failure!" <<endl << "  " << e << endl;
        cout << "Failure!" <<endl << "  " << e << endl;
    }
    //outputFile.close();
}

DataLog parser::get_datalog_object() {
    return D;
}

void parser::get_token_type() {
    current_token_type = tokenlist[index].get_token_type();
}
void parser::get_token_value() {
    current_token_value = tokenlist[index].get_token_value();
}
void parser::get_token_line() {
    current_token_line = tokenlist[index].get_token_line();
}
void parser::update_token() {
    get_token_type();
    get_token_value();
    get_token_line();
}

void parser::match( string match_token) {
    
    if(index > (tokenlist.size())) {
        //return;
        error();
    }
    update_token();
    if(match_token == current_token_type) {
        index++;
    }
    else error();
}

void parser::error() {
    stringstream ss;
    ss << "(" << current_token_type << ",\"" << current_token_value << "\"," << current_token_line << ")";
    string error = ss.str();
    throw error;
}

void parser::predicatelist() {
    predicate();
    R.add_rule(P);
    if (current_token_type == "COMMA") {
        match("COMMA");
        predicatelist();
    }
}
void parser::predicate() {
    match("ID");
    P.clear();
        P.add_id(current_token_value);
    update_token();
    match("LEFT_PAREN");
    parameterlist();
    match("RIGHT_PAREN");
    update_token();
    //add predicate to datalog program
}
void parser::parameterlist() {
   // update_token();
    parameter();
    update_token();
    if(current_token_type == "COMMA"){
        match("COMMA");
        //P.add_param(current_token_value);
        parameterlist();
    }
    /*
    if(current_token_type == "STRING"){
        match("STRING");
        parameterlist();
    }*/
}
void parser::parameter() {
    update_token();
    if (current_token_type == "ID") {
        match("ID");
        P.add_param(current_token_value);
        
    }
    else if (current_token_type == "STRING") {
        match("STRING");
        P.add_param("'"+current_token_value+"'");
        D.add_to_domains(current_token_value);
    }
    else
        error();
        //P.add_param(get_token_value());
        //P.add_param("'");
        //Par.add_param(get_token_value());
    
    //else
      //  match("ERROR");
   
}
void parser::schemelist() {
    scheme();
    D.add_to_schemes(P);
    //get_token_type();
    if(current_token_type == "ID")
        schemelist();
}
void parser::scheme() {
    predicate();
}
void parser::factlist() {
   if (current_token_type != "RULES") {
    fact();
    factlist();
   }
}
void parser::fact() {
    update_token();
    
        predicate();
        match("PERIOD");
        D.add_to_facts(P);
        update_token();
    }
void parser::rulelist() {
    update_token();
    if(current_token_type != "QUERIES") {
        rule();
        match("PERIOD");
        D.add_to_rules(R);
        update_token();
        if(current_token_type == "ID")
            rulelist();
        else if(current_token_type == "COLON_DASH") {
            match("COLON_DASH");
            rulelist();
        }
        else if(current_token_type == "COMMA") {
            match("COMMA");
            rulelist();
        }
        else {}
    }
}
void parser::rule() {
    
    R.clear();
    predicate();
    R.add_head(P);
    match("COLON_DASH");
    predicatelist();
}
void parser::querylist() {
    if(index < tokenlist.size()) {
        query();
        D.add_to_queries(P);
        update_token();
        if(current_token_type == "ID")
            querylist();
        }
    }
void parser::query() {
    predicate();
    match("Q_MARK");
}