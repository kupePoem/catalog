#ifndef CORETREEWIDGET_H
#define CORETREEWIDGET_H
#include <QTreeWidget>
class IDataMng;
class CCoreTreeWidget :
	public QTreeWidget
{
public:
	CCoreTreeWidget(void);

	
	
	~CCoreTreeWidget(void);


public slots:

void initCoreTreeWidget(IDataMng *pDbMng);

void resetTreeWidget();
private:


private:
	IDataMng * m_pbMng;
};

#endif
