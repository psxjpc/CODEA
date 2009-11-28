/** 
   @class JFOAgent
  
   @brief Establishes the pattern to create JFO based agents.
   
   This class sets a number of virtual methods that mimics the 
   behaviour of a Jumping Frog Optimization Agent. To find more
   information about this, please refer to:

   \code

      \newblock F. Javier Martinez Garcia, Jose A. Moreno Perez.
      \newblock Jumping Frogs Optimization: a new swarm method for discrete optimization.
      \newblock {\em Documentos de Trabajo del DEIOC}. N. 3/2008, Universidad de La Laguna

      \newblock Discrete Particle Swarm Optimization for the p-median problem
      \newblock F.J. Martinez, Jose A. Moreno,
      \newblock {\em MIC 2007, Metaheuristics International Conference} Montreal, Canada, 2007

      \newblock Discrete Particle Swarm Optimization for the minimum labelling Steiner tree problem
      \newblock Consoli S., Moreno-Perez J.A., Darby-Dowman K., Mladenovic N.
      \newblock :{\em Nature Inspired Cooperative Strategies for Optimization (NICSO 2007)} 
      \newblock Vol. 129, Studies in Computational Intelligence, pp. 313-322, 2007   

   \endcode

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef JFOAGENT_H
#define JFOAGENT_H

#include <string>
#include <cmath>

#include "../../core/core.h"
#include "../../core/header.h"
#include "../../core/multiObjectiveSolution.h"
#include "../../core/multiObjectiveProblem.h"

#include "../../misc/MersenneTwister.h"

#define PI 3.1415926

typedef double JFOParameters;

class JFOAgent : public core
{
   private:
      /**
         Likelihood indexes. This are the parameters of the JFO
         uses to decide which move to trigger. The idea is to 
         divide a segment in four sub-segments. Where c1 is the
         amplitude of the first sub-segment, c2 the amplitude 
         of the second one and so on. Plus, each sub-segment is
         related to a type of move. c1 is related to the 
         inertial move, c2 to the cognitive movement, c3 to
         a local movement and c4 to a social movement.

         In order to decide which move to perform, a JFO based 
         agent generates a random number U[0,1]. Then, depending on
         which sub-segment this value falls, a type of move
         is selected.
      */
      JFOParameters c1, c2, c3, c4;

      /**
         Best solution this agent has achieved.
      */
      multiObjectiveSolution* bestOwnSolution;

      /**
         Best solution its neighborhood has achieved.
      */
      multiObjectiveSolution* bestSolutionOfGroup;

   protected:

   public:
      /**
         Default constructor. It initializes some parameters.
      */
      JFOAgent();
      /**
         Default destructor. It does nothing.
      */
      ~JFOAgent();

      /**
         Method that sets the best solution this agent has achieved.
         @param multiObjectiveSolution* is a pointer to the new best solution.
      */
      void setBestOwnSolution(multiObjectiveSolution*);

      /**
         Method that sets the best solution all the agents are pointing to.
         @param multiObjectiveSolution* is a pointer to the new best solution.
      */
      void setBestSolutionOfGroup(multiObjectiveSolution*);

      /**
         Method that returns the best solution achieved by this agent.
         @return a pointer to the best solution it has found.
      */
      multiObjectiveSolution* getBestOwnSolution() const;

      /**
         Method that returns the best solution found by the group.
         @return a pointer to the best solution the group has found.
      */
      multiObjectiveSolution* getBestSolutionOfGroup() const;

      /**
         Method that returns the value amplitude of the first sub-segment.
         @return a pointer to the value of c1.
      */
      JFOParameters* getPointerToC1()  { return &(this->c1); };

      /**
         Method that returns the value ampl3.1415926itude of the second sub-segment.
         @return a pointer to the value of c2.
      */
      JFOParameters* getPointerToC2()  { return &(this->c2); };

      /**
         Method that returns the value amplitude of the third sub-segment.
         @return a pointer to the value of c3.
      */
      JFOParameters* getPointerToC3()  { return &(this->c3); };

      /**
         Method that returns the value amplitude of the fourth sub-segment.
         @return a pointer to the value of c4.
      */
      JFOParameters* getPointerToC4()  { return &(this->c4); };

      /**
         Method that initialize the value of the JFO parameters: c1, c2, c3, c4
      */
      void initializeParameters();

      /**
         Method that updates the value of the JFO parameters: c1, c2, c3, c4
      */
      void updateParameters(unsigned);

      /**
         Virtual method that is intended to implement the JFO's inertial move.
         This movement doesn't require an attractor.
         @param  multiObjectiveSolution* is a pointer to the current solution
         @param  multiObjectiveSolution* is a pointer to the output solution
         @param  const std::string options is a reserved string for parameters
      */
      virtual void inertialMovement( multiObjectiveSolution* currentSolution, 
                                     multiObjectiveSolution* metaSolutionOut,
                                     const std::string options = "") = 0;

      /**
         Virtual method that is intended to implement the JFO's cognitive move.
         The attractor in this case should be the best solution in the neighborhood.
         @param  multiObjectiveSolution* is a pointer to the solution that acts as the follower
         @param  multiObjectiveSolution* is a pointer to the soluiton that asts as the attractor
         @param  multiObjectiveSolution* is a pointer to the output solution
         @param  const std::string options is a reserved string for parameters
      */
      virtual void cognitiveMovement(multiObjectiveSolution* currentSolution, 
                                     multiObjectiveSolution* attractor,
                                     multiObjectiveSolution* metaSolutionOut,
                                     const std::string options = "") = 0;

      /**
         Virtual method that is intended to implement the JFO's local move.
         The attractor in this case should be the best solution this agent has achieved.
         @param  multiObjectiveSolution* is a pointer to the solution that acts as the follower
         @param  multiObjectiveSolution* is a pointer to the soluiton that asts as the attractor
         @param  multiObjectiveSolution* is a pointer to the output solutionid 	socialMoveme
         @param  const std::string options is a reserved string for parameters
      */
      virtual void localMovement(multiObjectiveSolution* currentSolution, 
                                     multiObjectiveSolution* attractor,
                                     multiObjectiveSolution* metaSolutionOut,
                                     const std::string options = "") = 0;
      /**
         Virtual method that is intended to implement the JFO's social move.
         The attractor in this case should be the best solution achieve by the whole swarm.
         @param  multiObjectiveSolution* is a pointer to the solution that acts as the follower
         @param  multiObjectiveSolution* is a pointer to the soluiton that asts as the attractor
         @param  multiObjectiveSolution* is a pointer to the output solution
         @param  const std::string options is a reserved string for parameters
      */
      virtual void socialMovement(multiObjectiveSolution* currentSolution, 
                                     multiObjectiveSolution* attractor,
                                     multiObjectiveSolution* metaSolutionOut,
                                     const std::string options = "") = 0;

      /**
         Virtual method that is intended to implement a local search as it is
         specified in(eps + (eps/double(3)) the JFO Algorithm.
      */
      virtual void localSearchMethod(multiObjectiveSolution* currentSolution,
                                     const std::string options = "") = 0;

      /**
         Virtual method that is intended to accept or reject new solution or
         output of movements. This is useful if you want agents to move only
         on feasible areas.
      */
      virtual bool isAValidMovement() = 0;
};

