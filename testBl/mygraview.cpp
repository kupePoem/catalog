#include "mygraview.h"
#include <QMouseEvent>
#include "rasterItem.h"
#include "irasterdata.h"
#include <qwt_plot.h>
#include "mygrascene.h"
CMyGraView::CMyGraView(QWidget * parent)
	: QGraphicsView(parent)
{
	
}

CMyGraView::~CMyGraView()
{

}


void CMyGraView::zoomIn()
{
	scale(1.5,1.5);
}
void CMyGraView::zoomOut()
{
	scale(1/1.5,1/1.5);
}
void CMyGraView::rotateLeft()
{
	rotate(-90);
}
void CMyGraView::rotateRight()
{
	rotate(90);
}


	void CMyGraView::initView()
	{
		
	}

 void	CMyGraView::mouseMoveEvent ( QMouseEvent * event )
 {

	 QGraphicsView::mouseMoveEvent(event);
 }
 void	CMyGraView::mousePressEvent ( QMouseEvent * event )
 {

	 int i=0;

	 QPointF pt=event->posF();

	 QList<QGraphicsItem*> itemList=this->items(pt.rx(),pt.ry());

	 QPointF scenePt=this->mapToScene(pt.rx(),pt.ry());

	 int ncount=itemList.size();
	 QPointF itemPt;
	 QList<double> lstData;
	 for(int i=0;i<ncount;i++)
	 {
	   CCoreRasterDataItem *item= qgraphicsitem_cast<CCoreRasterDataItem*>(itemList[i]);

	   if(item!=NULL)
	   {
		   ((CMyGraScene*)scene())->setMyRectPos(scenePt);

		   ICoreRasterData *pCoreRasterData=item->getCoreRasterData();

		    itemPt=item->mapFromScene(scenePt.rx(),scenePt.ry());

			pCoreRasterData->readPixel(itemPt.rx()+0.5,itemPt.ry()+0.5,lstData);

			emit spectralValueChanged(lstData);

			
			
	   }
	 }

	 QGraphicsView::mousePressEvent(event);
 }
 void	CMyGraView::mouseReleaseEvent ( QMouseEvent * event )
 {
	 QGraphicsView::mouseReleaseEvent(event);
 }
