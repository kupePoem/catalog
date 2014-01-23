#include "RasterItem.h"
#include "irasterdata.h"
#include <QPainter>
 #include <QtGlobal>
#include <QRectF>
CCoreRasterDataItem::CCoreRasterDataItem()
{

}

CCoreRasterDataItem::~CCoreRasterDataItem()
{



}
void CCoreRasterDataItem::setBand(int bandR,int bandG,int bandB)
{
	m_bandIndex[0]=bandR;
	m_bandIndex[1]=bandG;
	m_bandIndex[2]=bandB;
}
CCoreRasterDataItem::CCoreRasterDataItem(ICoreRasterData*pCoreRasterData,QGraphicsItem * parent ):QGraphicsItem(parent)
{
	 Q_ASSERT(pCoreRasterData!=NULL);

	m_pCoreRasterData=pCoreRasterData;

	int nh=pCoreRasterData->getH();
	int nw=pCoreRasterData->getW();
	m_boundingBox.setRect( 0, 0, nw,nh);

	m_nH=nh;
	m_nW=nw;
	m_bandIndex[0]=167;
	m_bandIndex[1]=243;
	m_bandIndex[2]=340;
	fillPixMap();
}
CCoreRasterDataItem::CCoreRasterDataItem(ICoreRasterData*pCoreRasterData,const QRect& rect, QGraphicsItem * parent ):QGraphicsItem(parent)
{
	Q_ASSERT(pCoreRasterData!=NULL);

	m_pCoreRasterData=pCoreRasterData;

	int nh=pCoreRasterData->getH();
	int nw=pCoreRasterData->getW();
	m_nH=nh;
	m_nW=nw;

	m_boundingBox.setRect( 0, 0, nw,nh);

	setPos(rect.topLeft());

	m_bandIndex[0]=167;
	m_bandIndex[1]=243;
	m_bandIndex[2]=340;
	fillPixMap();
}
void CCoreRasterDataItem::fillPixMap()
{


	ICoreRasterData*pCoreRasterData=m_pCoreRasterData;
	int nh=m_nH;
	int nw=m_nW;
	int nDataType=pCoreRasterData->getDataType(m_bandIndex[0]);

  	QImage myImage(nw, nh, QImage::Format_RGB32);


	unsigned short int *pBufferR=new unsigned short int[nw*nh];
	pCoreRasterData->readData(m_bandIndex[0],0,0,nw,nh,nDataType,(void*)pBufferR);
	
	double dMinR,dMaxR,dMeanR,dstdR;
	pCoreRasterData->computeStatistics(m_bandIndex[0],&dMinR,&dMaxR,&dMeanR,&dstdR);

	unsigned short int *pBufferG=new unsigned short int[nw*nh];
	pCoreRasterData->readData(m_bandIndex[1],0,0,nw,nh,nDataType,(void*)pBufferG);
	double dMinG,dMaxG,dMeanG,dstdG;
	pCoreRasterData->computeStatistics(m_bandIndex[1],&dMinG,&dMaxG,&dMeanG,&dstdG);

	unsigned short int *pBufferB=new unsigned short int[nw*nh];
	pCoreRasterData->readData(m_bandIndex[2],0,0,nw,nh,nDataType,(void*)pBufferB);
	double dMinB,dMaxB,dMeanB,dstdB;
	pCoreRasterData->computeStatistics(m_bandIndex[2],&dMinB,&dMaxB,&dMeanB,&dstdB);

	QRgb rgb;
	for(int i=0;i<nh*nw;i++)
	{
		int nvalR=(pBufferR[i]-dMinR)/(dMaxR-dMinR)*255+0.5;
		int nvalG=(pBufferG[i]-dMinG)/(dMaxG-dMinG)*255+0.5;
		int nvalB=(pBufferB[i]-dMinB)/(dMaxB-dMinB)*255+0.5;

		myImage.setPixel(i%nw,i/nw,QColor(nvalR,nvalG,nvalB).rgb());
	}
	
	 m_coreMap=QPixmap::fromImage(myImage);
	

	 delete []pBufferR;
	 delete []pBufferB;
     delete []pBufferG;
}
QRectF CCoreRasterDataItem::boundingRect() const
{

	return m_boundingBox;

}
QPainterPath CCoreRasterDataItem::shape() const
{
	QPainterPath path;
	path.addRect( m_boundingBox );
	return path;

}
void CCoreRasterDataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
	// 绘制地图
	painter->drawPixmap( m_boundingBox.toRect(), m_coreMap );

}

ICoreRasterData * CCoreRasterDataItem::getCoreRasterData()
{
	return m_pCoreRasterData;
}

CDrillRasterDataItem::CDrillRasterDataItem()
{
	m_boundingBox.setRect(0,0,0,0);
}

CDrillRasterDataItem::CDrillRasterDataItem(IDrillRasterData*pDrillRasterData,const QRect& rect, QGraphicsItem * parent ):QGraphicsItem(parent)
{
	int nw=pDrillRasterData->getW();
	int nh=pDrillRasterData->getH();

	m_boundingBox.setRect(0,0,nw,nh);

	//目前全部生成coreRasterDateItem 以后应该根据视图动态生成coreRasterDataItem

	QList<int> keyLst=pDrillRasterData->getCoreIdLst();

	int nsize=keyLst.size();
	int nTempYPos=0;
	QRect tempRect;
	for(int i=0;i<nsize;++i)
	{
		ICoreRasterData *pCoreRasterData=pDrillRasterData->getCoreRasterData(keyLst[i]);

		int nCoreW=pCoreRasterData->getW();
		int nCoreH=pCoreRasterData->getH();

		tempRect.setRect(rect.topLeft().rx(),rect.topLeft().ry()+nTempYPos,nCoreH,nCoreW);
		
		CCoreRasterDataItem *pItem=new CCoreRasterDataItem(pCoreRasterData,tempRect,this);

		nTempYPos=nTempYPos+nCoreH;

		m_childItem.insert(keyLst[i],pItem);
	}

	m_pDrillRasterData=pDrillRasterData;

	setPos(rect.topLeft());


}

CDrillRasterDataItem::~CDrillRasterDataItem()
{
	QList<int> keyList=m_childItem.keys();

	int nsize=keyList.size();

	for(int i=0;i<nsize;++i)
		delete m_childItem.value(keyList[i]);

	m_childItem.clear();
}

void CDrillRasterDataItem::addItem(ICoreRasterData *pCoreRasterData)
{
	int nw=pCoreRasterData->getW();

	int nh=pCoreRasterData->getH();
	
	m_boundingBox.setWidth(m_boundingBox.width());

	m_boundingBox.setHeight(m_boundingBox.height()+nh);

	QRect rect;
	rect.setRect(m_boundingBox.topLeft().rx(),m_boundingBox.topLeft().ry(),nw,nh);
	CCoreRasterDataItem *pItem=new CCoreRasterDataItem(pCoreRasterData,rect,this);

	m_childItem.insert(pCoreRasterData->getCoreId(),pItem);
	//rect.setRect(m_boundingBox.topLeft())
}


QRectF CDrillRasterDataItem::boundingRect() const
{

	return m_boundingBox;

}
QPainterPath CDrillRasterDataItem::shape() const
{
	QPainterPath path;
	path.addRect( m_boundingBox );
	return path;

}
void CDrillRasterDataItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

	int n=5;
	// 绘制地图
	//painter->drawPixmap( m_boundingBox.toRect(), m_coreMap );

}

