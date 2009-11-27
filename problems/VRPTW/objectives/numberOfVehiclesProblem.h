/** 
   @class numberOfVehiclesProblem
  
   @brief Evaluates the number of vehicles used in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef NUMBEROFVEHICLESPROBLEM_H
#define NUMBEROFVEHICLESPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class numberOfVehiclesProblem : public singleObjectiveProblem
{
   private:

   protected:

   public:

      /**
         Default constructor. It does nothing. 
      */
      numberOfVehiclesProblem();

      /**
         Default destructor. It does nothing.
      */
      ~numberOfVehiclesProblem();

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
};

numberOfVehiclesProblem::numberOfVehiclesProblem()
{ }

numberOfVehiclesProblem::~numberOfVehiclesProblem()
{ }

inline T numberOfVehiclesProblem::evaluate(multiObjectiveSolution* currentSolution)
{
   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   T numberOfVehicles = VRPSol->getNumberOfRoutes();

   return numberOfVehicles;
}

inline T numberOfVehiclesProblem::evaluate(const routesType& routes)
{
   unsigned numberOfRoutes = 0;
   for (size_t i = 0; i < routes.size(); i++)
      if (routes[i] == 0)
         numberOfRoutes++;
   return (numberOfRoutes - 1);
}



#endif
