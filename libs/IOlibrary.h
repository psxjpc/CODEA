/** 
   @library IOlibrary

   @brief Implements a number of functions to work output information
   in the standard output.

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/


#ifndef IOLIBRARY
#define IOLIBRARY

#include <vector>
#include <iomanip>
#include <iostream>
#include <valarray>

#include "./boost/boost/any.hpp"

using std::string; 
using std::cout;
using std::endl;
using std::vector;
using std::ostream;

/**
   Overloading of the << operator to output matrixes(std).
   @param const vector<vector<T> >& is a constant reference to the matrix to be output.
*/
template <class T>
ostream& operator<< (ostream& os, const vector<vector<T> >& object) 
{
   unsigned width = 5;
   for (unsigned i = 0; i < object.size(); i++)
   {
      for (unsigned j = 0; j < object[i].size(); j++)
         os << std::setw(width) << object[i][j] << " ";         
      os << endl;
   }
   return os;
}

/**
   Overloading of the << operator to output std::valarray(s).
   @param const std::valarray<T>& is a constant reference to the valarray to be output.
*/
template <class T>
ostream& operator<< (ostream& os, const std::valarray<T>& object)
{
   os << "[ ";
   for (size_t i = 0; i < object.size(); i++)
      os << object[i] << " ";
   os << "]";
   return os;
}

/**
   Overloading of the << operator to output std::vector(s).
   @param const std::vector<T>& is a constant reference to the vector to be output.
*/
template <class T>
ostream& operator<< (ostream& os, const vector<T>& object) 
{
   for (unsigned i = 0; i < object.size(); i++)
      os << object[i] << " ";         
   return os;
}
/**
   Function that outputs a boost::any object.
   @param const boost::any& is a constant reference to the any object to be output.
*/
void printBoostObject(const boost::any &object)
{
   
   if (object.type() == typeid(unsigned))
   {
      cout << *boost::any_cast<unsigned>(&object) << endl;
      return;
   }   
   
   if (object.type() == typeid(unsigned*))
   {
      cout << *(*boost::any_cast<unsigned*>(&object)) << endl;
      return;
   }   
   
   if (object.type() == typeid(int))
   {
      cout << *boost::any_cast<int>(&object) << endl;
      return;
   }

   if (object.type() == typeid(int*))
   {
      cout << *(*boost::any_cast<int*>(&object)) << endl;
      return;
   }

   if (object.type() == typeid(float))
   {
      cout << *boost::any_cast<float>(&object) << endl;
      return;
   }

   if (object.type() == typeid(float*))
   {
      cout << *(*boost::any_cast<float*>(&object)) << endl;
      return;
   }

   if (object.type() == typeid(double))
   {
      cout << *boost::any_cast<double>(&object) << endl;
      return;
   }

   if (object.type() == typeid(double*))
   {
      cout << *(*boost::any_cast<double*>(&object)) << endl;
      return;
   }

   if (object.type() == typeid(string))
   {
      cout << *boost::any_cast<string>(&object) << endl;
      return;
   }
   if (object.type() == typeid(vector<int>))
   {
      cout << *boost::any_cast<vector<int> >(&object) << endl;
      return;
   }
   if (object.type() == typeid(vector<int>*))
   {
      cout << *(*boost::any_cast<vector<int>*>(&object)) << endl;
      return;
   }
   if (object.type() == typeid(vector<unsigned>))
   {
      cout << *boost::any_cast<vector<unsigned> >(&object) << endl;
      return;
   }
   if (object.type() == typeid(vector<unsigned>*))
   {
      cout << *(*boost::any_cast<vector<unsigned>*>(&object)) << endl;
      return;
   }
   
}

/**
   Overloading of the << operator to output a boost::any object.
   @param const boost::any& is a constant reference to the any object to be output.
*/
ostream& operator <<(ostream& sOut, const boost::any& object)
{
   if (object.type() == typeid(unsigned))
   {
      sOut << *boost::any_cast<unsigned>(&object) << endl;
      return sOut;
   }   

   if (object.type() == typeid(unsigned*))
   {
      sOut << *(*boost::any_cast<unsigned*>(&object)) << endl;
      return sOut;
   }   

   if (object.type() == typeid(int*))
   {
      sOut << *(*boost::any_cast<int*>(&object)) << endl;
      return sOut;
   }   

   if (object.type() == typeid(int))
   {
      sOut << *boost::any_cast<int>(&object) << endl;
      return sOut;
   }
   if (object.type() == typeid(float))
   {
      sOut << *boost::any_cast<float>(&object) << endl;
      return sOut;
   }
   if (object.type() == typeid(float*))
   {
      sOut << *(*boost::any_cast<float*>(&object)) << endl;
      return sOut;
   }
   if (object.type() == typeid(double))
   {
      sOut << *boost::any_cast<double>(&object) << endl;
      return sOut;
   }
   if (object.type() == typeid(double*))
   {
      sOut << *(*boost::any_cast<double*>(&object)) << endl;
      return sOut;
   }
   if (object.type() == typeid(string))
   {
      sOut << *boost::any_cast<string>(&object) << endl;
      return sOut;
   }
   if (object.type() == typeid(vector<int>))
   {
      sOut << *boost::any_cast<vector<int> >(&object) << endl;
      return sOut;
   }
   if (object.type() == typeid(vector<int>*))
   {
      sOut << *(*boost::any_cast<vector<int>* >(&object)) << endl;
      return sOut;
   }
   if (object.type() == typeid(vector<unsigned>*))
   {
      sOut << *(*boost::any_cast<vector<unsigned>* >(&object)) << endl;
      return sOut;
   }
   if (object.type() == typeid(vector<unsigned>))
   {
      sOut << *boost::any_cast<vector<unsigned> >(&object) << endl;
      return sOut;
   }
   return sOut;
}

#endif
