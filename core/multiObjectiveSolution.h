/** 
   @class multiObjectiveSolution
  
   @brief Store multi-objective solutions.

   This class is designed to store multi-objective solutions. It has two 
   attributes: a vector of objective values and their names. The second
   attribute is intended to identify each objective and for output purposes.
   However, the first one was included to deal with complex problem with
   many objectives. Even if it is possible to obtain the values of this 
   vector using the evaluation process in the multiObjectiveProblem, it may be
   very time consuming to perform this operation repeteadly. For example,
   if we want to compare many solutions, all of them should be evaluated
   time after time. If a problem is dealing with many objective, a high 
   computational cost could arise. 

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef MULTIOBJECTIVESOLUTION_H
#define MULTIOBJECTIVESOLUTION_H

#include <iostream>
#include <string>
#include <vector>

#include "header.h"
#include "../libs/conversions.h"
#include "../libs/funcLibrary.h"

class multiObjectiveSolution 
{
   private:
      /**
         Vector of objectives. It holds the result of the evaluation of the problems
         using a givel solution.
      */
      objectivesType objectives;

      /**
         Vector of objective names. 
      */ 
      objectivesNameType objectivesName;

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      multiObjectiveSolution() { };

      /**
         Default destructor. It does nothing.
      */
      ~multiObjectiveSolution() { };

      /**
         Method that given a position in the vector of objectives returns its value.
         @param const unsigned is the position we want the value of.
         @return the value of the given position.
      */ 
      const T getObjective(const unsigned) const;

      /**
         Method that returns the vector of values.
         @return the vector of objectives.
      */
      const objectivesType& getObjectives() const;

      /**
         Method that returns the number objectives this solution has.
         @return the number of cells of the vector of objectives.
      */
      const unsigned getNumberOfObjectives() const;

      /**
         Method that returns a pointer to the vector of values.
         @return a pointer to the vector of objectives.
      */
      objectivesType* getPointerToObjectives() const;

      /**
         Method that sets the vector of values.
         @param const unsigned is the postion to be set.
         @param const T is the value to be set in the given position.
      */
      void setObjective(const unsigned, const T);

      /**
         Method that sets the whole vector of values.
         @param const objectivesType& is the vector to be set.
      */
      void setObjectives(const objectivesType&);

      /**
         Method that returns whether the vector of values is empty or not.
         @param a boolean expression that is true if the vector of values is empty and false if not.
      */
      const bool isEmpty() const;

      /**
         Operator that returns true if a solution if equal to the current one (the 
         one this object holds).
         @param const multiObjectiveSolution* is a pointer to the solution to be compared with the 
         current one.
      */
      bool operator==(const multiObjectiveSolution* const) const;

      /**
         Method that turns the numerical values contained in the data-structure this object work
         with to a std::string. This has been designed to output the information of the attributes
         of this object.
         return a std::string that contains the numerical values in a string format.
      */
      const std::string objectivesToString() const;

      /**
         Virtual method that is intended to provide access from this class to the output
         of inherited classes. This it's not necessary to access inner classes using 'casts'
         but it's only needed use this function as a gateway.
         @return a string that contains a solution in a string format.
      */      
      virtual const std::string toString() const = 0;

      /**
         Virtual method that forces to implement the copy of inner data-structures in 
         inherited classes. This acts as the copy-constructor.
         @param const multiObjectiveSolution* is the object we want to copy from.
      */
      virtual void copy(const multiObjectiveSolution* const) = 0;
};

inline const std::string multiObjectiveSolution::objectivesToString() const
{
   std::string os = "";
   for (size_t i = 0; i < this->objectives.size(); i++)
         os += objectivesName[i] + "= " + somethingToString<T>(this->objectives[i]) + '\n';
   return os;
}

inline const T multiObjectiveSolution::getObjective(const unsigned i) const
{
   assert(this->objectives.size() > i);
   return this->objectives[i];
}

inline const objectivesType& multiObjectiveSolution::getObjectives() const
{
   return this->objectives;
}

inline const unsigned multiObjectiveSolution::getNumberOfObjectives() const
{
   return this->objectives.size();
}

inline objectivesType* multiObjectiveSolution::getPointerToObjectives() const
{
   return const_cast<objectivesType*>(&(this->objectives));
}

inline void multiObjectiveSolution::setObjective(const unsigned i, const T objective)
{
   assert(this->objectives.size() > i);
   this->objectives[i] = objective;
}

inline void multiObjectiveSolution::setObjectives(const objectivesType& objectives)
{
   this->objectives = objectives;
}

inline const bool multiObjectiveSolution::isEmpty() const 
{
   return (this->objectives.size() == 0);
}

inline bool multiObjectiveSolution::operator==(const multiObjectiveSolution* const object) const
{
   // They are pointing to the same place, so they are the same
   if (this == object)
      return true;

   // The incoming object cannot point to NULL
   assert(object != NULL);
   // We're not permitting the comparison between different types of solutions
   assert(this->objectives.size() == object->getObjectives().size());

   for (size_t i = 0; i < this->objectives.size(); i++)
      if (this->objectives[i] != object->getObjective(i))
         return false;
   return true;
}

#endif
