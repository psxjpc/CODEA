# Makefile test

MAIN= CODEA2.cpp
SRCS= 

INCS= ./core/abstractMOScoreCriterion.h ./core/container.h ./core/header.h ./core/neighborhood.h ./core/stopCriterion.h ./core/agent.h ./core/core.h ./core/mailBox.h ./core/phase.h ./core/systemGeneralStopCriterion.h ./core/codeaParameters.h ./core/decentralizedSystem.h ./core/multiObjectiveProblem.h ./core/singleObjectiveProblem.h ./core/systemStopCriterion.h ./core/coDecentralizedArchitecture.h ./core/generalStopCriterion.h ./core/multiObjectiveSolution.h ./core/ssystem.h ./core/MOScoreCriterionTypes/aggregationMOScoreCriterion.h  ./core/MOScoreCriterionTypes/basicParetoFrontMOScoreCriterion.h ./core/neighborhoodTypes/staticNeighborhood.h
 
PLIBS= 
LIBS= ./libs/debugGCCHelper.h  ./libs/funcLibrary.h  ./libs/geneticAlgorithms.h  ./libs/IOlibrary.h ./libs/conversions.h

MISC= ./misc/file.h  ./misc/MersenneTwister.h  ./misc/triBool.h
                                   
AGNT= ./agents/JFOAgent/JFOAgent.h ./agents/JFOAgent/JFOphases/JFOCommunicationPhase.h ./agents/JFOAgent/JFOphases/JFOResolutorPhase.h  .

PROB= ./problems/VRPTW/dataTypes.h ./problems/VRPTW/VRPLib.h ./problems/VRPTW/VRPSolution.h ./problems/VRPTW/VRPTWDataProblem.h ./problems/VRPTW/objectives/distanceProblem.h  ./problems/VRPTW/objectives/numberOfVehiclesProblem.h ./problems/VRPTW/objectives/timeWindowViolationProblem.h ./problems/VRPTW/objectives/vehicleCapacityViolationProblem.h ./problems/VRPTW/objectives/elapsedTimeProblem.h ./problems/VRPTW/objectives/timeWindownViolationProblem.h ./problems/VRPTW/objectives/vehicleCapacitynViolationsProblem.h ./problems/VRPTW/objectives/waitingTimeProblem.h

OBJS= CODEA2.o
EXEC= CODEA2
# Compiler
#
CC= g++
CFLAGS= -ansi -pedantic -I./libs/ -ansi -pedantic
CDEBUG= -ggdb -O0
QUICK= -O3 -march=nocona

# Rules
#
default: $(EXEC)	

$(EXEC): $(MAIN) $(SRCS) $(AGNT) $(PROB) $(INCS) $(MISC) $(LIBS)
	$(CC) $(CFLAGS) $(CDEBUG) $(MAIN) $(SRCS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC) core*.*

fast: 
	
	$(CC) $(CFLAGS) $(QUICK) $(MAIN) $(SRCS) -o $(EXEC)


.SUFFIXES: .c.o.cpp

%.o: %.c
	$(CC) $(CFLAGS) $(CDEBUG) -o $@ $<
