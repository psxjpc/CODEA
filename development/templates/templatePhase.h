/** 
   @class templatePhase
  
   @brief Implements a generic communication phase.

   This is an example class that inherits from phase. To include
   this phase in your code, just modify "templatePhase" in this
   class using the name of your class (you can use the 'find & replace'
   feature that most editors have. You also have to change:

   #ifndef TEMPLATE_PHASE_H
   #define TEMPLATE_PHASE_H
 
   using the name of your class. 

   Once you've changed the phase, you can simply save this file
   into the folder "phases" of the agent you are working with.

   @note The path of the needed files to have this class working are
   supposing you will save this file in:
   <PATH_OF_CODEA>/agents/your_Agent/phases/ 

   @note You may also need to include the reference to your agent.
   #include "../youAgent.h"

   @note You should delete all this comments in your class
   and include yours with a decription of this phase.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2009
*/

#ifndef TEMPLATE_PHASE_H
#define TEMPLATE_PHASE_H

#include <vector> 

#include "../../../core/agent.h"
#include "../../../core/phase.h"

class templatePhase : public phase
{
   private:
      // Here you can write the data you need to use in the class

   protected:

      /**
         Method that implements the inherited virtual method from phase.
         It is intended to perform operations related to the initialization.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void prePhase(agent*, std::vector<agent*>);

      /**
         Method that implements the inherited virtual method from phase.
         It is intended to implement the core of what this phase was designed for.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void core(agent*, std::vector<agent*>);

      /**
         Method that implements the inherited virtual method from phase.
         It is inteded to hold update operations.
         @param agent* is a pointer to the agent is going to perform this phase.
         @param std::vector<agent*>* is a pointer to the group of agents. 
      */
      void postPhase(agent*, std::vector<agent*>);

   public:
      /**
         Default constructor.
      */
      templatePhase();

      /**
         Default destructor.
      */
      ~templatePhase();

templatePhase::templatePhase()
{
   // Write here the code related to the contruction of the object.
}

templatePhase::~templatePhase()
{
   // Write here the code related to the destruction of the object.
}


void templatePhase::prePhase(agent *currentAgent, std::vector<agent*> team)
{
   // Write here the code related to the initilization operations of the phase.
}

void templatePhase::core(agent *currentAgent, std::vector<agent*> team)
{
   // Write here the code related to the operations of the phase.
}

void templatePhase::postPhase(agent *currentAgent, std::vector<agent*> team)
{
   // Write here the code related to the update operations of the phase.
}

#endif
