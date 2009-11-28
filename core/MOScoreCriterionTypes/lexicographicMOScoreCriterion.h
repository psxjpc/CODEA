/** 
   @class lexicographiMOScoreCritrion
  
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef LEXICOGRAPHICMOSCORECRITERION_H
#define LEXICOGRAPHICMOSCORECRITERION_H

#include "../multiObjectiveSolution.h"
#include "../abstractMOScoreCriterion.h"
#include "../header.h"

class lexicographicMOScoreCriterion : public abstractMOScoreCriterion 
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      lexicographicMOScoreCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~lexicographicMOScoreCriterion() { };

      /** 
         Method that returns (True/False/Undefined) depending on the lexicographic approach
      */
      triBool firstSolutionIsBetter(const multiObjectiveSolution*, 
                                    const multiObjectiveSolution*, 
                                    const problemsType&,
                                    const string options) const;

      unsigned getObjectiveIndexGivenPriority(const unsigned, const problemsType&) const;
}; 


inline unsigned lexicographicMOScoreCriterion::getObjectiveIndexGivenPriority(const unsigned p, const problemsType& problems) const
{
   codeaParameters* neuralItem = codeaParameters::instance();
   unsigned _p = p;
   for (size_t j = 0; j < problems.size(); j++)
   {    
      for (size_t i = 0; i < problems.size(); i++)   
         if (problems[i]->getPriority() == _p && neuralItem->getRandomNumber()->rand() < 0.7)
            return i;
      _p++;
   }

   for (size_t i = 0; i < problems.size(); i++)   
      if (problems[i]->getPriority() == p)
         return i;

   std::cout << "Critical Error: 'inline unsigned getObjectiveIndexGivenPriority(const unsigned p, const problemsType& problems)' in lexicographicMOScoreCriterion.h" << std::endl;
   exit(1);
}


inline  triBool lexicographicMOScoreCriterion::
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

   unsigned index = 0;
   for (size_t p = 0; p < firstMetaSolution->getNumberOfObjectives(); p++)
   {
      index = getObjectiveIndexGivenPriority(p, problems);
      if (firstMetaSolution->getObjective(index) < secondMetaSolution->getObjective(index))
         return triBool(true);
      if (firstMetaSolution->getObjective(index) > secondMetaSolution->getObjective(index))
         return triBool(false);
   }
   return triBool(null);

}

#endif



