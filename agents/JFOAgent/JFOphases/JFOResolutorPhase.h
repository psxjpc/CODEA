/** 
   @class JFOResolutorPhase
  
   @brief Carries out the Resolutor Phase of a JFO Agent.

   This class is designed to carry out solving related operations.
   While the JFO agent's core holds all the atomic operations (methods)
   this agent is able to perform. This class acts as a clock that
   put all those mechanisms working together. Note that all these
   is still not related to the problem is going to be solved.
   This class does not depend on the problem the agents are going
   to tackle.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef JFORESOLUTORPHASE_H
#define JFORESOLUTORPHASE_H

#include <iostream>
#include <vector>
#include <string>

#include "../../../core/agent.h"
#include "../../../core/codeaParameters.h"
#include "../../../core/header.h"
#include "../../../core/phase.h"

#include "../../../misc/chrono.h"
#include "../../../misc/MersenneTwister.h"

#include "../../../libs/funcLibrary.h"

#include "../JFOAgent.h"


class JFOResolutorPhase : public phase
{
   private:

      /**
         Initial Solution - Benchmarking purposes
      */
      multiObjectiveSolution* initialSolution;

      /**
         Solution is going to act as the attractor. This is used to 
         be assigned with the best of the neighborhood depending on
         the received messages.
      */
      multiObjectiveSolution* attractor;

      /**
         JFOParameters. Pointers to the parameters described in the
         class JFOAgent.
      */
      JFOParameters *c1, *c2, *c3, *c4;
 
      /**
         Vector for statistical purposes. This vector of counters 
         scores positevely when an type of move improve a current
         solution.
      */
      std::vector<unsigned> movementScore;

      /**
         Vector for statistical purposes. This vector of counters 
         enumerates the times a type of move is performed.
      */
      std::vector<unsigned> movementTry;

      /**
         Variable for statistical purposes. This variable holds 
         the score of the agent. This score depends on how many
         times this agent has improved the current solution.
      */
      unsigned ownScore;

      /**
         This counter enumerates how many times this phase has
         been triggered.
      */
      unsigned numberOfIterations;

      unsigned totalNumberOfIterations;

   protected:
      /**
         Method tha implements operations related to initialization.
      */
      void prePhase(agent*, std::vector<agent*>*);

      /**
         It accomplishes all the steps related to the algorithm 
         specified in the JFO.
      */
      void core(agent*, std::vector<agent*>*);

      /**
         Method that implements operations related to the update
         of parameters.
      */
      void postPhase(agent*, std::vector<agent*>*);

      /**
         Method that gets the attractor totalNumberOfIterationsfrom the mailbox.
         It compares all the solutions in the mailbox and
         returns the best one.
         @param agent* is a pointer to the agent we want 
         to check out the mailbox of.
         @returns the solution that is going to act as
         the attractor.
      */
      multiObjectiveSolution* getAttractorFromInBox(agent*);

      multiObjectiveSolution* getAttractorFromInBox_(agent*);

   public:
      /**
         Default constructor. It initializes all the parameters.
      */
      JFOResolutorPhase();

      /**
         Alternative constructor. It initializes all the parameters
         using the parameters given.
         @param JFOParameters* is a poninter to c1.
         @param JFOParameters* is a poninter to c2
         @param JFOParameters* is a poninter to c3.
         @param JFOParameters* is a poninter to c4.
      */
      JFOResolutorPhase(JFOParameters*, JFOParameters*, JFOParameters*, JFOParameters*);

      /**
         Default destructor. It does nothing.
      */
      ~JFOResolutorPhase() { };

};

JFOResolutorPhase::JFOResolutorPhase() 
{
  
   this->attractor = NULL;
   this->movementScore.resize(4, 0);
   this->movementTry.resize(4, 0);
   this->numberOfIterations = 0;
   this->ownScore = 0;
}

JFOResolutorPhase::JFOResolutorPhase(JFOParameters* c1, JFOParameters* c2, JFOParameters* c3, JFOParameters* c4)
{
   this->attractor = NULL;
   this->movementScore.resize(4, 0);
   this->movementTry.resize(4, 0);
   this->c1 = c1;
   this->c2 = c2;
   this->c3 = c3;
   this->c4 = c4;
   this->numberOfIterations = 0;

   // DEBUG Purposes
   this->totalNumberOfIterations = 5000;

   this->ownScore = 0;
}

// Sub-Phases

