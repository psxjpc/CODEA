/** 
   @class vehicleCapacityViolationProblem
  
   @brief Evaluates the amount of capacity violated in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef VEHICLECAPACITYVIOLATIONPROBLEM_H
#define VEHICLECAPACITYVIOLATIONPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class vehicleCapacityViolationProblem : public singleObjectiveProblem
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      vehicleCapacityViolationProblem();

      /**
         Default destructor. It does nothing.
      */
      ~vehicleCapacityViolationProblem();

      /**
         Method that return the evaluation of the given 
         objective using a solution.
         @param multiObjectiveSolution* is a pointer to 
         the solution is going to be evaluated.
         @return the value of the objective after the
         evaluation.
      */
      T evaluate(multiObjectiveSolution*) const;

      /**
         Method that return the evaluation of the given 
         objective using a route-plan.
         @param multiObjectiveSolution* is a pointer to 
         the solution is going to be evaluated.
         @return the value of the objective after the
         evaluation.
      */
      T evaluate(const routesType& routes) const;

      T evaluate(const boost::any&) const;
};

vehicleCapacityViolationProblem::vehicleCapacityViolationProblem()
{ }

vehicleCapacityViolationProblem::~vehicleCapacityViolationProblem()
{ }

inline T vehicleCapacityViolationProblem::evaluate(multiObjectiveSolution* currentSolution) const
{
   // std::cout << "vechileCapacitynViolationsProblem" << std::endl;

   assert(currentSolution != NULL);

   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());
   //std::cout << "   Current Route: " << routes << std::endl;   

   T currentCapacity = 0;
   T excededCapacity = 0;
   unsigned numberOfViolations = 0;

   for (size_t i = 1; i < routes.size(); i++)
   {
      if (routes[i] == 0)
      { 
         if (currentCapacity > VRPTWData->getFleet()[0].second)
         {
               excededCapacity += currentCapacity - VRPTWData->getFleet()[0].second;
               numberOfViolations++;
               // cout << "[+] numberOfViolation: " << numberOfViolations << endl;
         }
         currentCapacity = 0;
      }
      else 
      {
         // cout << "Costumer[" << routes[i] << "]: " << VRPTWData->getDemand()[routes[i]] << endl;
         currentCapacity += VRPTWData->getDemand()[routes[i]];
         // cout << "[->currentCapacity = " <<  currentCapacity << endl;
      }
   }

   return excededCapacity;
}

inline T vehicleCapacityViolationProblem::evaluate(const routesType& routes) const
{

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   T currentCapacity = 0;
   T excededCapacity = 0;
   unsigned numberOfViolations = 0;

   for (size_t i = 1; i < routes.size(); i++)
   {
      if (routes[i] == 0)
      { 
         if (currentCapacity > VRPTWData->getFleet()[0].second)
         {
               excededCapacity += currentCapacity - VRPTWData->getFleet()[0].second;
               numberOfViolations++;
         }
         currentCapacity = 0;
      }
      else 
         currentCapacity += VRPTWData->getDemand()[routes[i]];
   }

   return excededCapacity;
}

T vehicleCapacityViolationProblem::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
