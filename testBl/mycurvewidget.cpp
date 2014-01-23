#include "mycurvewidget.h"
#include <qwt_plot_curve.h>

CMyCurveWidget::CMyCurveWidget(QWidget *parent)
	: QwtPlot(parent)
{
	ui.setupUi(this);

	this->setAxisAutoScale(QwtPlot::xBottom,true);
	this->setAxisAutoScale(QwtPlot::yLeft,true);


}

CMyCurveWidget::~CMyCurveWidget()
{

}

void CMyCurveWidget::addCurve(const QVector<double> &xData,const QVector<double> &yData,const QString &strCurveName)
{

	QwtPlotCurve *pCurve=new QwtPlotCurve(strCurveName);


	pCurve->setSamples(xData,yData);

	pCurve->attach(this);

	pCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);

	
	replot();
}