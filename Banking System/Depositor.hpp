//
//  Depositor.hpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#ifndef Depositor_hpp
#define Depositor_hpp

#include <stdio.h>
#include "Name.hpp"

class Depositor
{
    string _ssn;
    Name _name;
public:
    Depositor(void);
    Depositor(const Depositor& depositor);
    Depositor(Name& name, string ssn);
    ~Depositor(void);
    
    Name& getName();
    string getSSN();
};
#endif /* Depositor_hpp */
