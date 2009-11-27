/** 
   @class mailBox
  
   @brief Stores the messages sent by other agents.

   This class handles basic methods to manage a virtual mailbox of message
   sent by other agents. 

   @author Group of Intelligent Computing - Universidad de La Laguna - 2008
*/

#ifndef MAILBOX_H
#define MAILBOX_H

#include <deque>

#include "header.h"

class mailBox
{
   private:
      /**
         Mailbox of messages. This object is intended to receive messages and not to be
         a platform to send them. To send messages there is an object for this purpose in
         agent (@see agent).        
      */
      std::deque<message> inBox;

   protected:

   public:
      /**
         Default constructor. It does nothing.
      */
      mailBox() { };

      /**
         Default destructor. It does nothing.
      */
      ~mailBox() { };

      /** 
         Method that returns the mailbox.
         @return the data structure that holds the messages.
      */
      std::deque<message> getInBox() const;

      /** 
         Method that returns the mailbox.
         @return a pointer to the data structure that holds the messages.
      */
      std::deque<message>* getPointerToInBox();

      /** 
         Method that sets the mailbox.
         @param const std::deque<message> is the mailbox.
      */
      void setInBox(const std::deque<message>);

      /** 
         Method that clears up the mailbox.
      */
      void clear();

      /** 
         Method that inserts a new message in the mailbox.
         @param const message is the new message to be inserted in the mailbox.
      */
      void insert(const message);

      /** 
         Method that inserts a new message in the mailbox.
         @param const message is the new message to be inserted in the mailbox.
         @note This method was implemented to maintain compatibility with the STL.
      */
      void push_back(const message);

      /** 
         Method that returns true or false depending on whether the mailbox is empty or not.
         @param bool is true if the mailbox is empty, false otherwise.
      */
      bool empty() const;
};

inline std::deque<message> mailBox::getInBox() const
{
   return this->inBox;
}

inline std::deque<message>* mailBox::getPointerToInBox() 
{
   return &(this->inBox);
}

inline void mailBox::setInBox(const std::deque<message> inBox) 
{
   this->inBox = inBox;
}

inline void mailBox::clear()
{
   this->inBox.clear();
}

inline void mailBox::insert(const message newMessage)
{
   this->inBox.push_back(newMessage);
}

inline void mailBox::push_back(const message newMessage)
{
   this->inBox.push_back(newMessage);
}

inline bool mailBox::empty() const
{
   return this->inBox.empty();
}

#endif
