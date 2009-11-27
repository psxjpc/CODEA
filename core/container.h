/** 
   @class container
  
   @brief Allows to store a pair compound by an id and
   any type of information.

   A message consists of a vector of this data structure (object).
   
   Basic schema for a message : 
   \code
   ________________________________________________________
   ||''''''''''''''''''''||''''''''''''''''''''|           | 
   ||   id1   |  object1 ||   id2   |  object2 |    ...    |
   ||....................||....................|           | 
   |     container1             container2                 | 
   |_______________________________________________________|  
                          message

   \endcode
   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef CONTAINER_H_
#define CONTAINER_H_


#include <iostream>
#include <string>

#include "../libs/boost/boost/any.hpp"
#include "../libs/IOlibrary.h"

using boost::any;
using std::string;

using std::ostream;

class container
{
   private:

      /**
         Identifier for the information contained. This id identify the information
         stored in this cell of information. It is important to set this field when
         we are going to work with agents that send different types of information.
         This will allows us to control which type of information it is begin sent
         and received.   
      */
      string id;

      /**
         Object that stores the information. To know how this object works see:
         http://www.boost.org/doc/libs/1_36_0/doc/html/any.html  
      */
      any object;

   protected:

   public:

      /**
         Default constructor. It does nothing.
      */
      container() { }

      /**
         Standard constructor. 
         @param const std::string is the id of the information to be stored.
         @param const boost::any is the object to be stored
      */
      container(const string, const any);

      /**
         Default destructor. It does nothing.
      */
      ~container() { }

      /** 
         Method that returns the identifier of the information stored.
         @return a standard string that contains the id of the object stored.
      */
      string getId() const;

      /** 
         Method that returns the object stored.
         @return a boost object that wraps the information.
      */
      any getObject() const;      

      /** 
         Method that returns the object stored.
         @return a pointer to a boost object that wraps the information.
      */
      any* getObjectPointer();

      /** 
         Method that sets the id of the information to be saved.
         @param const std::string is id of the information stored.
      */
      void setId(const string);

      /** 
         Method that sets the boost object to be saved.
         @param const boost::any is object that will be stored.
      */
      void setObject(const any);

      /** 
         Method that sets the both the id and the boost object to be saved.
         @param const std::string is id of the information stored.
         @param const boost::any is object that will be stored.
      */
      void set(const string, const any);

      /** 
         Method that sends the content of an instance of this class to the
         standard output.
      */
      friend ostream& operator << (ostream&, const container&);
};

container::container(const string id, const any object)
{
   this->id = id;
   this->object = object;
}

string container::getId() const 
{
   return id;   
}

any container::getObject() const 
{
   return object;   
}

any* container::getObjectPointer()
{
   return &object;
}

void container::setId(const string id) 
{
   this->id = id;   
}

void container::setObject(const any object) 
{
   this->object = object;
}

void container::set(const string id, const any object) 
{
   this->id = id;
   this->object = object;
}


ostream& operator<< (ostream& os, const container& object)
{
   os << "Type: " << object.getId() << std::endl;
   
   // this function is included in IOlibrary.h
   // printBoostObject(object.getObject());

   return os;
}

#endif
