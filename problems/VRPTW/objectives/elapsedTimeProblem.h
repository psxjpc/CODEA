/** 
   @class elapsedTimeProblem
  
   @brief Evaluates the travel time used in a given solution.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef ELAPSEDTIMEPROBLEM_H
#define ELAPSEDTIMEPROBLEM_H

#include "../VRPSolution.h"
#include "../../../core/header.h"
#include "../../../core/multiObjectiveSolution.h"
#include "../../../core/singleObjectiveProblem.h"
#include "../dataTypes.h"

class VRPSolution;

class elapsedTimeProblem : public singleObjectiveProblem
{
   private:

   protected:
      /**
         Method that given two costumers computes the time
         to serve them. It computes the time it takes to 
         move from one to another and the service time.
         @param T& is the elapsed time so far is going to
         be incremented.
         @param const unsgined is the id of the first costumer.
         @param const unsigned is the id of the second costumer. 
      */
      void elapsedTimeBetweenTwoCostumers(T&, const unsigned, const unsigned);

   public:
      /**
         Default constructor. It does nothing.
      */
      elapsedTimeProblem();

      /**
         Default destructor. It does nothing.
      */
      ~elapsedTimeProblem();

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
      T evaluate(const routesType&, const unsigned, const unsigned);

};

elapsedTimeProblem::elapsedTimeProblem()
{ }

elapsedTimeProblem::~elapsedTimeProblem()
{ }

inline void elapsedTimeProblem::elapsedTimeBetweenTwoCostumers(T& totalElapsedTime, const unsigned i, const unsigned j)
{
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   // Time it takes to go from <costumer i> to <costumer i+1>
   totalElapsedTime += VRPTWData->getDistanceMatrix()[i][j];

   // Time we have to wait if we arrive before the <costumer i> opens
   //    First, we calculate whether we're going to wait or not.
   if (VRPTWData->getTimeWindow()[j].first > totalElapsedTime)
      totalElapsedTime = VRPTWData->getTimeWindow()[j].first;

   // Finally, we have to sum up the servicetime at the <costumer i> 
   totalElapsedTime += VRPTWData->getServiceTime()[j];

   // cout << "from: " <<  i << " to: " << j << " it takes: " << totalElapsedTime << endl;
}


inline T elapsedTimeProblem::evaluate(multiObjectiveSolution* currentSolution)
{
   // std::cout << "ElapsedTimeProblem" << std::endl;

   assert(currentSolution != NULL);

   VRPSolution* VRPSol = static_cast<VRPSolution*>(currentSolution);
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;

   routesType routes = const_cast<const routesType&>(VRPSol->getRoutes());
   // std::cout << "   Current Route: " << routes << std::endl;   

   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;
   // std::cout << "   Elapsed time: " << totalElapsedTime << std::endl;
   // std::cout << "<--- ElapsedTimeProblem" << std::endl;
   return totalElapsedTime;
}

inline T elapsedTimeProblem::evaluate(const routesType& routes)
{
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;
   return totalElapsedTime;
}

inline T elapsedTimeProblem::evaluate(const routesType& routes, const unsigned position, const unsigned costumer)
{
   T totalElapsedTime = 0;
   T routeElapsedTime = 0;
   // Before the element
   for (size_t i = 0; i < position - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;
   routeElapsedTime = 0;
   // Now we have to add time<position - 1, costumer> and time<costumer, position + 1>
   if (routes[position - 1] == 0)
   {
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, routes[position - 1], costumer);
      totalElapsedTime += routeElapsedTime;
      routeElapsedTime = 0;
   }
   else 
      elapsedTimeBetweenTwoCostumers(totalElapsedTime, routes[position - 1], costumer);
   elapsedTimeBetweenTwoCostumers(totalElapsedTime, costumer, routes[position]);

   // After the elemtent
   for (size_t i = position; i < routes.size() - 1; i++)
   {
      if (routes[i] == 0)
      {
         totalElapsedTime += routeElapsedTime;
         routeElapsedTime = 0;
      }
      elapsedTimeBetweenTwoCostumers(routeElapsedTime, routes[i], routes[i + 1]);
   }
   totalElapsedTime += routeElapsedTime;
   return totalElapsedTime;
}

#endif
