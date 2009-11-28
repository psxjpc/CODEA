/** 
   @class codeaParameters
  
   @brief Global Variables CODEA needs to work 

   This class is intended to store those global variables CODEA may need
   to work. It is opened to include any variable but it must be related
   to CODEA's core. The class is implemented using a Singleton Patter, 
   for more info: http://en.wikipedia.org/wiki/Singleton_pattern

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef CODEAPARAMETERS_H
#define CODEAPARAMETERS_H

#include "../misc/MersenneTwister.h"

#include "header.h"

class codeaParameters
{
   private:
      /**
         Single Pattern. This is a pointer to the object itself.         
      */
      static codeaParameters* codeaParametersInstance;

      /**
         Random Numbers Generator. @see MersenneTwister
         This object is here because it depends on an initialization
         parameter (seed). It doesn't make sense to create an object
         with a different seed every time we need a random number.
         This way, the idea is to create the random generator only
         once with a given seed, then to pass the pointer to this class 
         and finally invoke this object to obtain the randon number
         generator.
      */
      MTRand* randomNumber;

      /**
         Pointer to the problems the system is taclking
      */
      const problemsType* problems;

      

   protected:
      
      /**
          Default constructor. It does nothing.
          It's protected due to its Singleto nature.
      */
      codeaParameters() { };

      /**
          Default destructor. It does nothing.
          It's protected due to its Singleto nature.
      */
      ~codeaParameters() { };

      /**
          Standard Singleton's destructor. It frees the memory this object takes.
          It's protected due to its Singleto nature. This is supposed to be called
          automatically at the end of the execution.
      */
      static void destroySingleton();

   public:
   
      /**
          Method that creates a new object if this is its first invokation. Otherwise,
          it will return a pointer to the existent one.
      */
      static codeaParameters* instance();

      /** 
          Method that returns a pointer to the object MersenneTwister
          @return a pointer to the random number generator.
      */
      MTRand* getRandomNumber() const;

      /**
          Method that returns the pointer to the multiObjective functions
          @return problemsType* is the pointer to the problems
      */
      const problemsType* getProblems() const;

      /**
          Method that sets the randon number generator.
          @param MTRand* is a pointer to the random number generator.
      */
      void setRandomNumber(MTRand*);

      /**
          Method that sets the pointer to the multiObjective functions
          @param problemsType* is the pointer to the problems
      */
      void setProblems(const problemsType*);

      // Temporal
      unsigned rankingScheme;
};
 
void codeaParameters::destroySingleton()
{ 
   delete(codeaParametersInstance); 
   codeaParametersInstance = NULL; 
}

codeaParameters* codeaParameters::codeaParametersInstance = NULL;

codeaParameters* codeaParameters::instance()
{
   if (codeaParametersInstance == NULL)
   {
      codeaParametersInstance = new codeaParameters;
      codeaParametersInstance->setProblems(NULL);
      codeaParametersInstance->setRandomNumber(NULL);
      std::atexit(&codeaParameters::destroySingleton);
   }
   return codeaParametersInstance;
}

MTRand* codeaParameters::getRandomNumber() const
{
   return this->randomNumber;
}

const problemsType* codeaParameters::getProblems() const 
{
   return this->problems;
}

void codeaParameters::setRandomNumber(MTRand* randomNumber)
{
   this->randomNumber = randomNumber;
}

void codeaParameters::setProblems(const problemsType* problems)  
{
   this->problems = problems;
}

#endif
