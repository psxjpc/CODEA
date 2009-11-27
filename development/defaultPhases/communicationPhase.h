/** 
   @class communicationPhase
  
   @brief Implements a generic communication phase.

   This class inherits from phase implementing a generic phase
   an agent can communicate a message with. It is
   assumed that the message is already created (otherwise, it will 
   send an empty message). Then it takes the list of recipients
   depending on the neighboring topology. And the process finishes
   storing the message in the recipients' mailboxes.

   @note that this class is in this path because its generic
   use. If you're going to create specific classes for you agent
   follow the rules that appears in the main page.

   @note The path of the needed files to have this class working are
   supposing you will save this file in:
   <PATH_OF_CODEA>/agents/your_Agent/phases/ 

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef COMMUNICATIONPHASE_H
#define COMMUNICATIONPHASE_H

#include <vector> 

#include "../../../core/agent.h"
#include "../../../core/phase.h"

class communicationPhase : public phase
{
   private:

   protected:

      /**
         Method that implements the inherited virtual method from phase.
         It does nothing.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void prePhase(agent*, std::vector<agent*>);

      /**
         Method that implements the inherited virtual method from phase.
         First, it gets the group of recipients that is going to receive the message.
         And seconly, for each agent in this group it pushes back the 
         message in the recipients' mailbox.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void core(agent*, std::vector<agent*>);

      /**
         Method that implements the inherited virtual method from phase.
         It does nothing.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void postPhase(agent*, std::vector<agent*>);

   public:
      /**
         Default constructor. It does nothing.
      */
      communicationPhase()  { };

      /**
         Default destructor. It does nothing.
      */
      ~communicationPhase() { };

};

void communicationPhase::prePhase(agent *currentAgent, std::vector<agent*> team)
{

}

void communicationPhase::core(agent *currentAgent, std::vector<agent*> team)
{

   std::vector<agent*> *group = currentAgent->getNeighborhood()->list();
   for (unsigned i = 0; i < (*group).size(); i++)
      // This 'if-statement' avoid an agent to send the messege to itself.
      if (currentAgent->getId() != (*group)[i]->getId())
         ((*group)[i])->getPointerToInBox()->push_back(currentAgent->getMessage()); 
}

void communicationPhase::postPhase(agent *currentAgent, std::vector<agent*> team)
{

}

#endif
