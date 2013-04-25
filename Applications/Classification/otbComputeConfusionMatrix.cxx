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

#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbOGRDataSourceToLabelImageFilter.h"
#include "itkImageRegionConstIterator.h"
#include "otbOGRDataSourceWrapper.h"

#include "itkImageRegionSplitter.h"
#include "otbStreamingTraits.h"

#include "itkVariableSizeMatrix.h"

namespace otb
{
namespace Wrapper
{

class ComputeConfusionMatrix : public Application
{
public:
  /** Standard class typedefs. */
  typedef ComputeConfusionMatrix Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(ComputeConfusionMatrix, otb::Application);

  typedef itk::ImageRegionConstIterator<Int32ImageType> ImageIteratorType;

  typedef otb::OGRDataSourceToLabelImageFilter<Int32ImageType> RasterizeFilterType;

  typedef otb::StreamingTraits<Int32ImageType> StreamingTraitsType;

  typedef itk::ImageRegionSplitter<2> SplitterType;

  typedef Int32ImageType::RegionType RegionType;

  typedef int                                              ClassLabelType;
  typedef std::map<ClassLabelType, int>                    MapOfClassesType;
  typedef unsigned long                                    ConfusionMatrixEltType;
  typedef itk::VariableSizeMatrix<ConfusionMatrixEltType>  ConfusionMatrixType;

  typedef std::map<
                   ClassLabelType,
                   std::map<ClassLabelType, ConfusionMatrixEltType>
                  > OutputConfusionMatrixType;


private:
  void DoInit()
  {
  SetName("ComputeConfusionMatrix");
  SetDescription("Computes the confusion matrix of a classification");

  // Documentation
  SetDocName("Confusion matrix Computation");
  SetDocLongDescription("This application computes the confusion matrix of a classification map relatively to a ground truth. "
      "This ground truth can be given as a raster or a vector data. Only reference and produced pixels with values different "
      "from NoData are handled in the calculation of the confusion matrix. The confusion matrix is organized the following way: "
      "rows = reference labels, columns = produced labels. In the header of the output file, the reference and produced class labels "
      "are ordered according to the rows/columns of the confusion matrix.");
  SetDocLimitations("None");
  SetDocAuthors("OTB-Team");
  SetDocSeeAlso(" ");

  AddDocTag(Tags::Learning);

  AddParameter(ParameterType_InputImage, "in", "Input Image");
  SetParameterDescription( "in", "The input classification image." );

  AddParameter(ParameterType_OutputFilename, "out", "Matrix output");
  SetParameterDescription("out", "Filename to store the output matrix (csv format)");
  
  AddParameter(ParameterType_Choice,"ref","Ground truth");
  SetParameterDescription("ref","Choice of ground truth format");
  
  AddChoice("ref.raster","Ground truth as a raster image");
  
  AddChoice("ref.vector","Ground truth as a vector data file");
  
  AddParameter(ParameterType_InputImage,"ref.raster.in","Input reference image");
  SetParameterDescription("ref.raster.in","Input image containing the ground truth labels");
  
  AddParameter(ParameterType_InputFilename,"ref.vector.in","Input reference vector data");
  SetParameterDescription("ref.vector.in", "Input vector data of the ground truth");
  
  AddParameter(ParameterType_String,"ref.vector.field","Field name");
  SetParameterDescription("ref.vector.field","Field name containing the label values");
  SetParameterString("ref.vector.field","Class");
  MandatoryOff("ref.vector.field");
  DisableParameter("ref.vector.field");

  AddParameter(ParameterType_Int,"nodatalabel","Value for nodata pixels");
  SetParameterDescription("nodatalabel", "Label for the NoData class. Such input pixels will be discarded from the "
      "ground truth and from the input classification map. By default, 'nodatalabel = 0'.");
  SetDefaultParameterInt("nodatalabel",0);
  MandatoryOff("nodatalabel");
  DisableParameter("nodatalabel");
  
  AddRAMParameter();

  // Doc example parameter settings
  SetDocExampleParameterValue("in", "clLabeledImageQB1.tif");
  SetDocExampleParameterValue("out", "ConfusionMatrix.csv");
  SetDocExampleParameterValue("ref", "vector");
  SetDocExampleParameterValue("ref.vector.in","VectorData_QB1_bis.shp");
  SetDocExampleParameterValue("ref.vector.field","Class");
  SetDocExampleParameterValue("nodatalabel","255");
  }

