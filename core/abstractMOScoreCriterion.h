/** 
   @class abstractMOScoreCriterion
  
   Interface for multi-objective ranking criterions

   This abstract class operates as an interface for the creation
   of differents classes that control how the ranking of solutions
   is made. 

   Only one method is virtual, the one that tells whether a solution
   is better than another or not. This method returns a 'triBool' 
   object which is a three-state boolean variable. If the first
   solution is better than the second one, it is supposed to output
   'true', otherwise 'false' and 'undefined' if none of them happen.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef ABSTRACTMOSCORECRITERION_H
#define ABSTRACTMOSCORECRITERION_H

#include <string>

#include "./header.h"
#include "./multiObjectiveSolution.h"

class multiObjectiveSolution;

class abstractMOScoreCriterion
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      abstractMOScoreCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~abstractMOScoreCriterion() { };

      /** 
         Virtual method that enables the comparison between solutions using
         different types of criterions. 
         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the first one we want to compare
         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the second one we want to compare
         @param problemType& is the set of problems (goals) we want to optimize. We need this to know which objectives
                             in the solutions must be minimized and which of them maximized.
         @param std::string is an extra paremeter to add 'options' if needed.
         @return a 'triBool' object (True/False/Undefined)
      */
      virtual triBool firstSolutionIsBetter(const multiObjectiveSolution*, 
                                            const multiObjectiveSolution*, 
                                            const problemsType&, 
                                            const std::string) const = 0;
};

#endif
