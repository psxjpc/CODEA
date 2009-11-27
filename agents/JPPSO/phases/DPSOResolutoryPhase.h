#ifndef DPSORESOLUTORYPHASE_H
#define DPSORESOLUTORYPHASE_H

class DPSOResolutoryPhase : public phase
{
   private:

   protected:
      void prePhase(coMetaheuristic*);
      void core(coMetaheuristic*);
      void postPhase(coMetaheristic*);


   public:
      DPSOResolutoryPhase();
      ~DPSOResolutoryPhase();
};

inline multiObjectiveSolution* DPSOResolutorPhase::updateNeighborSolution(coMetaheuristic* agent)
{
   swarmAgent* superFrog = static_cast<swarmAgent*>(agent->getCore());
   multiObjectiveSolution* incomingSolution = NULL;
   multiObjectiveSolution* gi = superFrog->getNeighborSolution(); 
   for (size_t i = 0; i < agent->getInBox().size(); i++)
   {
      incomingSolution = boost::any_cast<multiObjectiveSolution*> ((agent->getInBox())[i][1].getObject());
      if (gi == NULL || superFrog->getMOProblem()->firstSolutionIsBetter(incomingSolution, gi).isNullTrue())
         gi = incomingSolution;
   } 
}

void DPSOResolutoryPhase::prePhase(coMetaheuristic* agent)
{
   // First, we will update the best Solution whithin the current swarm
   swarmAgent* superFrog = static_cast<swarmAgent*>(agent->getCore());
   updateNeighborSolution(agent);
}

void DPSOResolutoryPhase::core(coMetaheuristic* agent)
{
   swarmAgent* superFrog = static_cast<swarmAgent*>(agent->getCore());

   // Current Position
   multiObjectiveSolution* xi = superFrog->getCurrentSolution();
   // Best Position found by the particle
   multiObjectiveSolution* bi = superFrog->getBestOwnSolution(); 
   // Best Position found by its neighborhood in the current interation
   multiObjectiveSolution* g = superFrog->getGlobalSolution();

   // Update Velocity and Position
   superFrog->updateVelocity();
   superFrog->updatePosition();

   // Get routes and evaluate new position
   (static_cast<VRPSolution*>(xi))->setRoutes(superFrog->getRoutes());
   xi->evalute();


   if (MOP->firstSolutionIsBetter(xi, bi).isNullTrue()) 
   {
      superFrog->setBestOwnSolution(xi);
      
      if (MOP->firstSolutionIsBetter(xi, g, "<global>").isNullTrue())
         superFrog->setGlobalSolution(xi);
   }
}

void DPSOResolutoryPhase::postPhase(coMetaheuristic* agent)
{
   agent->getPointerToInBox()->clear();
}

#endif

