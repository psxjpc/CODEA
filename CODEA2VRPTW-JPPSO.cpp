// C++ classes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Core classes
#include "./core/coDecentralizedArchitecture.h"
#include "./core/agent.h"
#include "./core/multiObjectiveSolution.h"
#include "./core/multiObjectiveProblem.h"
#include "./core/singleObjectiveProblem.h"
#include "./core/systemGeneralStopCriterion.h"

// Code parameters
#include "./core/codeaParameters.h"

// Objectives
#include "./problems/VRPTW/objectives/numberOfVehiclesProblem.h"
#include "./problems/VRPTW/objectives/distanceProblem.h"
#include "./problems/VRPTW/objectives/elapsedTimeProblem.h"
#include "./problems/VRPTW/objectives/timeWindowViolationProblem.h"
#include "./problems/VRPTW/objectives/timeWindownViolationProblem.h"
#include "./problems/VRPTW/objectives/vehicleCapacityViolationProblem.h"
#include "./problems/VRPTW/objectives/vehicleCapacitynViolationsProblem.h"
#include "./problems/VRPTW/objectives/waitingTimeProblem.h"


// Multi-objective Score Criterion
#include "./core/MOScoreCriterionTypes/aggregationMOScoreCriterion.h"
#include "./core/MOScoreCriterionTypes/basicParetoFrontMOScoreCriterion.h"

// Neighborhood
#include "./core/neighborhoodTypes/staticNeighborhood.h"

// VRPTW classes
#include "./problems/VRPTW/dataTypes.h"
#include "./problems/VRPTW/VRPTWDataProblem.h"
#include "./problems/VRPTW/VRPSolution.h"

// Libs
#include "./libs/conversions.h"
#include "./libs/funcLibrary.h"

// Agents
#include "./agents/JPPSO/swarmAgent.h"

// Phases
#include "./agents/JPPSO/phases/DPSOCommunicationPhase.h"
#include "./agents/JPPSO/phases/DPSOResolutorPhase.h"


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

int main( int argc, char **argv )
{
   cout << "CODEA - MOJPPSO 4 VRPTW" << endl;
   cout << "---------------------" << endl;

   if (argc < 3)
   {
      cout << "ERROR[!]" << endl;
      cout << "You must provide:" << endl;
      cout << "  - a filename with the data of the problem." << endl;
      cout << "  - the number of vehicles you want to work with." << endl;
      cout << "Example ./CODEA2 data.txt 10" << endl;
      exit(1);
   }
   cout << "Starting up..." << endl;

   // Seed
   srand(time(NULL));
   MTRand randomNumber(time(NULL));

   // Get data from files
   readSolomonDataFile(argv[1]);
   unsigned numberOfVehicles = atoi(argv[2]);
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   VRPTWData->calculateDistanceMatrix();

   // Creation of the agents  
   unsigned numberOfAgents = 50;
   deque<message> inBox;
   vector<agent*> frogAgents;

   // All the agents will point to the best social solution
   multiObjectiveSolution* bestMOSolution = new VRPSolution(VRPTWData->getClientCoords().size());
   codeaParameters* neuralItem = codeaParameters::instance();  
   neuralItem->setRandomNumber(&randomNumber);


   for (unsigned i = 0; i < numberOfAgents; i++)
   {
      agent* superFrog = new agent();
      
      // Box for messages
      superFrog->setInBox(inBox);

      // Agetn's id
      superFrog->setId(i);

      // Problem - Objectives
      singleObjectiveProblem* vehiclesProblem = new numberOfVehiclesProblem;
      singleObjectiveProblem* elapsedProblem = new elapsedTimeProblem;
      singleObjectiveProblem* waitingProblem = new waitingTimeProblem;
      singleObjectiveProblem* distancesProblem = new distanceProblem;
      singleObjectiveProblem* timeWindowProblem = new timeWindowViolationProblem;
      singleObjectiveProblem* timeWindownProblem = new timeWindownViolationProblem;
      singleObjectiveProblem* vehicleCapacityProblem = new vehicleCapacityViolationProblem;
      singleObjectiveProblem* vehicleCapacitynProblem = new vehicleCapacitynViolationsProblem;

      // By default they are set to false [Agents]
      vehiclesProblem->setIsComparable(true);
      distancesProblem->setIsComparable(true);
      vehicleCapacityProblem->setIsComparable(true);
      timeWindownProblem->setIsComparable(true);
      //waitingProblem->setIsComparable(true);
      //elapsedProblem->setIsComparable(true);

      // By default they are set to false [Global]
      vehiclesProblem->setIsGlobalComparable(true);
      //distancesProblem->setIsGlobalComparable(true);
      vehicleCapacityProblem->setIsGlobalComparable(true);
      timeWindownProblem->setIsGlobalComparable(true);
      //waitingProblem->setIsGlobalComparable(true);
      //elapsedProblem->setIsGlobalComparable(true);  

      // Problem 
      multiObjectiveProblem* MOVRPTW = new multiObjectiveProblem;
      MOVRPTW->setMOScoreCriterion(new basicParetoFrontMOScoreCriterion());
      MOVRPTW->addProblem(vehiclesProblem);
      MOVRPTW->addProblem(elapsedProblem);
      MOVRPTW->addProblem(waitingProblem);
      MOVRPTW->addProblem(distancesProblem);
      MOVRPTW->addProblem(timeWindowProblem);
      MOVRPTW->addProblem(timeWindownProblem);
      MOVRPTW->addProblem(vehicleCapacityProblem);
      MOVRPTW->addProblem(vehicleCapacitynProblem);

      // Agent's Core
      JFOAgent* frog = new JFOVRPAgent();
      frog->setProblem(MOVRPTW);
      frog->initializeParameters();
      superFrog->setCore(frog);

      // Solution
      multiObjectiveSolution* MOVRPTWSol = new VRPSolution(VRPTWData->getClientCoords().size());
      (static_cast<VRPSolution*>(MOVRPTWSol))->setRandomRoutes(numberOfVehicles);
      (superFrog->getCore())->setCurrentSolution(MOVRPTWSol);
      (superFrog->getCore())->setBestSolution(bestMOSolution);
      MOVRPTW->evaluate(MOVRPTWSol);
      // Phases
      // Note: It's very important how we add the phases. Because they'll be
      //       executed in the same order.
      vector<phase*> phases;
      phases.push_back(new JFOCommunicationPhase());
      phases.push_back(new JFOResolutorPhase(frog->getPointerToC1(), frog->getPointerToC2(), frog->getPointerToC3(), frog->getPointerToC4()));
      superFrog->setPhases(phases);

      // Addition of this agent to the system
      frogAgents.push_back(superFrog);
   }

   // Neighborhood
   for (size_t i = 0; i < frogAgents.size(); i++)
      frogAgents[i]->setNeighborhood(new staticNeighborhood(&frogAgents));

   // Iterations of the system
   systemGeneralStopCriterion* haltCriterion = new systemGeneralStopCriterion();
   haltCriterion->setMaxIteration(10000000); 


   // Creation of the system
   coDecentralizedArchitecture CODEA;
   CODEA.setAgents(frogAgents);
   CODEA.setNumberOfPhases(2);
   CODEA.setStopCriterion(haltCriterion);
   CODEA.start();  
   cout << "End!" << endl;


   return 0;

}
