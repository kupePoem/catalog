#include "drillmap.h"
#include "rasterItem.h"
#include "irasterdata.h"
CDrillMap::CDrillMap()
{
	m_boundingBox.setRect(0,0,0,0);
}

CDrillMap::~CDrillMap()
{
  QList<int> keyList=m_mapDrillItem.keys();

  int nsize=keyList.size();

  for(int i=0;i<nsize;++i)
	  delete m_mapDrillItem.value(keyList[i]);

  m_mapDrillItem.clear();
}

void CDrillMap::addDrillItem(CDrillRasterDataItem *pItem)
{
	
}

void CDrillMap::addDrill(IDrillRasterData *pDrillData)
{
	int nw=pDrillData->getW();
	int nh=pDrillData->getH();

	if(m_boundingBox.height()<nh)
		m_boundingBox.setHeight(nh);

	QRect rect;

	
	if(m_boundingBox.width()==0)
    {
		//ֻ��һ��drill
	   m_boundingBox.setWidth(nw);
	   rect.setRect(m_boundingBox.topLeft().rx(),m_boundingBox.topLeft().ry(),nw,nh);
	}
	else
	{
		//����������drill ����drill֮������1��nw�Ŀ���
		m_boundingBox.setWidth(m_boundingBox.width()+2*nw);
		rect.setRect(m_boundingBox.topLeft().rx()+nw,m_boundingBox.topLeft().ry(),nw,nh);
	}


	
	



	CDrillRasterDataItem *pItem=new CDrillRasterDataItem(pDrillData,rect,this);

	m_mapDrillItem.insert(pDrillData->getDrillId(),pItem);

}
QRectF CDrillMap::boundingRect() const{
	return m_boundingBox;
}

QPainterPath CDrillMap::shape() const{
	QPainterPath path;
	path.addRect( m_boundingBox );
	return path;
}

void CDrillMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
	Q_UNUSED(widget);

	// ʲô������
}
