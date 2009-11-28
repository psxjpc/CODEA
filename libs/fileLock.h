#include <fcntl.h> // for open()
#include <cerrno> // for errno 
#include <cstdio> // for perror()
#include <string>

#include <iostream>
#include <fstream>

/*
  Extracted from:
  http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=144

  If the open() call  succeeds, it returns a descriptor, which is a small positive
  integer  that  identifies the  file. Otherwise, it returns -1 and assigns a mat-
  ching  error code to the global variable errno. The O_CREAT flag indicates  that 
  if the file doesn't exist, open() should create it. The O_EXCL flag ensures that
  the call is atomic; if the file already exists, open() will fail and  set  errno 
  to EEXIST. This way you guarantee that only a single  process at a time can hold 
  the lock. 
*/

int getLock(std::string fileName)
{

   int fd = open((fileName + ".lck").c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IWRITE | S_IREAD);

   // the file already exist, another process is possessing the lock 
   if (fd < 0 && errno == EEXIST)
      return fd;

   // another error
   else if (fd < 0)
   {  
      std::cout << "I/O Error: " << errno << std::endl;
      return fd;
   }
   
   return fd;
}

int freeLock(std::string fileName, int fd = 0) 
{
   close(fd);
   remove((fileName + ".lck").c_str());
}

bool tryWRString(std::string somethingToWrite, std::string fileName)
{
   int fd = getLock(fileName);  

   std::fstream file;
   file.open(fileName.c_str(), std::fstream::out);
   file << somethingToWrite;
   file.close();
   freeLock(fileName, fd);
   return true;
}
