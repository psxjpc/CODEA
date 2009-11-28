/** 
   @class agent
  
   @brief Contains propperties and methods agents work with at a high
   level. 

   This class doesn't have directions on how an agent behaves,
   but a basic scheme of all the components it uses to carry out
   its operations. These components are the attributes (explained
   below) that it needs to cooperate, perform solving operations,
   save temporary information, etcetera.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef AGENT_H
#define AGENT_H

#include <deque>
#include <vector>

#include "container.h"
#include "core.h"
#include "header.h" 
#include "mailBox.h"
#include "neighborhood.h"
#include "phase.h"

using std::vector;
using std::deque;

class phase;

class agent
{
   private:

      /**
         Agent's id. This is just a way to identify each agent.         
      */
      idAgentType id;

      /**
         Agent's state. It helps to disable an agent and its operations.         
      */
      bool active;

      /**
         Agent's core. It contains the structure that enables an agent to solve problems.
      */
      core *agentCore;

      /**
         Agent's neighborhood. Current list of neighboors the agent will communication with.
      */
      neighborhood *neighborhoodList;

      /**
         Agent's phases. List of states the agent will go through repeteadly. This is the 
            way an agent has to perform its operations at all levels.
      */
      vector<phase*> phases;

      /**
         Agent's mailbox. Place the agent has to storage the incoming mesages.
      */
      mailBox inBox; 

      /**
         Agent's delivery message. It contains the information the information the agent will
            be sharing (sending) in the communication phase.
      */      message msg;

   protected:


   public:

      /**
         Default constructor. It does nothing.
      */
      agent();

      /** 
         Standard constructor.
         @param idAgentType is the identificator for the agent.
         @param core* is a pointer to the core of the agent.
         @param deque<message> is the data structure the agent is going to use to store the incoming messages.
         @param neighborhood* is the list of agents it is going to communicate with.
         @param vector<phase*> is the list of phases it is going to go through.
         @return an agent with the given parameters.
      */
      agent(const idAgentType id, core* agentCore, 
            const deque<message> inBox, neighborhood* neighborhoodList, 
            const vector<phase*> phases);

      /**
         Default destructor. It frees all the memory used by this class.
      */
      ~agent();
      
      /** 
         Method that returns the agent's id.
         @return agent's id.
      */
      idAgentType getId() const;

      /** 
         Method that returns whether the agent is active or not.
         @return agent's state.
      */
      bool isActive() const;

      /** 
         Method that returns the agent's neighborhood.
         @return a pointer to agent's neighborhood.
      */
      neighborhood* getNeighborhood() const;

      /** 
         Method that returns the agent's core.
         @return a pointer to agent's core.
      */
      core* getCore() const;

      /** 
         Method that returns the agent's phases.
         @return agent's phases.
      */
      vector<phase*> getPhases() const;

      /** 
         Method that returns the agent's mailbox.
         @return a pointer to agent's mailbox.
      */
      deque<message>* getPointerToInBox();

      /** 
         Method that returns the agent's mailbox.
         @return agent's mailbox.
      */
      deque<message> getInBox() const;

      /** 
         Method that returns the agent's message to be delivered.
         @return a pointer to agent's message.
      */
      message* getPointerToMessage();

      /** 
         Method that returns the agent's message.
         @return agent's message.
      */
      message getMessage() const;

      /** 
         Method that sets the agent's id.
         @param agent's id.
      */
      void setId(const idAgentType);

      /** 
         Method that sets the agent's state.
         @param agent's state.
      */
      void setActive(const bool);

      /** 
         Method that sets the agent's neighborhood.
         @param a pointer to agent's neighborhood.
      */
      void setNeighborhood(neighborhood*);

      /** 
         Method that sets the agent's core.
         @param a pointer to agent's core.
      */
      void setCore(core*);
      
      /** 
         Method that sets the agent's mailbox.
         @param agent's mailbox.
      */
      void setInBox(const deque<message>);

      /** 
         Method that sets the agent's phases.
         @param agent's phases.
      */
      void setPhases(const vector<phase*>);

      /** 
         Method that sets the agent's message to be delivered.
         @param agent's message.
      */
      void setMessage(const message);
};

agent::agent()
{ 
   this->active = true;
   this->id = 0;
   this->neighborhoodList = NULL;
   this->agentCore = NULL;
}

agent::~agent() 
{
   delete(this->agentCore);
   delete(this->neighborhoodList);
}

agent::agent(const idAgentType id, core *agentCore, 
             const deque<message> inBox, neighborhood *neighborhoodList, 
             const vector<phase*> phases)
{
   this->id = id;
   this->agentCore = agentCore;
   this->active = true;
   this->inBox.setInBox(inBox);
   this->neighborhoodList = neighborhoodList;
   this->phases = phases;
}

idAgentType agent::getId() const
{
   return this->id;
}

core* agent::getCore() const
{
   return this->agentCore;
}

bool agent::isActive() const
{
   return this->active;
}

deque<message> agent::getInBox() const
{
   return this->inBox.getInBox();
}

message* agent::getPointerToMessage()
{
   return &(this->msg);
}

deque<message>* agent::getPointerToInBox()
{
   return this->inBox.getPointerToInBox();
}

neighborhood* agent::getNeighborhood() const
{
   return this->neighborhoodList;
}

vector<phase*> agent::getPhases() const
{
   return this->phases;
}

message agent::getMessage() const
{
   return this->msg;
}

void agent::setId(const idAgentType id)
{
   this->id = id;
}

void agent::setCore(core* agentCore)
{
   this->agentCore = agentCore;
}

void agent::setActive(const bool active)
{
   this->active = active;
}

void agent::setInBox(const deque<message> inBox)
{
   this->inBox.setInBox(inBox);
}

void agent::setNeighborhood(neighborhood* neighborhoodList)
{
   this->neighborhoodList = neighborhoodList;
}

void agent::setPhases(const vector<phase*> phases)
{
   this->phases = phases;
}

void agent::setMessage(const message msg)
{
   this->msg = msg;
}

#endif
