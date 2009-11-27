/** 
   @library VRPLib
  
   @brief Provides a number of operators to work with routes.
   
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef VRPLIB_H
#define VRPLIB_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "dataTypes.h"
#include "../../libs/funcLibrary.h"
#include "../../libs/IOlibrary.h"
#include "../../misc/MersenneTwister.h"
#include "VRPTWDataProblem.h"

#include "../../core/codeaParameters.h"
#include "../../core/singleObjectiveProblem.h"

#include "./objectives/elapsedTimeProblem.h"
#include "./objectives/distanceProblem.h"

// Objectives
#include "./objectives/numberOfVehiclesProblem.h"
#include "./objectives/distanceProblem.h"
#include "./objectives/timeWindowViolationProblem.h"
#include "./objectives/timeWindownViolationProblem.h"
#include "./objectives/vehicleCapacitynViolationsProblem.h"

typedef unsigned A;
typedef std::vector<A> chromosomeType;

inline unsigned rootGene(const chromosomeType& chromosome, unsigned gene)
{
   for (int i = gene; i >= 0; i--)
      if (chromosome[i] == 0)
         return i;

   cout << "VRPLib::selectARandomGene() is returning an unexpected value! - forcing exit" << endl;
   exit(1);
}

inline void selfLambdaOneInterchange(chromosomeType& parent, const string target = " ")
{
   codeaParameters* neuralItem = codeaParameters::instance();

   unsigned numberOfChanges = neuralItem->getRandomNumber()->randInt(parent.size() / 2);
   unsigned x, y;

   for (unsigned times = 0; times < numberOfChanges; times++)
   {
      do
      {
         x = neuralItem->getRandomNumber()->randInt(parent.size() - 2);
         y = neuralItem->getRandomNumber()->randInt(parent.size() - 2);

      }
      while (x == y || parent[x] == 0 || parent[y] == 0 || rootGene(parent, x) == rootGene(parent, y));
      basic::swap(parent, x, y);
   }

}

inline chromosomeType lambdaOneInterchange(const chromosomeType& parent, const string target = " ")
{
  // cout << "<lambda-i>" << endl;
   chromosomeType offspring = parent;
   codeaParameters* neuralItem = codeaParameters::instance();

   unsigned numberOfChanges = neuralItem->getRandomNumber()->randInt(offspring.size() / 2);
   unsigned x, y;
   for (unsigned times = 0; times < numberOfChanges; times++)
   {
      do
      {
         x = neuralItem->getRandomNumber()->randInt(offspring.size() - 2);
         y = neuralItem->getRandomNumber()->randInt(offspring.size() - 2);

      }
      while (x == y || parent[x] == 0 || parent[y] == 0 || rootGene(parent, x) == rootGene(parent, y));
      basic::swap(offspring, x, y);
   }
   return offspring;
}

inline chromosomeType twoOpt(const chromosomeType& parent, const string target = " ")
{
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   chromosomeType offspring = parent;
   chromosomeType bestOffspring;
   T bestScoreA = INFd;
   T scoreA = 0;
   
   elapsedTimeProblem elapsedProblem;

   unsigned dist = 1;
   unsigned numberOfLoops = 1;// + neuralItem->getRandomNumber()->randInt(offspring.size() / 2);
   for (size_t k = 0; k < numberOfLoops; k++)
      for (size_t i = 1; i + dist <= offspring.size() - 2; i++)
      {
         basic::swap(offspring, i, (i + dist));
         scoreA = 0;

         for (size_t j = 0; j < offspring.size() - 1; j++)
            scoreA += VRPTWData->getDistanceMatrix()[offspring[j]][offspring[j + 1]];

         if (scoreA < bestScoreA)
         {
            bestOffspring = offspring;
            bestScoreA = scoreA;
         }
         basic::swap(offspring, i, (i + dist));
      }

   return bestOffspring;
}

inline unsigned findElement(const chromosomeType& parent, unsigned element)
{
   for (size_t i = 1; i < parent.size() - 1; i++)
      if (parent[i] == element)
         return i;
   std::cout << "VRPLib.h::findElement(const chromosomeType& parent, unsigned element)" << std::endl;
   std::cout << "Message: <element = " << element << "> not found" << std::endl;
   exit(1);
}

inline unsigned selectAnElement(const chromosomeType& chromosome)
{
   codeaParameters* neuralItem = codeaParameters::instance();
   int n = 0;

   do n = neuralItem->getRandomNumber()->randInt(chromosome.size() - 3) + 1;
   while (chromosome[n] == 0);

   return n;
}

inline bool findElements(const chromosomeType& parent, unsigned start, unsigned length, unsigned element)
{
   for (size_t i = start; i < start + length; i++)
      if (parent[i] == element)
         return true;
   return false;
}

// This will remove two consecutives zeros in the chromosome
inline void cleanChromosome(chromosomeType& chromosome)
{  
   chromosomeType::iterator result;
   result = adjacent_find( chromosome.begin(), chromosome.end());
   while (result != chromosome.end())
   {   
      chromosome.erase(result);
      result = adjacent_find( chromosome.begin(), chromosome.end());
   }
}

inline chromosomeType MType1(const chromosomeType& parent, const chromosomeType& attractor, const string target = " ")
{
   chromosomeType offspring = parent;
   double bestScore = INFd;
   double score = INFd;
   int index = -1;
   unsigned length = 3;
   distanceProblem distancesProblem;
   codeaParameters* neuralItem = codeaParameters::instance();

   for (size_t i = 0; i < attractor.size() - length; i++)
   {
      score = distancesProblem.evaluate(attractor, i, length);
      if ((score < bestScore) /* && !findElements(attractor, i, length, 0) && (neuralItem->getRandomNumber()->rand() > 0.2)*/)
      {
         bestScore = score;
         index = i;
      }
   }

   for (size_t i = 0; i < length; i++)
      if (attractor[i + index] != 0)
         remove(offspring.begin(), offspring.end(), attractor[i + index]);

   unsigned start = neuralItem->getRandomNumber()->randInt(offspring.size() - 3) + 1;

   for (size_t i = 0; i < length; i++)
      offspring.insert(offspring.begin() + start + i, attractor[index + i]);

   // cleanChromosome(offspring);
   
   return offspring;   
}

