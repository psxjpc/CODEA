/** 
   @library datatypes
  
   @brief Stores the definition of VRP(TW) types.

   This class holds all the data types that are necessary
   to work with VRP(TW) using this implementation.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#include <vector>
#include <list>


/**
   These are used in the VRPLib.
*/
typedef unsigned A;
typedef std::vector<A> chromosomeType;

/**
   Type for the ID of the costumer.
*/
typedef unsigned cityIDType;
/**
   Type for distances.
*/
typedef double distanceType;
/**
   Type for time.
*/
typedef long timeType;
/**
   Type for capacities.
*/
typedef double capacityType;
/**
   Type for the pair that constitudes the time window.
*/
typedef std::pair<timeType, timeType> singleTimeWindowType;
/**
   Type for the pair that constitudes the vehicle.
*/
typedef std::pair<unsigned, capacityType> vehicleType;
/**
   Type for the demand.
*/
typedef double singleDemandType;
/**
   Type for the X-coord.
*/
typedef double XCoordType;
/**
   Type for the Y-coord.
*/
typedef double YCoordType;
/**
   Type for the pair that constitude the position of a costumer.
*/
typedef std::pair<XCoordType, YCoordType> pointType;

/**
   Type for the routes.
*/
typedef std::vector<cityIDType> routesType;
/**
   Type for the coordinates. 
*/
typedef std::vector<pointType> coordsType;
/**
   Type for the matrix of distances.
*/
typedef std::vector<std::vector<distanceType> >  distanceMatrixType;
/**
   Type for the matrix of travel times.
*/
typedef std::vector<std::vector<timeType> > timeMatrixType;
/**
   Type for the service time.
*/
typedef std::vector<timeType> serviceTimeType;
/**
   Type for the time window.
*/
typedef std::vector<singleTimeWindowType> timeWindowType;
/**
   Type for the fleet.
*/
typedef std::vector<vehicleType> fleetType;
/**
   Type for the demand.
*/
typedef std::vector<singleDemandType> demandType;
/**
   Type for creating the zone/groups relationship
*/
typedef std::vector<vector<cityIDType> > costumerZoneType;

