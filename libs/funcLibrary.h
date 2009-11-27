/** 
   @library conversions

   @brief Implements a number of general functions to work with.

   This library is intended to have a list of function related to
   general processes.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef FUNCLIBRARY_H
#define FUNCLIBRARY_H

#include <algorithm>
#include <functional>
#include <limits>
#include <vector>
#include <string>
#include "./boost/boost/bind.hpp"
#include "./boost/boost/function.hpp"

#define INFd std::numeric_limits<double>::infinity()
#define INFi std::numeric_limits<long>::infinity()

#include "../misc/MersenneTwister.h"

namespace basic 
{
   template <class T>
   inline unsigned max(const std::vector<T>& v)
   {
      unsigned index = 0;
      T max = 0;
      for (size_t i = 0; i < v.size(); i++)
         if (v[i] > max)
         {
            max = v[i];
            index = i;
         }
      return index;
   }

   template <class T>
   inline unsigned max(const std::vector<T>& v, const std::vector<bool>& b)
   {
      unsigned index = 0;
      T max = 0;
      for (size_t i = 0; i < v.size(); i++)
         if ((v[i] > max) && (b[i]))
         {
            max = v[i];
            index = i;
         }
      return index;
   }

   /**
      Function that swaps the values of two elemetns.
      @param T& is a reference to an element.
      @param T& is a reference to an element.
   */
   template <class T>
   inline void swap(T& a, T& b)
   {
      T c = a;
      a = b;
      b = c; 
   }

   /**
      Function that swaps the values of two cells in std::vector.
      @param std::vector<T>& is a reference to the vector that will be affected by the swap.
      @param const unsigned is the index to a position in the vector.
      @param const unsigned is the index to a position in the vector.
   */
   template <class T>
   inline void swap(std::vector<T>& v, const unsigned i, const unsigned j)
   {
      T temp = v[i];
      v[i] = v[j];
      v[j] = temp;
   }

   /**
      Function that swaps the values of two cells in std::vector.
      @param std::vector<T>& is a reference to the vector that will be affected by the swap.
      @param const unsigned is the index to a position in the vector.
      @param const unsigned is the index to a position in the vector.
   */
   template <class T>
   inline void swap(std::vector<T>* v, const unsigned i, const unsigned j)
   {
      T temp = (*v)[i];
      (*v)[i] = (*v)[j];
      (*v)[j] = temp;
   }


   /**
      Function that swaps the positions of two cells in std::vector.
      @param std::vector<T>::iterator is pointer to the cell to be swapped.
      @param std::vector<T>::iterator is pointer to the cell to be swapped.
   */
   template <typename T>
   inline void move(typename std::vector<T>::iterator scr, typename std::vector<T>::iterator dst)
   {
      if (scr < dst)
         rotate(scr, scr + 1, dst);
      else if (scr > dst)
         rotate(scr, dst - 1, dst);
   }

   /**
      Function that swaps the positions of two cells in std::vector.
      @param std::vector<T>& is a reference to the vector that will be affected by the swap.
      @param const unsigned is the index to a position in the vector.
      @param const unsigned is the index to a position in the vector.
   */
   template <typename T>
   inline void move(typename std::vector<T>& vect, unsigned scr, unsigned dst) 
   {
      if (scr < dst)
         rotate(vect.begin() + scr, vect.begin() +  scr + 1,vect.begin() +  dst + 1);
      else if (scr > dst)
         rotate(vect.begin() + dst + 1, vect.begin() +  scr, vect.begin() + (scr + 1));
   }
}

/**
   Function that returns true or false depending on if a number is in between other two.
   @param const T& is the number to know if is in inside the interval formed by the other two.
   @param const T& is the lower bound of the interval.
   @param const T& is the upper bound of the interval.
   @return a boolean expresion.
   @warning it doesn't test if the interval is correct.
*/
template <class T>
inline bool isInside(const T& number, const T& lowerBound, const T& upperBound)
{
   return (number >= lowerBound && number <= upperBound);
}


/**
   Function that trims the blank spaces at the beginning and the end of a given std::string.
   @param const std::string& is a constant reference to the string to be trimmed.
   @return a new std::string with the result of the operation.
*/
inline std::string trimSpacesLeftRight(const std::string& str)
{
   std::string cleanString = str;

   // Removing spaces at the end of the string
   size_t index = 0;
   for (size_t i = cleanString.length(); i > 0; i--)
      if (cleanString[i] != ' ')
      {
         index = i;
         break;
      }

   cleanString = cleanString.replace(index, cleanString.length() - index - 1, ""); 

   // Removing spaces at the beginning of the string
   index = cleanString.find_first_not_of(' ');
   cleanString = cleanString.replace(0, index, ""); 

   return cleanString; 
}


/**
   Function that splits a string in a std::vector of std::string(s). It receives
   a delimiter as a param, looks for it whithin a given std::string and splits up
   the string creating a std::vector.
   @param const std::string& is a constant reference to the string to be splitted.
   @param std::vector<std::string>& is a reference to the vector that will contain the
   @param const std::string& is a constant reference to the delimiter string that
   will be used to split the given string. By default is a blank space.
*/
inline void splitString(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
   // First we will remove the space at the beginning and the end of the string
   std::string cleanString = trimSpacesLeftRight(str);   

   std::string::size_type lastPos = 0;
   std::string::size_type pos = cleanString.find_first_of(delimiters, lastPos);

   while (std::string::npos != pos || std::string::npos != lastPos)
   {
      tokens.push_back(cleanString.substr(lastPos, pos - lastPos));
      lastPos = cleanString.find_first_not_of(delimiters, pos);
      pos = cleanString.find_first_of(delimiters, lastPos);
   }
}

/**
   Function that returns the positive value given any type of value.
   @param const T is the number we want to get the positive value from.
   @return a positive value from the value received.
*/
template <class T>
inline T abs(const T number)
{
   T temp = ((number > 0)? number : -1 * number);
   return temp;
}

/**
   Function that performs the operation |a - b|
   @param const T is a number to operate
   @param const T is a number to operate
   @return the result of the operation explained above.
*/
template <class T>
inline T abs(const T numberA, const T numberB)
{
   double temp = numberA - numberB;
   temp = (temp < 0)? (-1) * temp : temp;
   return (T)temp;
}

#endif


