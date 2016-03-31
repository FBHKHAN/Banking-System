//
//  Name.hpp
//  Banking System
//
//  Created by Farooq Khan on 3/31/14.
//  Copyright © 2014 Farooq Khan. All rights reserved.
//

#ifndef Name_hpp
#define Name_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Name
{
    string _firstName;
    string _lastName;
public:
    Name(void);
    Name(const Name& name);
    Name(string firstName, string lastName);
    ~Name(void);
    
    string getFirstname();
    string getLastname();
};
#endif /* Name_hpp */
