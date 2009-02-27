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
#ifndef __otbMultiChannelRAndBAndNIRVegetationIndexImageFilter_h
#define __otbMultiChannelRAndBAndNIRVegetationIndexImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "otbVegetationIndicesFunctor.h"

namespace otb
{

/** \class MultiChannelRAndBAndNIRVegetationIndexImageFilter
   * \brief Implements mutli channel R and B and NIR pixel-wise generic vegetation index operation on one vector image.
   *
   * This class is parameterized over the type of the input image and
   * the type of the output image.  It is also parameterized by the
   * operation to be applied, using a Functor style.
   *
   * \sa UnaryFunctorImageFilter
   * \ingroup Radiometry
 */
template <class TInputImage, class TOutputImage,
class TFunction = Functor::ARVI< typename TInputImage::InternalPixelType,
typename TInputImage::InternalPixelType,
typename TInputImage::InternalPixelType,
typename TOutputImage::PixelType>  >
class ITK_EXPORT MultiChannelRAndBAndNIRVegetationIndexImageFilter
      : public itk::UnaryFunctorImageFilter<TInputImage,TOutputImage,TFunction>
{
public:
  /** Standard class typedefs. */
  typedef MultiChannelRAndBAndNIRVegetationIndexImageFilter                Self;
  typedef itk::UnaryFunctorImageFilter<TInputImage,TOutputImage,TFunction> Superclass;
  typedef itk::SmartPointer<Self>                                          Pointer;
  typedef itk::SmartPointer<const Self>                                    ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MultiChannelRAndBAndNIRVegetationIndexImageFilter, UnaryFunctorImageFilter);

  /** Some typedefs. */
  typedef TFunction   FunctorType;

  /** Set/Get the red channel index. Value must be in [1...[ */
  itkSetMacro(RedIndex,unsigned int);
  itkGetMacro(RedIndex,unsigned int);
  /** Set/Get the blue channel index. Value must be in [1...[ */
  itkSetMacro(BlueIndex,unsigned int);
  itkGetMacro(BlueIndex,unsigned int);
  /** Set/Get the nir channel index. Value must be in [1...[ */
  itkSetMacro(NIRIndex,unsigned int);
  itkGetMacro(NIRIndex,unsigned int);

protected:
  /// Constructor
  MultiChannelRAndBAndNIRVegetationIndexImageFilter(): m_RedIndex(3),m_BlueIndex(1),m_NIRIndex(4) {};
  /// Destructor
  virtual ~MultiChannelRAndBAndNIRVegetationIndexImageFilter() {};
  /// Before generating data, set functor parameters
  virtual void BeforeThreadedGenerateData()
  {
    unsigned int lNbChan = this->GetInput()->GetNumberOfComponentsPerPixel();
    if (m_RedIndex < 1 || m_BlueIndex < 1 || m_NIRIndex < 1 ||
        m_RedIndex > lNbChan || m_BlueIndex > lNbChan || m_NIRIndex > lNbChan)
    {
      itkExceptionMacro(<<"Channel indices must belong to range [1, ...[");
    }
    this->GetFunctor().SetRedIndex(m_RedIndex);
    this->GetFunctor().SetBlueIndex(m_BlueIndex);
    this->GetFunctor().SetNIRIndex(m_NIRIndex);
  }
  /// PrintSelf
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    this->Superclass::PrintSelf(os,indent);
    os << indent << "Red  index: "<<m_RedIndex<<std::endl;
    os << indent << "Blue index: "<<m_BlueIndex<<std::endl;
    os << indent << "NIR  index: "<<m_NIRIndex<<std::endl;
  }

private:
  MultiChannelRAndBAndNIRVegetationIndexImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Red channel index */
  unsigned int m_RedIndex;
  /** Blue channel index */
  unsigned int m_BlueIndex;
  /** NIR channel index */
  unsigned int m_NIRIndex;
};

} // end namespace otb

#endif
