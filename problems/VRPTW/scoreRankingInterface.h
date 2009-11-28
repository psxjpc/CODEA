
#ifndef SCORERANKINGINTERFACE_H
#define SCORERANKINGINTERFACE_H

#include "dataTypes.h"

#include "../../core/codeaParameters.h"
#include "../../core/MOScoreCriterionTypes/dynamicLexMOScoreCriterion.h"
#include "../../core/MOScoreCriterionTypes/basicParetoFrontMOScoreCriterion.h"

#include <vector>

namespace scoreRankingInterface
{

   /**
      Function that ranks two solutions. 
   */
   triBool firstSolutionIsBetter(const objectivesType& v1, 
                                 const objectivesType& v2, 
                                 const basicParetoFrontMOScoreCriterion& scoreCriterion,
                                 const std::string& options = " ")
   {
      codeaParameters* neuralItem = codeaParameters::instance();
      return scoreCriterion.firstSolutionIsBetter(v1, v2, *(neuralItem->getProblems()));
   }


   /**
      Function that, given a solution, calculates its objective vector.  
   */
   objectivesType evaluate(const chromosomeType& f1, const std::string& options = " ")
   {
      codeaParameters* neuralItem = codeaParameters::instance();
      const problemsType* problems = neuralItem->getProblems();

      objectivesType output;
   
      // In order to call the problems evaluators we have to encapsulate this
      //   vector in a boost object.
      boost::any pointerToChromosome = f1;
 
      for (size_t i = 0; i < problems->size(); i++)
         output.push_back((*problems)[i]->evaluate(pointerToChromosome)); 
      
      return output;
   }
}

#endif
