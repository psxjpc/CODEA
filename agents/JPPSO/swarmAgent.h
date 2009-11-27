#ifndef SWARMVRPAGENT_H
#define SWARMVRPAGENT_H

class swarmVRPAgent : public core
{
   private:
      std::vector<particle> particles;
      multiObjectiveSolution* bestOwnSolution;
      multiObjectiveSolution* bestNeighborSolution;
      multiObjectiveSolution* currentSolution;   
      multiObjectiveSolution* globalSolution;      

   protected:

   public:
      swarmVRPAgent();
      ~swarmVRPAgent();

      // Setters - Pointers
      void setBestOwnSolution(multiObjectiveSolution*);
      void setBestNeighborSolution(multiObjectiveSolution*);
      void setCurrentSolution(multiObjectiveSolution*);
      void setGlobalSolution(multiObjectiveSolution*);

      void updatePosition();
      void updateVelocity();
      PSOPositionType getIndex(routesType, const PSOIdType) const;
      routesType getRoutes() const;
      PSOIdType getIdAt(const unsigned);
      std::vector<PSOIdType> getIdsAt(const unsigned);
};


// Setters - Pointers assigning

inline void swarmVRPAgent::setBestOwnSolution(multiObjectiveSolution* bestOwnSolution)
{
   this->bestOwnSolution = bestOwnSolution;
}

inline void swarmVRPAgent::setBestNeighborSolution(multiObjectiveSolution* bestNeighborSolution)
{
   this->bestNeighborSolution = bestNeighborSolution;
}

inline void swarmVRPAgent::setCurrentSolution(multiObjectiveSolution* currentSolution)
{
   this->currentSolution = currentSolution;
}

inline void swarmVRPAgent::setGlobalSolution(multiObjectiveSolution* globalSolution)
{
   this->globalSolution = globalSolution;
}

/* PROBLEMS:
      - Overlapping
      - Overflow

      This might be solved by ignoring the overflow here 
      and solving it when creating the route.
*/

inline void swarmVRPAgent::updatePosition()
{
   for (size_t i = 0; i < this->particles.size(); i++)
      this->particles[i].setPosition(this->particles[i] + this->particles[i].getVelocity());
}

/* PROBLEMS:
      - We have to take care about how to update the solutions and the routes
      - We have to convert the best solution of the swarm to a route to operate
      -   with it.
*/


inline void swarmVRPAgent::updateVelocity()
{
   neural* neuralItem = neural::instance();
   double r1, r2, r3;
   r1 = neuralItem->getRandomNumber()->rand();
   r2 = neuralItem->getRandomNumber()->rand();
   r3 = neuralItem->getRandomNumber()->rand();
   
   currentPosition = (static_cast<VRPSolution*>(currentSolution))->getRoutes();
   bestOwnPosition = (static_cast<VRPSolution*>(bestOwnSolution))->getRoutes();
   bestNeighborPosition = (static_cast<VRPSolution*>(bestNeighborSolution))->getRoutes();
   globalPosition = (static_cast<VRPSolution*>(globalSolution))->getRoutes();
   
   for (size_t i = 0; i < this->particles.size(); i++)
      this->particles[i].setVelocity(unsigned(
         this->particles[i].getC0() * this->particles[i].getVelocity() + 
         this->particles[i].getC1() * r1 * (getIndex(bestOwnPosition, this->particles[i].getId()) - this->particles[i].getPosition()) +
         this->particles[i].getC2() * r2 * (getIndex(bestNeighborPosition, this->particles[i].getId()) - this->particles[i].getPosition()) +
         this->particles[i].getC3() * r3 * (getIndex(bestGlobalPosition, this->particles[i].getId()) - this->particles[i].getPosition())
      ));
}

inline PSOPositionType swarmVRPAgent::getIndex(routesType routes, const PSOIdType id) const
{
   for (size_t i = 0; i < routes.size(); i++)
      if (routes[i] == id)
         return i; 
   std::cout << "PSOPositionType::getIndex(routesType routes, const PSOIdType) const. id = " << id << std::endl;  
   exit(1);
}

inline routesType swarmVRPAgent::getRoutes() const
{
   routesType routes;
   routesType nodes;
   for (size_t i = 0; i < this->particles.size(); i++)
   {
      nodes = getIdsAt(i);
      for (size_t j = 0; j < nodes.size(); j++)
         routes.push_back(nodes[j]);
      nodes.clear();
   }
   return routes;
}

inline std::vector<PSOIdType> swarmVRPAgent::getIdsAt(const PSOPositionType xi)
{
   std::vector<PSOIdType> aux;
   for (size_t i = 0; i < this->particles.size(); i++)
      if (this->particles[i].getPosition() == xi)
         aux.push_back(particles[i].getId());
   if (aux.size() != 0)
      return aux;
   std::cout << "Exception: PSOIdType swarmVRPAgent::getIdsAt(const PSOPositionType xi). xi = " << xi << std::endl;  
   exit(1);
}

inline PSOIdType swarmVRPAgent::getIdAt(const PSOPositionType xi)
{
   for (size_t i = 0; i < this->particles.size(); i++)
      if (this->particles[i].getPosition() == xi)
         return particles[i].getId();
   std::cout << "Exception: PSOIdType swarmVRPAgent::getIdAt(const PSOPositionType xi). xi = " << xi << std::endl;  
   exit(1);
}

#endif

