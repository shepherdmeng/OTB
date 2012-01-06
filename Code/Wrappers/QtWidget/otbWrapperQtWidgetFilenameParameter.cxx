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
#include "otbWrapperQtWidgetFilenameParameter.h"

namespace otb
{
namespace Wrapper
{

QtWidgetFilenameParameter::QtWidgetFilenameParameter(FilenameParameter* param, QtWidgetModel* m)
: QtWidgetParameterBase(param, m),
  m_FilenameParam(param)
{
}

QtWidgetFilenameParameter::~QtWidgetFilenameParameter()
{
}

void QtWidgetFilenameParameter::DoUpdateGUI()
{
  // Update the lineEdit
  QString text( QString::fromStdString(m_FilenameParam->GetValue() ));
  m_Input->setText(text);
}

void QtWidgetFilenameParameter::DoCreateWidget()
{
  // Set up input text edit
  m_HLayout = new QHBoxLayout;
  m_HLayout->setSpacing(0);
  m_HLayout->setContentsMargins(0, 0, 0, 0);
  m_Input = new QLineEdit;
  m_Input->setToolTip( m_FilenameParam->GetDescription() );
  connect( m_Input, SIGNAL(textChanged(const QString&)), this, SLOT(SetFileName(const QString&)) );
  connect( m_Input, SIGNAL(textChanged(const QString&)), GetModel(), SLOT(NotifyUpdate()) );

  m_HLayout->addWidget(m_Input);

  // Set up input text edit
  m_Button = new QPushButton;
  m_Button->setText("...");
  m_Button->setToolTip("Select file...");
  m_Button->setMaximumWidth(m_Button->width());
  connect( m_Button, SIGNAL(clicked()), this, SLOT(SelectFile()) );
  m_HLayout->addWidget(m_Button);

  this->setLayout(m_HLayout);
}

void QtWidgetFilenameParameter::SelectFile()
{
  QFileDialog fileDialog;
  fileDialog.setConfirmOverwrite(true);
  switch(m_FilenameParam->GetRole())
    {
    case Role_Input:
    {
    //fileDialog.setFileMode(QFileDialog::ExistingFile);
    // FIXME: parameter's role is not suitable to separate "input file" names from "output file" names
    fileDialog.setFileMode(QFileDialog::AnyFile); 
    }
    break;
    case Role_Output:
    {
    fileDialog.setFileMode(QFileDialog::AnyFile);
    }
    break;
    }

  fileDialog.setNameFilter("File (*)");

  if (fileDialog.exec())
    {
    this->SetFileName(fileDialog.selectedFiles().at(0));
    m_Input->setText(fileDialog.selectedFiles().at(0));
    }
}

void QtWidgetFilenameParameter::SetFileName(const QString& value)
{
  // save value
  m_FilenameParam->SetValue(value.toStdString());

  // notify of value change
  QString key( QString::fromStdString(m_FilenameParam->GetKey()) );
  emit ParameterChanged(key);
}

}
}
