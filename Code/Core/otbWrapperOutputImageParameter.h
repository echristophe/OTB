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
#ifndef __otbWrapperOutputImageParameter_h
#define __otbWrapperOutputImageParameter_h

#include "otbVectorImage.h"
#include "otbWrapperParameter.h"
#include "otbStreamingImageFileWriter.h"

namespace otb
{
namespace Wrapper
{
/** \class OutputImageParameter
 *  \brief This class represents a OutputImage parameter
 */

class ITK_EXPORT OutputImageParameter : public Parameter
{
public:
  /** Standard class typedef */
  typedef OutputImageParameter           Self;
  typedef Parameter                     Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef otb::StreamingImageFileWriter<VectorImageType> WriterType;

  /** Defining ::New() static method */
  itkNewMacro(Self);

  /** RTTI support */
  itkTypeMacro(OutputImageParameter,Parameter);

  /** Set the value */
  itkSetObjectMacro(Image, VectorImageType);

  /** Get the value */
  itkGetObjectMacro(Image, VectorImageType);

  /** Return any value */
  void SetValue(VectorImageType* image)
  {
    m_Image = image;
  }

  /** Return any value */
  VectorImageType* GetValue( void )
  {
    return m_Image;
  }

  itkSetStringMacro(FileName);
  itkGetStringMacro(FileName);
 
  itkGetObjectMacro( Writer, WriterType );

  void Write()
  {
    if (m_Image.IsNotNull())
      {
      m_Writer = WriterType::New();
      m_Writer->SetInput(m_Image);
      m_Writer->SetFileName(this->GetFileName());
      m_Writer->Update();
      }
  }

protected:
  /** Constructor */
  OutputImageParameter()
  {
    this->SetName("Output Image");
    this->SetKey("out");
    m_Writer = WriterType::New();
  }

  /** Destructor */
  virtual ~OutputImageParameter()
  {}

  VectorImageType::Pointer m_Image;
  std::string m_FileName;
  WriterType::Pointer m_Writer;

private:
  OutputImageParameter(const Parameter &); //purposely not implemented
  void operator =(const Parameter&); //purposely not implemented

}; // End class OutputImage Parameter

} // End namespace Wrapper
} // End namespace otb

#endif
