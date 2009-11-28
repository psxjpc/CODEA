// C++ classes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// QT classes
#include <QApplication>
#include <QTimer>


// VRPTW classes
#include "./dataTypes.h"
#include "./VRPTWDataProblem.h"
#include "./VRPSolDisplayer.h"

// Libs
#include "../libs/conversions.h"
#include "../libs/funcLibrary.h"

using namespace std;

void readSolomonDataFile(const char* fileName)
{
   std::fstream file;
   file.open(fileName);
   std::string line;
   unsigned numberOfLine = 1;
   std::vector<string> splittedLine;

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   // Solomon's benchmark problems have the same format. So this algorithm extract
   //   its data and stores it into an VRPTW->class data structure. 
   while (getline(file, line))
   {
     if (numberOfLine == 5)
     {
        splitString(line, splittedLine);
        vehicleType vehicle(fromStringTo<unsigned>(splittedLine[0]), fromStringTo<capacityType>(splittedLine[1]));
        VRPTWData->insertVehicle(vehicle);
     }
     else if (numberOfLine >= 10)
     {
        splittedLine.clear();
        splitString(line, splittedLine);

        // The second and the third columns are the coordinates
        pointType clientPosition(fromStringTo<XCoordType>(splittedLine[1]), fromStringTo<YCoordType>(splittedLine[2]));
        VRPTWData->insertCoord(clientPosition);
        // The fourth column is the amount of demand
        singleDemandType clientDemand = fromStringTo<singleDemandType>(splittedLine[3]);
        VRPTWData->insertDemand(clientDemand);
        // The fith and sith column are the time window
        singleTimeWindowType clientTimeWindow(fromStringTo<timeType>(splittedLine[4]), fromStringTo<timeType>(splittedLine[5]));
        VRPTWData->insertTimeWindow(clientTimeWindow);
        // The last column represents the service time
        timeType clientServiceTime = fromStringTo<timeType>(splittedLine[6]);
        VRPTWData->insertServiceTime(clientServiceTime);
     }
     numberOfLine++;
   }
}

routesType readSolution(const char* fileName)
{
   routesType routes;
   std::fstream file;
   file.open(fileName);
   unsigned costumer;
   // This is to get rid of the objectives part of the solution
   std::string dummy;
   //for (unsigned i = 1; i < 10; i++)
   //   file >> dummy;
   while (file >> costumer)
      routes.push_back(costumer);
   file.close();
   return routes;
}


int main( int argc, char **argv )
{
   QApplication app(argc, argv);

   if (argc < 2)
   {
      cout << "ERROR[!]" << endl;
      cout << "(1) You must provide a filename with the data of the problem." << endl;
      cout << "(2) You must provide a filename with the route to be displayed." << endl;
      cout << "Ex. CODEA2 data.txt route.txt" << endl;
      exit(1);
   }


   
   VRPSolDisplayer dis;
   


   
      readSolomonDataFile(argv[1]);
      VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
      VRPTWData->calculateDistanceMatrix();

  
      dis.setRoutes(readSolution(argv[2]));
      dis.paint();

 //  }
   return app.exec();
}
