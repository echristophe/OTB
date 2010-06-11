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

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif

#include <typeinfo>
#include <cassert>

#include "otbMacro.h"

#include "otbWorldView2ImageMetadataInterface.h"
#include "itkMetaDataObject.h"
#include "base/ossimKeywordlist.h"

namespace otb
{

WorldView2ImageMetadataInterface
::WorldView2ImageMetadataInterface()
{
}

bool
WorldView2ImageMetadataInterface::CanRead(const MetaDataDictionaryType& dict) const
{
  std::string sensorID = GetSensorID(dict);
  if (sensorID.find("WV02") != std::string::npos) return true;
  else return false;
}

WorldView2ImageMetadataInterface::VariableLengthVectorType
WorldView2ImageMetadataInterface::GetSolarIrradiance(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  VariableLengthVectorType outputValuesVariableLengthVector;
  ossimKeywordlist         kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string keyBId = "support_data.band_id";
  ossimString keywordStringBId = kwl.find(keyBId.c_str());
  if (keywordStringBId == ossimString("P"))
    {
    outputValuesVariableLengthVector.SetSize(1);
    outputValuesVariableLengthVector.Fill(1381.79);
    }
  else if (keywordStringBId == ossimString("Multi"))
    {
    outputValuesVariableLengthVector.SetSize(4);
    outputValuesVariableLengthVector[0] = 1924.59;
    outputValuesVariableLengthVector[1] = 1843.08;
    outputValuesVariableLengthVector[2] = 1574.77;
    outputValuesVariableLengthVector[3] = 1113.71;
    }
  else
    {
    itkExceptionMacro(<< "Invalid bandID " << keywordStringBId);
    }

  return outputValuesVariableLengthVector;
}

int
WorldView2ImageMetadataInterface::GetDay(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.tlc_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro(<< "Invalid Day");

  ossimString day = keywordStrings[2];

  return day.toInt();
}

int
WorldView2ImageMetadataInterface::GetMonth(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.tlc_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro(<< "Invalid Month");

  ossimString month = keywordStrings[1];

  return month.toInt();
}

int
WorldView2ImageMetadataInterface::GetYear(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.tlc_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro("Invalid Year");

  ossimString year = keywordStrings[0];

  return year.toInt();
}

int
WorldView2ImageMetadataInterface::GetHour(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.tlc_date";
  separatorList = "-T:";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro("Invalid Hour");

  ossimString hour = keywordStrings[3];

  return hour.toInt();
}

int
WorldView2ImageMetadataInterface::GetMinute(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.tlc_date";
  separatorList = "-T:";
  ossimString keywordString = kwl.find(key.c_str());

  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro("Invalid Minute");

  ossimString minute = keywordStrings[4];

  return minute.toInt();
}

int
WorldView2ImageMetadataInterface::GetProductionDay(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.generation_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro(<< "Invalid Day");

  ossimString day = keywordStrings[2];

  return day.toInt();
}

int
WorldView2ImageMetadataInterface::GetProductionMonth(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.generation_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro(<< "Invalid Month");

  ossimString month = keywordStrings[1];

  return month.toInt();
}

int
WorldView2ImageMetadataInterface::GetProductionYear(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);

  std::string key;
  ossimString separatorList;
  key = "support_data.generation_date";
  separatorList = "-T";

  ossimString              keywordString = kwl.find(key.c_str());
  std::vector<ossimString> keywordStrings = keywordString.split(separatorList);

  if (keywordStrings.size() <= 2) itkExceptionMacro("Invalid Year");

  ossimString year = keywordStrings[0];

  return year.toInt();
}

WorldView2ImageMetadataInterface::VariableLengthVectorType
WorldView2ImageMetadataInterface
::GetPhysicalBias(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }
  ImageKeywordlistType ImageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, ImageKeywordlist);
    }
  ossimKeywordlist kwl;
  ImageKeywordlist.convertToOSSIMKeywordlist(kwl);

  VariableLengthVectorType outputValuesVariableLengthVector;
  std::string              keyBId = "support_data.band_id";
  ossimString              keywordStringBId = kwl.find(keyBId.c_str());
  if (keywordStringBId == ossimString("P"))
    {
    outputValuesVariableLengthVector.SetSize(1);
    outputValuesVariableLengthVector.Fill(0.0);
    }
  else if (keywordStringBId == ossimString("Multi"))
    {
    outputValuesVariableLengthVector.SetSize(4);
    outputValuesVariableLengthVector.Fill(0.0);
    }
  else
    {
    itkExceptionMacro(<< "Invalid bandID " << keywordStringBId);
    }

  return outputValuesVariableLengthVector;
}

