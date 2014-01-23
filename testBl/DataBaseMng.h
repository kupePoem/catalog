#ifndef DATABASEMNG_H
#define DATABASEMNG_H
#include "IDataMng.h"
#include <QList>
class QSqlDatabase;
class CDataBaseMng :
	public IDataMng
{
public:
	CDataBaseMng(void);
	~CDataBaseMng(void);


	
	virtual bool newDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName,const std::string &strName,int dbtype,bool bdel=false);

	virtual bool  delDataBase(const std::string &strName);

	virtual  bool openDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName,const std::string &strName,int dbtype);

	virtual ICoreDataBase * getCoreDatabase(const std::string & strName);
	

	virtual QList<QString> getDbNames();



signals:
	void dbChangd();


private:
	QMap<QString,ICoreDataBase*> m_mapDataBase;
private:

};
#endif
