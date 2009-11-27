/** 
   @class coDecentralizedArchitecture
  
   @brief Invokes agent's phases repeteadly.

   This class inherits from decentralizedSystem implementing all the virtual
   methods imposed by decentralizedSystem and ssytem. 

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef CODECENTRALIZEDARCHITECTURE_H
#define CODECENTRALIZEDARCHITECTURE_H

#include "decentralizedSystem.h"
#include "header.h"
#include "multiObjectiveSolution.h"
#include "../libs/IOlibrary.h"


class coDecentralizedArchitecture : public decentralizedSystem
{
   private:
      /**
         Number of phases the agents are working with whithin the system
      */
      unsigned numberOfPhases;

   protected:
      /**
         Space to perform operations before the agents start running their phases
      */
      void preOperationsSystem();

      /**
         Method that invokes the agents' phases. There is a double loop in which 
         the first one iterates over the number of phases (numberOfPhases) and
         the second one over the number of agents.
      */
      void phase();

      /**
         Space to perform operations after the agents finished their phases
      */
      void postOperationsSystem();


   public:

      /**
         Default constructor. It sets basic propperties inherited from ssytem
         to null values.
      */
      coDecentralizedArchitecture();

      /**
         Standard constructor. It sets basic propperties inherited from ssytem
         to null values plus attributes the system needs to work.
         @param vector<agent*> is a vector of agents.
         @param systemStopCriterion* is a pointer to the criterion it will make
           the system stop.
         @param const unsigned is the number of phases (numberOfPhases).
         @param multiObjectiveSolution* is a pointer to the best solution found.
      */
      coDecentralizedArchitecture(const vector<agent*>, systemStopCriterion* , const unsigned, multiObjectiveSolution*);

      /**
          Default destructor. It does nothing.
      */
      ~coDecentralizedArchitecture();

      /** 
         Method that returns the number of phases(numberOfPhases) the agents count with
         @return the number of phases
      */
      unsigned getNumberOfPhases();

      /** 
         Method that sets the number of phases the system is going through
         @param const unsigned is the number of phases 
      */
      void setNumberOfPhases(const unsigned);

};

coDecentralizedArchitecture::coDecentralizedArchitecture()
{
   this->setBestSolution(NULL);
   this->setStopCriterion(NULL);
   this->setIteration(0);
   this->setIterationOfBestSolution(0);
   this->setElapsedTimeOfBestSolution(0);
}


coDecentralizedArchitecture::coDecentralizedArchitecture(const vector<agent*> agents, 
                                                           systemStopCriterion* stopController, 
                                                           const unsigned numberOfPhases,
                                                           multiObjectiveSolution* bestSolution)
{
   this->setAgents(agents);
   this->setBestSolution(bestSolution);
   this->setIteration(0);
   this->setIterationOfBestSolution(0);
   this->setElapsedTimeOfBestSolution(0);
   this->setStopCriterion(stopController);
   this->numberOfPhases = numberOfPhases;   
}

coDecentralizedArchitecture::~coDecentralizedArchitecture()
{

}

inline void coDecentralizedArchitecture::preOperationsSystem()
{

}


inline void coDecentralizedArchitecture::phase()
{
   vector<agent*>::size_type numberOfAgents = this->getAgents().size();

   for (unsigned j = 0; j < this->numberOfPhases; j++)
   {
      for (vector<agent*>::size_type i = 0; i < numberOfAgents; i++)
      {
         if (this->getAgents()[i]->getPhases()[j] != NULL)
            this->getAgents()[i]->getPhases()[j]->start(this->getAgents()[i], getPointerToAgents());
      }
   }
   this->increaseIteration();
}

inline void coDecentralizedArchitecture::postOperationsSystem()
{

}

inline unsigned coDecentralizedArchitecture::getNumberOfPhases()
{
   return this->numberOfPhases;
}

inline void coDecentralizedArchitecture::setNumberOfPhases(const unsigned numberOfPhases)
{
   this->numberOfPhases = numberOfPhases;
}
#endif