WorldView2ImageMetadataInterface::VariableLengthVectorType
WorldView2ImageMetadataInterface
::GetPhysicalGain(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }
  ImageKeywordlistType ImageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, ImageKeywordlist);
    }
  ossimKeywordlist kwl;
  ImageKeywordlist.convertToOSSIMKeywordlist(kwl);

  ossimString keywordStringBitsPerPixel = kwl.find("support_data.bits_per_pixel");
  int         bitsPerPixel = keywordStringBitsPerPixel.toInt();
  if (bitsPerPixel != 16 )
    {
    itkExceptionMacro(<< "Invalid bitsPerPixel " << bitsPerPixel);
    }

  std::string keyBId = "support_data.band_id";
  ossimString keywordStringBId = kwl.find(keyBId.c_str());
  if (keywordStringBId != ossimString("P") && keywordStringBId != ossimString("Multi"))
    {
    itkExceptionMacro(<< "Invalid bandID " << keywordStringBId);
    }
    
  ossimString keywordStringTDILevel = kwl.find("support_data.TDI_level");
  int         TDILevel = keywordStringTDILevel.toInt();
  if (keywordStringBId == ossimString("P") && TDILevel != 24 )
    {
    itkExceptionMacro(<< "Invalid TDILevel " << TDILevel);
    }

  VariableLengthVectorType outputValuesVariableLengthVector;
  if (keywordStringBId == ossimString("P")) outputValuesVariableLengthVector.SetSize(1);
  else outputValuesVariableLengthVector.SetSize(4);
  outputValuesVariableLengthVector.Fill(1.);

  if (keywordStringBId == ossimString("P"))
     {
       ossimString keywordStringAbsCalFactor = kwl.find("support_data.absCalFactor");
       outputValuesVariableLengthVector[0] = keywordStringAbsCalFactor.toDouble();
     }
     else
     {
       ossimString keywordStringAbsCalFactor = kwl.find("support_data.B_band_absCalFactor");
       outputValuesVariableLengthVector[0] = keywordStringAbsCalFactor.toDouble();
       keywordStringAbsCalFactor = kwl.find("support_data.G_band_absCalFactor");
       outputValuesVariableLengthVector[1] = keywordStringAbsCalFactor.toDouble();
       keywordStringAbsCalFactor = kwl.find("support_data.N_band_absCalFactor");
       outputValuesVariableLengthVector[2] = keywordStringAbsCalFactor.toDouble();
       keywordStringAbsCalFactor = kwl.find("support_data.R_band_absCalFactor");
       outputValuesVariableLengthVector[3] = keywordStringAbsCalFactor.toDouble();
     }


/* PIO : To be confirmed !!!
 if (keywordStringBId == ossimString("P"))
    {
    outputValuesVariableLengthVector[0] = 1.0 / outputValuesVariableLengthVector[0];
    }
  else
    {
    outputValuesVariableLengthVector[0] = 1.000 / outputValuesVariableLengthVector[0];
    outputValuesVariableLengthVector[1] = 1.000 / outputValuesVariableLengthVector[1];
    outputValuesVariableLengthVector[2] = 1.000 / outputValuesVariableLengthVector[2];
    outputValuesVariableLengthVector[3] = 1.000 / outputValuesVariableLengthVector[3];
    }
*/
  return outputValuesVariableLengthVector;
}

double
WorldView2ImageMetadataInterface::GetSatElevation(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);
  std::string key = "support_data.sat_elevation_angle";
  ossimString keywordString = kwl.find(key.c_str());

  return keywordString.toDouble();
}

double
WorldView2ImageMetadataInterface::GetSatAzimuth(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);
  std::string key = "support_data.sat_azimuth_angle";
  ossimString keywordString = kwl.find(key.c_str());

  return keywordString.toDouble();
}

WorldView2ImageMetadataInterface::VariableLengthVectorType
WorldView2ImageMetadataInterface
::GetFirstWavelengths(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  VariableLengthVectorType wavel(1);
  wavel.Fill(0.);

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);
  std::string key = "support_data.band_id";
  ossimString keywordStringBId = kwl.find(key.c_str());

  if (keywordStringBId != ossimString("P") && keywordStringBId != ossimString("Multi"))
    {
    itkExceptionMacro(<< "Invalid bandID " << keywordStringBId);
    }

  // Panchromatic case
  if (keywordStringBId == ossimString("P"))
    {
    wavel.SetSize(1);
    wavel.Fill(0.450);
    }
  else
    {
    wavel.SetSize(4);
    wavel[0] = 0.450;
    wavel[1] = 0.520;
    wavel[2] = 0.630;
    wavel[3] = 0.760;
    }

  return wavel;
}

WorldView2ImageMetadataInterface::VariableLengthVectorType
WorldView2ImageMetadataInterface
::GetLastWavelengths(const MetaDataDictionaryType& dict) const
{
  if (!this->CanRead(dict))
    {
    itkExceptionMacro(<< "Invalid Metadata, no WorldView2 Image");
    }

  ImageKeywordlistType imageKeywordlist;

  if (dict.HasKey(MetaDataKey::OSSIMKeywordlistKey))
    {
    itk::ExposeMetaData<ImageKeywordlistType>(dict, MetaDataKey::OSSIMKeywordlistKey, imageKeywordlist);
    }

  VariableLengthVectorType wavel(1);
  wavel.Fill(0.);

  ossimKeywordlist kwl;
  imageKeywordlist.convertToOSSIMKeywordlist(kwl);
  std::string key = "support_data.band_id";
  ossimString keywordStringBId = kwl.find(key.c_str());

  if (keywordStringBId != ossimString("P") && keywordStringBId != ossimString("Multi"))
    {
    itkExceptionMacro(<< "Invalid bandID " << keywordStringBId);
    }

  // Panchromatic case
  if (keywordStringBId == ossimString("P"))
    {
    wavel.SetSize(1);
    wavel.Fill(0.900);
    }
  else
    {
    wavel.SetSize(4);
    wavel[0] = 0.520;
    wavel[1] = 0.600;
    wavel[2] = 0.690;
    wavel[3] = 0.900;
    }

  return wavel;
}

} // end namespace otb