void JFOResolutorPhase::prePhase(agent* currentAgent, std::vector<agent*>* team) 
{ 
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());
   assert(superFrog->getCurrentSolution() != NULL);

   // First iteration: This condition should not happen after this iteration
   if (superFrog->getBestSolution()->getNumberOfObjectives() == 0)
      superFrog->updateBestSolution(superFrog->getCurrentSolution());

   if (superFrog->getBestOwnSolution() == NULL)
      superFrog->setBestOwnSolution(superFrog->getCurrentSolution()->clone());

   // Adaptative JFO 
   if (isInside((double)this->numberOfIterations, (double)0, (double)(0.03 * this->totalNumberOfIterations)))
      superFrog->setCoefficients(0.10, 0.30, 0.30, 0.30);
   else if (isInside((double)this->numberOfIterations, (double)(0.03 * this->totalNumberOfIterations),(double)(0.10 * this->totalNumberOfIterations)))
      superFrog->setCoefficients(0.25, 0.25, 0.25, 0.25);
   else if (isInside((double)this->numberOfIterations, (double)(0.10 * this->totalNumberOfIterations), (double)(0.20 * this->totalNumberOfIterations)))
      superFrog->setCoefficients(0.40, 0.20, 0.20, 0.20);
   else if (isInside((double)this->numberOfIterations, (double)(0.20 * this->totalNumberOfIterations), (double)1))
      superFrog->setCoefficients(0.75, 0.05, 0.05, 0.05);

}

multiObjectiveSolution* JFOResolutorPhase::getAttractorFromInBox_(agent* currentAgent)
{
   // Extension:
   // 1) We are going to look for the worst objective we have.
   // 2) We will choose the solution with such that this objective is the best as the atractor
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());
   multiObjectiveSolution* xi = superFrog->getCurrentSolution();
   const multiObjectiveProblem* const MOP = currentAgent->getCore()->getProblem();

   // Normalization
   std::vector<double> values;
   for (size_t i = 0; i < xi->getObjectives().size(); i++)
      values.push_back(xi->getObjectives()[i] / initialSolution->getObjectives()[i]);

   std::vector<bool> valuesBool;
   for (size_t i = 0; i < xi->getObjectives().size(); i++)
      if (i != 0)
         valuesBool.push_back(MOP->getProblems()[i]->isComparable());
      else
         valuesBool.push_back(false);

   unsigned objectiveCandidate = basic::max(values, valuesBool);

   // We'll loop over the mailbox looking for a solution to mix our current one with.
   multiObjectiveSolution* incomingSolution = NULL;
   double candidate = INFd;
   this->attractor = NULL;
   for (size_t i = 0; i < currentAgent->getInBox().size(); i++)
   {
      incomingSolution = boost::any_cast<multiObjectiveSolution*> ((currentAgent->getInBox())[i][1].getObject());
      if (this->attractor == NULL || incomingSolution->getObjectives()[objectiveCandidate] < candidate)
      {
         candidate = incomingSolution->getObjectives()[objectiveCandidate];
         this->attractor = incomingSolution;
      }
   }
   return this->attractor;
}

multiObjectiveSolution* JFOResolutorPhase::getAttractorFromInBox(agent* currentAgent)
{
   // We'll loop over the mailbox looking for a solution to mix our current one with.

   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());
   boost::shared_ptr<multiObjectiveSolution> incomingSolution;
   this->attractor = NULL;
   agent* sender = NULL;
   // We will be looking for the best one (non-dominated solution). If we are not
   //   able to find it, we will return the first one.

   for (size_t i = 0; i < currentAgent->getInBox().size(); i++)
   {
      incomingSolution = boost::any_cast<boost::shared_ptr<multiObjectiveSolution> > ((currentAgent->getInBox())[i][1].getObject());
      sender = boost::any_cast<agent*> ((currentAgent->getInBox())[i][0].getObject());

      if (this->attractor == NULL || superFrog->getProblem()->firstSolutionIsBetter(incomingSolution.get(), attractor).isTrue())
         this->attractor = incomingSolution.get();

   }

   return this->attractor;
}

