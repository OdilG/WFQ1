//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/**  @file PrecondViolatedExcep.h */

#ifndef PRECOND_VIOLATED_EXCEP_
#define PRECOND_VIOLATED_EXCEP_

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::logic_error
{
public:
   PrecondViolatedExcept(const std::string& message = "");
}; // end PrecondViolatedExcep 
#endif
