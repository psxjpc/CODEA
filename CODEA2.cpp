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
// Experimental
#include "./problems/VRPTW/objectives/timeWindowsDistribution.h"


// Multi-objective Score Criterion
#include "./core/MOScoreCriterionTypes/aggregationMOScoreCriterion.h"
#include "./core/MOScoreCriterionTypes/basicParetoFrontMOScoreCriterion.h"
#include "./core/MOScoreCriterionTypes/dynamicLexMOScoreCriterion.h"

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
#include "JFOVRPAgent.h"

// Phases
#include "./agents/JFO/JFOphases/JFOCommunicationPhase.h"
#include "./agents/JFO/JFOphases/JFOResolutorPhase.h"


using namespace std;

void readCordeauDataFile(const char* fileName)
{
   std::fstream file;
   file.open(fileName);
   std::string line;
   unsigned numberOfLine = 1;
   std::vector<string> splittedLine;

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   // Cordeau's benchmark problems have the same format. So this algorithm extract
   //   its data and stores it into an VRPTW->class data structure. 
   unsigned sizeOfFleet = 0;
   while (getline(file, line))
   {
     splittedLine.clear();
     splitString(line, splittedLine);

     if (numberOfLine == 1)
        sizeOfFleet = fromStringTo<unsigned>(splittedLine[1]);

     else if (numberOfLine == 2)
     {
        vehicleType vehicle(sizeOfFleet, fromStringTo<capacityType>(splittedLine[1]));
        VRPTWData->insertVehicle(vehicle);
     }
     else if (numberOfLine >= 3)
     {
        // The first column is the id of the costumer (we won't use it)
        // *

        // The second and the third columns are the coordinates
        pointType clientPosition(fromStringTo<XCoordType>(splittedLine[1]), fromStringTo<YCoordType>(splittedLine[2]));
        VRPTWData->insertCoord(clientPosition);

        // The third column represents the service time
        timeType clientServiceTime = fromStringTo<timeType>(splittedLine[3]);
        VRPTWData->insertServiceTime(clientServiceTime);

        // The fourth column is the amount of demand
        singleDemandType clientDemand = fromStringTo<singleDemandType>(splittedLine[4]);
        VRPTWData->insertDemand(clientDemand);

        // The fith and sith column are the time window
        // The thrid line has a column less than the rest. 
        if (numberOfLine == 3)   
        {
           singleTimeWindowType clientTimeWindow(fromStringTo<timeType>(splittedLine[7]), fromStringTo<timeType>(splittedLine[8]));
           VRPTWData->insertTimeWindow(clientTimeWindow);
        }
        else 
        {
           singleTimeWindowType clientTimeWindow(fromStringTo<timeType>(splittedLine[8]), fromStringTo<timeType>(splittedLine[9]));
           VRPTWData->insertTimeWindow(clientTimeWindow);
        }

       

     }
     numberOfLine++;
   }
   // VRPTWData->print();
   // exit(0);
}

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
   //cout << "CODEA - MOJFO 4 VRPTW" << endl;
   //cout << "---------------------" << endl;

   if (argc < 5)
   {
      cout << "ERROR[!]" << endl;
      cout << "You must provide:" << endl;
      cout << "  - a filename with the data of the problem." << endl;
      cout << "  - the number of vehicles you want to work with." << endl;
      cout << "  - the number of agents within the swarm." << endl;
      cout << "  - the number of evolutions. " << endl;
      cout << "  - the ranking type: 0 Pareto, 1 Lexicographic, 2 Dynamic lexicographic. " << endl;
      cout << "  - seed." << endl;
      cout << "Example ./CODEA2 data.txt 10 50 5000 0 200" << endl;
      exit(1);
   }
   //cout << "Starting up..." << endl;

   // Variables
   char* fileName = argv[1];
   unsigned numberOfVehicles = atoi(argv[2]);
   unsigned numberOfAgents = atoi(argv[3]);
   unsigned numberOfEvolutions = atoi(argv[4]);
   unsigned rankingType = atoi(argv[5]);
   unsigned seed = atoi(argv[6]);


   

   // Seed
   //srand(time(NULL));
   //MTRand randomNumber(time(NULL));

   srand(seed);
   MTRand randomNumber(seed);

   // Get data from files
   // readSolomonDataFile(fileName);
   readCordeauDataFile(fileName);

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   VRPTWData->calculateDistanceMatrix();

   // @Experimental: This is a new approach to add a new objective that takcles the tw violations in a different way
   //VRPTWData->createZones(numberOfVehicles);


   // Creation of the agents  

   deque<message> inBox;
   vector<agent*> frogAgents;

   // All the agents will point to the best social solution
   multiObjectiveSolution* bestMOSolution = new VRPSolution(VRPTWData->getClientCoords().size());
   codeaParameters* neuralItem = codeaParameters::instance();  
   neuralItem->setRandomNumber(&randomNumber);

   // Ranking scheme
   neuralItem->rankingScheme = rankingType; 


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
      //singleObjectiveProblem* timeWindowsDistributionProblem = new timeWindowsDistribution;
      
      // Setting priorities
      vehiclesProblem->setPriority(3);
      elapsedProblem->setPriority(4);
      waitingProblem->setPriority(2);
      distancesProblem->setPriority(1);
      timeWindowProblem->setPriority(5);
      timeWindownProblem->setPriority(0);
      vehicleCapacityProblem->setPriority(6); 
      vehicleCapacitynProblem->setPriority(7);
      //timeWindowsDistributionProblem->setPriority(0);


      // By default they are set to false [Agents]
      vehiclesProblem->setIsComparable(true);
      distancesProblem->setIsComparable(true);
      vehicleCapacityProblem->setIsComparable(true);
      timeWindownProblem->setIsComparable(true);
      //waitingProblem->setIsComparable(true);
      //elapsedProblem->setIsComparable(true);
      //timeWindowsDistributionProblem->setIsComparable(true);

      // By default they are set to false [Global]
      vehiclesProblem->setIsGlobalComparable(true);
      distancesProblem->setIsGlobalComparable(true);
      //vehicleCapacityProblem->setIsGlobalComparable(true);
      timeWindownProblem->setIsGlobalComparable(true);
      //waitingProblem->setIsGlobalComparable(true);
      //elapsedProblem->setIsGlobalComparable(true);  
      //timeWindowsDistributionProblem->setIsGlobalComparable(true);

      // Problem 
      multiObjectiveProblem* MOVRPTW = new multiObjectiveProblem;
      MOVRPTW->addProblem(vehiclesProblem);
      MOVRPTW->addProblem(elapsedProblem);
      MOVRPTW->addProblem(waitingProblem);
      MOVRPTW->addProblem(distancesProblem);
      MOVRPTW->addProblem(timeWindowProblem);
      MOVRPTW->addProblem(timeWindownProblem);
      MOVRPTW->addProblem(vehicleCapacityProblem);
      MOVRPTW->addProblem(vehicleCapacitynProblem);
      //MOVRPTW->addProblem(timeWindowsDistributionProblem);
      //MOVRPTW->setMOScoreCriterion(new dynamicLexMOScoreCriterion(MOVRPTW->getProblems().size()));
      MOVRPTW->setMOScoreCriterion(new basicParetoFrontMOScoreCriterion());

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
     
   // WARNING: If the agent zero does not contains the problem, this will crash
   neuralItem->setProblems(&(frogAgents[0]->getCore()->getProblem()->getProblems())); 


   // Iterations of the system
   systemGeneralStopCriterion* haltCriterion = new systemGeneralStopCriterion();
   haltCriterion->setMaxIteration(2000); 


   // Creation of the system
   coDecentralizedArchitecture CODEA;
   CODEA.setAgents(frogAgents);
   CODEA.setNumberOfPhases(2);
   CODEA.setStopCriterion(haltCriterion);
   CODEA.start();  
   cerr << "End!" << endl;


   return 0;

}
