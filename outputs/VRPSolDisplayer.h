

#ifndef VRPSOLDISPLAYER_H
#define VRPSOLDISPLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <QTimer>

#include "paintable.h"

#include "../libs/fileLock.h"

class VRPSolDisplayer :  public paintable
{

   private:
       routesType routes;
       QTimer* timer;

   protected:

   public slots:
        void run()
        { 
           unsigned costumer;
           std::string fileName = "final";
           routesType auxRoutes;
           int fd = getLock(fileName);
           if (fd >= 0)
           {
              std::fstream file;
              file.open(fileName.c_str());

              if (!file.is_open())	
                 return;
              routes.clear();
              // This is to get rid of the objectives part of the solution
              std::string dummy;
              //for (unsigned i = 1; i < 10; i++)
              //   file >> dummy; 
              // <-
              while (file >> costumer)
                 routes.push_back(costumer);

              freeLock(fileName, fd);
              file.close();
           }
           paint();
            
        };


   public:
       VRPSolDisplayer();
       ~VRPSolDisplayer();
       void setRoutes(const routesType& routes) { this->routes = routes; }
       void paint();


};

VRPSolDisplayer::VRPSolDisplayer()
{ 

}

VRPSolDisplayer::~VRPSolDisplayer()
{ }

//void VRPSolDisplayer::dummy() { paint(); }

inline void VRPSolDisplayer::paint()
{
   clearScene();
   //std::cout << "R.size(): " << routes.size() << std::endl;

   VRPTWDataProblem* VRPTWData = VRPTWDataProblem::instance();

   unsigned red, green, blue;
   red = 0;
   green = 0;
   blue = 0;

   unsigned costumer = 0;
   unsigned nextCostumer = 0;
   for (size_t i = 0; i < routes.size() - 1; i++)
   {
      costumer = routes.at(i);
      nextCostumer = routes.at(i + 1);
      if (routes[i] == 0)
      {
         red = rand() % 256;
         green = rand() % 256;
         blue = rand() % 256;
      } 
      drawLine(VRPTWData->getClientCoords()[costumer].first,
               VRPTWData->getClientCoords()[costumer].second,
               VRPTWData->getClientCoords()[nextCostumer].first,
               VRPTWData->getClientCoords()[nextCostumer].second,
               red, green, blue);
   }

   drawPoint(VRPTWData->getClientCoords()[0].first, VRPTWData->getClientCoords()[0].second, 0.5,  "red");
   drawText("0", VRPTWData->getClientCoords()[0].first, VRPTWData->getClientCoords()[0].second);
   for (coordsType::size_type i = 1; i < VRPTWData->getClientCoords().size(); i++)
   {
      drawPoint((VRPTWData->getClientCoords())[i].first, (VRPTWData->getClientCoords())[i].second, 0.5);
      drawText(somethingToString<cityIDType>(i).c_str(), VRPTWData->getClientCoords()[i].first, VRPTWData->getClientCoords()[i].second);
   }
   display();
}




#endif
