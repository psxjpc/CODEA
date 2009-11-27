/*! \mainpage CODEA: COoperative DEcentralized Architecture
 
  \section intro_sec Introduction

   CODEA is a library of classes to experiment with agents who cooperate to solve problems.
   This cooperation is not supervised by any entity but it's carried out by the group of 
   agents whithin the system. The main idea is to have a system in which each agent is free
   to perform its own operations, to send the information it wants to share with a list
   of agents it wants to communicate with.

   CODEA was conceived to explore different strategies of cooperation with metaheuristics.
   It stands for COoperative Decentralized Architecture because the agents whithin the 
   system are not under any control or limitation. We started with the idea of creating
   something simple, flexible and fast to enhance the agents to come out with an intelligent
   behabour. To achieve this, we designed CODEA by modules that will be explained later.

   The following diagram shows how CODEA works:
   
  \image html "GDiagram.jpg"
 
   As it can be seen at the top of the image, there is an elemnent called system. This element
   contains a number of agents and a couple of properties. Even if it holds the group of agents
   who are going to work whithin it, this element doesn't know how the agents are going to work,
   nor the relation among them. This element is intended to store general propierties as the 
   up time and the iteration in which the best solution was found (elpased time, iteration), 
   the best solution found by the agents (they must update it), and a criterion to stop the
   execution of main-loop that keep the agent running operations (phases). From the implementation
   point of view, this element behaviour is represented in the class ssystem.

   The next element in the figure is the agent element/cell. This cell shows the sub-elements
   an agent holds. We must hightlight the existence of three components in it: neighborhood,
   core and phase. These components give agents especial abilities to share information
   (neighborhood), hold the information to solve problems (core), and the way to carry out their
   operations (phase). Beside these modules, an agents has a number of parameters to control
   its state, id, etc. Plus a number of data-containers as a mailbox for incoming messages 
   and a container to set the message that packs the information to be shared. 
   
   The neighborhood sub-component is a module that controls the list of recipients who are going to
   recieve the message to be sent in each iteration. The main purpose is to provide the ability
   of managing different communication topologies in real time depending on the state of the system.
   This abstract layer will let us to design and implement all kind of topologies.

   Another important sub-element in the structure of an agent is the phase component. An agent
   runs its operations by using phases. Every agent has a number of phases that are executed 
   repeteadly until a system stop criterion is met. There is not limitation in the number of
   phases or what they do, but they tend to be used to invoke the operations that are specified
   in the agent's core. The picture shows this as the link between the phases and the PSOAgent's
   methods.

   The third sub-module is the core component. This module is intended to store the problem is
   going to be solved and its objectives, the solution and how the agent operates to solve it.
   Inside the cell that represents the agent's core, there is a number of attributes:
   best solution (the best solution achieved by the agent), elapsed time and iteration (that 
   it took the agent to get that solution) and a stop criterion that enables agents to have
   their own loop-controllers. Next to them, the two main sub-components are: multi-objective
   solution and multi-objective problem. The first one has two modules: score criterion and 
   problems. Score criterion is designed to support the ranking of multi-objective solutions
   using different criterions implemented at the lowest level. In the picture there is the
   aggregation approach and the Pareto Front pending of this module. Next to this, there is 
   the problem component whithing the multi-objective problem cell. It stores a number of 
   objectives that represents different evaluations of the problem the agents are dealing with.
   All this objective has very simple attributes, but the most important on, from the CODEA
   point of view, is 'isMax'. This specify whether the objective is to be minimized or 
   maximized. This is a key point because the score criterion need this information for 
   ranking the solutions. These solutions consist of a set of objective that represent the 
   evaluation of the current solution in the different problems described in problems.

  \section install_sec Installation
 
   CODEA has be entirely programmed using C++
   and an object of the boost library to store the contents of messages that agents
   send. Lately we are approching to the use of QT Libraries to output graphical information,
   but CODEA is not directly linked to it, what means that it's not necessary to have QT libraries
   installed to work with it.

  \subsection step1 Step 1: Get the source.
   
   Not available yet ;) 
  
  \subsection step2 Step 2: Copy the source in a working folder.
  \subsection step3 Step 3: Try to compile the source.
  

*/

