

//
//  LexicalAnalyzer.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include "LexicalAnalyzer.h"

using namespace std;

//  initialize the constructor
LexAn::LexAn(){};
LexAn::~LexAn(){};

vector<Token> LexAn::lex(char* filename) {
   
    ifstream inputFile;
    inputFile.open(filename);

    
    while(getline(inputFile, line)) {
        
        new_input(line);
        
        linenumber++;
        
        while(char_class != STOP) {
            
            get_token();
            
            if (token_type == STOP )
               // push_token();
                break; //do not show any end of line (STOP) tokens
            
            push_token();
            //cout << tokenlist.back().toString() << endl;
           // get_token();
        }
    }
    tokenlist.push_back(Token("ENDFILE","Endfile",linenumber++));
    inputFile.close();
    return tokenlist;
}

//  deconstruct the constructor



// gets the new input char

void LexAn::new_input(string in)
{
	input=line;
	get_char();
    
}

// gets the input char from new_input() and assigns its a character class

void LexAn::get_char()
{
	if (input.size()>0) {
        next_char = input[0];
        input.erase(0,1);
	}
	else
        next_char = '\n';
    
	char_class = ERROR;
    
    switch (next_char) {
        case 65 ... 90:
            char_class = LETTER;
            break;
        case 96 ... 123:
            char_class = LETTER;
            break;
        case 48 ... 57:
            char_class = DIGIT;
            break;
        case ' ':
            char_class = SPACE;
            break;
        case '\n':
            char_class = STOP;
            break;
        case '+':
            char_class = PLUS_CODE;
            break;
        case '?':
            char_class = Q_MARK;
            break;
        case ',':
            char_class = COMMA;
            break;
        case '.':
            char_class = PERIOD;
            break;
        case '(':
            char_class = LEFT_PAREN;
            break;
        case ')':
            char_class = RIGHT_PAREN;
            break;
        case ':':
            char_class = COLON;
            break;
        case ';':
            char_class = SEMI_COLON;
            break;
        case '-':
            char_class = DASH;
            break;
        case '#':
            char_class = STOP;
            break;
        case 39:
            char_class = QUOTATION;
            break;
        case 92:
            char_class = BACK_SLASH;
            break;
        case '_':
            char_class = UNDERSCORE;
            break;
        case 9:
            char_class = SPACE;
            break;
        default:
            char_class = ERROR;
            break;
    }
}

//  adds the character to the lexeme string

void LexAn::add_char()
{
	lexeme+=next_char;
}

//
int LexAn::rule1() {
    
    while (char_class == LETTER || char_class == DIGIT) {
        add_char();
        get_char();
    }
    
    if (lexeme == "Queries") {
        token_type = QUERIES;
        return token_type;
    }
    if (lexeme == "Schemes") {
        token_type = SCHEMES;
        return token_type;
    }
    if (lexeme == "Rules") {
        token_type = RULES;
        return token_type;
    }
    if (lexeme == "Facts") {
        token_type = FACTS;
        return token_type;
    }
    else {
        token_type = ID;
        return token_type;
    }
}

int LexAn::rule2() {
    
    while (char_class != QUOTATION && char_class != STOP) {
        add_char();
        get_char();
    }
    add_char();
    get_char();
    lexeme.erase( 0, 1 ); // erase the first character
    if (lexeme.back() == 39) {
        lexeme.erase( lexeme.size() - 1 ); // erase the last character
        token_type = STRING;
        return token_type;
    }
    else
        return ERROR;
} 

int LexAn::rule3() {
    
    while (char_class == LETTER || char_class == DASH) {
        add_char();
        get_char();
    }
    if (lexeme == "\n")
        return SPACE;
    else {
        token_type = ID;
        return token_type;
    }
}

int LexAn::get_token() {
    //get_char();
    lexeme="";
    
    while (char_class == SPACE)   //  moves to the next character if there is a space. Does not add to the lexeme
        get_char();
    
    if (char_class == ERROR) {    //  simply throws an error if the character isnt recognized
        add_char();
        get_char();
        token_type = ERROR;
        return token_type;
    }
    if (char_class == STOP) {      //  when line reaches the end, it produces a STOP token
        token_type = STOP;
        return token_type;
    }
    switch (char_class) {         // switch statement for the other character classes.
        case LETTER:
            add_char();
            get_char();
            return rule1();
            break;
        case DIGIT:
            add_char();
            get_char();
            while (char_class == DIGIT) {
                add_char();
                get_char();
            }
            token_type = INTEGER;
            return token_type;
            break;
        case PLUS_CODE:
            add_char();
            get_char();
            token_type = ERROR;
            return token_type;
            break;
        case COMMA:
            add_char();
            get_char();
            token_type = COMMA;
            return token_type;
            break;
        case PERIOD:
            add_char();
            get_char();
            token_type = PERIOD;
            return token_type;
            break;
        case Q_MARK:
            add_char();
            get_char();
            token_type = Q_MARK;
            return token_type;
            
            break;
        case LEFT_PAREN:
            add_char();
            get_char();
            token_type = LEFT_PAREN;
            return token_type;
            break;
        case RIGHT_PAREN:
            add_char();
            get_char();
            token_type = RIGHT_PAREN;
            return token_type;
            break;
        case COLON:
            add_char();
            get_char();
            while(char_class == DASH) {
                add_char();
                get_char();
            }
            if (lexeme == ":-") {
                token_type = COLON_DASH;
                return token_type;
            }
            else {
                token_type = COLON;
                return token_type;
            }
            break;
        case DASH:
            add_char();
            get_char();
            token_type = DASH;
            return token_type;
            break;
        case COLON_DASH:
            add_char();
            get_char();
            token_type = COLON_DASH;
            return token_type;
            break;
        case SEMI_COLON:
            add_char();
            get_char();
            token_type = ERROR;
            return token_type;
            break;
        case COMMENT:
            add_char();
            get_char();
            token_type = STOP;
            return token_type;
            break;
        case QUOTATION:
            add_char();
            get_char();
            return rule2();
            break;
        case BACK_SLASH:
            add_char();
            get_char();
            return rule3();
            break;
        case UNDERSCORE:
            add_char();
            get_char();
            token_type = ERROR;
            return token_type;
            break;
        default:
            token_type = ERROR;
            return token_type;
    }
}
string LexAn::get_token_type() {
    switch (token_type) {
        case SPACE:  return "SPACE";
        case ERROR:  return "ERROR";
        case STOP:  return "STOP";
        case COMMA:  return "COMMA";
        case PERIOD:  return "PERIOD";
        case Q_MARK:  return "Q_MARK";
        case LEFT_PAREN:  return "LEFT_PAREN";
        case RIGHT_PAREN:  return "RIGHT_PAREN";
        case COLON:  return "COLON";
        case COLON_DASH:  return "COLON_DASH";
        case SCHEMES:  return "SCHEMES";
        case FACTS:  return "FACTS";
        case RULES:  return "RULES";
        case QUERIES:  return "QUERIES";
        case ID:  return "ID";
        case STRING:  return "STRING";
        default:  return "ERROR";
    }
}
string LexAn::get_token_value() {
    return lexeme;
}
int LexAn::get_line_number() {
    return linenumber;
}
void LexAn::push_token() {
    
    tokenlist.push_back(Token(get_token_type(),get_token_value(),get_line_number()));
    //cout << tokenlist.back().toString() << endl;
}

