/** 
   @class systemGeneralStopCriterion
  
   @brief General Stop Criterion for ssystem.

   This class inherits from systemStopCriterion to enable stop controllers in
   system's main loop. This class shares the same philosophy that the one in
   generalStopCriterion (please refer to this class for more information).

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef SYSTEMGENERALSTOPCRITERION_H
#define SYSTEMGENERALSTOPCRITERION_H

#include "header.h"
#include "ssystem.h"
#include "systemStopCriterion.h"


class systemGeneralStopCriterion: public systemStopCriterion
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
      systemGeneralStopCriterion();

      /**
         Default destructor. It does nothing.
      */
      ~systemGeneralStopCriterion() { };

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
         @param ssystem* is the pointer to ssytem object.
      */
      bool stop(ssystem*);
};

systemGeneralStopCriterion::systemGeneralStopCriterion()
{ 
   maxTime = (double)INFd;
   maxIteration = (long)INFi;
   extSignal = false; 
}

inline double systemGeneralStopCriterion::getMaxTime() const
{
   return this->maxTime;
}

inline unsigned systemGeneralStopCriterion::getMaxIterations() const
{
   return this->maxIteration;
}

inline bool systemGeneralStopCriterion::getExtSignal() const
{
   return this->extSignal;
}

inline void systemGeneralStopCriterion::setMaxTime(const double time)
{
   this->maxTime = time;
}

inline void systemGeneralStopCriterion::setMaxIteration(const unsigned i)
{
   this->maxIteration = i;
}

inline void systemGeneralStopCriterion::setExtSignal(const bool signal)
{
   this->extSignal = signal;
}

inline bool systemGeneralStopCriterion::stop(ssystem* sys)
{
   return (this->extSignal || ((double)(clock() / CLOCKS_PER_SEC) > this->maxTime) || (sys->getIteration() >= this->maxIteration));
}

#endif
