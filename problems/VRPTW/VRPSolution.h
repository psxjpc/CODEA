/** 
   @class VRPSolution
  
   @brief Stores the information of a VRP(TW) solution.

   This class is a storage centre for all the parameters of the VRP(TW)
   problem we are going to solve. It uses a Singleton Pattern to be
   accessible whithin the system at all levels.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef VRPSOLUTION_H
#define VRPSOLUTION_H

#include <iostream>
#include <string>
#include <vector>

#include "../../core/multiObjectiveSolution.h"
#include "../../core/codeaParameters.h"

#include "../../libs/conversions.h"
#include "../../libs/funcLibrary.h"


#include "./dataTypes.h"
#include "./VRPTWDataProblem.h"

#include <functional>
#include <algorithm>

class VRPSolution : public multiObjectiveSolution
{

   private:
      /**
         Stores the route-plan.
      */
      routesType routes;

      /**
         Iterator for the solution.
      */
      routesType::iterator routesIterator;

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      VRPSolution() { };

      /** 
         Alternative constructor. It gets the number of
         costumer this solution is going to work with.
         Next, it generates a vector with the costumers
         ready to introduce the number of vechiles.
         @param const unsigned& is the number of costumers
         to work with.
         
      */
      VRPSolution(const unsigned&);
 
      /**
         Standard constructor. It gets the route-plan
         and assigns it to the object in this class.
         @param const routesType& is the object that 
         contains the route-plan.
      */
      VRPSolution(const routesType&);


      VRPSolution(const multiObjectiveSolution* const);

      /**
         Default destructor. It does nothing.
      */
      ~VRPSolution() { };

      /**
         Copy method. It copies the current solution to
         a new one.
         @const multiObjectiveSolution* const is the pointer
         that points to the solution to be copied.
      */
      void copy(const multiObjectiveSolution* const);

      /**
         Method that initializes the strutures.
         It does the same as the Alterntive Constructor.
         @param const unsigned& is the number of costumers
         to work with.
      */
      void initialize(const unsigned&);

      /**
         Method that set the route-plan just like the
         Standard Constructor. 
         @param const routesType& is the object that contains
         the route-plan.
      */
      void setRoutes(const routesType&);

      /**
         Method that creates a random route-plan as a 
         way to initialize the solution.
         @const unsigned& is 
      */
      void setRandomRoutes(const unsigned&);
 
      /**
         Method that returns the route-plan this solution has.
         @returns the route-plan.
      */
      const routesType& getRoutes() const;

      routesType& getModificableRoutes()
      {   return this->routes;   }
      /**
         Method that returns the a pointer to the routes-plan.
         @return a pointer to the route-plan.
      */     
      routesType* getPointerToRoutes() const;
 
      /**
         Method that returns the number of vehicles this solution
         requires to serve all the costumers.
         @return the number of routes the solution has.
      */
      const unsigned getNumberOfRoutes();

      /**
         Method that uses the information given by a problem instance
         to check whether a solution is feasible or not.
      */
      static bool isFeasible();

      /**
         Method that uses the information given by a problem instance
         to check whether a solution is feasible or not.
         @param const VRPSolutio& is the solution to be checked.
      */
      static bool isFeasible(const VRPSolution&);

      /**
         Method that uses the information given by a problem instance
         to check whether a solution is feasible or not.
         @param const routesType& is route to be checked.
      */
      static bool isFeasible(const routesType&);

      /**
         Method that formats the solution in a std::string.
         @return a std::string with the solution data.
      */
      const std::string toString() const;

      multiObjectiveSolution* clone();
};

VRPSolution::VRPSolution(const routesType& routes)
{
   this->routes = routes;
}

multiObjectiveSolution* VRPSolution::clone()
{
   return new VRPSolution(this);
}

VRPSolution::VRPSolution(const multiObjectiveSolution* const newSolution)
{
   // Routes
   const VRPSolution* const newVRPSolution = static_cast<const VRPSolution* const>(newSolution);
   this->routes = newVRPSolution->getRoutes();

   // The objectives of the mother class
   setObjectives(newSolution->getObjectives());
}

VRPSolution::VRPSolution(const unsigned& numberOfCostumers)
{
   for (size_t i = 1; i < numberOfCostumers; i++)
      this->routes.push_back(i);
}

void VRPSolution::copy(const multiObjectiveSolution* const newSolution)
{
   // Routes
   const VRPSolution* const newVRPSolution = static_cast<const VRPSolution* const>(newSolution);
   this->routes = newVRPSolution->getRoutes();

   // The objectives of the mother class
   setObjectives(newSolution->getObjectives());
}

void VRPSolution::initialize(const unsigned& numberOfCities)
{
   for (size_t i = 0; i < numberOfCities; i++)
      this->routes.push_back(i);
}

const unsigned VRPSolution::getNumberOfRoutes()
{
   unsigned numberOfRoutes = 0;
   for (routesIterator = this->routes.begin(); routesIterator != this->routes.end(); routesIterator++)
      if ((*routesIterator) == 0)
         numberOfRoutes++;
   return (numberOfRoutes - 1);
}

// random generator function:
ptrdiff_t myrandom (ptrdiff_t i) 
{
 codeaParameters* neuralItem = codeaParameters::instance();  
 return neuralItem->getRandomNumber()->rand(i - 1);
}

// pointer object to it:
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;


inline void VRPSolution::setRandomRoutes(const unsigned& n = 10)
{
   
   for (size_t i = 1; i < n; i++)
      routes.push_back(0);

   random_shuffle(routes.begin(), routes.end(), p_myrandom);
   routes.insert(routes.begin(), 0);
   routes.push_back(0);
}

inline void VRPSolution::setRoutes(const routesType& routes)
{
   this->routes = routes;   
}

inline const routesType& VRPSolution::getRoutes() const
{
   return this->routes;
}

inline routesType* VRPSolution::getPointerToRoutes() const
{ 
   return const_cast<routesType*>(&this->routes); 
}

std::ostream& operator<<(std::ostream& os, const VRPSolution& object)
{
   os << std::endl;
   os << "Objectives: ";
   for (size_t i = 0; i < object.getObjectives().size(); i++)
      os << object.getObjective(i) << " ";
   os << std::endl;
   os << "Route: ";
   for (size_t i = 0; i < object.getRoutes().size(); i++)
      os << object.getRoutes()[i] << " ";
   os << std::endl; 

   return os;
}

const std::string VRPSolution::toString() const
{
   string outputString = "";
   for (size_t i = 0; i < getObjectives().size(); i++)
      outputString += somethingToString<T>(getObjective(i)) + " ";
 /*  outputString += "\n";
   outputString += "Route: ";
   for (size_t i = 0; i < getRoutes().size(); i++)
      outputString += somethingToString<T>(getRoutes()[i]) + " ";
   outputString += "\n";
*/
   return outputString;
}

#endif
