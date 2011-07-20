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
#ifndef __otbLabelToProSailParameters_txx
#define __otbLabelToProSailParameters_txx

#include "itkNumericTraits.h"

#include "otbLabelToProSailParameters.h"

namespace otb
{

template <class TLabel>
LabelToProSailParameters<TLabel>
::LabelToProSailParameters()
{
}

template <class TLabel>
const typename LabelToProSailParameters<TLabel>::ParametersType &
LabelToProSailParameters<TLabel>
::GetStep1Parameters()
{
   return this->m_Step1Parameters;
}

template <class TLabel>
const typename LabelToProSailParameters<TLabel>::ParametersType &
LabelToProSailParameters<TLabel>
::GetStep2Parameters()
{
   return this->m_Step2Parameters;
}


template <class TLabel>
void
LabelToProSailParameters<TLabel>
::GenerateData()
{
  //int value = 0;
  //    this->m_Label;
  this->m_Step1Parameters.SetSize(6);
  this->m_Step2Parameters.SetSize(8);

  //TODO accessor must be implemented in otbLabelToSimulationParametersBase
  // and default values need to migrate to class constructor.
  this->m_Step1Parameters[0] = 30.0;
  this->m_Step1Parameters[1] = 10.0;
  this->m_Step1Parameters[2] = 0.0;
  this->m_Step1Parameters[3] = 0.015;
  this->m_Step1Parameters[4] = 0.009;
  this->m_Step1Parameters[5] = 1.2;

  this->m_Step2Parameters[0] = 2;
  this->m_Step2Parameters[1] = 50;
  this->m_Step2Parameters[2] = 1;
  this->m_Step2Parameters[3] = 70;
  this->m_Step2Parameters[4] = 0.2;
  this->m_Step2Parameters[5] = 30;
  this->m_Step2Parameters[6] = 0;
  this->m_Step2Parameters[7] = 0;

}


} // end namespace otb

#endif