void JFOResolutorPhase::core(agent* currentAgent, std::vector<agent*>* team)
{
   chrono* myChrono = chrono::instance();
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());
   codeaParameters* neuralItem = codeaParameters::instance();
   MTRand ranGenerator;
   bool modified = 0;
   double randomNumber = -1.0;


   // Current Position
   multiObjectiveSolution* xi = superFrog->getCurrentSolution();
   // Best Position found by the particle
   multiObjectiveSolution* bi = superFrog->getBestOwnSolution(); 
   // Best Position found by the swarm
   multiObjectiveSolution* g  = superFrog->getBestSolution();
   // Best Position found by its neighborhood in the current interation
   multiObjectiveSolution* gi = NULL;

   // Debug purposes only
   /*
   std::cout << "xi:" << xi->toString() << std::endl;
   std::cout << "bi:" << bi->toString() << std::endl;
   if (gi != NULL)
      std::cout << "gi:" << gi->toString() << std::endl;
   if (g != NULL)
      std::cout << "g:"  <<  g->toString() << std::endl;
   */

   // Next Position
   multiObjectiveSolution* ni(xi);
 

   std::string target = "";

   if (currentAgent->getId() == 0 && this->numberOfIterations == 0)
      std::cout << myChrono->getSeconds() << " " << this->numberOfIterations << " " << g->toString() << std::endl;

   const multiObjectiveProblem* const MOP = currentAgent->getCore()->getProblem();
   unsigned movementType = -1;


   // Debug
   /*
   std::cout << "Agent[" << currentAgent->getId() << std::endl;
   std::cout << "ci: ["  << superFrog->getCurrentSolution() << "]: "<< superFrog->getCurrentSolution()->toString() << std::endl;
   std::cout << "bi: ["  << bi << "]: " << bi->toString() << std::endl;
   std::cin.get();
   */

   randomNumber = neuralItem->getRandomNumber()->rand();
   if (isInside(randomNumber, 0.0, *c1)) // inertia
   {
      superFrog->inertialMovement(xi, ni, target);
      movementType = 0;
      movementTry[movementType] += 1;
      modified = true;
   }
   else if (isInside(randomNumber, *c1, *c1 + *c2)) // cognitive
   {
      gi = JFOResolutorPhase::getAttractorFromInBox(currentAgent);
      if (gi != NULL && gi != bi)
      {
         superFrog->cognitiveMovement(xi, gi, ni);
         movementType = 1;
         movementTry[movementType] += 1;
         modified = true; 
      }
   }
   else if (isInside(randomNumber, *c1 + *c2, *c1 + *c2 + *c3)) // local
   {
      if (bi != xi)
      {
         superFrog->localMovement(xi, bi, ni);
         movementType = 2;
         movementTry[movementType] += 1;
         modified = true;
      }
   }
   else if (isInside(randomNumber, *c1 + *c2 + *c3, 1.0)) // social
   {
      if (g != xi)
      {
         superFrog->socialMovement(xi, g, ni);
         movementType = 3;
         movementTry[movementType] += 1;
         modified = true;
      }
   }


   // If the currentSolution was modified 
   if (modified)
   {
      superFrog->localSearchMethod(ni, target);
      superFrog->getProblem()->evaluate(ni);

      // Update of solutions
      if (MOP->firstSolutionIsBetter(ni, bi).isNullTrue())
      {
         movementScore[movementType] += 1;
         superFrog->updateBestOwnSolution(ni);
         this->ownScore++;
      
         if (MOP->firstSolutionIsBetter(ni, g, "<global>").isNullTrue())
         {
            this->ownScore++;
            superFrog->updateBestSolution(ni);
            movementScore[movementType] += 1;
         
            // Let's output something

            //std::cout << "Score: " << movementScore << std::endl;
            //std::cout << "Tries: " << movementTry << std::endl;
            //std::cout << (*g).toString() << std::endl;

            // We will use an extra solution just for benchmark purposes
            //  This will be stored in codeaParameters.
            if (MOP->firstSolutionIsBetter(g, neuralItem->getGenericSolution()).isTrue())
            {
               neuralItem->setGenericSolution(g);
               std::cout << myChrono->getSeconds() << " ";
               std::cout << this->numberOfIterations << " ";
               std::cout << (*g).toString() << std::endl;
            }
         }
      }
      superFrog->setCurrentSolution(ni);
   }

}

void JFOResolutorPhase::postPhase(agent* currentAgent, std::vector<agent*>* team)
{
   // If you clear the mailBox before, you may get a Segmentation Fault because 
   //    the attractor would be pointing to nowhere.
   currentAgent->getPointerToInBox()->clear();
   this->numberOfIterations++;
}


#endif
