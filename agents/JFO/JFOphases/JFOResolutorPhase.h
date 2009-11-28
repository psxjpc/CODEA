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

#include "../../../core/MOScoreCriterionTypes/basicParetoFrontMOScoreCriterion.h"
#include "../../../core/MOScoreCriterionTypes/lexicographicMOScoreCriterion.h"
#include "../../../core/MOScoreCriterionTypes/dynamicLexMOScoreCriterion.h"

#include "../../../misc/MersenneTwister.h"

#include "../../../libs/fileLock.h"
#include "../../../libs/funcLibrary.h"

#include "../JFOAgent.h"


class JFOResolutorPhase : public phase
{
   private:

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

      unsigned maxTimeWindowViolations;

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
         Method that gets the attractor from the mailbox.
         It compares all the solutions in the mailbox and
         returns the best one.
         @param agent* is a pointer to the agent we want 
         to check out the mailbox of.
         @returns the solution that is going to act as
         the attractor.
      */
      multiObjectiveSolution* getAttractorFromInBox(agent*);

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
   attractor = NULL;
   movementScore.resize(4, 0);
   movementTry.resize(4, 0);
   this->numberOfIterations = 0;
   this->ownScore = 0;
   
   this->maxTimeWindowViolations = 100;
}

JFOResolutorPhase::JFOResolutorPhase(JFOParameters* c1, JFOParameters* c2, JFOParameters* c3, JFOParameters* c4)
{
   attractor = NULL;
   movementScore.resize(4, 0);
   movementTry.resize(4, 0);
   this->c1 = c1;
   this->c2 = c2;
   this->c3 = c3;
   this->c4 = c4;
   this->numberOfIterations = 0;
   this->ownScore = 0;
   this->maxTimeWindowViolations = 100;
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
      superFrog->setBestOwnSolution(superFrog->getCurrentSolution());
}


multiObjectiveSolution* JFOResolutorPhase::getAttractorFromInBox(agent* currentAgent)
{
   codeaParameters* neuralItem = codeaParameters::instance();
   // We'll loop over the mailbox looking for a solution to mix our current one with.

   // In case the mailBox is empty, we will rapidly exit
   if (currentAgent->getInBox().size() == 0)
      return NULL;

   const multiObjectiveProblem* const MOP = currentAgent->getCore()->getProblem();
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());

   // Criterion to rank the solution from the inbox

   // Reseting parameters
   multiObjectiveSolution* incomingSolution = NULL;
   this->attractor = NULL;


   abstractMOScoreCriterion* scoreCriterion; 
   unsigned rankingType = neuralItem->rankingScheme;
   if (neuralItem->rankingScheme == 0) // Pareto
   {
      //std::cout << "Pareto" << std::endl;
      basicParetoFrontMOScoreCriterion scoreCriterion;

      for (size_t i = 0; i < currentAgent->getInBox().size(); i++)
      {
         incomingSolution = boost::any_cast<multiObjectiveSolution*> ((currentAgent->getInBox())[i][1].getObject());

         if (this->attractor == NULL || (scoreCriterion.firstSolutionIsBetter(incomingSolution, this->attractor, MOP->getProblems()).isTrue()), "kkj")
            this->attractor = incomingSolution;
      }

   }
   else if (neuralItem->rankingScheme == 1) // Lex
   {
      //std::cout << "Lex" << std::endl;
      lexicographicMOScoreCriterion scoreCriterion;   

      for (size_t i = 0; i < currentAgent->getInBox().size(); i++)
      {
         incomingSolution = boost::any_cast<multiObjectiveSolution*> ((currentAgent->getInBox())[i][1].getObject());

         if (this->attractor == NULL || (scoreCriterion.firstSolutionIsBetter(incomingSolution, this->attractor, MOP->getProblems()).isTrue()), "kkj")
            this->attractor = incomingSolution;
      }

   }
   else if (neuralItem->rankingScheme == 2) // DynLex
   {
      //std::cout << "Dynlex " << std::endl;
      dynamicLexMOScoreCriterion scoreCriterion(superFrog->getCurrentSolution()->getNumberOfObjectives());

      for (size_t i = 0; i < currentAgent->getInBox().size(); i++)
      {
         incomingSolution = boost::any_cast<multiObjectiveSolution*> ((currentAgent->getInBox())[i][1].getObject());

         if (this->attractor == NULL || (scoreCriterion.firstSolutionIsBetter(incomingSolution, this->attractor, MOP->getProblems()).isTrue()), "kkj")
            this->attractor = incomingSolution;
      }

   }
   else
   {
      std::cout << "Ranking scheme not known" << std::endl;
      exit(1);
   }



 
   return this->attractor;
}

