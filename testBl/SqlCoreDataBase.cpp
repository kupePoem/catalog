#include "SqlCoreDataBase.h"
#include <QSqlQuery>

#include <QTextStream>
#include<QStringList>
#include <QFile>
#include <QCoreApplication>
#include <QSqlRecord>

CSqlCoreDataBase::CSqlCoreDataBase()
{
	//m_db=QSqlDatabase::addDatabase("QMYSQL");

	
	//m_stSkData

}


CSqlCoreDataBase::~CSqlCoreDataBase(void)
{
	closeServer(); 

}


 void CSqlCoreDataBase::closeServer()
 {
	 m_db.close();

	 
	
 }

  bool CSqlCoreDataBase::openDataBase(const std::string & strDbName)
 {
	m_db.setDatabaseName(strDbName.c_str());


	bool b=m_db.open();

	if(b)
		m_bdbopen=true;
	bool b2=m_db.isOpen();
	 return  b;
 }



bool CSqlCoreDataBase::openServer(const std::string & strUserName,const std::string & passwd,const std::string &strHostName)
{

	m_db=QSqlDatabase::addDatabase("QMYSQL");

	m_strUserName=strUserName;
	m_strPasswd=passwd;

	m_strHostName=strHostName;

	m_db.setHostName(strHostName.c_str());


	m_db.setUserName(strUserName.c_str());      //登录名

	m_db.setPassword(passwd.c_str());    //密码


	bool b= m_db.open();
	m_bdbopen=b;

	return b;

}

// bool CSqlCoreDataBase::openDataBase(const std::string & strDbName,bool bcreate)
//{
//
//   m_db.close();
//
//	m_db.setDatabaseName(strDbName.c_str());
//	 
//	bool b=m_db.open();
//
//	bool b2=m_db.isOpen();
//	bool bsuc=false;
//	return b;
//	
//}

 int CSqlCoreDataBase::addRegion(const stRegion &r)
 {
	 
	 if(!m_bdbopen)
		 return -1;

	 	QSqlQuery query(m_db);  //新建一个查询


		//insert
	QString strCreate=QString("INSERT INTO regions(region_id, region_name, region_des) ")+QString("VALUES(%1,'%2', '%3')").arg(r.regionId).arg(r.regionName).arg(r.regionDes);


	bool bsuc=query.exec(strCreate);  //使用SQL语句新建一个数据库 


	 return bsuc;
 }

 int CSqlCoreDataBase::addDrill(const stDrill & d)
 {
	 if(!m_bdbopen)
		 return -1;

	 QSqlQuery query(m_db);  //新建一个查询


	 //insert
	 QString strCreate=QString("INSERT INTO drills(drill_id, drill_name, drill_des,drill_latitude,drill_longtitude,region_id  ) ")+QString("VALUES('%1','%2', '%3','%4','%5')").arg(d.drillId).arg(d.drillName).arg(d.drillDes).arg(d.dlattitude).arg(d.dlongtitude).arg(d.regionId);


	 bool bsuc=query.exec(strCreate);  //使用SQL语句新建一个数据库 


	 return bsuc;
 }

 int CSqlCoreDataBase::addCore(const stCore & c)
 {
	 if(!m_bdbopen)
		 return -1;

	 QSqlQuery query(m_db);  //新建一个查询


	 //insert
	 QString strCreate=QString("INSERT INTO cores(core_id, core_name,core_depth,core_length,core_des ,drill_id  ) ")+QString("VALUES('%1','%2', '%3','%4','%5')").arg(c.coreId).arg(c.coreName).arg(c.coreDepth).arg(c.coreLength).arg(c.coreDes).arg(c.drillId);


	 bool bsuc=query.exec(strCreate);  //使用SQL语句新建一个数据库 


	 return bsuc;
 }

 ICoreDataBase * CSqlCoreDataBase::createCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,const QString &strRasterFilePath,bool bdel)
{
	QString strAppPath=QCoreApplication::applicationDirPath ();//获取当前应用程序路径


	return createCoreDataBase(strUserName,passwd,strHostName,strDbName,strAppPath+QString("/MYSQLTemplate/create.sql"),strAppPath+QString("/MYSQLTemplate/populate.sql"),"",bdel);

	
}