  void DoUpdateParameters()
  {
    // Nothing to do here : all parameters are independent
  }

  void DoExecute()
  {
    Int32ImageType* input = this->GetParameterImage<Int32ImageType> ("in");

    std::string field;
    int nodata = this->GetParameterInt("nodatalabel");


    Int32ImageType::Pointer reference;
    otb::ogr::DataSource::Pointer ogrRef;
    RasterizeFilterType::Pointer rasterizeReference = RasterizeFilterType::New();

    if (GetParameterString("ref") == "raster")
      {
      reference = this->GetParameterImage<Int32ImageType> ("ref.raster.in");
      }
    else
      {
      ogrRef = otb::ogr::DataSource::New(GetParameterString("ref.vector.in"), otb::ogr::DataSource::Modes::Read);
      field = this->GetParameterString("ref.vector.field");

      rasterizeReference->AddOGRDataSource(ogrRef);
      rasterizeReference->SetOutputParametersFromImage(input);
      rasterizeReference->SetBackgroundValue(nodata);
      rasterizeReference->SetBurnAttribute(field.c_str());

      reference = rasterizeReference->GetOutput();
      reference->UpdateOutputInformation();
      }

    // Prepare local streaming
    SplitterType::Pointer splitter = SplitterType::New();
    unsigned int numberOfStreamDivisions = StreamingTraitsType::CalculateNumberOfStreamDivisions(
      input,
      input->GetLargestPossibleRegion(),
      splitter,
      otb::SET_BUFFER_MEMORY_SIZE,
      0, 1048576*GetParameterInt("ram"), 0);
    RegionType streamRegion;

    otbAppLogINFO("Number of stream divisions : "<<numberOfStreamDivisions);


    // Extraction of the Class Labels from the Reference image/rasterized vector data + filling of m_Matrix
    MapOfClassesType  mapOfClassesRef, mapOfClassesProd;
    MapOfClassesType::iterator  itMapOfClassesRef, itMapOfClassesProd;
    int labelRef = 0, labelProd = 0;
    int itLabelRef = 0, itLabelProd = 0;

    for (unsigned int index = 0; index < numberOfStreamDivisions; index++)
      {
      streamRegion = splitter->GetSplit(index, numberOfStreamDivisions, reference->GetLargestPossibleRegion());

      input->SetRequestedRegion(streamRegion);
      input->PropagateRequestedRegion();
      input->UpdateOutputData();

      reference->SetRequestedRegion(streamRegion);
      reference->PropagateRequestedRegion();
      reference->UpdateOutputData();

      ImageIteratorType itInput(input, streamRegion);
      itInput.GoToBegin();

      ImageIteratorType itRef(reference, streamRegion);
      itRef.GoToBegin();

      while (!itRef.IsAtEnd())
        {
        labelRef = static_cast<ClassLabelType> (itRef.Get());
        labelProd = static_cast<ClassLabelType> (itInput.Get());

        // Extraction of the reference/produced class labels
        if ((labelRef != nodata) && (labelProd != nodata))
          {
          // If the current labels have not been added to their respective mapOfClasses yet
          if (mapOfClassesRef.count(labelRef) == 0)
            {
            mapOfClassesRef[labelRef] = itLabelRef;
            ++itLabelRef;
            }
          if (mapOfClassesProd.count(labelProd) == 0)
            {
            mapOfClassesProd[labelProd] = itLabelProd;
            ++itLabelProd;
            }

          // Filling of m_Matrix
          if (m_Matrix[labelRef][labelProd] == 0)
            {
            m_Matrix[labelRef][labelProd] = 1;
            }
          else
            {
            m_Matrix[labelRef][labelProd]++;
            }

          } // END if ((labelRef != nodata) && (labelProd != nodata))
        ++itRef;
        ++itInput;
        }
      } // END of for (unsigned int index = 0; index < numberOfStreamDivisions; index++)


    /////////////////////////////////////////////
    // Filling the 2 headers for the output file
    const std::string commentRefStr = "#Reference labels (rows):";
    const std::string commentProdStr = "#Produced labels (columns):";
    const char separatorChar = ',';
    std::ostringstream ossHeaderRefLabels, ossHeaderProdLabels;

    // Filling ossHeaderRefLabels for the output file
    ossHeaderRefLabels << commentRefStr;
    itMapOfClassesRef = mapOfClassesRef.begin();
    while (itMapOfClassesRef != mapOfClassesRef.end())
      {
      // labels labelRef of mapOfClassesRef are already sorted
      labelRef = itMapOfClassesRef->first;
      otbAppLogINFO("mapOfClassesRef[" << labelRef << "] = " << itMapOfClassesRef->second);
      ossHeaderRefLabels << labelRef;
      ++itMapOfClassesRef;
      if (itMapOfClassesRef != mapOfClassesRef.end())
        {
        ossHeaderRefLabels << separatorChar;
        }
      else
        {
        ossHeaderRefLabels << std::endl;
        }
      }

    // Filling ossHeaderProdLabels for the output file
    ossHeaderProdLabels << commentProdStr;
    itMapOfClassesProd = mapOfClassesProd.begin();
    while (itMapOfClassesProd != mapOfClassesProd.end())
      {
      // labels labelProd of mapOfClassesProd are already sorted
      labelProd = itMapOfClassesProd->first;
      otbAppLogINFO("mapOfClassesProd[" << labelProd << "] = " << itMapOfClassesProd->second);
      ossHeaderProdLabels << labelProd;
      ++itMapOfClassesProd;
      if (itMapOfClassesProd != mapOfClassesProd.end())
        {
        ossHeaderProdLabels << separatorChar;
        }
      else
        {
        ossHeaderProdLabels << std::endl;
        }
      }


    std::ofstream outFile;
    outFile.open(this->GetParameterString("out").c_str());
    outFile << std::fixed;
    outFile.precision(10);

    /////////////////////////////////////
    // Writing the 2 headers
    outFile << ossHeaderRefLabels.str();
    outFile << ossHeaderProdLabels.str();
    /////////////////////////////////////


    // Initialization of the Confusion Matrix for the application LOG
    unsigned int nbClassesRef = mapOfClassesRef.size();
    unsigned int nbClassesProd = mapOfClassesProd.size();
    m_MatrixLOG.SetSize(nbClassesRef, nbClassesProd);
    m_MatrixLOG.Fill(0);

    int indiceLabelRef = 0, indiceLabelProd = 0;
    for (itMapOfClassesRef = mapOfClassesRef.begin(); itMapOfClassesRef != mapOfClassesRef.end(); ++itMapOfClassesRef)
      {
      // labels labelRef of mapOfClassesRef are already sorted
      labelRef = itMapOfClassesRef->first;

      indiceLabelProd = 0;
      for (itMapOfClassesProd = mapOfClassesProd.begin(); itMapOfClassesProd != mapOfClassesProd.end(); ++itMapOfClassesProd)
        {
        // labels labelProd of mapOfClassesProd are already sorted
        labelProd = itMapOfClassesProd->first;

        m_MatrixLOG(indiceLabelRef, indiceLabelProd) = m_Matrix[labelRef][labelProd];

        ///////////////////////////////////////////////////////////
        // Writing the ordered confusion matrix in the output file
        outFile << m_Matrix[labelRef][labelProd];
        if (indiceLabelProd < (nbClassesProd - 1))
          {
          outFile << separatorChar;
          }
        else
          {
          outFile << std::endl;
          }
        ///////////////////////////////////////////////////////////
        ++indiceLabelProd;
        }
      m_Matrix[labelRef].clear();
      ++indiceLabelRef;
      }

    // m_Matrix is cleared in order to remove old results in case of successive runs of the GUI application
    m_Matrix.clear();
    outFile.close();

    otbAppLogINFO("Reference class labels ordered according to the rows of the output confusion matrix: " << ossHeaderRefLabels.str());
    otbAppLogINFO("Produced class labels ordered according to the columns of the output confusion matrix: " << ossHeaderProdLabels.str());
    otbAppLogINFO("Output confusion matrix (rows = reference labels, columns = produced labels):\n" << m_MatrixLOG);

  }// END Execute()

  ConfusionMatrixType m_MatrixLOG;
  OutputConfusionMatrixType m_Matrix;
};

}
}
OTB_APPLICATION_EXPORT(otb::Wrapper::ComputeConfusionMatrix)
