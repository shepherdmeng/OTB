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
#include "otbCoordinateToName.h"
#include "otbGroundSpacingImageFunction.h"
#include "vnl/vnl_random.h"

namespace otb
{
namespace Wrapper
{

class ReadImageInfo : public Application
{
public:
  /** Standard class typedefs. */
  typedef ReadImageInfo                 Self;
  typedef Application                   Superclass;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef otb::GroundSpacingImageFunction<FloatVectorImageType> GroundSpacingImageType;
  typedef GroundSpacingImageType::FloatType                     FloatType;
  typedef GroundSpacingImageType::ValueType                     ValueType;

  /** Standard macro */
  itkNewMacro(Self);

  itkTypeMacro(ReadImageInfo, otb::Application);

private:
  void DoInit()
  {
    SetName("ReadImageInfo");
    SetDescription("Get information about the image");

    // Documentation
    SetDocName("Read image information");
    SetDocLongDescription("Display informations about the input image like: image size, metadata, projections...");
    SetDocLimitations("None");
    SetDocAuthors("OTB-Team");
    SetDocSeeAlso(" ");

    AddDocTag("Utilities");
    AddDocTag(Tags::Manip);
    AddDocTag(Tags::Meta);

    AddParameter(ParameterType_InputImage,  "in",   "Input Image");
    
    AddParameter(ParameterType_Empty, "keywordlist", "Display the OSSIM keywordlist");
    SetParameterDescription("keywordlist", "Output the OSSIM keyword list.\n"                                      "It contains metadata informations (sensor model, geometry ). Informations are store in keyword list (pairs of key/value)");
    DisableParameter("keywordlist");
    MandatoryOff("keywordlist");
    //Create output parameters to store image informations
    AddParameter(ParameterType_Int,"sizex","Size X");
    SetParameterRole("sizex", Role_Output);
    AddParameter(ParameterType_Int,"sizey","Size Y");
    SetParameterRole("sizey", Role_Output);

    AddParameter(ParameterType_Float,"spacingx","Pixel Size X");
    SetParameterRole("spacingx", Role_Output);
    AddParameter(ParameterType_Float,"spacingy","Pixel Size Y");
    SetParameterRole("spacingy", Role_Output);

    AddParameter(ParameterType_Float,"estimatedgroundspacingx","Estimated ground spacing X (in meters)");
    SetParameterRole("estimatedgroundspacingx", Role_Output);
    AddParameter(ParameterType_Float,"estimatedgroundspacingy","Estimated ground spacing Y (in meters)");
    SetParameterRole("estimatedgroundspacingy", Role_Output);

    AddParameter(ParameterType_Int,"numberbands","Number Of Bands");
    SetParameterRole("numberbands", Role_Output);
    
    AddParameter(ParameterType_String,"sensor","Sensor id");
    SetParameterRole("sensor", Role_Output);
   
    AddParameter(ParameterType_String,"id","Image id");
    SetParameterRole("id", Role_Output);

    AddParameter(ParameterType_String,"time","Acquisition time");
    SetParameterRole("time", Role_Output);

    AddParameter(ParameterType_Float,"ullat","Upper left lattitude");
    SetParameterRole("ullat", Role_Output);
    SetDefaultParameterFloat("ullat", 0);

    AddParameter(ParameterType_Float,"ullon","Upper left longitude");
    SetParameterRole("ullon", Role_Output);
    SetDefaultParameterFloat("ullon", 0);

    AddParameter(ParameterType_Float,"urlat","Upper right lattitude");
    SetParameterRole("urlat", Role_Output);
    SetDefaultParameterFloat("urlat", 0);

    AddParameter(ParameterType_Float,"urlon","Upper right longitude");
    SetParameterRole("urlon", Role_Output);
    SetDefaultParameterFloat("urlon", 0);

    AddParameter(ParameterType_Float,"lrlat","Lower right lattitude");
    SetParameterRole("lrlat", Role_Output);
    SetDefaultParameterFloat("lrlat", 0);

    AddParameter(ParameterType_Float,"lrlon","Lower right longitude");
    SetParameterRole("lrlon", Role_Output);
    SetDefaultParameterFloat("lrlon", 0);

    AddParameter(ParameterType_Float,"lllat","Lower left lattitude");
    SetParameterRole("lllat", Role_Output);
    SetDefaultParameterFloat("lllat", 0);

    AddParameter(ParameterType_Float,"lllon","Lower left longitude");
    SetParameterRole("lllon", Role_Output);
    SetDefaultParameterFloat("lllon", 0);


    AddParameter(ParameterType_String,"town","Main town near center of image");
    SetParameterRole("town", Role_Output);

    AddParameter(ParameterType_String,"country","Country of the image");
    SetParameterRole("country", Role_Output);

    AddParameter(ParameterType_Group, "rgb", "Default RGB Display");
    SetParameterDescription("rgb","This group of parameters allows to access to the default rgb composition.");

    AddParameter(ParameterType_Int, "rgb.r", "Red Band");
    SetParameterDescription("rgb.r","Red band Number");
    SetDefaultParameterInt("rgb.r", 1);
    SetParameterRole("rgb.r", Role_Output);

    AddParameter(ParameterType_Int, "rgb.g", "Green Band");
    SetParameterDescription("rgb.g","Green band Number");
    SetDefaultParameterInt("rgb.g", 2);
    SetParameterRole("rgb.g", Role_Output);

    AddParameter(ParameterType_Int, "rgb.b", "Blue Band");
    SetParameterDescription("rgb.b","Blue band Number");
    SetDefaultParameterInt("rgb.b", 3);
    SetParameterRole("rgb.b", Role_Output);

    AddParameter(ParameterType_String,"projectionref","Projection Coordinate System");
    SetParameterRole("projectionref", Role_Output);

    AddParameter(ParameterType_String,"keyword","Image Keywordlist");
    SetParameterRole("keyword", Role_Output);

    AddParameter(ParameterType_Group, "gcp", "Ground Control Points informations");
    SetParameterDescription("gcp","This group of parameters allows to access to the GCPs informations.");
    SetParameterRole("gcp", Role_Output);

    AddParameter(ParameterType_Int, "gcp.count", "GCPs Number");
    SetParameterDescription("gcp.count","Number of GCPs");
    SetDefaultParameterInt("gcp.count", 0);
    SetParameterRole("gcp.count", Role_Output);

    AddParameter(ParameterType_String,"gcp.proj","GCP Projection System");
    SetParameterRole("gcp.proj", Role_Output);

    AddParameter(ParameterType_StringList,"gcp.ids","GCPs Id");
    SetParameterRole("gcp.ids", Role_Output);
    AddParameter(ParameterType_StringList,"gcp.info","GCPs Info");
    SetParameterRole("gcp.info", Role_Output);
    AddParameter(ParameterType_StringList,"gcp.imcoord","GCPs Image Coordinates");
    SetParameterRole("gcp.imcoord", Role_Output);
    AddParameter(ParameterType_StringList,"gcp.geocoord","GCPs Geographic Coordinates");
    SetParameterRole("gcp.geocoord", Role_Output);

    // Doc example parameter settings
    SetDocExampleParameterValue("in", "QB_Toulouse_Ortho_XS.tif");
  }

