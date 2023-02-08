//
//  CppPractice.cpp
//  CppPractice
//
//  Created by John Kooistra on 2023-02-08.
//

#include <iostream>
#include "CppPractice.hpp"
#include "CppPracticePriv.hpp"

void CppPractice::HelloWorld(const char * s)
{
    CppPracticePriv *theObj = new CppPracticePriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void CppPracticePriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