JFOAgent::JFOAgent()
{
   setIteration(0);
   setIterationOfBestSolution(0);
   this->bestOwnSolution = NULL;
   this->bestSolutionOfGroup = NULL;
}

JFOAgent::~JFOAgent()
{

}

// Setters

inline void JFOAgent::setBestOwnSolution(multiObjectiveSolution* newSolution)
{
   this->bestOwnSolution = newSolution;
}

inline void JFOAgent::setBestSolutionOfGroup(multiObjectiveSolution* newSolution)
{
   this->bestSolutionOfGroup = newSolution;
}

// Getters

inline multiObjectiveSolution* JFOAgent::getBestOwnSolution() const
{
   return this->bestOwnSolution;
}

inline multiObjectiveSolution* JFOAgent::getBestSolutionOfGroup() const
{
   return this->bestSolutionOfGroup;
}

/*
inline void JFOAgent::updateParameters(unsigned it)
{
   //this->c1 = 0.90 * ((double)it/(double)2000) * sin((double)it / (double)10); //20 min -> 8 violations

   //this->c1 =  ((double)it / (double)2) * sin((double)1 / (double)10 * (double)PI * (double)it) / (double)it;
   //this->c1 = (this->c1 < 0)? 0 : this->c1;
   this->c1 = abs(this->c1);
   double delta = 1 - this->c1;
   
   this->c2 = delta / 3;
   this->c3 = delta / 3;
   this->c4 = 1 - (this->c1 + this->c2 + this->c3);
   //std::cout << "PI: " << PI << " it: " << it << " PI * it: " << PI * it << " (2 * PI * it) / 300: " << (2 * PI * it) / 300 << std::endl;
   //std::cout << "(sin((2 * PI * it) / 300): " << sin(2 * PI * it / 300) << " (1/4) * K: " << (0.25) * sin(2 * PI * it / 300) << std::endl;
   //std::cout << "PI: " << PI << "PI: " << PI << "PI: " << PI << std::endl;
   //std::cout << "c1: " << c1 << " c2: " << c2 << " c3: " << c3 << " c4: " << c4 << std::endl;
}*/


/*
inline void JFOAgent::updateParameters(unsigned id)
{
   double eps = 0.1;

   //std::cout << "id: " << id << std::endl;
   if (id == 1)
      this->c1 += (eps + (eps/double(3)));
   if (id == 2)
      this->c2 += (eps + (eps/double(3)));
   if (id == 3)
      this->c3 += (eps + (eps/double(3)));
   if (id == 4)
      this->c4 += (eps + (eps/double(3)));

   this->c1 = (double)(this->c1 - (eps/double(3)));
   this->c2 = (double)(this->c2 - (eps/double(3)));
   this->c3 = (double)(this->c3 - (eps/double(3)));
   this->c4 = (double)(this->c4 - (eps/double(3)));

   this->c1 = ((this->c1 < 0)? 0 : this->c1);
   this->c2 = ((this->c2 < 0)? 0 : this->c2);
   this->c3 = ((this->c3 < 0)? 0 : this->c3);
   this->c4 = ((this->c4 < 0)? 0 : this->c4);
   
   //std::cout << this->c1 << " " << this->c2 << " " << this->c3 << " " << this->c4 << std::endl;

   if (this->c1 >= 1 || this->c2 >= 1 || this->c3 >= 1 || this->c4 >= 1)
      initializeParameters();  
}
*/

inline void JFOAgent::updateParameters(unsigned it)
{
   if (this->c1 < 0.01)
   {
      this->c2 = 0.33;
      this->c3 = 0.33;
      this->c4 = 0.33;
      return;
   }

   double itMax = (double)1000;
   double currentIt = itMax - it;
   double initialDelta = 0.50;
   
   double previousC1 = this->c1;

   this->c1 = initialDelta * currentIt / itMax;

   double delta = previousC1 - this->c1;
   
   this->c2 += delta/(double)3;
   this->c3 += delta/(double)3;
   this->c4 += delta/(double)3; 
}


inline void JFOAgent::initializeParameters()
{
   this->c1 = 0.25;
   this->c2 = 0.25;
   this->c3 = 0.25;
   this->c4 = 0.25;
}

#endif
