//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Listing 7-5.
    @file PrecondViolatedExcep.h */

#ifndef TEACH_CSCI235_STACKADT__PRECONDITIONVIOLATEDEXCEPTION_H
#define TEACH_CSCI235_STACKADT__PRECONDITIONVIOLATEDEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;


// A simple exception class as a child of logic_error.
class PreconditionViolatedException : public logic_error
{
public:
   PreconditionViolatedException(const string& message = "");
}; // end PrecondViolatedExcep 
#endif  // TEACH_CSCI235_STACKADT__PRECONDITIONVIOLATEDEXCEPTION_H
