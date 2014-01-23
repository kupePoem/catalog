#include "caddregiondlg.h"
#include <QList>
#include <QString>
#include <dsCommon.h>
#include <QIntValidator>

CAddRegionDlg::CAddRegionDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


bool b= connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_Btn_OK()));



b=connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(on_Btn_Cancel()));


QValidator *validator = new QIntValidator(10000, 99999, this);

ui.lineEdit_regionId->setValidator(validator);
}

CAddRegionDlg::~CAddRegionDlg()
{

}

stAddRegionPara CAddRegionDlg::getStAddRegionPara()
{
	
	
	return m_para;
}


void CAddRegionDlg::initPara(IDataMng *pDataMng)
{
	QList<QString> strLst=pDataMng->getDbNames();

	int ncount=strLst.size();

	ui.comboBox_RegionDb->addItems(strLst);

	//ui.comboBox_RegionDb
	//ui.comboBox
	
}

void CAddRegionDlg::on_Btn_OK()
{
	stAddRegionPara rp;

	QString strRegion_id=ui.lineEdit_regionId->text();
	if(strRegion_id.isEmpty())
	{
		on_Btn_Cancel();
	}


	rp.r.regionId=strRegion_id.toInt();

	copyStdStringToChar(rp.r.regionName,ui.lineEdit_regionName->text().toStdString(),g_NameStrLength);

	copyStdStringToChar(rp.r.regionDes,ui.lineEdit_regionDes->text().toStdString(),g_DesStrLength);

	rp.strDbName=ui.comboBox_RegionDb->currentText();


	m_para=rp;

	QDialog::accept();
}


void CAddRegionDlg::on_Btn_Cancel()
{
	QDialog::reject();

}

