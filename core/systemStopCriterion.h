/** 
   @class systemStopCriterion
  
   @brief Interface for stop criterions for ssystem.

   This abstract class acts as an interface between the system that keeps the
   agents executing their phases and complex stop criterions. Inherited classes
   are only pushed to implement a stop method that specify when to stop. This
   class shares the same idea as stopCriterion.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef SYSTEMSTOPCRITERION_H
#define SYSTEMSTOPCRITERION_H

#include "ssystem.h"

class ssystem;

class systemStopCriterion
{
   private:

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      systemStopCriterion() { };

      /**
         Default destructor. It does nothing.
      */
      ~systemStopCriterion() { };

      /**
         Virtual method that is intended to be implemented in the stop
         criterion to be used.
         @param ssytem* is the pointer to the system in which the agents
         live and do their operations.
      */
      virtual bool stop(ssystem*) = 0;
};

#endif