  void DoUpdateParameters()
  {
    // Nothing to do here : all parameters are independent
  }

  void DoExecute()
  {
    std::ostringstream ossOutput;
    FloatVectorImageType::Pointer inImage = GetParameterImage("in");
      
    ossOutput << std::endl << "Image general informations:" << std::endl;

    // Read informations
    typedef otb::ImageMetadataInterfaceBase ImageMetadataInterfaceType;
    ImageMetadataInterfaceType::Pointer metadataInterface = ImageMetadataInterfaceFactory::CreateIMI(inImage->GetMetaDataDictionary());

    //Get number of bands
    SetParameterInt("numberbands", inImage->GetNumberOfComponentsPerPixel());
    ossOutput << "\tNumber of bands : " << GetParameterInt("numberbands") << std::endl;

    //Get image size
    SetParameterInt("sizex", inImage->GetLargestPossibleRegion().GetSize()[0]);
    SetParameterInt("sizey", inImage->GetLargestPossibleRegion().GetSize()[1]);

    ossOutput << "\tSize :  [" << GetParameterInt("sizex") << "," << GetParameterInt("sizey") << "]" << std::endl;
    //Get image spacing
    SetParameterFloat("spacingx", inImage->GetSpacing()[0]);
    SetParameterFloat("spacingy", inImage->GetSpacing()[1]);
    ossOutput << "\tSpacing :  [" << GetParameterFloat("spacingx") << "," << GetParameterFloat("spacingy") << "]" << std::endl;
      
    //Estimate ground spacing
    GroundSpacingImageType::Pointer groundSpacing = GroundSpacingImageType::New();
    groundSpacing->SetInputImage(inImage);
      
    FloatType approxGroundSpacing = std::make_pair(itk::NumericTraits<ValueType>::Zero, itk::NumericTraits<ValueType>::min());

    FloatVectorImageType::IndexType  index;
    vnl_random rand;

    index[0] = static_cast<FloatVectorImageType::IndexType::IndexValueType>(rand.lrand32(0, inImage->GetLargestPossibleRegion().GetSize()[0]));
    index[1] = static_cast<FloatVectorImageType::IndexType::IndexValueType>(rand.lrand32(0, inImage->GetLargestPossibleRegion().GetSize()[1]));
      
    approxGroundSpacing = groundSpacing->EvaluateAtIndex(index);

    //Get image estimated ground spacing (in m)
    SetParameterFloat("estimatedgroundspacingx", approxGroundSpacing.first);
    SetParameterFloat("estimatedgroundspacingy", approxGroundSpacing.second);

    ossOutput << "\tEstimated ground spacing (in meters): [" << GetParameterFloat("estimatedgroundspacingx") << "," << GetParameterFloat("estimatedgroundspacingy") << "]" << std::endl;

    ossOutput << std::endl << "Image acquisition informations:" << std::endl;
      
    SetParameterString("sensor", metadataInterface->GetSensorID());
    ossOutput << "\tSensor : ";
    if (!GetParameterString("sensor").empty())
      ossOutput <<  GetParameterString("sensor");
      
    ossOutput << std::endl;

    ossOutput << "\tImage identification number: ";
    if (metadataInterface->GetImageKeywordlist().HasKey("image_id"))
      {
      SetParameterString("id", metadataInterface->GetImageKeywordlist().GetMetadataByKey("image_id"));
      ossOutput << GetParameterString("id");
      }
    ossOutput << std::endl;
    SetParameterString("projectionref", metadataInterface->GetProjectionRef());
    if (!GetParameterString("projectionref").empty())
      ossOutput << "\tImage projection : " << GetParameterString("projectionref") << std::endl;
      
    // Format acquisition time
    //Test if this information is available and silently catch
    //associated exception
    try
      {
      std::ostringstream osstime;
      osstime<<metadataInterface->GetYear()<<"-";
      if(metadataInterface->GetMonth()<10)
        osstime<<"0";
      osstime<<metadataInterface->GetMonth()<<"-";
      if(metadataInterface->GetDay()<10)
        osstime<<"0";
      osstime<<metadataInterface->GetDay()<<"T";
      if(metadataInterface->GetHour()<10)
        osstime<<"0";
      osstime<<metadataInterface->GetHour()<<":";
      if(metadataInterface->GetMinute()<10)
        osstime<<"0";
      osstime<<metadataInterface->GetMinute();
      osstime<<":00";
      SetParameterString("time", osstime.str());
      
      ossOutput << "\tAcquisition time : " << GetParameterString("time") << std::endl;
      }
    catch ( itk::ExceptionObject & err )
      {
      }

    try
      {
      double ullat = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ul_lat").c_str());
      double ullon = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ul_lon").c_str());
      double urlat = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ur_lat").c_str());
      double urlon = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ur_lon").c_str());
      double lrlat = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("lr_lat").c_str());
      double lrlon = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("lr_lon").c_str());
      double lllat = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ll_lat").c_str());
      double lllon = atof(metadataInterface->GetImageKeywordlist().GetMetadataByKey("ll_lon").c_str());
      
