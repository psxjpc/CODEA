/** 
   @class timeWindowsDistribution
  
   @brief Evaluates the penalties given by the time windows distribution
   
   @author ASAP - University of Nottingham - 2009
*/

#ifndef TIMEWINDOWSDISTRIBUTION_H
#define TIMEWINDOWSDISTRIBUTION_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class VRPSolution;

class timeWindowsDistribution : public singleObjectiveProblem
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      timeWindowsDistribution();

      /**
         Default destructor. It does nothing.
      */
      ~timeWindowsDistribution();

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
      T evaluate(const routesType&, const unsigned, const unsigned) const;

      T evaluate(const boost::any&) const;

};

timeWindowsDistribution::timeWindowsDistribution()
{ }

timeWindowsDistribution::~timeWindowsDistribution()
{ }
inline T timeWindowsDistribution::evaluate(multiObjectiveSolution* currentSolution) const
{
   assert(currentSolution != NULL);
   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   return evaluate(const_cast<const routesType&>(VRPSol->getRoutes()));
}

inline T timeWindowsDistribution::evaluate(const routesType& routes) const
{
   // std::cout << "Time Windows Distribution" << std::endl;
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   T penalties = 0;
   int index = 0;
   unsigned delta = 0;

   // std::cout << "Routes: " << routes << std::endl;

   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      //if (routes[i] != 0);
      // std::cout << "[i: " << index << "] costumer: [" << routes[i] << "] -> Z: " <<  VRPTWData->getZone(routes[i]) << " i + d = " << index + delta << " < " << VRPTWData->getZone(routes[i]) << "?";
      if (routes[i] == 0)
         index = -1;


      else if ((index + delta) != VRPTWData->getZone(routes[i]) /*&& (index < VRPTWData->getZone(routes[i]))*/)
      {
         penalties++;
        //// cout << " p: " << penalties;
      }
      //std::cout << std::endl;
      index++;  
   }
  // std::cout << "Penalties: " << penalties << std::endl;
 //  exit(1);
   return penalties;
}

T timeWindowsDistribution::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
