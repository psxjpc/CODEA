/** 
   @class VRPTWDataProblem
  
   @brief Stores the information of a VRP(TW) problem instance.

   This class is a storage centre for all the parameters of the VRP(TW)
   problem we are going to solve. It uses a Singleton Pattern to be
   accessible whithin the system at all levels.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef VRPTWDATAPROBLEM_H
#define VRPTWDATAPROBLEM_H

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <memory>

#include "../../libs/conversions.h"
#include "dataTypes.h"
#include "../../libs/IOlibrary.h"

class VRPTWDataProblem 
{
   private:
      /**
         Singleton Pattern. This pointers refers to itself.
      */
      static VRPTWDataProblem* VRPTWData;

      /**
         Vector that stores the position of the clients in an Euclidean space.
      */
      coordsType clientCoords;

      /** 
         Matrix that stores the distance between any pair of clients.
      */
      distanceMatrixType distanceMatrix;

      /** 
         Matrix that stores the travel time between any pair of clients.
      */
      timeMatrixType timeMatrix;

      /** 
         Vector that stores the service time of the clients, i.e, the time
         it takes to serve the client after you stop the truck.
      */
      serviceTimeType serviceTime;

      /** 
         Vector that stores the time window the clients must be served.
      */
      timeWindowType timeWindow;
      
      /**
         Vector that stores the capacity the fleet has.
      */ 
      fleetType fleet;

      /**
         Vector that stores the amount of demand the clients require.
      */
      demandType demand; 

   protected:
      /**
         Default constructor. It does nothing.
      */
      VRPTWDataProblem() { };

      /**
         Default destructor. It does nothing.
      */
      ~VRPTWDataProblem() { };
      
      /**
         Destructor of the Singleton Pattern. 
      */
      static void destroySingleton() { delete VRPTWData; VRPTWData = NULL; };

   public:

      /**
         Method that instances the Singleton Pattern. If it's the first time,
         it will create the object and return the pointer to it, if it already
         exists, it will return the existent pointer to it.         
      */
      static VRPTWDataProblem* instance();

      /**
         Method that sets the coords of the clients.
         @param const coordsType& is the vector that contains the coord of the client.
      */
      void setClientCoords(const coordsType&); 

      /**
         Method that sets the distance matrix.
         @param const distanceMatrixType& is the matrix that contains the matrix distance.
      */
      void setDistanceMatrix(const distanceMatrixType&);

      /**
         Method that sets the travel time matrix.
         @param const timeMatrixType& is the matrix that contains the matrix time travel.
      */
      void setTimeMatrix(const timeMatrixType&);

      /**
         Method that sets the service time vector.
         @param const serviceTimeType& is the vector that contains the service time.
      */
      void setServiceTime(const serviceTimeType&);

      /**
         Method that sets the time window vector.
         @param const timeWindowType& is the vector that contains the time windows.
      */
      void setTimeWindow(const timeWindowType&);

      /**
         Method that sets the fleet capacities.
         @param const fleetType& is the vector that contains the capacities of the fleet.
      */
      void setFleet(const fleetType&);

      /**
         Method that sets the amount of demand.
         @param const demantType& is the vector that contains the amount of demand.
      */
      void setDemand(const demandType&);
      
      /**
         Method that returns the coords of the clients.
         @return a vector that contains the coords of the clients.
      */
      const coordsType& getClientCoords() const { return this->clientCoords; };

      /**
         Method that returns the distances between any two pair of clients.
         @return a matrix tha contains the matrix with de distances.
      */
      const distanceMatrixType& getDistanceMatrix() const;

      /**
         Method that returns the time travel between any to pair of clients.
         @return a vector that contains the coords of the client.
      */
      const timeMatrixType& getTimeMatrix() const;

      /**
         Method that returns the service time of the clients
         @return a vector that contains the service time of the clients.
      */
      const serviceTimeType& getServiceTime() const;

      /**
         Method that returns the time window of the clients.
         @return a vector that contains the time windows of the clients.
      */
      const timeWindowType& getTimeWindow() const;

      /**
         Method that returns the capacity of the fleet.
         @return a vector that contains the capacity of each component of the of the fleet.
      */
      const fleetType& getFleet() const;

      /**
         Method that returns the demand of the clients.
         @return a vector that contains the demand of the clients.
      */
      const demandType& getDemand() const;

      /**
         Method to add a new vehicle into the fleet.
         @param const vehicle& is the new vechile to be added.
      */
      void insertVehicle(const vehicleType&);

      /**
         Method to add the coords of a new client.
         @param const pointtype& is the position of the new client to be added.
      */
      void insertCoord(const pointType&);

      /**
         Method to add a new demand of a client.
         @param const singleDemandType& is the new new demand to be added.
      */
      void insertDemand(const singleDemandType& demand);

      /**
         Method to add a new time window of a client.
         @param const singleTimeWindow& is the new time window to be added.
      */
      void insertTimeWindow(const singleTimeWindowType&);

      /**
         Method to add a new service time of a client.
         @param const vehicle& is the new service time to be added.
      */
      void insertServiceTime(const timeType&);

      /**
         Method that sets the distance matrix by using the coords of the clients.
         It applies the Ecludian equation to calculate the distance.
      */
      void calculateDistanceMatrix();

      /** 
         Method that prints the attributes of this objects.
         This is merely used to output all the data.
      */
      void print() const;
};
 


