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
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbStreamingStatisticsVectorImageFilter.h"
#include "otbEigenvalueLikelihoodMaximisation.h"
#include "otbVcaImageFilter.h"
#include "otbUnConstrainedLeastSquareImageFilter.h"

#include "otbVectorImageToMatrixImageFilter.h"

int main(int argc, char * argv[])
{
  if (argc != 3)
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << "inputFileName outputFileName " << std::endl;
    return EXIT_FAILURE;
    }

  const char *       infname = argv[1];
  const char *       outfname = argv[2];
  const unsigned int Dimension = 2;

  typedef double                                  PixelType;
  typedef otb::VectorImage<PixelType, Dimension>  ImageType;
  
  typedef otb::ImageFileReader<ImageType>         ReaderType;
  typedef otb::ImageFileWriter<FloatImageType>    WriterType;
  
  typedef otb::StreamingStatisticsVectorImageFilter<ImageType> StreamingStatisticsVectorImageFilterType;
  typedef otb::EigenvalueLikelihoodMaximisation<double>        ELMType;
  typedef otb::VCAImageFilter<ImageType>                       VCAFilterType;

  typedef otb::UnConstrainedLeastSquareImageFilter<ImageType,ImageType,double> UCLSUnmixingFilterType;

  typedef otb::VectorImageToMatrixImageFilter<ImageType> VectorImageToMatrixImageFilterType;

  typedef vnl_vector<double> VectorType;
  typedef vnl_matrix<double> MatrixType;

/// / Noise filtering
  //  typedef otb::LocalActivityVectorImageFilter< ImageType, ImageType > NoiseFilterType;

  // // Image filtering
  //  typedef otb::MNFImageFilter< ImageType, ImageType,
  //    NoiseFilterType, otb::Transform::FORWARD > FilterType;

  //read image
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(infname);
  reader->UpdateOutputInformation();

  std::cout << "Computing stats" << std::endl;

  StreamingStatisticsVectorImageFilterType::Pointer stats = StreamingStatisticsVectorImageFilterType::New();

  stats->SetInput(reader->GetOutput());
  otb::StandardWriterWatcher watcher(stats->GetStreamer(), stats->GetFilter(), "Computing image stats");
  stats->Update();

  VectorType mean (stats->GetMean().GetDataPointer(), stats->GetMean().GetSize());
  MatrixType covariance  = stats->GetCovariance().GetVnlMatrix();
  MatrixType correlation = stats->GetCorrelation().GetVnlMatrix();

  /*
         * Estimate Endmembers Numbers
         */
  std::cout << "Estimate Endmembers Numbers by ELM" << std::endl;

  ELMType::Pointer elm = ELMType::New();
  elm->SetCovariance(covariance);
  elm->SetCorrelation(correlation);
  elm->SetNumberOfPixels(reader->GetOutput()->GetLargestPossibleRegion().GetNumberOfPixels());
  elm->Compute();

  const unsigned int nbEndmembers = elm->GetNumberOfEndmembers();

  std::cout << "ELM : " << nbEndmembers << " estimated endmembers" << std::endl;

  std::cout << "ELM likelihood values: " << elm->GetLikelihood() << std::endl;
    

/*
       * Estimate Endmembers
       */
  std::cout << "Estimate Endmembers by VCA" << std::endl;

  VCAFilterType::Pointer vca = VCAFilterType::New();
  vca->SetNumberOfEndmembers(nbEndmembers);
  vca->SetInput(reader->GetOutput());

  ImageType::Pointer endmembersImage;
  endmembersImage = vca->GetOutput();

  /*
     * Transform Endmembers image to matrix representation
     */
  std::cout << "Endmembers extracted" << std::endl;
  std::cout << "Converting endmembers to matrix" << std::endl;
  VectorImageToMatrixImageFilterType::Pointer endMember2Matrix = VectorImageToMatrixImageFilterType::New();
  endMember2Matrix->SetInput(endmembersImage);
  endMember2Matrix->Update();

  MatrixType endMembersMatrix = endMember2Matrix->GetMatrix();
  std::cout << "Endmembers matrix : " << endMembersMatrix << std::endl;

  /*
     * Unmix
     */
  UCLSUnmixingFilterType::Pointer unmixer =
    UCLSUnmixingFilterType::New();

  unmixer->SetInput(reader->GetOutput());
  unmixer->SetMatrix(endMembersMatrix);
  unmixer->SetNumberOfThreads(1); // FIXME : currently buggy
      
  ImageType::Pointer abundanceMap;
  abundanceMap = unmixer->GetOutput();
      
  /*
  * Write abundance map
  */
  std::cout << "Write abundance map " << outfname << std::endl;

  WriterType::Pointer  writer = WriterType::New();
  writer->SetInput(abundanceMap);
  writer->SetFileName(outfname);
  
  writer->Update();

  return EXIT_SUCCESS;
} // end main
