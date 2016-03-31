//
//  Depositor.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include "Depositor.hpp"

Depositor::Depositor(void)
{
}

Depositor::~Depositor(void)
{
}

Depositor::Depositor(const Depositor& depositor)
{
    _ssn = depositor._ssn;
    _name = depositor._name;
}

Depositor::Depositor(Name& name, string ssn)
{
    _ssn = ssn;
    _name = name;
}

Name& Depositor::getName()
{
    return _name;
}

string Depositor::getSSN()
{
    return _ssn;
}
