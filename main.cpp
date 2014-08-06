//
//  main.cpp
//  Project1
//
//  Created by Michael Bird on 6/25/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
#include "parser.h"
#include "Interpreter.h"

using namespace std;

int main (int argc, char *argv[])
{
    
    LexAn LA;
    vector<Token> tokens = LA.lex(argv[1]);

    parser PA;
    PA.parse(tokens);
    
    
    Interpreter INT;
    INT.interpret(PA.get_datalog_object(), argv[2]);
    
    return 0;
}




