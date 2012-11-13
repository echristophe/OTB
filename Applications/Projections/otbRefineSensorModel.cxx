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
#include "otbWrapperChoiceParameter.h"
#include "otbWrapperElevationParametersHandler.h"
#include "otbWrapperMapProjectionParametersHandler.h"
#include "otbSensorModelAdapter.h"
#include "itkPoint.h"
#include "itkEuclideanDistance.h"
#include "otbGenericRSTransform.h"

namespace otb
{
namespace Wrapper
{
class RefineSensorModel : public Application
{
public:
  /** Standard class typedefs. */
  typedef RefineSensorModel             Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef itk::Point<double,3>                 PointType;
  typedef itk::Statistics::EuclideanDistance<PointType> DistanceType;

  typedef std::pair<PointType,PointType>       TiePointType;
  typedef std::vector<TiePointType>            TiePointsType;

  typedef otb::GenericRSTransform<double,3,3>  RSTransformType;   
  
  /** Standard macro */
  itkNewMacro(Self);
  itkTypeMacro(RefineSensorModel, otb::Application);

private:
  void DoInit()
  {
    SetName("RefineSensorModel");
    SetDescription("Perform LSQR to fit sensor model to a set of tie points");
    
    SetDocName("Refine Sensor Model");
    SetDocLongDescription("TODO");
    
    SetDocLimitations("None");
    SetDocAuthors("OTB-Team");
    
    AddParameter(ParameterType_InputFilename,"ingeom","Input geom file");
    SetParameterDescription("ingeom","Geom file containing the sensor model to refine");

    AddParameter(ParameterType_OutputFilename,"outgeom","Output geom file");
    SetParameterDescription("outgeom","Geom file containing the refined sensor model");

    AddParameter(ParameterType_InputFilename,"inpoints","Input file containing tie points");
    SetParameterDescription("inpoints","Input file containing tie points. Points are stored in following format: row col lon lat. Line beginning with # are ignored.");

    AddParameter(ParameterType_OutputFilename,"outstat","Output file containing output precision statistics");
    SetParameterDescription("outstat","Output file containing the following info: ref_lon ref_lat elevation predicted_lon predicted_lat x_error_ref(meters) y_error_ref(meters) global_error_ref(meters) x_error(meters) y_error(meters) overall_error(meters)");
    MandatoryOff("outstat");
    DisableParameter("outstat");

    // Build the Output Map Projection
    MapProjectionParametersHandler::AddMapProjectionParameters(this, "map");

    // Elevation
    ElevationParametersHandler::AddElevationParameters(this, "elev");
    
  }

  void DoUpdateParameters()
  {
    // Nothing to do here : all parameters are independent
  }

