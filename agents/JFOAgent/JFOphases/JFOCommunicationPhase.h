/** 
   @class JFOCommunicationPhase
  
   @brief Carries out the Communicatio Phase of a JFO Agent.

   This class is designed to implement the steps to share information
   with other agents. To do this, it starts retrieving the list of
   recipients depending on the neighborhood of this agent. Next, it
   packs the message to be sent. And finally, it puts the message
   on neighbor's mailboxes.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef JFOCOMMUNICATIONPHASE_H
#define JFOCOMMUNICATIONPHASE_H

#include <vector>

#include "../../../core/agent.h"
#include "../../../core/phase.h"

#include "../JFOAgent.h"

#include "../../../libs/boost/shared_ptr.hpp"

class JFOCommunicationPhase : public phase
{
   private:

   protected:
      /**
         Method that implements initialization steps.
         It packs the message to be sent.
      */
      void prePhase(agent*, std::vector<agent*>*);

      /**
         Method that retrieves the list of agents who are
         going to received the message and puts it
         into their mailboxes.
      */
      void core(agent*, std::vector<agent*>*);
  
      /** 
         Method that perform update operations. 
         In this case, it does nothing.
      */
      void postPhase(agent*, std::vector<agent*>*) { };

   public:
      /**
         Default constructor. It does nothing.
      */
      JFOCommunicationPhase() {};

      /**
         Default destructor. It does nothing.
      */
      ~JFOCommunicationPhase() {};

};

void JFOCommunicationPhase::prePhase(agent* currentAgent, std::vector<agent*>* team)
{
   message info;
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());

   container data("Sender", currentAgent);
   info.push_back(data);

   // Let's start the tests by sending the best solution found by the agent.
   //    We will see if what happen when we send other solutions.

   // NOTE: This type of agent can't send a pointer to it's solution because
   // Since this solution is going to be crossed with the receiver's solution,
   // If A1 shares its solution with A2 and viceversa, when A1 crosses its
   // solution with A2, A1's solution is not the same as A2 expects. So this
   // approach is not valid.
   data.set("Solution", boost::shared_ptr<multiObjectiveSolution>(superFrog->getCurrentSolution()->clone()));
   info.push_back(data);

   currentAgent->setMessage(info);
}

void JFOCommunicationPhase::core(agent* currentAgent, std::vector<agent*>* team)
{
   if (!currentAgent->getMessage().empty() && currentAgent->getNeighborhood() != NULL)
   {
      vector<agent*> *group = currentAgent->getNeighborhood()->list();
      for (unsigned i = 0; i < (*group).size(); i++)
         if (currentAgent->getId() != (*group)[i]->getId())
            (*group)[i]->getPointerToInBox()->push_back(currentAgent->getMessage());
   }
}


#endif
