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
#ifndef _otbFlusserPathFunction_txx
#define _otbFlusserPathFunction_txx

#include "otbFlusserPathFunction.h"
#include "otbComplexMomentPathFunction.h"
#include "itkNumericTraits.h"
#include "otbMacro.h"

namespace otb
{

/**
   * Constructor
   */
template < class TInputPath, class TOutput>
FlusserPathFunction<TInputPath, TOutput >
::FlusserPathFunction()
{
  m_MomentNumber =-1; 
}

/**
   *
   */
template < class TInputPath, class TOutput>
void
FlusserPathFunction< TInputPath, TOutput >
::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  this->Superclass::PrintSelf(os,indent);
  os << indent << " m_MomentNumber           : "  << m_MomentNumber << std::endl;
}


template < class TInputPath, class TOutput>
typename FlusserPathFunction<TInputPath, TOutput>::RealType
FlusserPathFunction<TInputPath, TOutput >
::Evaluate( const PathType& path) const
{
  typedef ComplexMomentPathFunction<PathType>     FunctionType;
  typedef typename FunctionType::ComplexType      ComplexType;

  RealType                            FlusserValue;
  ComplexType                         FlusserValueComplex;

  typename FunctionType::Pointer function =FunctionType::New();
 
  function->SetStep( this->GetStep() );
  function->SetInputPath( this->GetInputPath() );
  
  switch(m_MomentNumber)
    {
    case 1 : 
        {
	ComplexType C11;
	function->SetP(1);
	function->SetQ(1);
	C11 = function->Evaluate( );
        FlusserValue = C11.real() ;
	}
	break;
    case 2:
        {
	ComplexType C21,C12;
	function->SetP(2);
	function->SetQ(1);
	C21 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate(  );

	FlusserValue = abs( C21 * C12 ) ;
	}
	break;
    case 3:
        {
	ComplexType C20,C12;
	function->SetP(2);
	function->SetQ(0);
	C20 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C20 * pow(C12,2);
	FlusserValue = FlusserValueComplex.real();
	}
	break;
    case 4:
        {
	ComplexType C20,C12;
	function->SetP(2);
	function->SetQ(0);
	C20 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C20 * pow(C12,2);
	FlusserValue = FlusserValueComplex.imag();
	}
	break;
    case 5:
        {
	ComplexType C30,C12;
	function->SetP(3);
	function->SetQ(0);
	C30 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );

	FlusserValueComplex = C30 * pow(C12,3) ;
	FlusserValue = FlusserValueComplex.real();       
	}	
	break;
    case 6:
        {
	ComplexType C30,C12;
	function->SetP(3);
	function->SetQ(0);
	C30 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );

	FlusserValueComplex = C30 * pow(C12,3) ;
	FlusserValue = FlusserValueComplex.real();       
	}	
	break;
    case 7 : 
        {
	ComplexType C22;
	function->SetP(2);
	function->SetQ(2);
	C22 = function->Evaluate( );
        FlusserValue = C22.real() ;
	}
	break;
    case 8:
        {
	ComplexType C31,C12;
	function->SetP(3);
	function->SetQ(1);
	C31 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C31 * pow(C12,2);
	FlusserValue = FlusserValueComplex.real();
	}
	break;
    case 9:
        {
	ComplexType C31,C12;
	function->SetP(3);
	function->SetQ(1);
	C31 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C31 * pow(C12,2);
	FlusserValue = FlusserValueComplex.imag();
	}
	break;
    case 10:
        {
	ComplexType C40,C12;
	function->SetP(4);
	function->SetQ(0);
	C40 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C40 * pow(C12,4);
	FlusserValue = FlusserValueComplex.real();
	}
	break;
    case 11:
        {
	ComplexType C40,C12;
	function->SetP(4);
	function->SetQ(0);
	C40 = function->Evaluate( );
	function->SetP(1);
	function->SetQ(2);
	C12 = function->Evaluate( );
	FlusserValueComplex = C40 * pow(C12,4);
	FlusserValue = FlusserValueComplex.imag();
	}
	break;
	
    default:
	itkWarningMacro("Flusser's invariant parameters are between 1 and 11");	
    }


  return (static_cast<RealType>(FlusserValue) );

}

template < class TInputPath, class TOutput>
typename FlusserPathFunction<TInputPath, TOutput>::RealType
FlusserPathFunction<TInputPath, TOutput >
::Evaluate() const
{
  if( !this->GetInputPath() )
    {
    otbMsgDevMacro( << "Pb with GetInputPath" );
    return static_cast<RealType>( itk::NumericTraits<float>::max());
    }

  RealType Result =  Evaluate( *(this->GetInputPath()) );
  
  return Result;

}


} // namespace otb

#endif
