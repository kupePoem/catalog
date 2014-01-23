#include "DataBaseMng.h"
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
 #include <QRegExp>
#include <QStringList>
#include "SqlCoreDataBase.h"
CDataBaseMng::CDataBaseMng(void)
{

}


CDataBaseMng::~CDataBaseMng(void)
{

	QMapIterator<QString,ICoreDataBase*> i(m_mapDataBase);
	while (i.hasNext()) {
		i.next();
		delete i.value();
	}

	m_mapDataBase.clear();
}

  bool CDataBaseMng::openDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName,const std::string &strDbName,int dbtype)
{

	bool bsuc=false;
	if(dbtype==en_MySqlType)
	{
		ICoreDataBase *p=new CSqlCoreDataBase();

		p->openServer(strUserName,passwd,strHostName);
		p->openDataBase(strDbName);

	
		if(p!=NULL)
			{
				bsuc=true;
				if(m_mapDataBase.value(strDbName.c_str())==NULL)
				m_mapDataBase.insert(strDbName.c_str(),p);
		}
	}

	return bsuc;
}
 bool CDataBaseMng::newDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName,const std::string &strdbName,int dbtype,bool bdel)
 {

	 if(dbtype==en_MySqlType)
	 {
             ICoreDataBase *p=CSqlCoreDataBase::createCoreDataBase(strUserName.c_str(),passwd.c_str(),strHostName.c_str(),strdbName.c_str(),"",bdel);

			 if(p!=NULL)
				 m_mapDataBase.insert(strdbName.c_str(),p);
	 }



	 return true;
 }

 bool  CDataBaseMng::delDataBase(const std::string &strName)
 {

	 return false;
 }

 ICoreDataBase * CDataBaseMng::getCoreDatabase(const std::string & strName)
 {

	m_mapDataBase.find(strName.c_str());
	 return  m_mapDataBase.value(strName.c_str());;
 }


  QList<QString>  CDataBaseMng::getDbNames()
  {

	  
	  return m_mapDataBase.keys();
  }