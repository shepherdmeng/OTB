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

/*===========================================================================*/
/*===============================[ Includes ]================================*/
/*===========================================================================*/

/*===========================================================================*/
/*==============================[ other stuff ]==============================*/
/*===========================================================================*/

template <class TransformationFunctor>
inline
otb::DefaultGeometriesToGeometriesFilter<TransformationFunctor>::DefaultGeometriesToGeometriesFilter()
: m_TransformationFunctor(TransformationFunctor())
{}

template <class TransformationFunctor>
inline
/*virtual*/
otb::DefaultGeometriesToGeometriesFilter<TransformationFunctor>::~DefaultGeometriesToGeometriesFilter()
{}