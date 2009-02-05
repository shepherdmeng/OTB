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
#include "itkExceptionObject.h"

#include "otbUnaryFunctorNeighborhoodWithOffsetImageFilter.h"
#include "otbVectorImage.h"
#include "itkConstNeighborhoodIterator.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbTextureFunctorBase.h"


template <class TIterInput1, class TIterInput2, class TOutput>
class ITK_EXPORT TextureFunctorTest : 
	public otb::Functor::TextureFunctorBase<TIterInput1, TIterInput2, TOutput>
{
public:
  TextureFunctorTest()
    {};
  ~TextureFunctorTest(){};

  typedef TIterInput1                           IterType1;
  typedef TIterInput2                           IterType2;
  typedef TOutput                               OutputType;
  typedef typename IterType1::OffsetType        OffsetType;
  typedef typename IterType1::RadiusType        RadiusType;
  typedef typename IterType1::InternalPixelType InternalPixelType;
  typedef typename IterType1::ImageType         ImageType;
  typedef itk::Neighborhood<InternalPixelType,::itk::GetImageDimension<ImageType>::ImageDimension>    NeighborhoodType;
  
  virtual double ComputeOverSingleChannel(const NeighborhoodType &neigh, const NeighborhoodType &neighOff)
  {
    double out = neigh.GetCenterValue(); 
    
	return out;
  }
};


int otbTextureFunctorBase(int argc, char * argv[])
{
  const char * inputFileName  = argv[1];
  const char * outputFileName = argv[2];

  typedef double InputPixelType;
  const int Dimension = 2;
  typedef otb::VectorImage<InputPixelType,Dimension> ImageType;
  typedef ImageType::PixelType PixelType;
  typedef ImageType::OffsetType OffsetType;
  typedef otb::ImageFileReader<ImageType>  ReaderType;
  typedef otb::ImageFileWriter<ImageType> WriterType;

  typedef itk::ConstNeighborhoodIterator<ImageType>   IterType;;
  typedef TextureFunctorTest<IterType, IterType, PixelType>  FunctorType;
  typedef otb::UnaryFunctorNeighborhoodWithOffsetImageFilter<ImageType, ImageType, FunctorType> UnaryFunctorNeighborhoodImageFilterType;

  // Instantiating object
  UnaryFunctorNeighborhoodImageFilterType::Pointer object = UnaryFunctorNeighborhoodImageFilterType::New();
  ReaderType::Pointer reader  = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  reader->SetFileName(inputFileName);
  writer->SetFileName(outputFileName);

  object->SetInput(reader->GetOutput());
  object->SetRadius(atoi(argv[3]));
  OffsetType offset;
  offset[0] =  atoi(argv[4]);
  offset[1] =  atoi(argv[5]);

  object->SetOffset(offset);
  writer->SetInput(object->GetOutput());

  writer->Update();


  return EXIT_SUCCESS;
}
