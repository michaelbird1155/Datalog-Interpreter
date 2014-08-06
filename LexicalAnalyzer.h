
//
//  LexicalAnalyzer.h
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.

#ifndef __Project2__LexicalAnalyzer__
#define __Project2__LexicalAnalyzer__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Token.h"


using namespace std;

//  list of enum types

enum {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, SEMI_COLON, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, DASH, QUOTATION, COMMENT, BACK_SLASH, DIGIT, UNDERSCORE, TAB, LETTER, INTEGER, ERROR, SPACE, STOP, PLUS_CODE, EPSILON};

//  the class and its public and private methods and values

class LexAn  
{

public:
    
	LexAn();
    ~LexAn();
    string input;
    string line;
    int char_class;
    char next_char;
    int token_type;
	string lexeme;
   // string tokenizer(int token);
    string get_token_value();
    string get_token_type();
    int get_line_number();
    int get_token();
    string lex();
    int rule1();
    int rule2();
    int rule3();
	void new_input(string in);
	//void toString();
    void push_token();
    int linenumber = 0;
    vector<Token> lex(char* filename);

private:
	
    void add_char();
	void get_char();
    vector<Token> tokenlist;


};
#endif /* defined(__Project2__LexicalAnalyzer__) */