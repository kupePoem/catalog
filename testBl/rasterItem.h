#ifndef RASTERITEM_H
#define RASTERITEM_H
#include <QGraphicsItem>
class ICoreRasterData;
class QPainter;
class IDrillRasterData;
class CCoreRasterDataItem:public QGraphicsItem
{

public:
	enum { Type = UserType + 101 };

	int type() const
	{
		// Enable the use of qgraphicsitem_cast with this item.
		return Type;
	}

	CCoreRasterDataItem();
	~CCoreRasterDataItem();

	CCoreRasterDataItem(ICoreRasterData*pCoreRasterData, QGraphicsItem * parent = 0);

	CCoreRasterDataItem(ICoreRasterData*pCoreRasterData,const QRect& rect, QGraphicsItem * parent = 0);
	//  重载函数
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
	void setBand(int bandR,int bndG,int bandB);
	ICoreRasterData * getCoreRasterData();
private:
	void fillPixMap();
   
private:

	
	QRectF  m_boundingBox;     // 像素坐标
	QPixmap m_coreMap; // 地图纹理
	ICoreRasterData * m_pCoreRasterData;
	int m_nW;
	int m_nH;
	int m_bandIndex[3];
};

class CDrillRasterDataItem:public QGraphicsItem
{
public:
	CDrillRasterDataItem();
	CDrillRasterDataItem(IDrillRasterData*pDrillRasterData,const QRect& rect, QGraphicsItem * parent = 0);
	~CDrillRasterDataItem();
	enum { Type = UserType + 102 };

	int type() const
	{
		// Enable the use of qgraphicsitem_cast with this item.
		return Type;
	}
   
	void addItem(ICoreRasterData *pCoreRasterData);

	void addItem(IDrillRasterData *pDrillRasterData);
	//  重载函数
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
private:
	QMap<int,CCoreRasterDataItem *> m_childItem;
		QRectF  m_boundingBox;     // 像素坐标

		IDrillRasterData *m_pDrillRasterData;
};



#endif

