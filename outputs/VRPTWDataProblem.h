#ifndef VRPTWDATAPROBLEM_H
#define VRPTWDATAPROBLEM_H

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <memory>

#include "../libs/conversions.h"
#include "dataTypes.h"
#include "../libs/IOlibrary.h"
// #include "../graphics/paintable.h"


class VRPTWDataProblem /*: public paintable*/
{
   private:
      // Singleton Pattern
      static VRPTWDataProblem* VRPTWData;

      coordsType clientCoords;

      // With a large amount of client would be better to use a triangular matrix
      //    for n clients: n x n / 2 cells
      distanceMatrixType distanceMatrix;
      timeMatrixType timeMatrix;
      serviceTimeType serviceTime;
      timeWindowType timeWindow;
      fleetType fleet;
      demandType demand; 

   protected:
      VRPTWDataProblem() { };
      ~VRPTWDataProblem() { };
      
      static void destroySingleton() { delete VRPTWData; VRPTWData = NULL; };

   public:
      static VRPTWDataProblem* instance();

      void setClientCoords(const coordsType&); 
      void setDistanceMatrix(const distanceMatrixType&);
      void setTimeMatrix(const timeMatrixType&);
      void setServiceTime(const serviceTimeType&);
      void setTimeWindow(const timeWindowType&);
      void setFleet(const fleetType&);
      void setDemand(const demandType&);
      
      const coordsType& getClientCoords() const { return this->clientCoords; };
      const distanceMatrixType& getDistanceMatrix() const;
      const timeMatrixType& getTimeMatrix() const;
      const serviceTimeType& getServiceTime() const;
      const timeWindowType& getTimeWindow() const;
      const fleetType& getFleet() const;
      const demandType& getDemand() const;

      
      void insertVehicle(const vehicleType&);
      void insertCoord(const pointType&);
      void insertDemand(const singleDemandType& demand);
      void insertTimeWindow(const singleTimeWindowType&);
      void insertServiceTime(const timeType&);

      void calculateDistanceMatrix();
      void print() const;
      void paint();


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
 /*  std::cout << "Time Matrix: " << std::endl;
   // std::cout << distanceMatrix << std::endl;
   for (size_t i = 0; i < distanceMatrix.size(); i++)
   {
      for (size_t j = 0; j < distanceMatrix[i].size(); j++)
         std::cout << distanceMatrix[i][j] << ";"; 
      std::cout << std::endl;
   }

   print();*/
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
/*
inline void VRPTWDataProblem::paint()
{
   resizeWindow( 600, 600);
   setTitle("CODEA-2- Problem Data");
 
   drawPoint(clientCoords[0].first, clientCoords[0].second, 0.5,  "red");
   drawText("0", clientCoords[0].first, clientCoords[0].second);
   for (coordsType::size_type i = 1; i < clientCoords.size(); i++)
   {
      drawPoint(clientCoords[i].first, clientCoords[i].second, 0.5);
      drawText(somethingToString<cityIDType>(i).c_str(), clientCoords[i].first, clientCoords[i].second);
   }
   display();
}
*/
#endif
