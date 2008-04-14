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

#include "otbVectorDataFileReader.h"
#include "otbVectorDataSource.h"

int otbVectorDataFileReaderNew(int argc, char * argv[])
{
        typedef otb::VectorDataFileReader<otb::VectorDataSource> VectorDataFileReaderType;
        VectorDataFileReaderType::Pointer object = VectorDataFileReaderType::New();
        return 0;
}
