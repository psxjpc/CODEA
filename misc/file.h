/**
  @class file

  Manages input/output in plain text files.

  This class cointains a very simply set of methods to 
  work with plain text files.

 */

#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

template <class T>
class file 
{
   private:
      std::fstream fileIO;           // Fichero input/output

   protected:

   public:

      /**
         Standard constructor. It creates an object to be read
         or write with the name given as a parameter.
         @param const char* is the name of the file-
         @return a file object.
      */
      file(const char*);

      /**
         Alternative constructor. It creates an object using
         a standard fstream object.
         @param const std::fstream& is the object that represents the file.
         @return a file object.
      */
      file(const std::fstream&);

      /**
         Default destructor. It closes the file.
      */
      ~file();

      /**
         Method that looks up if the next char is '#'.
         @returns a boolean varible is the next char is '#', false otherwise.
      */
      bool isASharp();

      /**
         Method that looks up if the next char is and end of line (EOL).
         @returns a boolean varible is the next char is (EOL), false otherwise.
      */
      bool isAEndL();

      /**
         Method that reads a std::string from the file and returns it.
         @returns a std::string that is readed from the file.
      */
      string getString();

      /**
         Method that read a number from the file and returns it.
         @returns a T that represents the number readed.
      */
      T getNumber();

      /**
         Method that read and returns a square matrix of given size.
         @param const unsigned is the size of the matrix to be readed.
         @returns a square matrix(std).
      */
      vector<vector<T> > getSquareMatrix(const unsigned);

      /**
         Method that read and returns a matrix.
         @returns a matrix(std).
      */
      vector<vector<T> > getMatrix();

      /**
         Method that read and returns a vector.
         @returns a std::vector.
      */
      vector<T> getVector();

};

template <class T>
file<T>::file(const char* fileName)
{
   this->fileIO.open(fileName);
   if(!fileIO)
   {
      std::cout << "File not found or damaged" << std::endl;
      exit(1);
   }
}


template <class T>
file<T>::file(const std::fstream& fileIO)
{
   this->fileIO = fileIO;
}

template <class T>
file<T>::~file()
{
   this->fileIO.close();
}

template <class T>
inline bool file<T>::isASharp()
{
   char character = ' ';
   this->fileIO >> character;
   if (character == '#')
      return true;

   this->fileIO.seekg((unsigned)this->fileIO.tellg() - sizeof(char));
   return false;
}

template <class T>
inline bool file<T>::isAEndL()
{
   char character = ' ';
   this->fileIO.get(character);
   if (character == '\n')
      return true;
   this->fileIO.seekg((unsigned)this->fileIO.tellg() - sizeof(char));
   return false;
}

template <class T>
inline string file<T>::getString() 
{
   string inputString = "";
   this->fileIO >> inputString;
   return inputString;
}
  
template <class T>
inline T file<T>::getNumber() 
{
   char trash[128];
   while ((isASharp()) && !(this->fileIO.eof()))
      this->fileIO.getline(trash, sizeof(trash));

   T inputNumber = 0;
   if (fileIO >> inputNumber)
      return inputNumber;
   return INFd;
      
}

template <class T>
vector<vector<T> > file<T>::getMatrix()
{
   vector<T> auxVector;
   vector<vector<T> > auxMatrix;
   while (!(this->fileIO.eof()))
   {   
      while (!(isAEndL()) && !(this->fileIO.eof()))
	 auxVector.push_back(getNumber());
      
      if (auxVector.size() > 0)
         auxMatrix.push_back(auxVector);
      auxVector.clear();
   }
   // cout << auxMatrix << endl;      
   return auxMatrix;
}

template <class T>
vector<vector<T> > file<T>::getSquareMatrix(const unsigned maxElements)
{
   vector<vector<T> > auxMatrix;
  
   auxMatrix.resize(maxElements);
   for (unsigned i = 0; i < maxElements; i++)
      auxMatrix[i].resize(maxElements, 0);
   
   for (unsigned i = 0; i < maxElements; i++)
      for (unsigned j = 0; j < maxElements; j++)
         auxMatrix[i][j] = getNumber();

   // cout << auxMatrix << endl;      
   return auxMatrix;	 
}

template <class T>
vector<T> file<T>::getVector()
{
   vector<T> auxVector;
  
   T number;
   while (fileIO >> number)
      auxVector.push_back(number);      

   return auxVector;	 
}


#endif