ICoreDataBase * CSqlCoreDataBase::createCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,const QString & strTableDefSqlPath,const QString & strTableConSqlPath,const QString &strRasterFilePath,bool bdel)

{


	//连接数据库
	QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

	db.setHostName(strHostName);


	db.setUserName(strUserName);      //登录名

	db.setPassword(passwd);    //密码

	if(!db.open())
		return false;


	bool bsuc=false;


	QSqlQuery query;  //新建一个查询

	if(bdel)
	{
		//删除已有数据库

	QString strDel=QString("drop database ")+strDbName;

	query.exec(strDel);
	}



	//创建数据库
	QString strCreate=QString("create database ")+strDbName;

	bsuc=query.exec(strCreate);  //使用SQL语句新建一个数据库 

	if(!bsuc)
		return NULL;

	db.setDatabaseName(strDbName);

	bsuc=db.open();


	if(!bsuc)
		return false;

	//创建表
	if(strTableConSqlPath.isEmpty())
		return NULL;

	db.transaction();

		QFile file(strTableDefSqlPath);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{

			return NULL;
		}

		QTextStream in(&file);
		QString strLine;
		while (!in.atEnd()) {
			QString strTemp=in.readLine();
			if(!strTemp.contains("#"))
				strLine = strLine+strTemp;
		}

		QStringList strList= strLine.split(";");

		foreach (const QString &str,strList)
		{
			bsuc=query.exec(str); 

		}

	if(bsuc)
		db.commit();
	else
	db.rollback();


	////增加表数据
	//QFile file2(strTableConSqlPath);
	//if(!strTableConSqlPath.isEmpty() && file2.open(QIODevice::ReadOnly | QIODevice::Text))
	//	
	//{
	//	
	//	
	//	db.transaction();

	//	QTextStream in(&file2);
	//	QString strLine;
	//	while (!in.atEnd()) {
	//		QString strTemp=in.readLine();
	//		if(!strTemp.contains("#"))
	//			strLine = strLine+strTemp;
	//	}

	//	QStringList strList= strLine.split(";");

	//	foreach (const QString &str,strList)
	//	{

	//		if(!str.isEmpty())
	//		bsuc=query.exec(str); 

	//	}

	//	if(bsuc)
	//		db.commit();
	//	else
	//		db.rollback();
	//	
	//}
 // 

	//db.close();

	//db.close();

	ICoreDataBase * pCoreDataBase=new CSqlCoreDataBase();

	//pCoreDataBase->openServer(strUserName.toStdString(),passwd.toStdString(),strHostName.toStdString());

	//pCoreDataBase->openDataBase(strDbName.toStdString());

	//pCoreDataBase->openDataBase(strDbName.toStdString(),false);

	((CSqlCoreDataBase*)pCoreDataBase)->setDb(db);

	return pCoreDataBase;



}

	 std::string CSqlCoreDataBase::getDbName()
	{

		return m_strDbName;
	}

	void CSqlCoreDataBase::setDb(QSqlDatabase & db )
	{
		m_db=db;

		m_strDbName=m_db.databaseName().toStdString();
		m_strHostName=m_db.hostName().toStdString();

		m_strPasswd=m_db.password().toStdString();

		m_strUserName=m_db.userName().toStdString();

	}
