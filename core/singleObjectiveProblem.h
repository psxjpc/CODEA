/** 
   @class singleObjectiveProblem
  
   @brief Interface for problems.

   This abstract class acts as an interface between the multiObjectiveProblem
   and its implementation. It contains basic data all 'problems' should have 
   (see bellow for more info). 
   @note We're refering to 'problems' as objective functions we want to optimize.

   Inherited classes (problems) are only forced to implement the method
   'evaluate'. This acts as the gateway or connection whithin the agent at
   low levels.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef SINGLEOBJECTIVEPROBLEM_H
#define SINGLEOBJECTIVEPROBLEM_H

#include "header.h"
#include "multiObjectiveSolution.h"

class multiObjectiveSolution;

class singleObjectiveProblem 
{
   private:
      /**
         Name of the objective.
      */
      std::string objectiveName;
      /**
         Type of objective. If this field is true, we will be dealing with a maximization
         objective, false otherwise.
      */
      bool maxProblem;
      /**
         Type of objective (from a comparison point of view). If this field is true, when
         two solutions are compared to discern which one is better, this objective will
         be compared.
         @note that even is this field exits for this purpose, it's not compulsory its use.
         It's a helper to enhace the operations whithin this class.
      */
      bool comparable;

      /**
         Type of objective (from a global comparison point of view). If this field is true, when
         two solutions are compared to discern which one is better, this objective will
         be compared. This is a special case of the attribute comparable to be used in the
         comparison with globa-solutions. We might want to use a special set of objective
         to discern if a solution is better than any other.
         @note that even is this field exits for this purpose, it's not compulsory its use.
         It's a helper to enhace the operations whithin this class.
      */
      bool globalComparable;

      unsigned priority;
   protected:
     

   public:
      /**
         Default constructor. It sets the fields of this class to default parameters.
         \code
            this->maxProblem = false;
            this->comparable = false;
            this->globalComparable = false;
         \endcode
      */
      singleObjectiveProblem();

      /**
         Constructor. It sets the fields of this class to default parameters.
         \code
            this->maxProblem = false;
            this->comparable = false;
            this->globalComparable = false;
         \endcode
      */
      singleObjectiveProblem(const unsigned);

      /**
         Default destructor. It does nothing.
      */
      ~singleObjectiveProblem();

      /**
         Method that returns the name of the objective.
         @return std::string that contains the name of this objective.
      */
      std::string getObjectiveName() const;

      /**
         Method that returns the priority of this problem
         @return unsigned with the priority of the problem
      */
      unsigned getPriority() const;

      /**
         Method that returns true if this objective is to be maximized, false otherwise.
         @return boolean expression with the type of problem (max = true, min = false).
      */
      bool isMaxProblem() const;

      /**
         Method that returns true if this objective is comparable, false otherwise.
         @return boolean expression with the type of problem (comparable = true, not comparable = false).
      */
      bool isComparable() const;

      /**
         Method that returns true if this objective is global-comparable, false otherwise. (see more info above
         in the attributes description.
         @return boolean expression with the type of problem (global comparable = true, not global comparable = false).
      */
      bool isGlobalComparable() const;

      /**
         Method that sets the name of the objective.
         @param const std::string is the the name of the objective.
      */
      void setObjectiveName(const std::string objectiveName);

      /**
         Method that sets the type of problem.
         @param const bool is the type of problem.
      */
      void setIsMaxProblem(const bool);

      /**
         Method that sets the type of problem (comparable or not comparable).
         @param const bool is the type of problem.
      */
      void setIsComparable(const bool);

      /**
         Method that sets the type of problem (global comparable or not global comparable).
         @param const bool is the type of problem.
      */
      void setIsGlobalComparable(const bool); 


      /**
         Method that sets the priority of this objective (useful for lexicographic approachs)
         @param const unsigned is the priority of the problem.
      */
      void setPriority(const unsigned); 

      /**
         Virtual method that is intended to evalute the objective given a solution and return a value.
         @param multiObjectiveSolution* is a pointer to the solution is going to be evaluated.
         @return the value of the evalua
      */
      virtual T evaluate(multiObjectiveSolution*) const = 0;

      /**
         Virtual method that is intended to evalute the objective given a solution and return a value.
         @param boost::any is a constant reference to a component of the solution is going to be evaluated.
         @return the value of the evalua
      */
      virtual T evaluate(const boost::any&) const = 0;
};

singleObjectiveProblem::singleObjectiveProblem()
{
   // By default, we'll set up objectives as minimisation
   //   problems and they won't be comparable.
   this->maxProblem = false;
   this->comparable = false;
   this->globalComparable = false;
}

singleObjectiveProblem::singleObjectiveProblem(const unsigned priority)
{
   // By default, we'll set up objectives as minimisation
   //   problems and they won't be comparable.
   this->maxProblem = false;
   this->comparable = false;
   this->globalComparable = false;
   this->priority = priority;
}

singleObjectiveProblem::~singleObjectiveProblem()
{ }

// Getters

inline std::string singleObjectiveProblem::getObjectiveName() const
{
   return this->objectiveName;
}

inline bool singleObjectiveProblem::isMaxProblem() const
{
   return this->maxProblem;
}

inline bool singleObjectiveProblem::isComparable() const
{
   return this->comparable;
}

inline bool singleObjectiveProblem::isGlobalComparable() const
{
   return this->globalComparable;
}

inline unsigned singleObjectiveProblem::getPriority() const
{
   return this->priority;
}

// Setters

inline void singleObjectiveProblem::setObjectiveName(const std::string objectiveName)
{ 
   this->objectiveName = objectiveName; 
}

inline void singleObjectiveProblem::setIsMaxProblem(const bool maxProblem)
{
   this->maxProblem = maxProblem;
}

inline void singleObjectiveProblem::setIsComparable(const bool comparable)
{
   this->comparable = comparable;
}

inline void singleObjectiveProblem::setIsGlobalComparable(const bool globalComparable) 
{ 
   this->globalComparable = globalComparable; 
}

inline void singleObjectiveProblem::setPriority(const unsigned priority) 
{ 
   this->priority = priority; 
}

#endif
