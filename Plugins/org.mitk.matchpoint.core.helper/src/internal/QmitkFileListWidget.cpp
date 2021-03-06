/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) University College London (UCL).
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "QmitkFileListWidget.h"

#include <ctkPathListWidget.h>
#include <ctkPathListButtonsWidget.h>

//-----------------------------------------------------------------------------
QmitkFileListWidget::QmitkFileListWidget(QWidget*)
{
  this->setupUi(this);
  this->m_PathListWidget->setMode(ctkPathListWidget::FilesOnly);
  this->m_PathListWidget->setFileOptions(ctkPathListWidget::Exists | ctkPathListWidget::Readable | ctkPathListWidget::Executable);
  this->m_PathListButtonsWidget->init(this->m_PathListWidget);
  this->m_PathListButtonsWidget->setOrientation(Qt::Vertical);
  connect(this->m_PathListWidget, SIGNAL(pathsChanged(QStringList,QStringList)), this, SLOT(OnPathsChanged(QStringList, QStringList)));
}


//-----------------------------------------------------------------------------
void QmitkFileListWidget::OnPathsChanged(const QStringList& before, const QStringList& after)
{
  emit pathsChanged(before, after);
}


//-----------------------------------------------------------------------------
QStringList QmitkFileListWidget::files(bool absolutePath) const
{
  return this->m_PathListWidget->files(absolutePath);
}


//-----------------------------------------------------------------------------
void QmitkFileListWidget::setFiles(const QStringList& paths)
{
  this->m_PathListWidget->setPaths(paths);
}
