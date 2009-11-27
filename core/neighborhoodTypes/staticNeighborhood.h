/** 
   @class staticNeighborhood
  
   @brief To work with static neighborhoods.

   This class inherits from neighborhood to deal with static communication
   topologies. The idea is to create for each agent a vector of neihgbors.
   This vector is to be assigned to the vector in the neihgborhood class using 
   the method setAgents contained in the same class. Thus, this clas will
   implement the virtual method getNeighborhood that will simply return
   the pointer to the vector contained in neihgborhood class.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef STATICNEIGHBORHOOD_H
#define STATICNEIGHBORHOOD_H

#include <vector>

#include "../agent.h"
#include "../header.h"
#include "../neighborhood.h"
#include "../multiObjectiveSolution.h"

class staticNeighborhood : public neighborhood
{
   private:

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      staticNeighborhood() { };

      /** 
         Standard constructor.
         @param vector<agent*>* const is the vector that contains the agents
         this one is related to.
         @return a static topology with the given data.
      */
      staticNeighborhood(vector<agent*>* const);

      /**
         Default destructor. It does nothing.
      */
      ~staticNeighborhood() { };

      /** 
         Method that returns the list of recipients the agent is going to send its message
         @return a pointer to the vector of recipients.
      */
      vector<agent*>* const list() const;
};

staticNeighborhood::staticNeighborhood(vector<agent*>* neighbours)
{
   this->setAgents(neighbours);
}

vector<agent*>* const staticNeighborhood::list() const
{
   return getAgents();
}

#endif
