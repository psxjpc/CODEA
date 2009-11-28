/** 
   @class vehiclesBalance
  
   @brief Evaluates the penalties given by the time windows distribution
   
   @author ASAP - University of Nottingham - 2009
*/

#ifndef VEHICLEBALANCE_H
#define VEHICLEBALANCE_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class VRPSolution;

class vehiclesBalance : public singleObjectiveProblem
{
   private:

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      vehiclesBalance();

      /**
         Default destructor. It does nothing.
      */
      ~vehiclesBalance();

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

vehiclesBalance::vehiclesBalance()
{ }

vehiclesBalance::~vehiclesBalance()
{ }
inline T vehiclesBalance::evaluate(multiObjectiveSolution* currentSolution) const
{
   assert(currentSolution != NULL);
   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   return evaluate(const_cast<const routesType&>(VRPSol->getRoutes()));
}

inline T vehiclesBalance::evaluate(const routesType& routes) const
{
   // std::cout << "Time Windows Distribution" << std::endl;
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   T penalties = 0;

   for (size_t i = 0; i < routes.size(); i++)
   
   return penalties;
}

T vehiclesBalance::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
