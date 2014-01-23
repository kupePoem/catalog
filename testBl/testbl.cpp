#include "testbl.h"
#include <QSplitter>
#include <QResizeEvent>
#include <QListView>
#include <QTreeView>
#include <QTextEdit>
#include <QTreeWidget>
#include <QToolBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QGroupBox>
#include <QDockWidget>
#include "DataBaseMng.h"
#include "CoreTreeWidget.h"
#include "caddregiondlg.h"
#include "mygrascene.h"
#include "mygraview.h"
#include "mygdalRasterData.h"
#include "rasterItem.h"
#include "drillmap.h"
#include "mycurvewidget.h"
testBl::testBl(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	initDockWidget();
	initSplitter2();

	initMenuSlot();


	m_pToolBar=this->addToolBar("MyToolBar");

	initToolBar();

	initDb();

	

	connect(m_view,SIGNAL(spectralValueChanged( const QList<double> & )),this,SLOT(changeSpectralValue( const QList<double> &)));


}

void testBl::initMenuSlot()
{
	  connect(ui.actionNew_DataBase, SIGNAL(triggered()), this, SLOT(newDataBase()));

	  connect(ui.actionAdd_Region,SIGNAL(triggered()),this,SLOT(addNewRegion()));
		
}

void testBl::initDockWidget()
{
	   QDockWidget * dockWidget=new QDockWidget(tr("databases"));


		CCoreTreeWidget *pCoreTreeWidget=new CCoreTreeWidget();

		m_pCoreTreewidget=pCoreTreeWidget;

	/*	m_pCoreTreewidget->setColumnCount(1);
		QList<QTreeWidgetItem *> items;
		for (int i = 0; i < 10; ++i)
			items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
		m_pCoreTreewidget->insertTopLevelItems(0, items);
*/

	dockWidget->setWidget(pCoreTreeWidget);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	addDockWidget(Qt::LeftDockWidgetArea,dockWidget);


	QDockWidget * dockWidget2=new QDockWidget(tr("properties"));
	dockWidget2->setWidget(new QTreeWidget());

	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	addDockWidget(Qt::LeftDockWidgetArea,dockWidget2);

	tabifyDockWidget(dockWidget2,dockWidget);

}


void testBl::initDb()
{
	m_pDatabaseMng=new CDataBaseMng();
	bool bsuc=m_pDatabaseMng->openDataBase("root","123456","localhost","myDb4",en_MySqlType);


	m_pCoreTreewidget->initCoreTreeWidget(m_pDatabaseMng);
}

void testBl::initSplitter2()
{
	m_pSplitter=new QSplitter(Qt::Horizontal);

	
	m_view=new CMyGraView(NULL);
    
	m_scene=new CMyGraScene(NULL);
	m_view->setScene(m_scene);

	m_view->scale(1/1.5,1/1.5);

	//ICoreRasterData *p=CMygdalCoreRasterData::createDataSet("E:\\myInfo\\shiyanshi\\biyelunwen\\201312312040-1",10001);

	//CCoreRasterDataItem *pitem=new CCoreRasterDataItem(p);


	//m_scene->addItem((CCoreRasterDataItem *)pitem);


	ICoreRasterData *p1=CMygdalCoreRasterData::createDataSet("E:\\myInfo\\shiyanshi\\biyelunwen\\201312312040-1",10001);
	ICoreRasterData *p2=CMygdalCoreRasterData::createDataSet("E:\\myInfo\\shiyanshi\\biyelunwen\\201312312040-2",10002);


	IDrillRasterData*pDrillRasterData=CMygdalDrillRasterData::createDataSet(20001);

	pDrillRasterData->addCoreRasterData(p1);
	pDrillRasterData->addCoreRasterData(p2);

	CDrillMap *pDrillMap=new CDrillMap();

	pDrillMap->addDrill(pDrillRasterData);


	m_scene->addMap(pDrillMap);

	m_scene->addMyRect();


	m_pSplitter->addWidget(m_view);




	m_pSplitter->addWidget(createCurveSplitter());

	m_pSplitter->setStyleSheet("QSplitter::handle { background-color: blue }"); //设置分界线的样式
	m_pSplitter->setHandleWidth(1);      //设置分界线的宽度

   this->setCentralWidget(m_pSplitter);

}

