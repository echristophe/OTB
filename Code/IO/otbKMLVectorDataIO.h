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
#ifndef __otbKMLVectorDataIO_h
#define __otbKMLVectorDataIO_h

#include "otbVectorDataIOBase.h"
#include <fstream>
#include <string>
#include <vector>


#include "kml/dom.h"
#include "kml/base/file.h"
using kmldom::KmlPtr;
using kmldom::ElementPtr;
using kmldom::FeaturePtr;
using kmldom::GeometryPtr;
using kmldom::ContainerPtr;

namespace otb
{

/** \class KMLVectorDataIO
 *
 * \brief ImageIO object for reading/writing KML format vector data
 *
 */
template <class TData>
class ITK_EXPORT KMLVectorDataIO
      : public VectorDataIOBase<TData>
{
public:

  /** Standard class typedefs. */
  typedef KMLVectorDataIO          Self;
  typedef VectorDataIOBase<TData>  Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(KMLVectorDataIO, VectorDataIOBase);

  /** Byte order typedef */
  typedef typename Superclass::ByteOrder  ByteOrder;

  /** Data typedef */
  typedef TData VectorDataType;
  typedef typename VectorDataType::DataTreeType  DataTreeType;
  typedef typename DataTreeType::TreeNodeType    InternalTreeNodeType;
  typedef typename InternalTreeNodeType::ChildrenListType        ChildrenListType;
  typedef typename DataTreeType::Pointer         DataTreePointerType;
  typedef typename DataTreeType::ConstPointer    DataTreeConstPointerType;
  typedef typename VectorDataType::DataNodeType  DataNodeType;
  typedef typename DataNodeType::Pointer         DataNodePointerType;
  typedef typename DataNodeType::PointType       PointType;
  typedef typename DataNodeType::LineType        LineType;
  typedef typename LineType::VertexListType      VertexListType;
  typedef typename VertexListType::ConstPointer  VertexListConstPointerType;
  typedef typename LineType::Pointer             LinePointerType;
  typedef typename LineType::VertexType          VertexType;
  typedef typename DataNodeType::PolygonType     PolygonType;
  typedef typename PolygonType::Pointer          PolygonPointerType;
  typedef typename DataNodeType::PolygonListType PolygonListType;
  typedef typename PolygonListType::Pointer      PolygonListPointerType;
  typedef typename VectorDataType::Pointer       VectorDataPointerType;
  typedef typename VectorDataType::ConstPointer  VectorDataConstPointerType;


  /*-------- This part of the interface deals with reading data. ------ */

  /** Determine the file type. Returns true if this VectorDataIO can read the
   * file specified. */
  virtual bool CanReadFile(const char*);

  /** Determine the file type. Returns true if the VectorDataIO can stream read the specified file */
  virtual bool CanStreamRead()
  {
    return false;
  };

  /*   /\** Set the spacing and dimention information for the set filename. *\/ */
  /*   virtual void ReadVectorDataInformation(); */

  /** Reads the data from disk into the data structure provided. */
  virtual void Read(VectorDataPointerType data);

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this VectorDataIO can read the
   * file specified. */
  virtual bool CanWriteFile(const char*);

  /** Determine the file type. Returns true if the VectorDataIO can stream write the specified file */
  virtual bool CanStreamWrite()
  {
    return false;
  };

  /*   /\** Writes the spacing and dimentions of the image. */
  /*    * Assumes SetFileName has been called with a valid file name. *\/ */
  /*   virtual void WriteVectorDataInformation(); */

  /** Writes the data to disk from the data structure provided */
  virtual void Write(VectorDataConstPointerType data);

protected:
  /** Construtor.*/
  KMLVectorDataIO();
  /** Destructor.*/
  virtual ~KMLVectorDataIO();

  virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

  static const FeaturePtr GetRootFeature(const ElementPtr& root);

  static void PrintIndented(std::string item, int depth);

  static void PrintFeature(const FeaturePtr& feature, int depth);

  void WalkGeometry(const GeometryPtr& geometry, DataNodePointerType father);

  void WalkFeature(const FeaturePtr& feature, DataNodePointerType father);

  void WalkContainer(const ContainerPtr& container, DataNodePointerType father);


  /** Conversion tools */
  DataNodePointerType ConvertGeometryToPointNode(const GeometryPtr& geometry);
  DataNodePointerType ConvertGeometryToLineStringNode(const GeometryPtr& geometry);
  DataNodePointerType ConvertGeometryToLinearRingNode(const GeometryPtr& geometry);
  DataNodePointerType ConvertGeometryToPolygonNode(const GeometryPtr& geometry);
  /** end conversion tools */

  typedef kmldom::KmlPtr KmlPtr;
  typedef kmldom::KmlFactory KmlFactory;
  typedef kmldom::DocumentPtr DocumentPtr;
  typedef kmldom::FolderPtr FolderPtr;
  typedef kmldom::MultiGeometryPtr MultiGeometryPtr;
  void ProcessNodeWrite(InternalTreeNodeType * source, KmlFactory* factory,
                        KmlPtr kml, DocumentPtr currentDocument, FolderPtr currentFolder,
                        MultiGeometryPtr currentMultiGeometry);

private:
  KMLVectorDataIO(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  DataTreePointerType m_Tree;

  unsigned int m_Kept;
};

} // end namespace otb

#ifndef OTB_MANUAL_INSTANTIATION
#include "otbKMLVectorDataIO.txx"
#endif

#endif // __otbKMLVectorDataIO_h
