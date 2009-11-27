#ifndef CHRONO_H
#define CHRONO_H

// This is for the atexit function
#include <cstdlib>
#include <time.h>

class chrono
{
   private:
      
      static chrono* chronoInstance;

      time_t currentTime;

   protected:

      chrono();
      ~chrono() { };     

      static void destroySingleton();

   public:

      static chrono* instance();
      time_t getSeconds();

};


chrono::chrono()
{
   this->currentTime = time(NULL);
}

chrono* chrono::chronoInstance = NULL;

void chrono::destroySingleton()
{
   delete(chronoInstance);
   chronoInstance = NULL;
}

chrono* chrono::instance()
{
   if (chronoInstance == NULL)
   {
      chronoInstance = new chrono;
      atexit(&chrono::destroySingleton);
   }
   return chronoInstance;
}

time_t chrono::getSeconds()
{
   return time(NULL) - this->currentTime;
}


	
#endif