bool  CSqlCoreDataBase::executeSql(QSqlDatabase *pdb,const std::string & strSqlPath)
{

	bool b=pdb->isOpen();
	if(!b)
		return false;
	pdb->transaction();

	QFile file(strSqlPath.c_str());
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		return false;
	}

	QTextStream in(&file);
	QString strLine;
	while (!in.atEnd()) {
		QString strTemp=in.readLine();
		if(!strTemp.contains("#"))
			strLine = strLine+strTemp;
	}

	QStringList strList= strLine.split(";");

	bool bsuc;
	QSqlQuery query;  //新建一个查询

	foreach (const QString &str,strList)
	{
		if(!str.isEmpty())
		bsuc=query.exec(str); 

	}

	if(bsuc)
		pdb->commit();
	else
		pdb->rollback();
}
 bool CSqlCoreDataBase::insertData(const std::string &strSqlPath)
{
	if(!m_bdbopen)
		return false;
	executeSql(&m_db,strSqlPath);

}
	bool CSqlCoreDataBase::delCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,bool bdel)
	{
		//连接数据库
		QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

		db.setHostName(strHostName);


		db.setUserName(strUserName);      //登录名

		db.setPassword(passwd);    //密码

		if(!db.open())
			return false;


		bool bsuc=false;


		QSqlQuery query;  //新建一个查询

	    //删除已有数据库

		QString strDel=QString("drop database ")+strDbName;

		query.exec(strDel);
		
	}
	QString CSqlCoreDataBase::getRegionTableName()
	{
		return "regions";
	}
	QString CSqlCoreDataBase::getDrillTableName()
	{
		return "drills";
	}
	QString CSqlCoreDataBase::getCoreTableName()
	{
		return "cores";
	}

	 QList<stRegion> CSqlCoreDataBase::getRegions()
	{

		QList<stRegion> lr;
		if(!m_bdbopen)
			return lr;
		
		bool b2=m_db.isOpen();

		QSqlQuery query(m_db);  //新建一个查询
		QString str="SELECT * FROM "+getRegionTableName();
		bool b=query.exec(str);

		int region_id_No = query.record().indexOf("region_id");
		int region_name_NO=query.record().indexOf("region_name");
		int region_des_NO=query.record().indexOf("region_des");
	
		while (query.next()) {
			    stRegion r1;

				r1.regionId = query.value(region_id_No).toInt();


				copyStdStringToChar(r1.regionName,query.value(region_name_NO).toString().toStdString(),g_NameStrLength);
		
				copyStdStringToChar(r1.regionDes,query.value(region_des_NO).toString().toStdString(),g_DesStrLength);
		       
				lr.push_back(r1);
		}
	
		return lr;

	}
	 QList<stDrill> CSqlCoreDataBase::getDrills(int regionId)
	{
		QList<stDrill> lr;
		if(!m_bdbopen)
			return lr;


		QSqlQuery query;  //新建一个查询


		QString str="select * from "+getDrillTableName()+" where region_id="+QVariant(regionId).toString();
		query.exec(str);


		int drill_id_NO = query.record().indexOf("drill_id");
		int drill_name_NO   =query.record().indexOf("drill_name");
		int drill_des_NO=query.record().indexOf("drill_des");

		int drill_latitude_NO=query.record().indexOf("drill_latitude");

		int drill_longtitude_NO=query.record().indexOf("drill_longtitude");
		while (query.next()) {
			stDrill r1;

			r1.drillId = query.value(drill_id_NO).toInt();

			copyStdStringToChar(r1.drillName,query.value(drill_name_NO).toString().toStdString(),g_NameStrLength);

			copyStdStringToChar(r1.drillDes,query.value(drill_des_NO).toString().toStdString(),g_DesStrLength);

			r1.dlattitude=query.value(drill_latitude_NO).toDouble();
            r1.dlongtitude=query.value(drill_longtitude_NO).toDouble();

			r1.regionId=regionId;
			lr.push_back(r1);
		}

		return lr;
	}
	 QList<stCore> CSqlCoreDataBase::getCores(int drillId)
	 {
		 QList<stCore> lr;
		 if(!m_bdbopen)
			 return lr;


		 QSqlQuery query;  //新建一个查询

	

		 QString str="select * from "+getCoreTableName()+" where drill_id= "+QVariant(drillId).toString();
		 query.exec(str);

		 int core_id_NO = query.record().indexOf("core_id");

		 int core_name_NO   =query.record().indexOf("core_name");
		 int core_depth_NO=query.record().indexOf("core_depth");

		 int core_Length_NO=query.record().indexOf("core_Length");

		 int core_des_NO=query.record().indexOf("core_des");

		 while (query.next()) {
			 stCore r1;

			  r1.coreId= query.value(core_id_NO).toInt();

			  

			 copyStdStringToChar(r1.coreName,query.value(core_name_NO).toString().toStdString(),g_NameStrLength);

			 r1.coreDepth=query.value(core_depth_NO).toDouble();

			 r1.coreLength=query.value(core_Length_NO).toDouble();


			 copyStdStringToChar(r1.coreDes,query.value(core_des_NO).toString().toStdString(),g_DesStrLength);

			 r1.drillId=drillId;
			 lr.push_back(r1);
		 }

		 return lr;
	 }

