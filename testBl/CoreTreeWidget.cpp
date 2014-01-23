#include "CoreTreeWidget.h"
#include <IDataMng.h>
#include <QTreeWidgetItem>

CCoreTreeWidget::CCoreTreeWidget(void)
{
	setHeaderHidden(true);
	this->setColumnCount(1);
}


CCoreTreeWidget::~CCoreTreeWidget(void)
{
}



void CCoreTreeWidget::initCoreTreeWidget(IDataMng *pDbMng)
{

	m_pbMng=pDbMng;

	resetTreeWidget();
	
}

void CCoreTreeWidget::resetTreeWidget()
{

	

	clear();

	IDataMng *pDbMng=m_pbMng;

	QList<QString> strDbNameLst=pDbMng->getDbNames();

	int ncount=strDbNameLst.size();



	for(int i=0;i<ncount;++i)
	{


	/*	QList<QTreeWidgetItem *> items;
		for (int i = 0; i < 10; ++i)
			items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
		this->insertTopLevelItems(0, items);
*/

		QTreeWidgetItem *pWidgetItem=new QTreeWidgetItem();
		ICoreDataBase *pCoreDataBase=pDbMng->getCoreDatabase(strDbNameLst[i].toStdString());

		pWidgetItem->setText(0,strDbNameLst[i]);

		this->insertTopLevelItem(0,pWidgetItem);

		QList<stRegion> regionLst=pCoreDataBase->getRegions();


		int nRegionSize=regionLst.size();

		for(int i=0;i<nRegionSize;i++)
		{
			//ÉèÖÃregion
				QTreeWidgetItem *pWidgetRegionItem=new QTreeWidgetItem(pWidgetItem);
				pWidgetRegionItem->setText(0,regionLst[i].regionName);

           //ÉèÖÃ×ê¿×

				QList <stDrill> drillLst=pCoreDataBase->getDrills(regionLst[i].regionId);

				int nDrillSize=drillLst.size();

				for(int i=0;i<nDrillSize;i++)
				{
					QTreeWidgetItem *pWidgetDrillItem=new QTreeWidgetItem(pWidgetRegionItem);
					pWidgetDrillItem->setText(0,drillLst[i].drillName);

					QList<stCore> coreLst=pCoreDataBase->getCores(drillLst[i].drillId);

					int nCoreSize=coreLst.size();

					for(int i=0;i<nCoreSize;++i)
					{
						QTreeWidgetItem *pWidgetCoreItem=new QTreeWidgetItem(pWidgetDrillItem);
						pWidgetCoreItem->setText(0,coreLst[i].coreName);
					}

				}
		}


	}
}
