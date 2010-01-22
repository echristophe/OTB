//*******************************************************************
//
// License:  See top level LICENSE.txt file.
// 
// Author: Garrett Potts (gpotts@imagelinks.com)
// Description: A brief description of the contents of the file.
//
//
//*************************************************************************
// $Id: ossimViewListener.h 9968 2006-11-29 14:01:53Z gpotts $
#ifndef ossimViewListener_HEADER
#define ossimViewListener_HEADER
#include <ossim/base/ossimListener.h>
#include <ossim/base/ossimViewEvent.h>

class OSSIMDLLEXPORT ossimViewListener : public ossimListener
{
public:
   ossimViewListener():ossimListener(){}
   virtual ~ossimViewListener(){}
   
   virtual void processEvent(ossimEvent& event);
   virtual void viewScaleChangeEvent(ossimViewEvent& event)
      {}
   virtual void viewTypeChangeEvent(ossimViewEvent& event)
      {}
   virtual void viewEvent(ossimViewEvent& event)
      {}
   virtual void viewTransformChangeEvent(ossimViewEvent& event)
      {}

   virtual void allViewEvents(ossimViewEvent& event)
      {}
TYPE_DATA
};

#endif
