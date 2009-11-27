/** 
   @class generalStopCriterion
  
   @brief General Stop Criterion for metaheuristics.

   This class inherits from stopCriterion to enable stop controllers in
   metaheuristic methods. Let's suppose we want to develop an agent whose
   core is going to perform a local search. We migh want to execute this
   procedure a numbre of times whithing the same method, or to simply 
   provide an amount of time to run this operation. To handle this type
   of tasks, it is possible to use this class.

   This way, the procedure in the agent's behabiour class could look like:

   \code

   // Creation of the stop controller
   generalStopCriterion* stopController = new generalStopCriterion();

   // We will set a max number of iterations and a max time.
   stopController->setMaxIteration(1000);
   stopController->setMaxTime(100);

   //
   //  The loop will stop when one of the agent's parameters meet any 
   //  of the parameters set in the stop controller.
   //

   do {
      // Perform the operation/s
      localSearch();
      // Update the parameters related to iterations and so on. 
      updateParameters();
   } while (!stopController->stop(this);

   \endcode

   @note systemGeneralStopCriterion uses the same philosophy and methodology to stop
   the execution of the main loop in which the agents live.
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef GENERALSTOPCRITERION_H
#define GENERALSTOPCRITERION_H

#include "stopCriterion.h"

class generalStopCriterion : public stopCriterion
{
   private:
      /**
         Max time the loop is alive. After this time the loop will be forced to finish.
      */
      double maxTime;

      /**
         Max number of iterations the loop is alive. After this number of iterations
         the loop will be forced to finish.
      */
      unsigned maxIteration;
      /**
         Aborption signal. If this signal is set to true, the loop will end in the next
         iteration.
      */
      bool extSignal;

   protected:
      
   public:
      /**
         Default constructor. It sets the fields of this class to default parameters (Infinite).
      */
      generalStopCriterion();

      /**
         Default destructor. It does nothing.
      */
      ~generalStopCriterion() { };

      /**
         Method that returns the max time established until the main loop should be alive. 
         @return Max time for the stop controller.
      */
      double getMaxTime() const;

      /**
         Method that returns the max number of iterations established until the main loop should be alive. 
         @return Max number of iterations for the stop controller.
      */
      unsigned getMaxIterations() const;

      /**
         Method that returns the state of the external signal.
         @return state of the external signal.
      */
      bool getExtSignal() const;

      /**
         Method that sets the max time until the loop is forced to end.
         @param const double is the max time the loop should be alive.
      */
      void setMaxTime(const double);

      /**
         Method that sets the max number of iterations until the loop is forced to end.
         @param const double is the max time the loop should be alive.
      */
      void setMaxIteration(const unsigned);

      /**
         Method that sets the external signal to force the stop in the next evaluation
         of the while's condition.
         @param const bool is the state of the external signal.
      */
      void setExtSignal(const bool);

      /**
         Method that controls when any of the criterions to stop is met.
         @param agent* is a pointer to the agent that invokes this method to access 
         its parameters (for example, the current iteration).
      */
      bool stop(agent*) const;
};

generalStopCriterion::generalStopCriterion(): maxTime(INFd), maxIteration(INFi), extSignal(false) { }

inline double generalStopCriterion::getMaxTime() const
{
   return this->maxTime;
}

inline unsigned generalStopCriterion::getMaxIterations() const
{
   return this->maxIteration;
}

inline bool generalStopCriterion::getExtSignal() const
{
   return this->extSignal;
}

inline void generalStopCriterion::setMaxTime(const double time)
{
   this->maxTime = time;
}

inline void generalStopCriterion::setMaxIteration(const unsigned i)
{
   this->maxIteration = i;
}

inline void generalStopCriterion::setExtSignal(const bool signal)
{
   this->extSignal = signal;
}

inline bool generalStopCriterion::stop(agent* agent007) const
{
   return (this->extSignal || ((double)(clock() / CLOCKS_PER_SEC) > this->maxTime) || (agent007->getIteration() >= this->maxIteration));
}

#endif
