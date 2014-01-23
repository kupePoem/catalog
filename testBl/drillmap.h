#ifndef DRILLMAP_H
#define DRILLMAP_H
#include <QObject>
#include <QGraphicsItem>
class CDrillRasterDataItem;
class IDrillRasterData;
class CDrillMap : public QObject,QGraphicsItem
{
Q_OBJECT

public:
	CDrillMap();
	~CDrillMap();

	enum { Type = UserType + 100 };

	int type() const
	{
		// Enable the use of qgraphicsitem_cast with this item.
		return Type;
	}

	void addDrillItem(CDrillRasterDataItem *pItem);
	void addDrill(IDrillRasterData *pDrillData);
	//  ÖØÔØº¯Êý
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);


private:

	  QMap<int,CDrillRasterDataItem*> m_mapDrillItem;

		QRectF  m_boundingBox;   // ÏñËØ×ø±ê		
	
};

#endif // DRILLMAP_H
