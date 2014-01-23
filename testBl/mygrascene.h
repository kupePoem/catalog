#ifndef MYGRASCENE_H
#define MYGRASCENE_H

#include <QGraphicsScene>
class CCoreRasterDataItem;
class CDrillMap;
class QGraphicsRectItem;
class CMyGraScene : public QGraphicsScene
{
	Q_OBJECT

public:
	CMyGraScene(QObject *parent);
	~CMyGraScene();

	void addCoreRasterDataItem(CCoreRasterDataItem * pItem);

	void addMap(CDrillMap *pDrillMap);

	void addMyRect();

	void setMyRectPos(const QPointF &);

private:
	CCoreRasterDataItem * m_pCoreRasterDataItem;

//	QMap<int,CDrillMap*> m_drillMap;
	QList<CDrillMap*> m_drillMapList;

	QGraphicsRectItem * m_pRectItem;
};

#endif // MYGRASCENE_H
