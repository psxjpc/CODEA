/** 
   @class stopCriterion
  
   @brief Interface for stop criterions for metaheuristics.

   This abstract class acts as an interface between agents who need loops
   to perform their operations and complex stop criterions. Inherited classes
   are only pushed to implement a stop method that specify when to stop.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef STOPCRITERION_H
#define STOPCRITERION_H

#include "agent.h"

class agent;

class stopCriterion
{
   private:

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      stopCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~stopCriterion() { };

      /**
         Virtual method that is intended to be implemented in the stop
         criterion to be used.
         @param agent* is a pointer to the agent that invokes this method.
         Since the agent class is the top class in the agent's class structure,
         the stop criterion has plenty access to all the parameters.
         This is especially useful to create complex stop criterions based
         on the state of the search or on the others behabour.
      */
      virtual bool stop(agent*) const = 0;
};

#endif
