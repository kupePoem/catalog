#ifndef CADDREGIONDLG_H
#define CADDREGIONDLG_H

#include <QDialog>
#include "ui_caddregiondlg.h"
#include <IDataMng.h>

struct stAddRegionPara 
{
	stRegion r;
	QString strDbName;
};

class CAddRegionDlg : public QDialog
{
	Q_OBJECT

public:
	CAddRegionDlg(QWidget *parent = 0);
	~CAddRegionDlg();

	void initPara(IDataMng *pDataMng);

	stAddRegionPara getStAddRegionPara();
private slots:
	void on_Btn_OK();

	void on_Btn_Cancel();
private:
	stAddRegionPara m_para;

	Ui::CAddRegionDlg ui;
};

#endif // CADDREGIONDLG_H
