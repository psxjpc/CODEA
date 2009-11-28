/** 
   @class lexicographiMOScoreCritrion
  
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef dynamicLexMOScoreCriterion_H
#define dynamicLexMOScoreCriterion_H

#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "../multiObjectiveSolution.h"
#include "../abstractMOScoreCriterion.h"
#include "../header.h"

#include "../../libs/funcLibrary.h"

/* TODO:
	- WARNING: We are assuming we have to minize!

*/

class dynamicLexMOScoreCriterion : public abstractMOScoreCriterion 
{
   private:
      std::vector<unsigned> ordering;

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      dynamicLexMOScoreCriterion() { };

      dynamicLexMOScoreCriterion(unsigned numberOfVars) 
      {  this->ordering = getOrdering(numberOfVars);  };

      /**
         Default destructor. It does nothing.
      */
      ~dynamicLexMOScoreCriterion() { };

      /** 
         Method that returns (True/False/Undefined) depending on the lexicographic approach
      */
      triBool firstSolutionIsBetter(const multiObjectiveSolution*, 
                                    const multiObjectiveSolution*, 
                                    const problemsType&,
                                    std::string options = " ") const;

      triBool firstSolutionIsBetter(const objectivesType&, 
                                    const objectivesType&, 
                                    const problemsType&,
                                    std::string options = " ") const;

      unsigned getObjectiveIndexGivenPriority(const unsigned, const problemsType&) const;
      std::vector<unsigned>  getOrdering(const unsigned) const;

      void clear() { this->ordering.clear(); }
}; 

inline unsigned dynamicLexMOScoreCriterion::getObjectiveIndexGivenPriority(const unsigned p, const problemsType& problems) const
{
   for (size_t i = 0; i < problems.size(); i++)   
      if (problems[i]->getPriority() == p)
         return i;
   std::cout << "Critical Error: 'inline unsigned getObjectiveIndexGivenPriority(const unsigned p, const problemsType& problems)' in lexicographicMOScoreCriterion.h" << std::endl;
   exit(1);
}

std::vector<unsigned> dynamicLexMOScoreCriterion::getOrdering(const unsigned numberOfVars) const
{
   codeaParameters* neuralItem = codeaParameters::instance();
   // double delta = 2.6 / (double)numberOfVars;
   double delta = 1;

   // Probability vector
   std::vector<double> probabilities;
   for (size_t i = 0; i < numberOfVars; i++)
   { 
      // This for creating the segments (n segments => n + 1 points)
      if (i == 0)
         probabilities.push_back(0.0);
       probabilities.push_back(0.9 * exp(-delta * i) + 0.05);
       //probabilities.push_back(-0.08 * (i - 10));

       //probabilities.push_back(0.4 * cos((i * 0.4) + 0.1) + 0.5);
   }


   double accProb = accumulate(probabilities.begin(), probabilities.end(), 0.0);


   // Scalation 
   for (size_t i = 1; i < probabilities.size(); i++)
      probabilities[i] /= accProb;

   // Accumulate probability
   for (size_t i = 2; i < probabilities.size(); i++)
      probabilities[i] += probabilities[i - 1];

   double r = 0.0;
   int pos = 0;
   std::vector<unsigned> order;
 
   while (order.size() < numberOfVars)
   {
      r = neuralItem->getRandomNumber()->rand();
      pos = -1;
      for (size_t i = 1; i < probabilities.size(); i++)
         if (isInside<double>(r, probabilities[i - 1], probabilities[i]))
         {
            pos = i - 1;
            break;
         }
      assert(pos >= 0);
      if (find(order.begin(), order.end(), pos) == order.end())
         order.push_back(pos);
   }

   return order;
}



inline  triBool dynamicLexMOScoreCriterion::
        firstSolutionIsBetter(const multiObjectiveSolution* firstMetaSolution, 
                              const multiObjectiveSolution* secondMetaSolution, 
                              const problemsType& problems,
                              std::string options) const
{
   // Preconditions
   assert(firstMetaSolution != NULL);
   assert(secondMetaSolution != NULL);
   assert(firstMetaSolution->getNumberOfObjectives() == 
          secondMetaSolution->getNumberOfObjectives());

   //copy(ordering.begin(), ordering.end(), std::ostream_iterator<unsigned>(std::cout," "));

   std::vector<unsigned> newOrdering;
   if ((this->ordering.size() == 0) || (options == "reset"))
      newOrdering = getOrdering(firstMetaSolution->getNumberOfObjectives());
   else
      newOrdering = this->ordering;
  
   unsigned index = 0;
   for (size_t p = 0; p < firstMetaSolution->getNumberOfObjectives(); p++)
   {
      index = getObjectiveIndexGivenPriority(newOrdering[p], problems);

      if (firstMetaSolution->getObjective(index) < secondMetaSolution->getObjective(index))
         return triBool(true);

      if (firstMetaSolution->getObjective(index) > secondMetaSolution->getObjective(index))
         return triBool(false);
    
   }
   return triBool(null);

}

inline  triBool dynamicLexMOScoreCriterion::
        firstSolutionIsBetter(const objectivesType& objectives1, 
                              const objectivesType& objectives2, 
                              const problemsType& problems,
                              std::string options) const
{
   // Preconditions
   assert(objectives1.size() == objectives2.size());

   std::vector<unsigned> newOrdering;
   if ((this->ordering.size() == 0) || (options == "reset"))
      newOrdering = getOrdering(objectives1.size());
   else   
      newOrdering = this->ordering;

   unsigned index = 0;
   for (size_t p = 0; p < objectives1.size(); p++)
   {
      index = getObjectiveIndexGivenPriority(newOrdering[p], problems);
      if (objectives1[index] < objectives2[index])
         return triBool(true);
      
      if (objectives1[index] > objectives2[index])
         return triBool(false);
   }
   return triBool(null);

}


#endif