chromosomeType MType0(const chromosomeType& parent, const chromosomeType& attractor, const string target = " ")
{ 
   chromosomeType offspring = parent;
   unsigned elementPositionInParent = selectAnElement(parent);   
   unsigned elementPositionInAttractor = findElement(attractor, parent[elementPositionInParent]);
   unsigned elementPositionToExchange = findElement(parent, attractor[elementPositionInAttractor - 1]);
   basic::move<A>(offspring, elementPositionToExchange, elementPositionInParent);
   return offspring;
}

inline void selfMType0(chromosomeType& parent, const chromosomeType& attractor, const string target = " ")
{ 
   unsigned elementPositionInParent = selectAnElement(parent);   
   unsigned elementPositionInAttractor = findElement(attractor, parent[elementPositionInParent]);
   unsigned elementPositionToExchange = findElement(parent, attractor[elementPositionInAttractor - 1]);
   basic::move<A>(parent, elementPositionToExchange, elementPositionInParent);
}

chromosomeType localSearch(const chromosomeType& parent, const string target = "")
{
   codeaParameters* neuralItem = codeaParameters::instance();

   timeWindownViolationProblem twvp;
   distanceProblem dp;
   double bestScore = INFd;
   double score = INFd;
   double bestScoreTW = INFd;
   double scoreTW = INFd;
   chromosomeType bestOffspring;
   chromosomeType offspring = parent;
   bool improvement = true;
   bool greedy = true;
   while (improvement)
   {
      improvement = false;
      for (size_t distance = 1; distance < (offspring.size() - 1); distance++)
      {
         for (size_t i = 1; i < (offspring.size() - distance - 1); i++)
         {
            basic::swap(offspring, i, i + distance);
            scoreTW = twvp.evaluate(offspring);
            score = dp.evaluate(offspring);
            if (bestScore >= score && bestScoreTW > scoreTW)
            {
               bestOffspring = offspring;
               bestScore = score;
               bestScoreTW = scoreTW;
               improvement = true;
            }
            if (improvement && greedy)
               break;
            basic::swap(offspring, i, i + distance);
         }
         if (improvement && greedy)
            break;
      }
      offspring = bestOffspring;
   }
   return bestOffspring;
}


