/*===================================================================

  The Medical Imaging Interaction Toolkit (MITK)

  Copyright (c) German Cancer Research Center,
  Division of Medical and Biological Informatics.
  All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without
  even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.

  See LICENSE.txt or http://www.mitk.org for details.

  ===================================================================*/

#ifndef LOGOOVERLAY_H
#define LOGOOVERLAY_H

#include "MitkOverlaysExports.h"
#include <mitkLocalStorageHandler.h>
#include <mitkVtkOverlay.h>
#include <vtkSmartPointer.h>

class mitkVtkLogoRepresentation;
class vtkImageData;
class vtkImageReader2Factory;
class vtkImageImport;

namespace mitk
{
  /** \brief Displays a logo on the renderwindow */
  class MITKOVERLAYS_EXPORT LogoOverlay : public mitk::VtkOverlay
  {
  public:
    class LocalStorage : public mitk::Overlay::BaseLocalStorage
    {
    public:
      /** \brief Actor of a 2D render window. */
      vtkSmartPointer<vtkImageData> m_LogoImage;
      vtkSmartPointer<mitkVtkLogoRepresentation> m_LogoRep;

      /** \brief Timestamp of last update of stored data. */
      itk::TimeStamp m_LastUpdateTime;

      /** \brief Default constructor of the local storage. */
      LocalStorage();
      /** \brief Default deconstructor of the local storage. */
      ~LocalStorage();
    };

    mitkClassMacro(LogoOverlay, mitk::VtkOverlay);
    itkFactorylessNewMacro(Self) itkCloneMacro(Self)

      vtkSmartPointer<vtkImageReader2Factory> m_readerFactory;

    void SetLogoImagePath(std::string text);
    std::string GetLogoImagePath() const;

    /** \brief The relative offset to the corner position */
    void SetOffsetVector(const Point2D &OffsetVector);
    Point2D GetOffsetVector() const;

    /** \brief The corner where the logo is displayed.
   0 = Bottom left
   1 = Bottom right
   2 = Top right
   3 = Top left
   4 = Center*/
    void SetCornerPosition(const int &corner);
    int GetCornerPosition() const;

    void SetRelativeSize(const float &size);
    float GetRelativeSize() const;

  protected:
    /** \brief The LocalStorageHandler holds all LocalStorages for the render windows. */
    mutable mitk::LocalStorageHandler<LocalStorage> m_LSH;

    virtual vtkProp *GetVtkProp(BaseRenderer *renderer) const override;
    void UpdateVtkOverlay(mitk::BaseRenderer *renderer) override;

    vtkImageData *CreateMbiLogo();

    /** \brief explicit constructor which disallows implicit conversions */
    explicit LogoOverlay();

    /** \brief virtual destructor in order to derive from this class */
    virtual ~LogoOverlay();

  private:
    vtkSmartPointer<vtkImageImport> m_VtkImageImport;

    /** \brief copy constructor */
    LogoOverlay(const LogoOverlay &);

    /** \brief assignment operator */
    LogoOverlay &operator=(const LogoOverlay &);
  };

} // namespace mitk
#endif // LOGOOVERLAY_H
