/** 
   @class aggregationMOScoreCriterion
  
   An aggregation ranking criterion.

   This class inherits from abstractMOScoreCriterion to provide an aggregation
   ranking scheme.   

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef AGGREGATIONMOSCORECRITERION_H
#define AGGREGATIONMOSCORECRITERION_H

#include "../multiObjectiveSolution.h"
#include "../abstractMOScoreCriterion.h"
#include "../header.h"

class aggregationMOScoreCriterion : public abstractMOScoreCriterion 
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      aggregationMOScoreCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~aggregationMOScoreCriterion() { };

      /** 
         Method that compares to solutions using
         the simplest aggregation scheme. This consists of summing up (+/-)
         the objective scores and returning the one whose sum is greater (max) or
         less (min) than the other one. 
         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the first one we want to compare
         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the second one we want to compare
         @param problemType& is the set of problems (goals) we want to optimize. We need this to know which objectives
                             in the solutions must be minimized and which of them maximized.
         @param std::string is an extra paremeter to add 'options' if needed.
         @return a 'triBool' object (True/False/Undefined)
         @warning We are supposing all the objective must be minimized 
      */
      triBool firstSolutionIsBetter(const multiObjectiveSolution*, 
                                    const multiObjectiveSolution*, 
                                    const problemsType&,
                                    const string options) const;
}; 

inline  triBool aggregationMOScoreCriterion::
        firstSolutionIsBetter(const multiObjectiveSolution* firstMetaSolution, 
                              const multiObjectiveSolution* secondMetaSolution, 
                              const problemsType& problems,
                              const string options = " ") const
{
   T firstSum = 0;
   T secondSum = 0;
   assert(firstMetaSolution != NULL);
   assert(secondMetaSolution != NULL);
   assert(firstMetaSolution->getObjectives().size() == secondMetaSolution->getObjectives().size());

   // Summing up the objectives
   for (size_t i = 0; i < firstMetaSolution->getObjectives().size(); i++)
      if (problems[i]->isComparable())
      {
         firstSum += firstMetaSolution->getObjective(i);
         secondSum += secondMetaSolution->getObjective(i);

      }

   return (triBool(firstSum < secondSum));
}

#endif
