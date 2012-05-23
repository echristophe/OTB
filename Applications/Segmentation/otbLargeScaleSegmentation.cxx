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
// Wrappers
#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

// Segmentation filters includes
#include "otbMeanShiftVectorImageFilter.h"
#include "otbMeanShiftImageFilter2.h"
#include "otbConnectedComponentMuParserFunctor.h"
#include "itkConnectedComponentFunctorImageFilter.h"
#include "otbMaskMuParserFilter.h"

// Large scale vectorization framework
#include "otbStreamingVectorizedSegmentationOGR.h"
#include "otbOGRDataSourceWrapper.h"

namespace otb
{
namespace Wrapper
{
class LargeScaleSegmentation : public Application
{
public:
  /** Standard class typedefs. */
  typedef LargeScaleSegmentation        Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Images typedefs */
  typedef UInt32ImageType               LabelImageType;
  typedef UInt32ImageType               MaskImageType;

  // Segmentation filters typedefs
  // Edison mean-shift
  typedef otb::MeanShiftVectorImageFilter
  <FloatVectorImageType,
   FloatVectorImageType,
   LabelImageType>                        EdisonSegmentationFilterType;
  // Home made mean-shift
  typedef otb::MeanShiftImageFilter2
  <FloatVectorImageType, 
   FloatVectorImageType>
                                          MeanShiftFilterType;
  // Simple connected components
  typedef otb::Functor::ConnectedComponentMuParserFunctor
  <FloatVectorImageType::PixelType>       FunctorType;

  typedef itk::ConnectedComponentFunctorImageFilter
  <FloatVectorImageType,
   LabelImageType,
   FunctorType,
   MaskImageType >                        ConnectedComponentSegmentationFilterType;
  
  // mask filter
  typedef otb::MaskMuParserFilter
  <FloatVectorImageType, MaskImageType>   MaskMuParserFilterType;

  // Vectorize filters
  // Edison mean-shift
  typedef otb::StreamingVectorizedSegmentationOGR
  <FloatVectorImageType, 
   EdisonSegmentationFilterType>          EdisontreamingVectorizedSegmentationOGRType;
  
  // Connected components
  typedef otb::StreamingVectorizedSegmentationOGR
  <FloatVectorImageType, 
   ConnectedComponentSegmentationFilterType> 
                                          ConnectedComponentStreamingVectorizedSegmentationOGRType;

