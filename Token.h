//
//  Token.h
//  Project2
//
//  Created by Michael Bird on 7/16/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__Token__
#define __Project2__Token__

#include <iostream>
#include <vector>

using namespace std;

class Token {
    
public:
    
    Token();
    Token(string type, string value, int line_number);
    ~Token();
    
    void set_token_type(string type_);
    void set_token_value(string value_);
    void set_token_line(int line_);
    
    string get_token_type();
    string get_token_value();
    int get_token_line();
    
    string toString() {
        return "(" + type + ",'" + value + "'," + to_string(line) + ")";
    }
    
private:

    string type;
    string value;
    int line;
    
    
};


#endif /* defined(__Project2__Token__) */
