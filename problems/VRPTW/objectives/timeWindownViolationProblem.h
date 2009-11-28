/** 
   @class timeWindownViolationProblem
  
   @brief Evaluates the number of time window violated in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef TIMEWINDOWNVIOLATIONPROBLEM_H
#define TIMEWINDOWNVIOLATIONPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class timeWindownViolationProblem : public singleObjectiveProblem
{
   private:

   protected:
      void elapsedTimeBetweenTwoCostumers(T&, unsigned&, const unsigned, const unsigned) const;


   public:
      /**
         Default constructor. It does nothing.
      */
      timeWindownViolationProblem();

      /**
         Default destructor. It does nothing.
      */
      ~timeWindownViolationProblem();

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

timeWindownViolationProblem::timeWindownViolationProblem()
{ }

timeWindownViolationProblem::~timeWindownViolationProblem()
{ }

inline void timeWindownViolationProblem::elapsedTimeBetweenTwoCostumers(T& totalElapsedTime, unsigned& numberOfViolations, const unsigned i, const unsigned j) const
{
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   // Time it takes to go from <costumer i> to <costumer i+1>
   totalElapsedTime += VRPTWData->getDistanceMatrix()[i][j];
   //cout << "TW:(" << i << "," << j << ") [" << VRPTWData->getTimeWindow()[j].first << "," << VRPTWData->getTimeWindow()[j].second << "]";

   // Time we have to wait if we arrive before the <costumer i> opens
   //    First, we calculate whether we're going to wait or not.
   if (VRPTWData->getTimeWindow()[j].first > totalElapsedTime)
      totalElapsedTime = VRPTWData->getTimeWindow()[j].first;
   else if (VRPTWData->getTimeWindow()[j].second < totalElapsedTime)
   {
      numberOfViolations++; 
      
      //cout << "[+] - numberOfViolations: " << numberOfViolations << endl;
   }
   // Finally, we have to sum up the servicetime at the <costumer i> 
   totalElapsedTime += VRPTWData->getServiceTime()[j];

   //cout << "from: " <<  i << " to: " << j << " it takes: " << totalElapsedTime << endl;
}


inline T timeWindownViolationProblem::evaluate(multiObjectiveSolution* currentSolution) const
{
   // std::cout << "tineWindowsViolationProblem" << std::endl;

   assert(currentSolution != NULL);

   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   unsigned numberOfViolations = 0;

   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());
   // std::cout << "   Current Route: " << routes << std::endl;   

   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, numberOfViolations, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;

   // std::cout << "   timeWindownViolationProblem: " << numberOfViolations << std::endl;
   // std::cout << "<--- tinemWindowViolationProblem" << std::endl;
   return (T)numberOfViolations;
}

inline T timeWindownViolationProblem::evaluate(const routesType& routes) const
{
   // std::cout << "tineWindowsViolationProblem" << std::endl;

   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   unsigned numberOfViolations = 0;


   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, numberOfViolations, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;

   // std::cout << "   timeWindownViolationProblem: " << numberOfViolations << std::endl;
   // std::cout << "<--- tinemWindowViolationProblem" << std::endl;
   return (T)numberOfViolations;
}

T timeWindownViolationProblem::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
