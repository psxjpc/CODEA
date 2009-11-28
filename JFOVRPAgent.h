/** 
   @class JFOVRPAgent
  
   @brief Implements the methods established in the JFOAgent
   for the VRPTW problem.

   This class is designed to implement the methods inherited
   from the JFOAgent class. It consists of a set of method
   that invokes functions of the VRPLibrary. 

   These functions will unpack the multiObjectiveSolutions sending
   two routes to a library function. This function will return a 
   route. This must be tested, if it's feasible then a metaSolution
   will be created and returned; otherwise, NULL will be returned.
   
   ci = currentSolution
   ai = attractor
   ni = newSolution

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef JFOVRPAGENT_H
#define JFOVRPAGENT_H

#include "./core/codeaParameters.h"
#include "./core/multiObjectiveSolution.h"
#include "./core/multiObjectiveProblem.h"

#include "./agents/JFO/JFOAgent.h"
#include "./problems/VRPTW/VRPSolution.h"
#include "./problems/VRPTW/VRPLib.h"


class JFOVRPAgent : public JFOAgent
{
   private:
      /**
         This route represent the output of the movement of a particle
         to a new solution.
      */
      routesType newRoutes;

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      JFOVRPAgent();

      /**
         Default destructor. It does nothing.
      */
      ~JFOVRPAgent();

      /**
         Method that implements the inherited virtual method from 
         JFOAgent. It performs an inertial movement in which there
         is not any attractor. It is supposed to be a random move
         respect to the current position (solution).
         @param multiObjectiveSolution* is the current solution
         @param multiObjectiveSolution* is the solution to be output.
         @param std::string options is a reserved with options.
      */
      void inertialMovement( multiObjectiveSolution* currentSolution, 
                             multiObjectiveSolution* metaSolutionOut,
                             const string options = "");

      /**
         Method that implements the inherited virtual method from 
         JFOAgent. It performs an cognitive movement in which the
         attractor is the best solution in the neighborhood.
         @param multiObjectiveSolution* is the current solution (follower)
         @param multiObjectiveSolution* is the solution to follow (attractor)
         @param multiObjectiveSolution* is the solution to be output.
         @param std::string options is a reserved with options.
      */
      void cognitiveMovement(multiObjectiveSolution* currentSolution, 
                             multiObjectiveSolution* attractor,
                             multiObjectiveSolution* metaSolutionOut,
                             const string options = "");

      /**
         Method that implements the inherited virtual method from 
         JFOAgent. It performs an local movement in which the
         attractor is the best own solution achieved so far.
         @param multiObjectiveSolution* is the current solution (follower)
         @param multiObjectiveSolution* is the solution to follow (attractor)
         @param multiObjectiveSolution* is the solution to be output.
         @param std::string options is a reserved with options.
      */
     void localMovement(multiObjectiveSolution* currentSolution, 
                             multiObjectiveSolution* attractor,
                             multiObjectiveSolution* metaSolutionOut,
                             const string options = "");

      /**
         Method that implements the inherited virtual method from 
         JFOAgent. It performs an social movement in which the
         attractor is the best solution found by the swarm so far.
         @param multiObjectiveSolution* is the current solution (follower)
         @param multiObjectiveSolution* is the solution to follow (attractor)
         @param multiObjectiveSolution* is the solution to be output.
         @param std::string options is a reserved with options.
      */
      void socialMovement(multiObjectiveSolution* currentSolution, 
                          multiObjectiveSolution* attractor,
                          multiObjectiveSolution* metaSolutionOut,
                          const string options = "");

      /**
         Method that implements the inherited virtual method from
         JFOAgent. It performs a local search as specified in the
         algorithm JFO
         @param multiObjectiveSolution* is the current solution
         @param const std::string options is a reserved string for
         optiones.
      */
      void localSearchMethod(multiObjectiveSolution* currentSolution, 
                             const string options = "");

      /**
         Virtual method that is intended to accept or reject new solution or
         output of movements. This is useful if you want agents to move only
         on feasible areas.
      */
      virtual bool isAValidMovement();
};

JFOVRPAgent::JFOVRPAgent()
{

}

JFOVRPAgent::~JFOVRPAgent()
{

}

inline void JFOVRPAgent::inertialMovement(multiObjectiveSolution* ci,
                                          multiObjectiveSolution* ni,
                                          const string options)
{
   codeaParameters* neuralItem = codeaParameters::instance();
   routesType offSpringRoutes;
   if (neuralItem->getRandomNumber()->rand() > 0.5)
      offSpringRoutes = closerNode((static_cast<VRPSolution*>(ci))->getRoutes(), options);
   else
      offSpringRoutes = lambdaOneInterchange((static_cast<VRPSolution*>(ci))->getRoutes(), options);
 
   (static_cast<VRPSolution*>(ni))->setRoutes(offSpringRoutes);
}

inline void JFOVRPAgent::cognitiveMovement(multiObjectiveSolution* ci, 
                                           multiObjectiveSolution* ai, 
                                           multiObjectiveSolution* ni,
                                           const string options)
{
   const routesType& follower = (static_cast<VRPSolution*>(ci))->getRoutes();
   const routesType& attractor = (static_cast<VRPSolution*>(ai))->getRoutes();
   routesType offSpringRoutes = twitter(follower, attractor, options);
   (static_cast<VRPSolution*>(ni))->setRoutes(offSpringRoutes);
}

inline void JFOVRPAgent::localMovement(multiObjectiveSolution* ci, 
                                       multiObjectiveSolution* ai, 
                                       multiObjectiveSolution* ni,
                                       const string options)
{
   routesType offSpringRoutes = twitter((static_cast<VRPSolution*>(ci))->getRoutes(),
                                     (static_cast<VRPSolution*>(ai))->getRoutes());

   (static_cast<VRPSolution*>(ni))->setRoutes(offSpringRoutes);
}

inline void JFOVRPAgent::socialMovement(multiObjectiveSolution* ci, 
                                        multiObjectiveSolution* ai, 
                                        multiObjectiveSolution* ni,
                                        const string options)
{ 
   routesType offSpringRoutes = twitter((static_cast<VRPSolution*>(ci))->getRoutes(),
                                     (static_cast<VRPSolution*>(ai))->getRoutes());

   (static_cast<VRPSolution*>(ni))->setRoutes(offSpringRoutes);
}

inline void JFOVRPAgent::localSearchMethod(multiObjectiveSolution* ci, const string options)
{ 
   routesType offSpringRoutes = localSearch((static_cast<VRPSolution*>(ci))->getRoutes(), options);

   (static_cast<VRPSolution*>(ci))->setRoutes(offSpringRoutes);
}

bool JFOVRPAgent::isAValidMovement()
{
   // We have to call here the VRPSolutions' method "isFeasible"
   //   this is static so we can call it using "VRPSolution::"
   // return VRPSolution::isFeasible(this->newRoutes);

   // We'll start by allowing any kind of movement
   return true;
}

#endif
