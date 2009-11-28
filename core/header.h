/** 
   @library header
  
   @brief This library is intended to store the declarations of
          different types of data CODEA will be using.

   The main purpose of this library is to collect general declarations
   it might be useful to CODEA to work.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <climits>
#include <limits>
#include <valarray>
#include <vector>

#include "../misc/triBool.h"
#include "container.h"

// CODEA General
typedef std::vector<container> message;

typedef double T;    // Common use
typedef double K;    // Multipliers
typedef double C;    // Coefficients
typedef unsigned idType;
typedef unsigned idAgentType;
typedef unsigned iterationType;

// Compound General
typedef std::vector<std::vector<T> > matrixType;

// Infinite <double>
// #define INFd (std::numeric_limits<double>::max)()
#define INFd std::numeric_limits<double>::infinity()
// Infinite <integer>
// #define INFi (std::numeric_limits<unsigned long>::max)()
#define INFi std::numeric_limits<long>::infinity()

// MultiObjective
typedef std::vector<T> objectivesType;
typedef std::vector<std::string> objectivesNameType;

class singleObjectiveProblem;
typedef std::vector<singleObjectiveProblem*> problemsType;



#endif
