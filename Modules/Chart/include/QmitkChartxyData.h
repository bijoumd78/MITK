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

#ifndef QmitkC3xyData_h
#define QmitkC3xyData_h

#include <QVariant>

/** /brief This class holds the actual data for the chart generation with C3.
* data can be loaded in constructor directly or with SetData
* It is derived from QObject, because we need Q_PROPERTIES to send Data via QWebChannel to JavaScript.
*/
class QmitkChartxyData : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QList<QVariant> m_YData READ GetYData WRITE SetYData NOTIFY SignalYDataChanged);
  Q_PROPERTY(QList<QVariant> m_XData READ GetXData WRITE SetXData NOTIFY SignalXDataChanged);
  Q_PROPERTY(QVariant m_Color READ GetColor WRITE SetColor NOTIFY SignalColorChanged);
  Q_PROPERTY(QVariant m_Label READ GetLabel WRITE SetLabel NOTIFY SignalLabelChanged);
  Q_PROPERTY(QVariant m_LineStyleName READ GetLineStyle WRITE SetLineStyle NOTIFY SignalLineStyleChanged);

public:
  explicit QmitkChartxyData(const QList<QVariant>& data, const QVariant& label); //Constructor for Data1D (y=1,5,6,...)
  explicit QmitkChartxyData(const QMap<QVariant, QVariant>& data, const QVariant& label); //Constructor for Data2D (x:y=1:2, 2:6, 3:7)

  void SetData(const QMap<QVariant, QVariant>& data, const QVariant& label);

  Q_INVOKABLE QList<QVariant> GetYData() const { return m_YData; };
  Q_INVOKABLE void SetYData(const QList<QVariant>& yData) { m_YData =yData; };

  Q_INVOKABLE QList<QVariant> GetXData() const { return m_XData; };
  Q_INVOKABLE void SetXData(const QList<QVariant>& xData) { m_XData =xData; };

  Q_INVOKABLE QVariant GetLabel() const { return m_Label; };
  Q_INVOKABLE void SetLabel(const QVariant& label) { m_Label = label; };

  Q_INVOKABLE QVariant GetColor() const { return m_Color; };
  Q_INVOKABLE void SetColor(const QVariant& color) { m_Color = color; };

  Q_INVOKABLE QVariant GetLineStyle() const { return m_LineStyleName; };
  Q_INVOKABLE void SetLineStyle(const QVariant& lineStyle) { m_LineStyleName = lineStyle; };

  
  /**
  * \brief Clears the Data.
  *
  * This function clears the data.
  */
  void ClearData();

signals:
  void SignalYDataChanged(const QList<QVariant> yData);
  void SignalXDataChanged(const QList<QVariant> xData);
  void SignalColorChanged(const QVariant color);
  void SignalLabelChanged(const QVariant label);
  void SignalLineStyleChanged(const QVariant lineStyle);

private:
  QList<QVariant>  m_YData;
  QList<QVariant>  m_XData;
  QVariant         m_Label;
  QVariant         m_Color;
  QVariant         m_LineStyleName;
};

#endif  //QmitkC3xyData_h