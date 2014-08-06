//
//  Token.cpp
//  Project2
//
//  Created by Michael Bird on 7/16/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "Token.h"

Token::Token() {};

Token::Token(string type_, string value_, int line_number_) {

    type = type_;
    value = value_;
    line = line_number_;

};

Token::~Token() {};

void Token::set_token_type(string type_){
    type = type_;
}
void Token::set_token_value(string value_){
    value = value_;
}
void Token::set_token_line(int line_){
    line = line_;
}

string Token::get_token_type() {
    return type;
}
string Token::get_token_value() {
    return value;
}
int Token::get_token_line() {
    return line;
}