void JFOResolutorPhase::core(agent* currentAgent, std::vector<agent*>* team)
{
   JFOAgent* superFrog = static_cast<JFOAgent*>(currentAgent->getCore());

   const multiObjectiveProblem* const MOP = currentAgent->getCore()->getProblem();
   codeaParameters* neuralItem = codeaParameters::instance();
   double randomNumber = neuralItem->getRandomNumber()->rand();
   unsigned movementType = -1;
   std::string target = "";

   // Current Position
   multiObjectiveSolution* xi = superFrog->getCurrentSolution();
   // Best Position found by the particle
   multiObjectiveSolution* bi = superFrog->getBestOwnSolution(); 
   // Best Position found by the swarm
   multiObjectiveSolution* g  = superFrog->getBestSolution();
   // Best Position found by its neighborhood in the current interation
   multiObjectiveSolution* gi = NULL;

   //if (currentAgent->getId() == 0)
   //   std::cout << this->numberOfIterations << g->toString() << std::endl;

   // Next Position
   multiObjectiveSolution* ni(xi);

   // Type of movements
   if (isInside(randomNumber, 0.0, *c1)) // inertia
   {
      superFrog->inertialMovement(xi, ni, target);
      movementType = 0;
      movementTry[movementType] += 1;
   }
   else if (isInside(randomNumber, *c1, *c1 + *c2)) // cognitive
   {
      gi = JFOResolutorPhase::getAttractorFromInBox(currentAgent);

      if (gi != NULL && gi != bi)
      {
         superFrog->cognitiveMovement(xi, gi, ni);
         movementType = 1;
         movementTry[movementType] += 1; 
      }
      else
      {
         superFrog->inertialMovement(xi, ni, target);
         movementType = 0;
         movementTry[movementType] += 1;
      }
   }
   else if (isInside(randomNumber, *c1 + *c2, *c1 + *c2 + *c3)) // local
   {
      if (bi != xi)
      {
         superFrog->localMovement(xi, bi, ni);
         movementType = 2;
         movementTry[movementType] += 1;
      }
      else
      {
         superFrog->inertialMovement(xi, ni, target);
         movementType = 0;
         movementTry[movementType] += 1;
      }
   }
   else if (isInside(randomNumber, *c1 + *c2 + *c3, 1.0)) // social
   {
      if (g != xi)
      {
         superFrog->socialMovement(xi, g, ni);
         movementType = 3;
         movementTry[movementType] += 1;
      }
      else
      {
         superFrog->inertialMovement(xi, ni, target);
         movementType = 0;
         movementTry[movementType] += 1;
      }
   }

   // Update of the current solution

   superFrog->localSearchMethod(ni, target);
   //std::cout << "---------" << std::endl;
   //std::cout << "ni: " << ni->toString() << std::endl; 
   //std::cout << "---------" << std::endl;
   superFrog->getProblem()->evaluate(ni);
   superFrog->setCurrentSolution(ni);
   
   if (MOP->firstSolutionIsBetter(ni, bi, "reset").isTrue())
   {
      movementScore[movementType] += 1;

      superFrog->setBestOwnSolution(ni);
      this->ownScore++;
      // std::cout << this->numberOfIterations << " " << bi->toString() << std::endl;
   }

      // lexicographicMOScoreCriterion lx;

   if ((MOP->firstSolutionIsBetter(ni, g, "reset").isTrue()))
   {
         this->ownScore++;		
         superFrog->updateBestSolution(ni);
         movementScore[movementType] += 1;
         

         // This is for showing results in real time
         //std::string outPutFile = "./outputs/test.out";
         //if (!tryWRString(ni->toString(), outPutFile))
         //   std::cout << "Error Writing : " << outPutFile << std::endl;

         //std::cout << this->numberOfIterations << " " << g->toString() << std::endl;

         // Let's output something
         // std::cout << "Score: " << movementScore << std::endl;
         // std::cout << "Tries: " << movementTry << std::endl;
         // std::cout << g->toString() << std::endl;
                     
         std::cout << this->numberOfIterations << " " << g->toString() << std::endl;
   }
   // Statistical purposes
   std::cout << this->numberOfIterations << " " << ni->toString() << std::endl;
   
}

void JFOResolutorPhase::postPhase(agent* currentAgent, std::vector<agent*>* team)
{
   // If you clear the mailBox before, you may get a Segmentation Fault because 
   //    the attractor would be pointing to nowhere.
   currentAgent->getPointerToInBox()->clear();
   this->numberOfIterations++;
}


#endif
