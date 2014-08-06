//
//  Parameter.h
//  Project2
//
//  Created by Michael Bird on 7/3/14.
//  Copyright (c) 2014 Michael Bird. All rights reserved.
//

#ifndef __Project2__Parameter__
#define __Project2__Parameter__

#include <iostream>
#include <vector>

using namespace std;

class Parameter {
    
public:
    
    Parameter();
    ~Parameter();
    
    string toString();
    void add_param(string param);
    void clear();
    vector<string> get_values();
    
private:
    
    vector<string> domains;

};
#endif /* defined(__Project2__Parameter__) */
