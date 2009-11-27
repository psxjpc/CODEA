/** 
   @class defaultAgent
  
   @brief Establishes the pattern to create defaultAgentName agents.

   This class is a template for you to create new agents.
   As an agent, this class inherits from 'core'. However,
   'core' doesn't have any virtual method, so we won't have
   to bother about that. 
 
   The behaviour of this class should NOT be subject to 
   any specific problem. Instead, this should work as
   an abstract layer of any problem with some abstract
   methods. These methods should be implemented in another
   class with the operation subject to a given problem.

   @note You should delete all this comments in your class
   and include yours with a decription of the agent.

   @note This class should be stored at:
   <PATH_OF_CODEA>/agents/your_Agent/phases/

   @author ASAP - University of Nottingham / Group of Intelligent Computing - Universidad de La Laguna - 2009
*/

#ifndef DEFAULT_AGENT_H
#define DEFAULT_AGENT_H

#include <string>

#include "../../core/core.h"
#include "../../core/header.h"
#include "../../core/multiObjectiveSolution.h"
#include "../../core/multiObjectiveProblem.h"

class defaultAgent : public core
{
   private:

   protected:

   public:
      /**
         Default constructor. 
      */
      defaultAgent();
      /**
         Default destructor.
      */
      ~defaultAgent();

     
};

defaultAgent::defaultAgent()
{

}

defaultAgent::~defaultAgent()
{

}



#endif
