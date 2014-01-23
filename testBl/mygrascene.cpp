#include "mygrascene.h"
#include "drillmap.h"

CMyGraScene::CMyGraScene(QObject *parent)
	: QGraphicsScene(parent)
{
	
}

CMyGraScene::~CMyGraScene()
{
	int nsize=m_drillMapList.size();

	for(int i=0;i<nsize;i++)
	{
		delete m_drillMapList[i];
	}
}

void CMyGraScene::addCoreRasterDataItem(CCoreRasterDataItem * pItem)
{
	this->addItem((QGraphicsItem*)pItem);
}


void CMyGraScene::addMap(CDrillMap *pDrillMap)
{
	m_drillMapList.push_back(pDrillMap);

	this->addItem((QGraphicsItem*)pDrillMap);
}

void CMyGraScene::addMyRect()
{
	m_pRectItem=addRect(0,0,30,30,QPen(QColor(255,0,0)));
}


void CMyGraScene::setMyRectPos(const QPointF &pt)
{
	m_pRectItem->setPos(pt+QPointF(-15,-15));
}