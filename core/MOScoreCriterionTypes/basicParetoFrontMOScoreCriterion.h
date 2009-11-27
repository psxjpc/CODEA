/** 
   @class basicParetoFrontMOScoreCriterion
  
   A very simple Pareto ranking criterion.

   This class inherits from abstractMOScoreCriterion to provide a Pareto 
   ranking scheme. More info about this scheme at:
   http://en.wikipedia.org/wiki/Pareto_efficiency
   

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef BASICPARETOFRONTMOSCORECRITERION_H
#define BASICPARETOFRONTMOSCORECRITERION_H

#include "../multiObjectiveSolution.h"
#include "../abstractMOScoreCriterion.h"
#include "../header.h"

class basicParetoFrontMOScoreCriterion : public abstractMOScoreCriterion 
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      basicParetoFrontMOScoreCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~basicParetoFrontMOScoreCriterion() { };

      /** 
         Method that returns (True/False/Undefined) depending on:
         - True: Iff the first solution (A) dominates the second one (B).
         - False: Iff the first solution (A) is is dominated the second one (B).
         - Undefined: Iff none of them dominate the other one. (Weak dominance).

         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the first one we want to compare
         @param multiObjectiveSolution* is a pointer to a multi-objetive solution, the second one we want to compare
         @param problemType& is the set of problems (goals) we want to optimize. We need this to know which objectives
                             in the solutions must be minimized and which of them maximized.
         @param std::string is an extra paremeter to add 'options' if needed.
         @return a 'triBool' object (True/False/Undefined)

         @note This method is implemented to treat the ranking of a global solution
               diferently. Thus, if the parameter "options" is set to "<global>"
               the comparison will be made using the attribute of multiObjectiveProblem
               'isGlobalComparable'. 
         @warning This method is implemented to work with problems in which all
         objectives are to be minimized.
      */
      triBool firstSolutionIsBetter(const multiObjectiveSolution*, 
                                    const multiObjectiveSolution*, 
                                    const problemsType&,
                                    const string options) const;
}; 

inline  triBool basicParetoFrontMOScoreCriterion::
        firstSolutionIsBetter(const multiObjectiveSolution* firstMetaSolution, 
                              const multiObjectiveSolution* secondMetaSolution, 
                              const problemsType& problems,
                              const string options = " ") const
{
   // Preconditions
   assert(firstMetaSolution != NULL);
   assert(secondMetaSolution != NULL);
   assert(firstMetaSolution->getNumberOfObjectives() == 
          secondMetaSolution->getNumberOfObjectives());

   unsigned firstSum = 0;
   unsigned secondSum = 0;

   unsigned comparableProblems = 0;

   for (size_t i = 0; i < firstMetaSolution->getNumberOfObjectives(); i++)
   {
      if (options == "<global>")
      {
         if (problems[i]->isGlobalComparable())
         {
            if (firstMetaSolution->getObjective(i) == secondMetaSolution->getObjective(i))
            { 
               firstSum++;
               secondSum++;
            }
            else
            {
               if (firstMetaSolution->getObjective(i) < secondMetaSolution->getObjective(i))
                  firstSum++;
               else
                  secondSum++;
            }
            comparableProblems++;
         }
      }

      else if (problems[i]->isComparable() || ((problems[i]->isGlobalComparable()) && (options == "<global>")))
      {
         if (firstMetaSolution->getObjective(i) == secondMetaSolution->getObjective(i))
         { 
            firstSum++;
            secondSum++;
         }
         else
         {
            if (firstMetaSolution->getObjective(i) < secondMetaSolution->getObjective(i))
               firstSum++;
            else
               secondSum++;
         }
         comparableProblems++;
      }
      
   }
 
   if (firstSum == secondSum)
       return triBool(null);

 
   if (firstSum == comparableProblems)
      return triBool(true);

   if (secondSum == comparableProblems)
      return triBool(false);

   return triBool(null);
}

#endif



