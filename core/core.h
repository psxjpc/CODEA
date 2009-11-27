/** 
   @class core
  
   @brief Contains propperties and methods agents work with at a low
   level to solve a given problem.

   This class is a base class for those that will implement different
   types of solvers. This basically stores the main solutions, the 
   problem the agent is dealing with and some fields for statistical
   and data mining purposes. See each field for more information.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef CORE_H
#define CORE_H

#include "header.h"

#include "multiObjectiveSolution.h"
#include "multiObjectiveProblem.h"

class core
{
   private:
      /**
         Agent's best solution. This is the best solution found by the agent up time.         
      */
      multiObjectiveSolution* bestSolution;

      /**
         Agent's current solution. This is the current solution of the agent. 
      */
      multiObjectiveSolution* currentSolution;

      /**
         Agent's current problem. This is the problem the agent is dealing with.
      */
      const multiObjectiveProblem* currentProblem;

      /**
         Agent's iteration. It counts how many time this agent has performed an operation.         
      */
      unsigned iteration;

      /**
         Agent's iteration in which the best solution was found.
      */
      unsigned iterationOfBestSolution;

      /**
         Agent's lifetime. Birthdate of the agent.         
      */
      double elapsedTime;

      /**
         Time in which the best solution was achieved.
      */
      double elapsedTimeOfBestSolution;

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      core();

      /**
         Default destructor. It frees all the memory used by this class.
      */
      ~core();

      /** 
         Method that returns the agent's best solution.
         @return a pointer to agent's best solution achieved.
      */
      multiObjectiveSolution* getBestSolution() const;

      /** 
         Method that returns the agent's current solution.
         @return a point to agent's current solution.
      */
      multiObjectiveSolution* getCurrentSolution() const;

      /** 
         Method that returns the problem the agent is trying to solve.
         @return a pointer to agent's problem.
      */
      const multiObjectiveProblem* const getProblem() const;

      /** 
         Method that returns the iteration the agent is in.
         @return agent's iteration.
      */
      unsigned getIteration() const;

      /** 
         Method that returns the iteration in which the agent found the best solution.
         @return the iteration of the best solution.
      */
      unsigned getIterationOfBestSolution() const;

      /** 
         Method that returns lifetime of the agent.
         @return the time since birthdate of the agent.
      */
      double getElapsedTime() const;

      /** 
         Method that returns the time in which the best solution was found.
         @return the time of the best solution.
      */
      double getElapsedTimeOfBestSolution() const;

      /** 
         Method that sets the agent's best solution.
         @param multiObjectiveSolution* is a pointer to the best solution.
      */
      void setBestSolution(multiObjectiveSolution*);

      /** 
         Method that update the agent's best solution.
         @param multiObjectiveSolution* is a pointer to the best solution.
         @warning  This method updates the params of this solution and not the
                   pointer. We are going to use the copy method.
      */
      void updateBestSolution(multiObjectiveSolution*);

      /** 
         Method that sets the agent's current solution.
         @param multiObjectiveSolution* is a pointer to the current solution.
      */
      void setCurrentSolution(multiObjectiveSolution*);

      /** 
         Method that update the agent's current solution.
         @param multiObjectiveSolution* is a pointer to the best solution.
         @warning  This method updates the params of this solution and not the
                   pointer. We are going to use the copy method.
      */
      void updateCurrentSolution(multiObjectiveSolution*);

      /** 
         Method that sets the agent's problem.
         @param multiObjectiveProblem* is a pointer to the problem to be solved.
      */
      void setProblem(const multiObjectiveProblem* const);

      /** 
         Method that sets the current iteration or number of times an agent has 
         carried out its phases.
         @param const unsigned is the current iteration.
      */
      void setIteration(const unsigned);

      /** 
         Method that sets the iteration of the best solution.
         @param const unsigned is the iteration of the best solution found.
      */
      void setIterationOfBestSolution(const unsigned);

      /** 
         Method that increases the current interation in one.
      */
      void increaseIteration();

      /** 
         Method that sets the lifetime of the agent.
         @param const double is the number that represents the lifetime.
      */
      void setElapsedTime(const double);

      /** 
         Method that sets the time in which the best solution was found.
         @param const double is the number that represents the time of the best solution.
      */
      void setElapsedTimeOfBestSolution(const double);

      /** 
         Method that resets the iteration counter of the agent.
      */
      void resetIteration();

      /** 
         Method that resets the lifetime counter of the agent.
      */
      void resetElapsedTime();
};

core::core()
{
   this->bestSolution = NULL;
   this->currentSolution = NULL;
   this->currentProblem = NULL;

   this->iteration = 0;
   this->iterationOfBestSolution = 0;

   this->elapsedTime = 0.0;
   this->elapsedTimeOfBestSolution = 0.0;
}

core::~core()
{
   delete(this->bestSolution);
   delete(this->currentSolution);
   delete(this->currentProblem);
}


inline void core::setIteration(const unsigned i)
{
   this->iteration = i;
}

inline void core::increaseIteration()
{
   this->iteration++;
}

inline void core::setIterationOfBestSolution(const unsigned i)
{
   this->iterationOfBestSolution = i;
}

inline void core::setElapsedTime(const double time)
{
   this->elapsedTime = time;
}

inline void core::setElapsedTimeOfBestSolution(const double time)
{
   this->elapsedTimeOfBestSolution = time;
}

inline multiObjectiveSolution* core::getBestSolution() const
{
   return this->bestSolution;
}

inline multiObjectiveSolution* core::getCurrentSolution() const
{
   return this->currentSolution;
}

inline const multiObjectiveProblem *const core::getProblem() const
{
   return this->currentProblem;
}

inline unsigned core::getIteration() const
{
   return this->iteration;
}

inline unsigned core::getIterationOfBestSolution() const
{
   return this->iterationOfBestSolution;
}

inline double core::getElapsedTime() const
{
   return this->elapsedTime;
}

inline double core::getElapsedTimeOfBestSolution() const
{
   return this->elapsedTimeOfBestSolution;
}

inline void core::setCurrentSolution(multiObjectiveSolution* newSolution)
{
   // We won't allow the bestSolution to point to NULL
   assert(newSolution != NULL);
   this->currentSolution = newSolution;
}

// WARNING: This method updates the params of this solution and not the
//  pointer. We're going to use the copy method.
inline void core::updateCurrentSolution(multiObjectiveSolution* newSolution)
{
   assert(newSolution != NULL);
   assert(this->currentSolution != NULL);

   this->currentSolution->copy(newSolution);
}

inline void core::setBestSolution(multiObjectiveSolution* newSolution)
{
   // We won't allow the bestSolution to point to NULL
   assert(newSolution != NULL);
   this->bestSolution = newSolution;
}

// WARNING: This method updates the params of this solution and not the
//  pointer. We're going to use the copy method.
inline void core::updateBestSolution(multiObjectiveSolution* newSolution)
{
   assert(newSolution != NULL);
   assert(this->bestSolution != NULL);

   this->bestSolution->copy(newSolution);
}

inline void core::setProblem(const multiObjectiveProblem* const newProblem)
{
   this->currentProblem = newProblem;
}

inline void core::resetIteration()
{
   this->iteration = 0;
}

inline void core::resetElapsedTime()
{
   this->elapsedTime = 0;
}
// v l y 5 h 3 i 3
#endif