  /** Standard macro */
  itkNewMacro(Self);
  itkTypeMacro(LargeScaleSegmentation, otb::Application);

private:
  void DoInit()
  {
    SetName("LargeScaleSegmentation");
    SetDescription("Performs Large scale segmentation");

    // Documentation
    SetDocName("Large Scale segmentation");
    SetDocLongDescription("This application is dedicated to image segmentation. "
      "By handling streaming and OGR framework, it has been optimized for processing large scale data ."
      " Numerous segmentations algorithms are available. Output are vector data type.");
    SetDocLimitations(" .");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso(" ");

    AddDocTag(Tags::Segmentation);

    AddParameter(ParameterType_InputImage, "in", "Input Image");
    SetParameterDescription("in", "The input image.");

    AddParameter(ParameterType_InputImage, "inmask", "Mask Image");
    SetParameterDescription("inmask", "Mask image. (Pixel with 0 will not be processed).");
    MandatoryOff("inmask");

    AddParameter(ParameterType_OutputFilename, "outvd", "Output VectorData");
    SetParameterDescription("outvd", "The name of output Vector Data.");

    AddParameter(ParameterType_OutputImage, "lout", "Labeled output");
    SetParameterDescription("lout", "The labeled output image.");
    MandatoryOff("lout");

    AddParameter(ParameterType_Choice, "filter", "Segmentation Filter");
    SetParameterDescription("filter", "Choose your segmentation filter method.");

    AddChoice("filter.meanshiftedison", "EDISON MeanShift");
    SetParameterDescription("filter.meanshiftedison",
                            "EDISON based MeanShift filter. (is going to be replaced by newframework).");
    // EDISON Meanshift Parameters
    AddParameter(ParameterType_Int, "filter.meanshiftedison.spatialr", "Spatial radius");
    SetParameterDescription("filter.meanshiftedison.spatialr", "Spatial radius defining neighborhood.");
    AddParameter(ParameterType_Float, "filter.meanshiftedison.ranger", "Range radius");
    SetParameterDescription("filter.meanshiftedison.ranger", "Range radius defining the interval in the color space.");
    AddParameter(ParameterType_Int, "filter.meanshiftedison.minsize", "Min region size");
    SetParameterDescription("filter.meanshiftedison.minsize", "Minimun size of a region to be kept after clustering.");
    AddParameter(ParameterType_Float, "filter.meanshiftedison.scale", "Scale");
    SetParameterDescription("filter.meanshiftedison.scale", "Scale to stretch the image before processing.");
    SetDefaultParameterInt("filter.meanshiftedison.spatialr", 5);
    SetDefaultParameterFloat("filter.meanshiftedison.ranger", 15.0);
    SetDefaultParameterInt("filter.meanshiftedison.minsize", 100);
    SetDefaultParameterFloat("filter.meanshiftedison.scale", 100000.);

    // AddChoice("filter.meanshift", "MeanShift");
    // SetParameterDescription(
    //                         "filter.meanshift",
    //                         "MeanShift filter (MeanShift filtered output is segmented by connected component segmentation, this step will be replaced by a dedicated scheme (WIP)).");
    // // MeanShift Parameters
    // AddParameter(ParameterType_Int, "filter.meanshift.spatialr", "Spatial radius");
    // SetParameterDescription("filter.meanshift.spatialr", "Spatial radius defining neighborhood.");
    // AddParameter(ParameterType_Float, "filter.meanshift.ranger", "Range radius");
    // SetParameterDescription("filter.meanshift.ranger", "Range radius defining the interval in the color space.");
    // AddParameter(ParameterType_Float, "filter.meanshift.thres", "convergence threshold");
    // SetParameterDescription("filter.meanshift.thres", "convergence threshold. iterative scheme will stop if MeanShift "
    //   "vector is below this threshold (1e-3 by default) or iteration number reached maximum iteration number.");
    // AddParameter(ParameterType_Int, "filter.meanshift.maxiter", "maximum iteration number");
    // SetParameterDescription("filter.meanshift.maxiter",
    //                         "iteration process is stopped if convergence hasn't been reached after this number of iteration (10 by default).");
    // AddParameter(ParameterType_Empty, "filter.meanshift.useoptim", "use optimization");
    // SetParameterDescription("filter.meanshift.useoptim", "Use mode optimization.");
    // MandatoryOff("filter.meanshift.useoptim");
    // AddParameter(ParameterType_String, "filter.meanshift.expr", "Connected Component Expression");
    // SetParameterDescription("filter.meanshift.expr", "Formula used for connected component segmentation");
    // SetDefaultParameterInt("filter.meanshift.spatialr", 5);

    // SetDefaultParameterInt("filter.meanshift.spatialr", 5);
    // SetDefaultParameterFloat("filter.meanshift.ranger", 15.0);
    // SetDefaultParameterFloat("filter.meanshift.thres", 1e-3);
    // SetMinimumParameterFloatValue("filter.meanshift.thres", 0.);
    // SetDefaultParameterInt("filter.meanshift.maxiter", 10);
    // SetMinimumParameterIntValue("filter.meanshift.maxiter", 1);

    AddChoice("filter.connectedcomponent", "ConnectedComponentMuParser");
    SetParameterDescription("filter.connectedcomponent", "connectedComponant muparser filter.");

    AddParameter(ParameterType_String, "filter.connectedcomponent.expr", "Connected Component Expression");
    SetParameterDescription("filter.connectedcomponent.expr", "Formula used for connected component segmentation");
    MandatoryOff("filter.connectedcomponent.expr");


    AddParameter(ParameterType_Int, "minsize", "Minimum object size");
    SetParameterDescription("minsize",
                            "object with size under this threshold (area in pixels) will be replaced by the background value.");
    SetDefaultParameterInt("minsize", 1);
    SetMinimumParameterIntValue("minsize", 1);
    MandatoryOff("minsize");

    AddParameter(ParameterType_String, "layername", "Layer Name");
    SetParameterDescription("layername", "Layer Name.(by default : Layer )");
    SetParameterString("layername", "layer");
    MandatoryOff("layername");

    AddParameter(ParameterType_String, "fieldname", "Field Name");
    SetParameterDescription("fieldname", "field Name.(by default : DN )");
    SetParameterString("fieldname", "DN");
    MandatoryOff("fieldname");

    AddParameter(ParameterType_Int, "tilesize", "tile size");
    SetParameterDescription("tilesize",
                            "streaming to dimension for computing vectorization.(automatic tile dimension is set "
                              "   if tile size set to 0 (by default).)");
    SetDefaultParameterInt("tilesize", 0);
    MandatoryOff("tilesize");

    AddParameter(ParameterType_Int, "startlabel", "start label");
    SetParameterDescription("startlabel", "Start label.(1 by default)");
    SetDefaultParameterInt("startlabel", 1);
    MandatoryOff("startlabel");

    AddParameter(ParameterType_Empty, "neighbor", "use 8 connected");
    SetParameterDescription("neighbor",
                            "Pixel neighborhood vectorization strategy. 4 or 8 neighborhood .(4 neighborhood by default.)");
    MandatoryOff("neighbor");

    // Doc example parameter settings

    SetDocExampleParameterValue("in", "QB_Toulouse_Ortho_PAN.tif");
    SetDocExampleParameterValue("outvd", "SegmentationVectorData.sqlite");
    SetDocExampleParameterValue("filter", "meanshift");

  }
  