void testBl::initToolBar()
{

	QString strAppPath=QCoreApplication::applicationDirPath ();//获取当前应用程序路径
	QString strIconPath=strAppPath+QString("/Icon");
	QIcon iconZoomIn;

	iconZoomIn.addFile(strIconPath+"/Zoomin");

	QAction *pActZoomIn=m_pToolBar->addAction(iconZoomIn,tr("Zoom in..."));

	connect(pActZoomIn,SIGNAL(triggered()),m_view,SLOT(zoomIn()));

	QIcon iconZoomOut;

	iconZoomOut.addFile(strIconPath+"/Zoomout");

	QAction *pActZoomOut=m_pToolBar->addAction(iconZoomOut,tr("Zoom out..."));

	connect(pActZoomOut,SIGNAL(triggered()),m_view,SLOT(zoomOut()));



	QIcon iconRoateLeft;

	iconRoateLeft.addFile(strIconPath+"/ZoomPrev");

	QAction *pActRoateLeft=m_pToolBar->addAction(iconRoateLeft,tr("Rotate Left..."));

	connect(pActRoateLeft,SIGNAL(triggered()),m_view,SLOT(rotateLeft()));


	QIcon iconRoateRight;

	iconRoateRight.addFile(strIconPath+"/ZoomNext");

	QAction *pActRoateRight=m_pToolBar->addAction(iconRoateRight,tr("Rotate Right..."));

	connect(pActRoateRight,SIGNAL(triggered()),m_view,SLOT(rotateRight()));
}
QSplitter * testBl::createCurveSplitter()
{


	QSplitter * pSplitter3=new QSplitter(Qt::Vertical,m_pSplitter);
	QSplitter * pSplitter1=new QSplitter(Qt::Horizontal,pSplitter3);
	QSplitter * pSplitter2=new QSplitter(Qt::Horizontal,pSplitter3);


	m_pCurveWidget=new CMyCurveWidget(pSplitter1);
	pSplitter1->addWidget(m_pCurveWidget);



	pSplitter1->addWidget(new QWidget(pSplitter1));

	pSplitter2->addWidget(new QWidget(pSplitter2));
	pSplitter2->addWidget(new QWidget(pSplitter2));

	pSplitter3->addWidget(pSplitter1);

	pSplitter3->addWidget(pSplitter2);

	pSplitter1->setStyleSheet("QSplitter::handle { background-color: blue }"); //设置分界线的样式
	pSplitter1->setHandleWidth(1);  

	pSplitter2->setStyleSheet("QSplitter::handle { background-color: blue }"); //设置分界线的样式
	pSplitter2->setHandleWidth(1);  

	pSplitter3->setStyleSheet("QSplitter::handle { background-color: blue }"); //设置分界线的样式
	pSplitter3->setHandleWidth(1); 

	return pSplitter3;
}

void testBl::initSplitter()
{
	m_pSplitter=new QSplitter(Qt::Horizontal,this->centralWidget());

	//addToolBar(new QToolBar());


	QGridLayout *layout = new QGridLayout();



	//QListView *listview = new QListView;
	//QTreeView *treeview = new QTreeView;
	//QTextEdit *textedit = new QTextEdit;
	//m_pSplitter->addWidget(listview);
	//m_pSplitter->addWidget(treeview);
	//m_pSplitter->addWidget(textedit);



	QSplitter *pSplitter=new QSplitter(Qt::Vertical);


	pSplitter->addWidget(new QTreeWidget());

	pSplitter->addWidget(new QGroupBox());

	pSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式

	pSplitter->setHandleWidth(1);      //设置分界线的宽度

	//

	layout->addWidget(pSplitter);



	layout->addWidget(new QGroupBox("ss"));

	layout->setRowMinimumHeight(1,100);





	QFrame *pd=new QFrame();
	pd->setLayout(layout);
	m_pSplitter->addWidget(pd);



	m_pSplitter->addWidget(new QWidget());
	m_pSplitter->addWidget(new QWidget());



	m_pSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式

	m_pSplitter->setHandleWidth(1);      //设置分界线的宽度
}
 void testBl::resizeEvent ( QResizeEvent * event )
 {
	// m_pSplitter->resize(event->size());
	 
 }
testBl::~testBl()
{

}


void testBl::addNewRegion()
{


	


	CAddRegionDlg dlg;
	dlg.initPara(m_pDatabaseMng);

	if(QDialog::Accepted==dlg.exec())
	{
		stAddRegionPara rp=dlg.getStAddRegionPara();

		m_pDatabaseMng->getCoreDatabase(rp.strDbName.toStdString())->addRegion(rp.r);
	}

	m_pCoreTreewidget->resetTreeWidget();



	//int n=5;
	//stRegion r;
	//r.regionId=10002;
	//copyStdStringToChar(r.regionName,"xiZhangQuLong",64);

	//copyStdStringToChar(r.regionDes,"xiZhangQuLong Mineral District",256);


	//m_pDatabaseMng->getCoreDatabase("myDb4")->addRegion(r);

	//m_pCoreTreewidget->initCoreTreeWidget(m_pDatabaseMng);
}



void testBl::newDataBase()
{

//bool b=	m_pDatabaseMng->openServer("root","123456","localhost");

//m_pDatabaseMng->newDataBase("testsqldatabase");

	m_pDatabaseMng->newDataBase("root","123456","localhost","myDb4",en_MySqlType,true);
	
	m_pDatabaseMng->getCoreDatabase("myDb4")->insertData("E:\\dev\\testBl\\Win32\\Debug\\MYSQLTemplate\\populate.sql");

	m_pCoreTreewidget->initCoreTreeWidget(m_pDatabaseMng);


	
}


void testBl::changeSpectralValue(const QList<double> &dataLst)
{
	int nsize=dataLst.size();
	QVector<double> vecX;
	for(int i=0;i<nsize;i++)
	{
		vecX.push_back(i+1);
		
	}

	
	m_pCurveWidget->addCurve(vecX,dataLst.toVector(),"myFirstCurve");
}