  void DoExecute()
  {
    otb::SensorModelAdapter::Pointer sm     = otb::SensorModelAdapter::New();
    otb::SensorModelAdapter::Pointer sm_ref = otb::SensorModelAdapter::New();
    
    // Read the geom file
    bool canRead = sm->ReadGeomFile(GetParameterString("ingeom"));
    canRead = sm_ref->ReadGeomFile(GetParameterString("ingeom"));

  // Setup elevation

    otb::DEMHandler::Pointer demHandler = otb::DEMHandler::New();

    double avg_elevation = 0;
    bool use_avg_elevation = false;
    switch(ElevationParametersHandler::GetElevationType(this, "elev"))
      {
      case Elevation_DEM:
      {
      demHandler->OpenDEMDirectory(ElevationParametersHandler::GetDEMDirectory(this, "elev"));
      demHandler->OpenGeoidFile(ElevationParametersHandler::GetGeoidFile(this, "elev"));
      }
      break;
      case Elevation_Average:
      {
      avg_elevation = ElevationParametersHandler::GetAverageElevation(this, "elev");
      use_avg_elevation = true;
      }
      break;
      }

  // Parse the input file for ground control points
  std::ifstream ifs;
  ifs.open(GetParameterString("inpoints").c_str());
   
  TiePointsType tiepoints;

  while(!ifs.eof())
    {
    std::string line;
    std::getline(ifs,line);
    
    double x,y,z,lat,lon;
    
    // Avoid commented lines or too short ones
    if (!line.empty() && line[0] != '#')
      {
      // retrieve the x component
      std::string::size_type pos = 0;
      std::string::size_type nextpos = line.find_first_of("\t", pos);
      x = atof(line.substr(pos, nextpos).c_str());
      pos = nextpos + 1;
      nextpos = line.find_first_of("\t", pos);
      y = atof(line.substr(pos, nextpos).c_str());
      pos = nextpos + 1;
      nextpos = line.find_first_of("\t", pos);
      lon = atof(line.substr(pos, nextpos).c_str());
      pos = nextpos + 1;
      nextpos = line.find_first_of("\t", pos);
      lat = atof(line.substr(pos, nextpos).c_str());
      
      if(!use_avg_elevation)
        z = demHandler->GetHeightAboveEllipsoid(lon,lat);
      else
        z = avg_elevation;

      otbAppLogINFO("Adding tie point x="<<x<<", y="<<y<<", z="<<z<<", lon="<<lon<<", lat="<<lat);
      
      sm->AddTiePoint(x,y,z,lon,lat);

      PointType p1,p2;
      p1[0]=x;
      p1[1]=y;
      p1[2]=z;
      p2[0]=lon;
      p2[1]=lat;
      p2[2]=z;

      tiepoints.push_back(std::make_pair(p1,p2));

      }
    }
  ifs.close();
  
  otbAppLogINFO("Optimization in progress ...");
  sm->Optimize();
  otbAppLogINFO("Done.\n");

  bool canWrite = sm->WriteGeomFile(GetParameterString("outgeom"));

  double rmse = 0;
  double rmsex = 0;
  double rmsey = 0;

  double meanx = 0;
  double meany = 0;

  double rmse_ref = 0;
  double rmsex_ref = 0;
  double rmsey_ref = 0;

  double meanx_ref = 0;
  double meany_ref = 0;


  DistanceType::Pointer distance = DistanceType::New();

  RSTransformType::Pointer rsTransform = RSTransformType::New();
  rsTransform->SetOutputProjectionRef(MapProjectionParametersHandler::GetProjectionRefFromChoice(this, "map"));
  rsTransform->InstanciateTransform();

  std::ofstream ofs;
  ofs<<std::fixed;
  ofs.precision(12);
  if(IsParameterEnabled("outstat"))
    {
    ofs.open(GetParameterString("outstat").c_str());
    ofs<<"#ref_lon ref_lat elevation predicted_lon predicted_lat x_error_ref(meters) y_error_ref(meters) global_error_ref(meters) x_error(meters) y_error(meters) global_error(meters)"<<std::endl;
    }

  for(TiePointsType::const_iterator it = tiepoints.begin();
      it!=tiepoints.end(); ++it)
    {
    PointType tmpPoint,tmpPoint_ref,ref;
    sm->ForwardTransformPoint(it->first[0],it->first[1],it->first[2],tmpPoint[0],tmpPoint[1],tmpPoint[2]);
    sm_ref->ForwardTransformPoint(it->first[0],it->first[1],it->first[2],tmpPoint_ref[0],tmpPoint_ref[1],tmpPoint_ref[2]);

    tmpPoint = rsTransform->TransformPoint(tmpPoint);
    tmpPoint_ref = rsTransform->TransformPoint(tmpPoint_ref);

    ref[0] = it->second[0];
    ref[1] = it->second[1];
    ref[2] = it->second[2];

    ref = rsTransform->TransformPoint(ref);

    double gerror = distance->Evaluate(ref,tmpPoint);
    double xerror = ref[0]-tmpPoint[0];
    double yerror = ref[1]-tmpPoint[1];
    
    double gerror_ref = distance->Evaluate(ref,tmpPoint_ref);
    double xerror_ref = ref[0]-tmpPoint_ref[0];
    double yerror_ref = ref[1]-tmpPoint_ref[1];


    if(IsParameterEnabled("outstat"))
      ofs<<ref[0]<<"\t"<<ref[1]<<"\t"<<it->first[2]<<"\t"<<tmpPoint[0]<<"\t"<<tmpPoint[1]<<"\t"<<tmpPoint[2]<<"\t"<<xerror_ref<<"\t"<<yerror_ref<<"\t"<<gerror_ref<<"\t"<<xerror<<"\t"<<yerror<<"\t"<<gerror<<std::endl;

    rmse += gerror*gerror;
    rmsex+= xerror*xerror;
    rmsey+= yerror*yerror;

    meanx += xerror;
    meany += yerror;

    rmse_ref += gerror_ref*gerror_ref;
    rmsex_ref+=xerror_ref*xerror_ref;
    rmsey_ref+=yerror_ref*yerror_ref;

    meanx_ref += xerror_ref;
    meany_ref += yerror_ref;


    }

  rmse/=tiepoints.size();

  rmsex/=tiepoints.size();

  rmsey/=tiepoints.size();


  meanx/=tiepoints.size();
  meany/=tiepoints.size();


  rmse_ref/=tiepoints.size();

  rmsex_ref/=tiepoints.size();

  rmsey_ref/=tiepoints.size();


  meanx_ref/=tiepoints.size();
  meany_ref/=tiepoints.size();


  double stdevx = vcl_sqrt(rmsex - meanx * meanx);
  double stdevy = vcl_sqrt(rmsey - meany * meany);

  double stdevx_ref = vcl_sqrt(rmsex_ref - meanx_ref * meanx_ref);
  double stdevy_ref = vcl_sqrt(rmsey_ref - meany_ref * meany_ref);


  rmse=vcl_sqrt(rmse);
  rmsex=vcl_sqrt(rmsex);
  rmsey=vcl_sqrt(rmsey);

  rmse_ref=vcl_sqrt(rmse_ref);
  rmsex_ref=vcl_sqrt(rmsex_ref);
  rmsey_ref=vcl_sqrt(rmsey_ref);

  otbAppLogINFO("Estimation of input geom file accuracy: ");
  otbAppLogINFO("Overall Root Mean Square Error: "<<rmse_ref<<" meters");
  otbAppLogINFO("X Mean Error: "<<meanx_ref<<" meters");
  otbAppLogINFO("X standard deviation: "<<stdevx_ref<<" meters");
  otbAppLogINFO("X Root Mean Square Error: "<<rmsex_ref<<" meters");
  otbAppLogINFO("Y Mean Error: "<<meany_ref<<" meters");
  otbAppLogINFO("Y standard deviation: "<<stdevy_ref<<" meters");
  otbAppLogINFO("Y Root Mean Square Error: "<<rmsey_ref<<" meters\n");

  otbAppLogINFO("Estimation of final accuracy: ");

  otbAppLogINFO("Overall Root Mean Square Error: "<<rmse<<" meters");
  otbAppLogINFO("X Mean Error: "<<meanx<<" meters");
  otbAppLogINFO("X standard deviation: "<<stdevx<<" meters");
  otbAppLogINFO("X Root Mean Square Error: "<<rmsex<<" meters");
  otbAppLogINFO("Y Mean Error: "<<meany<<" meters");
  otbAppLogINFO("Y standard deviation: "<<stdevy<<" meters");
  otbAppLogINFO("Y Root Mean Square Error: "<<rmsey<<" meters");


  if(IsParameterEnabled("outstat"))
    ofs.close();
}
};
}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::RefineSensorModel)