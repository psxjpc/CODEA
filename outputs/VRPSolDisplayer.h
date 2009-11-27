

#ifndef VRPSOLDISPLAYER_H
#define VRPSOLDISPLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "paintable.h"

class VRPSolDisplayer :  public paintable
{
   private:
       routesType routes;

   protected:

   public:
       VRPSolDisplayer();
       ~VRPSolDisplayer();
       void setRoutes(const routesType& routes) { this->routes = routes; }
       void paint();
};

VRPSolDisplayer::VRPSolDisplayer()
{ }

VRPSolDisplayer::~VRPSolDisplayer()
{ }

inline void VRPSolDisplayer::paint()
{
   if (blocked)
      return;

   clearScene();

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
