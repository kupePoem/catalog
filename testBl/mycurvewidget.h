#ifndef MYCURVEWIDGET_H
#define MYCURVEWIDGET_H

#include <qwt_plot.h>
#include "ui_mycurvewidget.h"

class CMyCurveWidget : public QwtPlot
{
	Q_OBJECT

public:
	CMyCurveWidget(QWidget *parent = 0);
	~CMyCurveWidget();
	void addCurve(const QVector<double> &xData,const QVector<double> &yData,const QString &strCurveName);

private:
	Ui::CMyCurveWidget ui;
};

#endif // MYCURVEWIDGET_H
