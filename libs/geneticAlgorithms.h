/** 
   @library geneticAlgorithms

   @brief Implements a number of functions to work with genetic algorithms

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#include <vector>
#include <algorithm>


using std::vector;

/**
   Function that performs the OXCrossOver.
   @param const std::vector<T>* is a pointer to a parent.
   @param const std::vector<T>* is a pointer to a parent.
   @param unsigned is a cut point.
   @param unsigned is a cut point.
   @return a std::vector containing one of the offspring of the OXCrossOver.
*/
template <typename T>
inline vector<T> OXCrossOver(const vector<T>* parent1, const vector<T>* parent2, unsigned cutPoint1, unsigned cutPoint2)
{
   if (parent1->size() != parent2->size())
      throw "<library geneticAlgorithms> [OXCrossOver] size of vectors (different)?";

   if (cutPoint1 > cutPoint2) 
      throw "<library geneticAlgorithms> [OXCrossOver] invalid cut points";
   
   if ((cutPoint1 > parent1->size() - 1) || (cutPoint2 > parent2->size() - 1)) 
      throw "<library geneticAlgorithms> [OXCrossOver] cut points out of range";
 
   vector<T> offspring(parent1->begin() + cutPoint1, parent1->begin() + cutPoint2);

   for (unsigned i = cutPoint2; i < parent2->size(); i++)
      if ((find(offspring.begin(), offspring.end(), (*parent2)[i]) == offspring.end()))
	 offspring.push_back((*parent2)[i]);
      
   for (unsigned i = 0; i < cutPoint1; i++)
      if ((find(offspring.begin(), offspring.end(), (*parent2)[i]) == offspring.end()))
	 offspring.push_back((*parent2)[i]);

   for (unsigned i = 0; i <= parent1->size(); i++)
   {
      if (offspring.size() == parent1->size())
	 break;
      
      if ((find(offspring.begin(), offspring.end(), i) == offspring.end()))
	 offspring.push_back(i);
   }

   rotate(offspring.begin(), offspring.end() - cutPoint1, offspring.end());

   return offspring;
}

/**
   Function that performs the OXCrossOver.
   @param const std::vector<T>* is a pointer to a parent.
   @param const std::vector<T>* is a pointer to a parent.
   @param T reserved value. If this value is found, this will no be treated the same way the others.
   @param unsigned is a cut point.
   @param unsigned is a cut point.
   @return a std::vector containing one of the offspring of the OXCrossOver.
*/
template <typename T>
inline vector<T> OXCrossOver(const vector<T>* parent1, const vector<T>* parent2, T specialValue, unsigned cutPoint1, unsigned cutPoint2)
{
   if (parent1->size() != parent2->size())
      throw "<library geneticAlgorithms> [OXCrossOver] size of vectors (different)?";

   if (cutPoint1 > cutPoint2) 
      throw "<library geneticAlgorithms> [OXCrossOver] invalid cut points";
   
   if ((cutPoint1 > parent1->size() - 1) || (cutPoint2 > parent2->size() - 1)) 
      throw "<library geneticAlgorithms> [OXCrossOver] cut points out of range";
 
   vector<T> offspring(parent1->begin() + cutPoint1, parent1->begin() + cutPoint2);

   for (unsigned i = cutPoint2; i < parent2->size(); i++)
      if ((parent2[i] != T) && (find(offspring.begin(), offspring.end(), (*parent2)[i]) == offspring.end()))
	 offspring.push_back((*parent2)[i]);
      
   for (unsigned i = 0; i < cutPoint1; i++)
      if ((parent2[i] != T) && (find(offspring.begin(), offspring.end(), (*parent2)[i]) == offspring.end()))
	 offspring.push_back((*parent2)[i]);

   for (unsigned i = 0; i <= parent1->size(); i++)
   {
      if (offspring.size() == parent1->size())
	 break;
      
      if ((find(offspring.begin(), offspring.end(), i) == offspring.end()))
	 offspring.push_back(i);
   }

   rotate(offspring.begin(), offspring.end() - cutPoint1, offspring.end());

   return offspring;
}