      double centerlat = 0.25*(ullat+urlat+lrlat+lllat);
      double centerlon = 0.25*(ullon+urlon+lrlon+lllon);

      CoordinateToName::Pointer coord2name = CoordinateToName::New();
      coord2name->SetLat(centerlat);
      coord2name->SetLon(centerlon);
      coord2name->Evaluate();

      if( !coord2name->GetCountryName().empty() )
        {
        SetParameterString("country", coord2name->GetCountryName());
        ossOutput << "\tCountry : " << GetParameterString("country") << std::endl;
        }
      else
        SetParameterString("country", "Not available");

      if( !coord2name->GetPlaceName().empty() )
        {
        SetParameterString("town", coord2name->GetPlaceName());
        ossOutput << "\tTown : " << GetParameterString("town") << std::endl;
        }
      else
        SetParameterString("town", "Not available");

      // Retrieve footprint
      SetParameterFloat("ullat", ullat);
      SetParameterFloat("ullon", ullon);
      SetParameterFloat("urlat", urlat);
      SetParameterFloat("urlon", urlon);
      SetParameterFloat("lrlat", lrlat);
      SetParameterFloat("lrlon", lrlon);
      SetParameterFloat("lllat", lllat);
      SetParameterFloat("lllon", lllon);

      ossOutput << std::endl << "Image footprint coordinates:" << std::endl;
      ossOutput << "\tUpper left corner (latitude, longitude) = [" << GetParameterFloat("ullat") << "," << GetParameterFloat("ullon") << "]" << std::endl;
      ossOutput << "\tUpper right corner (latitude, longitude) = [" << GetParameterFloat("urlat") << "," << GetParameterFloat("urlon") << "]" << std::endl;
      ossOutput << "\tLower left corner (latitude, longitude) = [" << GetParameterFloat("lllat") << "," << GetParameterFloat("lllon") << "]" << std::endl;
      ossOutput << "\tLower right corner (latitude, longitude) = [" << GetParameterFloat("lrlat") << "," << GetParameterFloat("lrlon") << "]" << std::endl;
      }
    catch ( itk::ExceptionObject & err )
      {
      }
      
