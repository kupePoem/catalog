#ifndef SQLCOREDATABASE_H
#define SQLCOREDATABASE_H
#include "idatamng.h"
#include <QMap>
#include <QSqlDatabase>
class QSqlDatabase;


struct St_CoreSkData
{

QMap<int,QString> m_mapDbTypeToDbString;
St_CoreSkData()
{
	m_mapDbTypeToDbString.insert(en_MySqlType,QString("QMYSQL"));
}

};
class CSqlCoreDataBase :
	public ICoreDataBase
{
public:
	CSqlCoreDataBase(int dbtype);
	CSqlCoreDataBase();
	~CSqlCoreDataBase(void);
	virtual bool openServer(const std::string & strUserName,const std::string & passwd,const std::string &strHostName);
	virtual bool openDataBase(const std::string & strDbName);

	

	virtual void closeServer();



//	virtual bool openDataBase(const std::string & strDbName);
	
	virtual int addRegion(const stRegion &);

	virtual int addDrill(const stDrill &);

	virtual int addCore(const stCore &);
	virtual bool  insertData(const std::string &strSqlPath);



	virtual QList<stRegion> getRegions();
	virtual QList<stDrill> getDrills(int regionId);
	virtual QList<stCore> getCores(int drillId);

	virtual std::string getDbName();
	


private:

	void setDb(QSqlDatabase & db );

	
	QString getRegionTableName();
	QString getDrillTableName();
	QString getCoreTableName();


	bool executeSql(QSqlDatabase *pdb,const std::string & strSqlPath);
private:
	QSqlDatabase m_db;
	bool m_bdbopen;
	std::string m_strUserName;
	std::string m_strPasswd;
	std::string m_strHostName;
	std::string m_strDbName;


public:


	//static QMap<int,QString> m_mapDbTypeToDbString;
	static ICoreDataBase * createCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,const QString &strRasterFilePath,bool bdel=false);

	bool delCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,bool bdel=false);
	

private:
	static ICoreDataBase * createCoreDataBase(const QString & strUserName,const QString & passwd,const QString &strHostName,const QString &strDbName,const QString & strTableDefSqlPath,const QString & strTableConSqlPath,const QString &strRasterFilePath,bool bdel=false);


	
};

#endif
