/** 
   @class distanceProblem
  
   @brief Evaluates the travel distance used in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef DISTANCEPROBLEM_H
#define DISTANCEPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class VRPSolution;

class distanceProblem : public singleObjectiveProblem
{
   private:

   protected:


   public:
      /**
         Default constructor. It does nothing.
      */
      distanceProblem();

      /**
         Default destructor. It does nothing.
      */
      ~distanceProblem();

      /**
         Method that return the evaluation of the given 
         objective using a solution.
         @param multiObjectiveSolution* is a pointer to 
         the solution is going to be evaluated.
         @return the value of the objective after the
         evaluation.
      */
      T evaluate(multiObjectiveSolution*);

      /**
         Method that return the evaluation of the given 
         objective using a route-plan.
         @param multiObjectiveSolution* is a pointer to 
         the solution is going to be evaluated.
         @return the value of the objective after the
         evaluation.
      */
      T evaluate(const routesType& routes);

      /**
         Method that return the evaluation of the given 
         objective using a route-plan in an interval.
         @param multiObjectiveSolution* is a pointer to 
         the solution is going to be evaluated.
         @param const unsigned start is the first costumer
         to start the evaluation with.
         @param const unsigned length is the number of 
         costumers to be evaluated.
         @return the value of the objective after the
         evaluation.
      */
      T evaluate(const routesType& routes, const unsigned start, const unsigned length);
};

distanceProblem::distanceProblem()
{ }

distanceProblem::~distanceProblem()
{ }

inline T distanceProblem::evaluate(multiObjectiveSolution* currentSolution)
{
   assert(currentSolution != NULL);
 
   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());

   T totalDistance = 0;
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   for (size_t i = 0; i < routes.size() - 1; i++)
      totalDistance += VRPTWData->getDistanceMatrix()[routes[i]][routes[i + 1]];

   return totalDistance;
}

inline T distanceProblem::evaluate(const routesType& routes)
{
   T totalDistance = 0;
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   for (size_t i = 0; i < routes.size() - 1; i++)
      totalDistance += VRPTWData->getDistanceMatrix()[routes[i]][routes[i + 1]];

   return totalDistance;
}

inline T distanceProblem::evaluate(const routesType& routes, const unsigned start, const unsigned length)
{
   assert(start + length < routes.size());
   T totalDistance = 0;
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   for (size_t i = start; i < start + length; i++)
      totalDistance += VRPTWData->getDistanceMatrix()[routes[i]][routes[i + 1]];

   return totalDistance;  
}

#endif