inline void selfLocalSearch(chromosomeType& parent, const string target = "")
{
   codeaParameters* neuralItem = codeaParameters::instance();

   timeWindownViolationProblem twvp;
   distanceProblem dp;
   double bestScore = INFd;
   double score = INFd;
   double bestScoreTW = INFd;
   double scoreTW = INFd;
   chromosomeType bestOffspring;

   bool improvement = true;
   bool greedy = true;
   while (improvement)
   {
      improvement = false;
      for (size_t distance = 1; distance < (parent.size() - 1); distance++)
      {
         for (size_t i = 1; i < (parent.size() - distance - 1); i++)
         {
            basic::swap(parent, i, i + distance);
            scoreTW = twvp.evaluate(parent);
            score = dp.evaluate(parent);
            if (bestScore >= score && bestScoreTW > scoreTW)
            {
               bestOffspring = parent;
               bestScore = score;
               bestScoreTW = scoreTW;
               improvement = true;
            }
            if (improvement && greedy)
               break;
            basic::swap(parent, i, i + distance);
         }
         if (improvement && greedy)
            break;
      }
      parent = bestOffspring;
   }

}

inline void selfCloserNode(chromosomeType& parent, const string target = " ")
{
   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   double bestScore = INFd;
   double score = INFd;
   int index = -1;

   unsigned node = selectAnElement(parent);
   for (size_t i = 1; i < parent.size() - 3; i++)
      if (i != node) 
      {
         score = VRPTWData->getDistanceMatrix()[parent[node]][parent[i]];
         if (score < bestScore)
         {
            bestScore = score;
            index = i;
         }
      }

   basic::move<A>(parent, index, node);

}


chromosomeType closerNode(const chromosomeType& parent, const string target = " ")
{
   // return localSearch(parent);

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();
   chromosomeType offspring = parent;
   double bestScore = INFd;
   double score = INFd;
   int index = -1;

   unsigned node = selectAnElement(offspring);
   for (size_t i = 1; i < offspring.size() - 3; i++)
      if (i != node) 
      {
         score = VRPTWData->getDistanceMatrix()[offspring[node]][offspring[i]];
         if (score < bestScore)
         {
            bestScore = score;
            index = i;
         }
      }

   basic::move<A>(offspring, index, node);
   return offspring;
}

chromosomeType twitter(const chromosomeType& follower, const chromosomeType& attractor, const string target = " ")
{
   chromosomeType next = follower;
   // get a random sub-route
   codeaParameters* neuralItem = codeaParameters::instance();
   if (neuralItem->getRandomNumber()->rand() < 0.60)
      return MType0(attractor, follower, target);
   //cout << "<twitter>" << endl;
   unsigned scr = rootGene(attractor, neuralItem->getRandomNumber()->randInt(attractor.size() - 2));

   //cout << "A: " << attractor << endl;
   //cout << "F: " << follower << endl;

   while (attractor[scr + 1] == 0)
      scr = rootGene(attractor, neuralItem->getRandomNumber()->randInt(attractor.size() - 2));

   //cout << "scr: " << scr << endl;
   // removal of elements
   chromosomeType::iterator result = adjacent_find(next.begin(), next.end());
   if (result != next.end())
      next.erase(result);
   else
      next.erase(find(next.begin() + 1, next.end() - 1, 0));
   //cout << "Deleting: ";
   for (size_t i = scr + 1; attractor[i] != 0; i++)
   {
      //cout << attractor[i] << " "; 
      next.erase(find(next.begin() + 1, next.end() - 1, attractor[i]));
   }
   //cout << endl;
   //cout << "N: " << next << endl;
   // copy of the new elements
   for (size_t i = scr + 1; attractor[i] != 0; i++)
      next.push_back(attractor[i]);
   next.push_back(0);

   //cout << "N: " << next << endl;
   return localSearch(next);
}

inline void selfTwitter(chromosomeType& follower, const chromosomeType& attractor, const string target = " ")
{
   // get a random sub-route
   codeaParameters* neuralItem = codeaParameters::instance();

   if (neuralItem->getRandomNumber()->rand() < 0.60)
   {
      selfMType0(follower, attractor, target);
      return;
   }

   unsigned scr = rootGene(attractor, neuralItem->getRandomNumber()->randInt(attractor.size() - 2));

   while (attractor[scr + 1] == 0)
      scr = rootGene(attractor, neuralItem->getRandomNumber()->randInt(attractor.size() - 2));

   chromosomeType::iterator result = adjacent_find(follower.begin(), follower.end());
   if (result != follower.end())
      follower.erase(result);
   else
      follower.erase(find(follower.begin() + 1, follower.end() - 1, 0));

   for (size_t i = scr + 1; attractor[i] != 0; i++)
      follower.erase(find(follower.begin() + 1, follower.end() - 1, attractor[i]));

   for (size_t i = scr + 1; attractor[i] != 0; i++)
      follower.push_back(attractor[i]);
   follower.push_back(0);

   selfLocalSearch(follower);
}

#endif
