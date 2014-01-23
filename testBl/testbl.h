#ifndef TESTBL_H
#define TESTBL_H

#include <QtGui/QMainWindow>
#include "ui_testbl.h"
class CDataBaseMng;
class QSplitter;
class CCoreTreeWidget;
class CMyGraView;
class CMyGraScene;
class QToolBar;
class CMyCurveWidget;
class QGraphicsRectItem;
class testBl : public QMainWindow
{
	Q_OBJECT

public:
	testBl(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testBl();


protected:
virtual void	resizeEvent ( QResizeEvent * event );

private:

	void initMenuSlot();


	void initSplitter();
	//初始化数据和属性停靠窗口
	void initDockWidget();

	//初始化拆分窗口
	void initSplitter2();
	QSplitter * createCurveSplitter();


	void initDb();

	void initToolBar();

	private slots:

		void newDataBase();
		void addNewRegion();
	
private slots:
void changeSpectralValue( const QList<double> &);
private:
	Ui::testBlClass ui;


private:

	CMyCurveWidget * m_pCurveWidget;

	CMyGraScene *m_scene;
	CMyGraView *m_view;
	QToolBar * m_pToolBar;

	QSplitter *m_pSplitter;
	CCoreTreeWidget * m_pCoreTreewidget;
	CDataBaseMng *m_pDatabaseMng;

private:
	QGraphicsRectItem * m_pRectItem;
};

#endif // TESTBL_H
