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



#include "otbBSQImageIO.h"
#include "itkExceptionObject.h"
#include <iostream>

int otbBSQImageIOTestCanRead(int argc, char* argv[])
{
  otb::BSQImageIO::Pointer lBSQImageIO = otb::BSQImageIO::New();
  bool                     lCanRead = lBSQImageIO->CanReadFile(argv[1]);
  if (lCanRead == false)
    {
    std::cerr << "Erreur otb::BSQImageIO : impossible d'ouvrir l'image BSQ " << argv[1] << "." << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
