//
//  Name.cpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#include "Name.hpp"

Name::Name(void)
{
}

Name::~Name(void)
{
}

Name::Name(const Name& name)
{
    _firstName = name._firstName;
    _lastName = name._lastName;
}

Name::Name(string firstName, string lastName)
{
    _firstName = firstName;
    _lastName = lastName;
}

string Name::getFirstname()
{
    return _firstName;
}

string Name::getLastname()
{
    return _lastName;
}