VRPTWDataProblem* VRPTWDataProblem::VRPTWData = NULL;

VRPTWDataProblem* VRPTWDataProblem::instance()
{
   if (VRPTWData == NULL)
   {
      VRPTWData = new VRPTWDataProblem;
      std::atexit(&VRPTWDataProblem::destroySingleton);
   }
   return VRPTWData;
}

inline void VRPTWDataProblem::setDistanceMatrix(const distanceMatrixType& distanceMatrix)
{
   this->distanceMatrix = distanceMatrix;
}

inline void VRPTWDataProblem::setTimeMatrix(const timeMatrixType& timeMatrix)
{
   this->timeMatrix = timeMatrix;
}

inline void VRPTWDataProblem::setServiceTime(const serviceTimeType& serviceTime)
{
   this->serviceTime = serviceTime;
}

inline void VRPTWDataProblem::setTimeWindow(const timeWindowType& timeWindow)
{
   this->timeWindow = timeWindow;
}

inline void VRPTWDataProblem::setFleet(const fleetType& fleet)
{
   this->fleet = fleet;
}

inline void VRPTWDataProblem::setDemand(const demandType& demand)
{
   this->demand = demand;
}
      
inline const distanceMatrixType& VRPTWDataProblem::getDistanceMatrix() const
{
   return this->distanceMatrix;
}

inline const timeMatrixType& VRPTWDataProblem::getTimeMatrix() const
{
   return this->timeMatrix;
}

inline const serviceTimeType& VRPTWDataProblem::getServiceTime() const
{
   return this->serviceTime;
}

inline const timeWindowType& VRPTWDataProblem::getTimeWindow() const
{
   return this->timeWindow;
}

inline const fleetType& VRPTWDataProblem::getFleet() const
{
   return this->fleet;
}

inline const demandType& VRPTWDataProblem::getDemand() const
{
   return this->demand;
}
 
inline void VRPTWDataProblem::insertVehicle(const vehicleType& vehicle) 
{
   this->fleet.push_back(vehicle);
}

inline void VRPTWDataProblem::insertCoord(const pointType& point)
{
   this->clientCoords.push_back(point);
}

inline void VRPTWDataProblem::insertDemand(const singleDemandType& demand)
{
   this->demand.push_back(demand);
}

inline void VRPTWDataProblem::insertTimeWindow(const singleTimeWindowType& singleTimeWindow)
{
   this->timeWindow.push_back(singleTimeWindow);
} 

inline void VRPTWDataProblem::insertServiceTime(const timeType& singleServiceTime)
{
   this->serviceTime.push_back(singleServiceTime);
}

inline void VRPTWDataProblem::calculateDistanceMatrix()
{
   distanceMatrix.resize(clientCoords.size());
   for (coordsType::size_type i = 0; i < clientCoords.size(); i++)
      distanceMatrix[i].resize(clientCoords.size());

   for (coordsType::size_type i = 0; i < clientCoords.size(); i++)
   { 
      distanceMatrix[i][i] = 0;
      for (coordsType::size_type j = 0; j < clientCoords.size(); j++)
         if (i != j)
         {
            distanceMatrix[i][j] = sqrt(pow(clientCoords[j].first - clientCoords[i].first, 2) 
                                      + pow(clientCoords[j].second - clientCoords[i].second, 2));
            distanceMatrix[j][i] = distanceMatrix[i][j];
         }
   }
}

inline void VRPTWDataProblem::print() const
{
   unsigned fieldWidth = 5;
   std::cout << "Clients Positions" << std::endl;
   for (coordsType::size_type i = 0; i < clientCoords.size(); i++)
      std::cout << std::setw(fieldWidth) << clientCoords[i].first << std::setw(fieldWidth) << clientCoords[i].second << std::endl;

   std::cout << std::endl;

   std::cout << "Demands" << std::endl;
   for (demandType::size_type i = 0; i < demand.size(); i++)
      std::cout << demand[i] << " ";
   std::cout << std::endl;

   std::cout << std::endl; 
   
   std::cout << "Fleet" << std::endl;
   for (fleetType::size_type i = 0; i < fleet.size(); i++)
      std::cout << std::setw(fieldWidth) << fleet[i].first << std::setw(fieldWidth) << fleet[i].second << std::endl;
   std::cout << std::endl;

   std::cout << std::endl; 
   
   std::cout << "TimeWindow" << std::endl;
   for (timeWindowType::size_type i = 0; i < timeWindow.size(); i++)
      std::cout << std::setw(fieldWidth) << timeWindow[i].first << std::setw(fieldWidth) << timeWindow[i].second << std::endl;
   std::cout << std::endl;

   std::cout << std::endl;

   std::cout << "Service Time" << std::endl;
   for (serviceTimeType::size_type i = 0; i < serviceTime.size(); i++)
      std::cout << serviceTime[i] << " ";
   std::cout << std::endl;

   std::cout << std::endl;

   std::cout << "Distance Matrix" << std::endl;
   std::cout << std::setw(fieldWidth + 5) << distanceMatrix << std::endl;
}

#endif
