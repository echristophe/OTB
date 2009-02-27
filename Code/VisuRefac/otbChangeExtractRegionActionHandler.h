/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __otbChangeExtractRegionActionHandler_h
#define __otbChangeExtractRegionActionHandler_h

#include "otbImageWidgetActionHandler.h"

namespace otb
{
/** \class ChangeExtractRegionActionHandler
*   \brief Implements basic Scroll, Full and Zoom  widgets resizing.
* 
*   \sa ImageWidgetController
*   \sa ImageWidgetActionHandler
*/

template <class TModel, class TView> 
class ChangeExtractRegionActionHandler
  : public ImageWidgetActionHandler
{
public:
  /** Standard class typedefs */
  typedef ChangeExtractRegionActionHandler Self;
  typedef ImageWidgetActionHandler               Superclass;
  typedef itk::SmartPointer<Self>                Pointer;
  typedef itk::SmartPointer<const Self>          ConstPointer;
  
  /** Method for creation through the object factory */
  itkNewMacro(Self);
  
  /** Runtime information */
  itkTypeMacro(ChangeExtractRegionActionHandler,ImageWidgetActionHandler);

  /** Model typedefs */
  typedef TModel                         ModelType;
  typedef typename ModelType::Pointer    ModelPointerType;
  typedef typename ModelType::RegionType RegionType;

  /** View typedefs */
  typedef TView                          ViewType;
  typedef typename ViewType::Pointer     ViewPointerType;


  /** Handle widget event
   * \param widgetId The id of the moved widget
   * \param event The event
   * \return The handling return code
   */
  virtual bool HandleWidgetEvent(std::string widgetId, int event)
  {
    if( m_View.IsNotNull() && m_Model.IsNotNull() )
      {
      if(widgetId == m_View->GetScrollWidget()->GetIdentifier()
	 && event == FL_PUSH)
	{
	otbMsgDevMacro(<<"ChangeExtractRegionActionHandler::HandleWidgetEvent(): handling ("<<widgetId<<", "<<event<<")");
	// Get the clicked index
	typename ViewType::IndexType index;
	index[0] = Fl::event_x();
	index[1] = Fl::event_y();
	// Change scaled extract region center
	m_Model->SetExtractRegionSubsampledCenter(m_View->GetScrollWidget()->ScreenIndexToRegionIndex(index));
	// Update model
	m_Model->Update();
	return true;
	}
      }
    return false;
  }
  
  /** Set/Get the pointer to the view */
  itkSetObjectMacro(View,ViewType);
  itkGetObjectMacro(View,ViewType);

  /** Set/Get the pointer to the model */
  itkSetObjectMacro(Model,ModelType);
  itkGetObjectMacro(Model,ModelType);

protected:
  /** Constructor */
  ChangeExtractRegionActionHandler() : m_View(), m_Model()
  {}

  /** Destructor */
  virtual ~ChangeExtractRegionActionHandler(){}
  /** Printself method */
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os,indent);
  }
 
private:
  ChangeExtractRegionActionHandler(const Self&);    // purposely not implemented
  void operator=(const Self&); // purposely not implemented

  // Pointer to the view
  ViewPointerType m_View;
  
  // Pointer to the model
  ModelPointerType m_Model;
  
}; // end class 
} // end namespace otb
#endif


