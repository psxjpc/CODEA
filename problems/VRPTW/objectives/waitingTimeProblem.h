/** 
   @class waitingTimeProblem
  
   @brief Evaluates the sum of waiting time the client are suffering in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef WAITINGTIMEPROBLEM_H
#define WAITINGTIMEPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class VRPSolution;

class waitingTimeProblem : public singleObjectiveProblem
{
   private:

   protected:
      /**
         Method that given two costumers computes the time
         to serve them. It computes the time it takes to 
         move from one to another and the service time.
         @param T& is the elapsed time so far is going to
         be incremented.
         @param T& is the elapsed time violation so far.
         @param const unsgined is the id of the first costumer.
         @param const unsigned is the id of the second costumer. 
      */
      void elapsedTimeBetweenTwoCostumers(T&, T&, const unsigned, const unsigned) const;

   public:
      /**
         Default constructor. It does nothing.
      */
      waitingTimeProblem();

      /**
         Default destructor. It does nothing.
      */
      ~waitingTimeProblem();

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

waitingTimeProblem::waitingTimeProblem()
{ }

waitingTimeProblem::~waitingTimeProblem()
{ }

inline void waitingTimeProblem::elapsedTimeBetweenTwoCostumers(T& totalElapsedTime, T& waitingTime, const unsigned i, const unsigned j) const
{
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   // Time it takes to go from <costumer i> to <costumer i+1>
   totalElapsedTime += VRPTWData->getDistanceMatrix()[i][j];

   // Time we have to wait if we arrive before the <costumer i> opens
   //    First, we calculate whether we're going to wait or not.
   if (VRPTWData->getTimeWindow()[j].first > totalElapsedTime)
   {
      waitingTime += VRPTWData->getTimeWindow()[j].first - totalElapsedTime;
      totalElapsedTime = VRPTWData->getTimeWindow()[j].first;
   }
   // Finally, we have to sum up the servicetime at the <costumer i> 
   totalElapsedTime += VRPTWData->getServiceTime()[j];

}


inline T waitingTimeProblem::evaluate(multiObjectiveSolution* currentSolution) const
{
   // std::cout << "tineWindowsViolationProblem" << std::endl;

   assert(currentSolution != NULL);

   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   T waitingTime = 0;

   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());
  

   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, waitingTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;

   return waitingTime;
}

inline T waitingTimeProblem::evaluate(const routesType& routes) const
{
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   T waitingTime = 0;

   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, waitingTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;

   return waitingTime;
}

T waitingTimeProblem::evaluate(const boost::any& anyRoute) const
{
   return evaluate(boost::any_cast<const routesType&> (anyRoute));
}

#endif
