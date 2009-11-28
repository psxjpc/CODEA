/** 
   @class vehicleCapacitynViolationsProblem
  
   @brief Evaluates the number vehicles whose capacity max load is violated in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef VEHICLECAPACITYNVIOLATIONSPROBLEM_H
#define VEHICLECAPACITYNVIOLATIONSPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class vehicleCapacitynViolationsProblem : public singleObjectiveProblem
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */    
      vehicleCapacitynViolationsProblem();

      /**
         Default destructor. It does nothing.
      */
      ~vehicleCapacitynViolationsProblem();

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

vehicleCapacitynViolationsProblem::vehicleCapacitynViolationsProblem()
{ }

vehicleCapacitynViolationsProblem::~vehicleCapacitynViolationsProblem()
{ }

inline T vehicleCapacitynViolationsProblem::evaluate(multiObjectiveSolution* currentSolution) const
{
   // std::cout << "vechileCapacitynViolationsProblem" << std::endl;

   assert(currentSolution != NULL);

   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());
   //std::cout << "   Current Route: " << routes << std::endl;   

   T currentCapacity = 0;
   unsigned numberOfViolations = 0;

   for (size_t i = 1; i < routes.size(); i++)
   {
      if (routes[i] == 0)
      { 
         if (currentCapacity > VRPTWData->getFleet()[0].second)
         {
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

   // std::cout << "   vechileCapacitynViolationsProblem time: " << numberOfViolations << std::endl;
   // std::cout << "<--- vechileCapacitynViolationsProblem" << std::endl;
   return (T)numberOfViolations;
}


inline T vehicleCapacitynViolationsProblem::evaluate(const routesType& routes) const
{   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   T currentCapacity = 0;
   unsigned numberOfViolations = 0;

   for (size_t i = 1; i < routes.size(); i++)
   {
      if (routes[i] == 0)
      { 
         if (currentCapacity > VRPTWData->getFleet()[0].second)
         {
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

   // std::cout << "   vechileCapacitynViolationsProblem time: " << numberOfViolations << std::endl;
   // std::cout << "<--- vechileCapacitynViolationsProblem" << std::endl;
   return (T)numberOfViolations;
}

T vehicleCapacitynViolationsProblem::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
