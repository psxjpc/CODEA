/** 
   @class triBool
  
   @brief Implements a tri-State Bool.

   This class extends the bool variable to include an extra state: undefined.
   Though it has several uses, the purpose of this class is to be used in
   some multi-objective solution ranking schemes. For example, this variable
   could have an 'undefined' value when comparing two solutions if none of 
   them dominate the other one (weak dominance).

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef _triBOOL_H
#define _triBOOL_H

#include <cassert>

#define null -1

class triBool
{
   private:
      /**
         Data that holds the state of the object. (Null) by default.
      */
      int state;

   protected:

   public:

      /**
         Default constructor. It sets the state to undefined (null).
      */
      triBool();

      /**
         Standard constructor. It sets the state to the given parameter.
         @param const int is the value to be set as state. There are 
         three possible values:
         (1) true
         (0) false
         (-1) undefined (null)
      */
      triBool(const int);

      /**
         Alternative constructor. It sets the state to the given parameter.
         @param const bool is a boolean expresion that could set the state
         to true or false.
         @note This constructor cannot set the state to 'undefined'.
      */
      triBool(const bool);

      /**
         Standard destructor. It does nothing.
      */
      ~triBool();

      /**
         Method that returns true if the state is set to true, false otherwise.
         @return a boolean expresion that is true is the state is set to true, false otherwise.
      */
      bool isTrue() const;

      /**
         Method that returns true if the state is set to false, false otherwise.
         @return a boolean expresion that is true is the state is set to false, false otherwise.
      */
      bool isFalse() const;

      /**
         Method that returns true if the state is set to null, false otherwise.
         @return a boolean expresion that is true is the state is set to null, false otherwise.
      */
      bool isNull() const;

      /**
         Method that returns true if the state is set to null or true, false otherwise.
         @return a boolean expresion that is true is the state is set to null or true, false otherwise.
         @note this is a shortcut to know if something is equal or better from a 'triBool' point of view.
      */
      bool isNullTrue() const;

      /**
         Method that returns true if the state is set to null or false, false otherwise.
         @return a boolean expresion that is true is the state is set to null or false, false otherwise.
         @note this is a shortcut to know if something is equal or worse from a 'triBool' point of view.
      */
      bool isNullFalse() const;

      /**
         Method that sets the state of this object with the given parameter.
         @param const int is the value to be set as state. There are 
         three possible values:
         (1) true
         (0) false
         (-1) undefined (null)
      */
      void setState(const int);
      
      /**
         Method that sets the state of this object with the given parameter.
         @param const bool is a boolean expresion that could set the state
         to true or false.
         @note This way it cannot be set the state to 'undefined'.
      */
      void setState(const bool);
};

triBool::triBool()
{
   // Null value by default
   this->state = -1; 
}

triBool::triBool(const int state)
{
   // Range of valid values
   assert(state >= -1 && state <= 1);
   this->state = state;
}

triBool::triBool(const bool state)
{
   if (state)
      this->state = 1;
   else 
      this->state = 0;
}

triBool::~triBool()
{ }

inline bool triBool::isTrue() const
{
   return (this->state == 1);
}

inline bool triBool::isFalse() const
{
   return (this->state == 0);
}
     
inline bool triBool::isNull() const
{
   return (this->state == -1);
}

inline bool triBool::isNullTrue() const
{
   return ((this->state == -1) || (this->state == 1));
}

inline bool triBool::isNullFalse() const
{
   return ((this->state == -1) || (this->state == 0));
}

inline void triBool::setState(const bool state)
{
   if (state)
      this->state = true;
   else 
      this->state = false;
}
      
inline void triBool::setState(const int state)
{
   // Range of valid values
   assert(state >= -1 && state <= 1);
   this->state = state;
}

#endif