    SetParameterInt("rgb.r", metadataInterface->GetDefaultDisplay()[0]);
    SetParameterInt("rgb.g", metadataInterface->GetDefaultDisplay()[1]);
    SetParameterInt("rgb.b", metadataInterface->GetDefaultDisplay()[2]);
 
    ossOutput << std::endl << "Image default RGB composition:" << std::endl;
    ossOutput << "\t[R, G, B] = [" << GetParameterInt("rgb.r") << "," << GetParameterInt("rgb.g") << "," << GetParameterInt("rgb.b") << "]" << std::endl;

    SetParameterInt("gcp.count", metadataInterface->GetGCPCount());
    SetParameterString("gcp.proj", metadataInterface->GetGCPProjection());
      
    ossOutput << std::endl << "Ground control points information:" << std::endl;
    ossOutput << "\tNumber of GCPs = " << GetParameterInt("gcp.count") << std::endl;
    ossOutput << "\tGCPs projection = " << GetParameterString("gcp.proj") << std::endl;
    std::vector<std::string> gcp_ids;
    std::vector<std::string> gcp_imcoord;
    std::vector<std::string> gcp_geocoord;
    std::vector<std::string> gcp_infos;
      
    for(int gcpIdx = 0; gcpIdx  < GetParameterInt("gcp.count"); ++ gcpIdx)
      {
      if (gcpIdx == 0)
        ossOutput << "\tGCP individual informations:" << std::endl;
        
      gcp_ids.push_back(metadataInterface->GetGCPId(gcpIdx));
      gcp_infos.push_back(metadataInterface->GetGCPInfo(gcpIdx));
      std::ostringstream oss;
      oss << "[" << metadataInterface->GetGCPCol(gcpIdx) << ", " << metadataInterface->GetGCPRow(gcpIdx) << "]";
      gcp_imcoord.push_back(oss.str());
      oss.str("");
      oss << "[" << metadataInterface->GetGCPX(gcpIdx) << ", " << metadataInterface->GetGCPY(gcpIdx) <<", " << metadataInterface->GetGCPZ(gcpIdx) << "]";
      gcp_geocoord.push_back(oss.str());
      ossOutput << "\t\tID =" << gcp_ids.back() << std::endl;
      ossOutput << "\t\tInfo =" << gcp_infos.back() << std::endl;
      ossOutput << "\t\tImage coordinates =" << gcp_imcoord.back() << std::endl;
      ossOutput << "\t\tGround  coordinates =" << gcp_geocoord.back() << std::endl;
      }
      
    SetParameterStringList("gcp.ids", gcp_ids);
    SetParameterStringList("gcp.imcoord", gcp_imcoord);
    SetParameterStringList("gcp.geocoord", gcp_geocoord);
    SetParameterStringList("gcp.info", gcp_infos);

    if ( IsParameterEnabled("keywordlist") )
      {
      std::ostringstream osskeywordlist;
      osskeywordlist<<metadataInterface->GetImageKeywordlist() << std::endl;
      SetParameterString("keyword", osskeywordlist.str());
        
      ossOutput << std::endl << "Image OSSIM keywordlist (optional):" << std::endl;
      ossOutput << "\t" << GetParameterString("keyword") << std::endl;
      }

    //Display image informations in the dedicated logger
    otbAppLogINFO( << ossOutput.str() );
  }

};

}
}

OTB_APPLICATION_EXPORT(otb::Wrapper::ReadImageInfo)