  void DoUpdateParameters()
  {
    // Nothing to do here : all parameters are independent
  }

  void DoExecute()
  {
    // Retrieve output filename as well as layer names
    std::string dataSourceName = GetParameterString("outvd");
    otb::ogr::DataSource::Pointer ogrDS = otb::ogr::DataSource::New(dataSourceName, otb::ogr::DataSource::Modes::write);
    std::string layerName = this->GetParameterString("layername");
    std::string fieldName = this->GetParameterString("fieldname");

    // Retrieve start label parameter 
    const unsigned int startLabel = this->GetParameterInt("startlabel");

    // Retrieve the 8-connected option
    bool use8connected = IsParameterEnabled("neighbor");

    // Retrieve min object size parameter
    const unsigned int minSize = static_cast<unsigned int> (this->GetParameterInt("minsize"));

    // Retrieve tile size parameter
    const unsigned int tileSize = static_cast<unsigned int> (this->GetParameterInt("tilesize"));


    // Switch on segmentation filter case
    switch (GetParameterInt("filter"))
      {
      // Edison mean-shift
      case 0:
        {
        EdisontreamingVectorizedSegmentationOGRType::Pointer
          edisonVectorizationFilter = EdisontreamingVectorizedSegmentationOGRType::New();

        edisonVectorizationFilter->SetInput(GetParameterFloatVectorImage("in"));

        if (HasValue("inmask"))
          {
          edisonVectorizationFilter->SetInputMask(this->GetParameterUInt32Image("inmask"));
          }
        edisonVectorizationFilter->SetOGRDataSource(ogrDS);

        if (tileSize != 0)
          {
          edisonVectorizationFilter->GetStreamer()->SetTileDimensionTiledStreaming(tileSize);
          }
        else 
          {
          edisonVectorizationFilter->GetStreamer()->SetAutomaticAdaptativeStreaming();
          }

        edisonVectorizationFilter->SetLayerName(layerName);
        edisonVectorizationFilter->SetFieldName(fieldName);
        edisonVectorizationFilter->SetStartLabel(startLabel);
        if (use8connected)
        otbAppLogINFO(<<"Use 8 connected neighborhood."<<std::endl);
        edisonVectorizationFilter->SetUse8Connected(use8connected);

        //segmentation paramters
        const unsigned int
            spatialRadius = static_cast<unsigned int> (this->GetParameterInt("filter.meanshiftedison.spatialr"));
        const unsigned int
            rangeRadius = static_cast<unsigned int> (this->GetParameterInt("filter.meanshiftedison.ranger"));
        const unsigned int
            minimumObjectSize = static_cast<unsigned int> (this->GetParameterInt("filter.meanshiftedison.minsize"));
        const float scale = this->GetParameterFloat("filter.meanshiftedison.scale");

        edisonVectorizationFilter->GetSegmentationFilter()->SetSpatialRadius(spatialRadius);
        edisonVectorizationFilter->GetSegmentationFilter()->SetRangeRadius(rangeRadius);
        edisonVectorizationFilter->GetSegmentationFilter()->SetMinimumRegionSize(minimumObjectSize);
        edisonVectorizationFilter->GetSegmentationFilter()->SetScale(scale);
        if (minSize > 1)
          {
          otbAppLogINFO(<<"Object with size under "<<minSize<<" will be suppressed."<<std::endl);
          edisonVectorizationFilter->SetFilterSmallObject(true);
          edisonVectorizationFilter->SetMinimumObjectSize(minSize);
          }

        edisonVectorizationFilter->SetSimplify(false);

        std::cout<<"Edison branch"<<std::endl;

        edisonVectorizationFilter->Initialize(); //must be called !
        edisonVectorizationFilter->Update(); //must be called !
        m_LabelImage = edisonVectorizationFilter->GetSegmentationFilter()->GetLabeledClusteredOutput();

        break;

        }
        // Home made mean-shift
      case 1:
        {
        otbAppLogFATAL(<<"Standard mean-shift not implemented yet");
        break;
        }
        // Connected component segmentation
      case 2:
        {
        ConnectedComponentStreamingVectorizedSegmentationOGRType::Pointer
            ccVectorizationFilter = ConnectedComponentStreamingVectorizedSegmentationOGRType::New();

        ccVectorizationFilter->SetInput(GetParameterFloatVectorImage("in"));
        if (HasValue("inmask"))
          {
          ccVectorizationFilter->SetInputMask(this->GetParameterUInt32Image("inmask"));
          ccVectorizationFilter->GetSegmentationFilter()->SetMaskImage(this->GetParameterUInt32Image("inmask"));

          }
        ccVectorizationFilter->SetOGRDataSource(ogrDS);

        if (tileSize != 0)
          {
          ccVectorizationFilter->GetStreamer()->SetTileDimensionTiledStreaming(tileSize);
          }
        else 
          {
          ccVectorizationFilter->GetStreamer()->SetAutomaticTiledStreaming();
          }

        ccVectorizationFilter->SetLayerName(layerName);
        ccVectorizationFilter->SetFieldName(fieldName);
        ccVectorizationFilter->SetStartLabel(startLabel);
        ccVectorizationFilter->SetUse8Connected(use8connected);

        ccVectorizationFilter->GetSegmentationFilter()->GetFunctor().SetExpression(
                                                                                   GetParameterString(
                                                                                                      "filter.connectedcomponent.expr"));
        AddProcess(ccVectorizationFilter->GetSegmentationFilter(), "Computing segmentation");

        ccVectorizationFilter->Initialize(); //must be called !
        ccVectorizationFilter->Update();
        m_LabelImage = ccVectorizationFilter->GetSegmentationFilter()->GetOutput();

        break;
        }

      default:
        {
        otbAppLogFATAL(<<"non defined filtering method "<<GetParameterInt("filter")<<std::endl);
        break;

        }
        return;
      }

    ogrDS->SyncToDisk();
    SetParameterOutputImage<LabelImageType> ("lout", m_LabelImage);

  }
    LabelImageType::Pointer     m_LabelImage;
};


}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::LargeScaleSegmentation)