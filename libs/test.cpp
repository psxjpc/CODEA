

#include <iostream>
#include <math.h>

#include "chrono.h"

using namespace std;

int main(void)
{
   chrono* myChrono = chrono::instance();
   cout << myChrono->getSeconds() << endl;

   unsigned long sum = 0;
   for (int i = 0; i < 1000; i++)
      for (int j = 0; j < 1000; j++)
         for (int z = 0; z < 1000; z++)
            sum += sqrt(i * j * z / 2);

   cout << "Sum: " << sum << endl;
   cout << myChrono->getSeconds() << endl;
   sum = 0;
   for (int i = 0; i < 1000; i++)
      for (int j = 0; j < 1000; j++)
         for (int z = 0; z < 1000; z++)
            sum += sqrt(i * j * z / 2); 

   cout << "Sum: " << sum << endl;
   cout << myChrono->getSeconds() << endl;
   sum = 0;
   for (int i = 0; i < 1000; i++)
      for (int j = 0; j < 1000; j++)
         for (int z = 0; z < 1000; z++)
            sum += sqrt(i * j * z / 2);
  
   cout << "Sum: " << sum << endl;
   cout << myChrono->getSeconds() << endl;
}
