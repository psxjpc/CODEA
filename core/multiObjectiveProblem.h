/** 
   @class multiObjectiveProblem
  
   @brief Deals with problems with one or more objectives

   This class is specially designed to work with multi-objective problems.
   The idea is to have a vector of evalution functions in which, each of
   these functions is an objective to be optimize. Moreover, this contains
   an object that acts as an interface to work with different types of 
   ranking schemes (e.g. Pareto Ranking, Aggregation, Lexicographical, ...).
   See more details bellow.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef MULTIOBJECTIVEPROBLEM_H
#define MULTIOBJECTIVEPROBLEM_H

#include <string>

#include "header.h"
#include "multiObjectiveSolution.h"
#include "abstractMOScoreCriterion.h"
#include "singleObjectiveProblem.h"

class multiObjectiveProblem 
{
   private:
      /**
         Vector of problem the agents are going to deal with.
      */
      problemsType problems;

      /**
         Pointer to an object to compare solutions. See more details 
         refering to the class.
      */
      abstractMOScoreCriterion* MOScoreCriterion;

   protected:
     

   public:
      /**
         Default constructor. It initilizes the score criterion's pointer to NULL.
      */
      multiObjectiveProblem();

      /**
         Default destructor. It frees the memory taken by the score criterion.
      */
      ~multiObjectiveProblem();

      /** 
         Method that returns the vector of 'problems' we're working on.
         @return std::vector that contains pointers to singleObjectiveProblem from. 
         which the objective function classes inherit.
      */
      problemsType getProblems() const { return problems; }

      /** 
         Method that sets the criteria it is going to be used to score the solutions.
         @param abstractMOScoreCriterion* is a pointer to the raking criterion object.
      */      
      void setMOScoreCriterion(abstractMOScoreCriterion*);
     
      /** 
         Method that compares two solutions using the established score criterion. 
         @param const multiObjectiveSolution* is a pointer to the first solution to be compared.
         @param const multiObjectiveSolution* is a pointer to the second solution to be compared.
         @param const std::string is reserved data field for options.
         @return a triBool object. The state in which the triBool is returned merely depends 
         on the ranking criteria.
      */    
      triBool firstSolutionIsBetter(const multiObjectiveSolution*, const multiObjectiveSolution*, const std::string) const;

      /** 
         Method that compares two solutions and returns true if they are equal and false otherwise.
         @param const multiObjectiveSolution* is a pointer to the first solution to be compared.
         @param const multiObjectiveSolution* is a pointer to the second solution to be compared.
         @return a boolean value depending on whether the solutions are equal or not.
      */    
      bool isEqual(const multiObjectiveSolution*, const multiObjectiveSolution*) const;

      /** 
         Method that adds a problem to the vector of problems.
         @param singleObjectiveProblem* is a pointer to the problem to be added.
      */    
      void addProblem(singleObjectiveProblem*);

      /** 
         Method that evaluates the vector of problems and puts the result in the multiobjectiveSolution
         received as a parameter.
         @param multiObjectiveSolution* is a pointer to the solution to be updated.
      */ 
      void evaluate(multiObjectiveSolution*) const;
};


multiObjectiveProblem::multiObjectiveProblem()
{
   this->MOScoreCriterion = NULL;
}

multiObjectiveProblem::~multiObjectiveProblem()
{
   delete(this->MOScoreCriterion);
}

inline void multiObjectiveProblem::setMOScoreCriterion(abstractMOScoreCriterion* MOScoreCriterion)
{
   this->MOScoreCriterion = MOScoreCriterion;
}

inline triBool multiObjectiveProblem::firstSolutionIsBetter(const multiObjectiveSolution *s1, 
                                                            const multiObjectiveSolution *s2,
                                                            const std::string options = " ") const
{
   assert(s1 != NULL);
   assert(s2 != NULL);
   return (MOScoreCriterion->firstSolutionIsBetter(s1, s2, this->problems, options));
}

inline bool multiObjectiveProblem::isEqual(const multiObjectiveSolution* s1, const multiObjectiveSolution* s2) const
{
   return (s1 == s2);
}

inline void multiObjectiveProblem::addProblem(singleObjectiveProblem* currentSingleObjectiveProblem)
{
   this->problems.push_back(currentSingleObjectiveProblem);
}

inline void multiObjectiveProblem::evaluate(multiObjectiveSolution* MOSolution) const
{
   objectivesType* objectives = MOSolution->getPointerToObjectives();

   // If this is the first time this solution is being evaluated, 
   //   the objectives will be created
   if (objectives->empty())
      for (size_t i = 0; i < problems.size(); i++)
         objectives->push_back(this->problems[i]->evaluate(MOSolution)); 
   else
      for (size_t i = 0; i < objectives->size(); i++)
         (*objectives)[i] = this->problems[i]->evaluate(MOSolution); 

}

#endif
