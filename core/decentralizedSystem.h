/** 
   @class decentralizedSystem
  
   @brief Basic abstract class that implements a dummy for the pre and
   post Phases inherited from ssytem.

   This class is a simple interface that connects ssystem class with 
   coDecentralizedArchitecture class. It is just an open class that 
   implements nothing with the purpose of being extended. 

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef DECENTRALIZEDSYSTEM_H
#define DECENTRALIZEDSYSTEM_H

#include "ssystem.h"

class decentralizedSystem : public ssystem
{
   private:

   protected:

      /**
         Virtual method inherited from ssystem to be implemented.
      */
      virtual void preOperationsSystem() = 0;

      /**
         Virtual method inherited from ssystem to be implemented.
      */
      virtual void phase() = 0;

      /**
         Virtual method inherited from ssystem to be implemented.
      */
      virtual void postOperationsSystem() = 0;
 
      /**
         Method inherited from ssystem that implements nothing.
      */
      void prePhase();

      /**
         Method inherited from ssystem that implements nothing.
      */
      void postPhase();

   public:

      /**
         Default constructor. It does nothing.
      */
      decentralizedSystem() { };

      /**
          Default destructor. It does nothing.
      */
      ~decentralizedSystem() { };     
};

inline void decentralizedSystem::prePhase()
{

}

inline void decentralizedSystem::postPhase()
{

}

#endif