/** 
   @class ssystem
  
   @brief This is the top class in the CODEA's class hierarchy.

   This class contains propperties and methods to manage CODEA at the
   highest level. It stores the agents but not its relationships due
   to the nature of a decentralized system. Moreover, it has the main
   loops the system goes through and the condition to stop it. 
   With it, a set of attributes control those variables that changes
   while the system is running.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "agent.h"
#include "multiObjectiveSolution.h"
#include "systemStopCriterion.h"

class agent;

class ssystem
{
   private:
      /**
         List of agents.
      */
      std::vector<agent*> agents;

      /**
         Best solutions found. Pointer to the best solution reached by the agents so far.
      */
      multiObjectiveSolution* bestSolution;

      /**
         Current iteration. It stores the current iteration of the system's main loop.
      */
      iterationType iteration;

      /**
         Iteration in which the best solution was achieved.
      */
      iterationType iterationOfBestSolution;

      /**
         Time in which the best solution was achieved.
      */
      double elapsedTimeOfBestSolution;

      /**
         Strop controller. Object that controls the halt of the main loop.         
      */
      systemStopCriterion *stopController;

   protected:    

      /**
         Method that resets the iteration counter.
      */
      void resetIteration();

      /**
         Method that adds one to the iteration counter.
      */
      void increaseIteration();

      /**
         Virtual method that is intented to perform initialization operations before the main loop
      */
      virtual void preOperationsSystem() = 0;

      /**
         Virtual method that is intented to perform initialization operations whithin the loop,
         these operations will be repeated until the stop criterion is met.
      */
      virtual void prePhase() = 0;

      /**
         Virtual method that is intented to perform the important set of instructions the system
         has been designed for.
      */
      virtual void phase() = 0;

      /**
         Virtual method that is intented to perform updating operations whithin the main loop,
         these operation will be repeated until the stop criterion is met.
      */
      virtual void postPhase() = 0;

      /**
         Virtual method that is intented to perform updating operations after the stop criterion
         is met.
      */
      virtual void postOperationsSystem() = 0;
 
   public:

      /**
         Default constructor. It does nothing.
      */
      ssystem();

      /**
         Default destructor. It frees all the memory used by this class.
      */
      ~ssystem();

      /** 
         Method that returns the group of agent the system has.
         @return the vector of agents.
      */
      std::vector<agent*> getAgents();

      /** 
         Method that returns the group of agent the system has.
         @return a pointer to vector of agents.
      */
      std::vector<agent*>* getPointerToAgents();

      /** 
         Method that returns the best solution reached so far.
         @return a pointer to the best solution.
      */
      multiObjectiveSolution* getBestSolution();

      /** 
         Method that returns the times the main loop has been repeated
         @return the current iteration of the main loop.
      */
      iterationType getIteration();     

      /** 
         Method that returns the iteration in which the best solution was found.
         @return the iteration of best solution.
      */
      iterationType getIterationOfBestSolution();

      /** 
         Method that returns the time in which the best  solution was found.
         @return the time of best solution.
      */
      double getElapsedTimeOfBestSolution();

      /** 
         Method that returns the object that controls whether the main loop is to be repeated.
         @return a pointer to the stop controller.
      */
      systemStopCriterion* getStopCriterion();

      /** 
         Method that sets the vector of agents.
         @param std::vector<agent*> is the list of agents.
      */
      void setAgents(const std::vector<agent*>);

      /** 
         Method that sets the best solution achieved whithin the system.
         @param multiObjectiveSolution* is the pointer to the best solution.
      */
      void setBestSolution(multiObjectiveSolution*);

      /** 
         Method that sets the current iteration.
         @param const iterationType is the current iteration to be set.
      */
      void setIteration(const iterationType);

      /** 
         Method that sets the iteration of the best solution.
         @param const iterationType is the iteration to be set.
      */
      void setIterationOfBestSolution(const iterationType);

      /** 
         Method that sets the time in which the best solution was found.
         @param const double is the time to be set.
      */
      void setElapsedTimeOfBestSolution(const double);

      /** 
         Method that sets the stop controller.
         @param systemStopCriterion* is a pointer to the stop controller.
      */
      void setStopCriterion(systemStopCriterion*);

      /** 
         Method that contains the calls for the system to perform all its operations.
         It also contains the main loop whithin the agents' phases that are invoked until
         a stop criterion is met.
      */
      void start();
};

ssystem::ssystem()
{
   this->bestSolution = NULL;
   this->iteration = 0;
   this->iterationOfBestSolution = 0;
   this->elapsedTimeOfBestSolution = 0;
   this->stopController = NULL;
}

ssystem::~ssystem()
{
   delete(this->bestSolution); 
   delete(this->stopController);
   for (unsigned i = 0; i < agents.size(); i++)
      delete(this->agents[i]);
}

inline std::vector<agent*> ssystem::getAgents()
{
   return this->agents;
}

inline std::vector<agent*>* ssystem::getPointerToAgents()
{
   return &(this->agents);
}

inline multiObjectiveSolution* ssystem::getBestSolution()
{
   return this->bestSolution;
}

inline iterationType ssystem::getIteration()
{
   return this->iteration;
}

inline iterationType ssystem::getIterationOfBestSolution()
{
   return this->iterationOfBestSolution;
}

inline double ssystem::getElapsedTimeOfBestSolution()
{
   return this->elapsedTimeOfBestSolution;
}

inline systemStopCriterion* ssystem::getStopCriterion()
{
   return this->stopController;
}

inline void ssystem::setAgents(const std::vector<agent*> agents)
{
   this->agents = agents;
}

inline void ssystem::setBestSolution(multiObjectiveSolution *bestSolution)
{
   this->bestSolution = bestSolution;
}

inline void ssystem::setIteration(const iterationType iteration)
{
   this->iteration = iteration;
}

inline void ssystem::setIterationOfBestSolution(const iterationType iterationOfBestSolution)
{
   this->iterationOfBestSolution = iterationOfBestSolution;
}

inline void ssystem::setElapsedTimeOfBestSolution(const double elapsedTimeOfBestSolution)
{
   this->elapsedTimeOfBestSolution = elapsedTimeOfBestSolution;
}

inline void ssystem::setStopCriterion(systemStopCriterion* stopController)
{
   this->stopController = stopController;
}

inline void ssystem::resetIteration()
{
   this->iteration = 0;
}

inline void ssystem::increaseIteration()
{
   this->iteration++;
}

inline void ssystem::start()
{
   preOperationsSystem();
   do
   {
      prePhase();
      phase();      postPhase();
   }
   while (!(this->getStopCriterion())->stop(this));
   postOperationsSystem();
}

#endif
