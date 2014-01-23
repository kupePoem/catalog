#ifndef IDATA_MNG_H
#define IDATA_MNG_H
#include <iostream>
#include <string>
#include <QSqlRelationalTableModel>
class ICoreDataBase;
#include <QAbstractItemModel>
#include <QString>
#include <QList>
#include "dsCommon.h"
enum en_DataBaseType
{
	en_MySqlType,en_OracleType

};

const int g_NameStrLength=64;
const int g_DesStrLength=256;
const int g_FilePathLength=256;
struct stRegion
{
    int regionId;
	char regionName[g_NameStrLength];
	char regionDes[g_DesStrLength];
};

struct stDrill
{
	int drillId;
	char drillName[g_NameStrLength];
	double dlongtitude;
	double dlattitude;
	char drillDes[g_DesStrLength];

	int regionId;

};

struct stCore
{
	int coreId;
	char coreName[g_NameStrLength];
	double coreDepth;
	double coreLength;
	
	char coreDes[g_DesStrLength];

	char coreDataPath[g_FilePathLength];
	
	int drillId;

	
};
class IDataMng
{
public:
	
	virtual bool newDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName ,const std::string &strDbName,int dbType,bool bDel=false)=0;

	virtual bool  delDataBase(const std::string &strName)=0;

	virtual ICoreDataBase * getCoreDatabase(const std::string & strName)=0;

	virtual QList<QString> getDbNames()=0;

	virtual  bool openDataBase(const std::string & strUserName,const std::string & passwd,const std::string &strHostName,const std::string &strName,int dbtype)=0;

	//连接服务器
	//virtual bool conServer(const std::string & strUserName,const std::string & passwd,const std::string &strHostName);


};

class IDbCon
{
public:
	//连接服务器
	virtual bool openServer(const std::string & strUserName,const std::string & passwd,const std::string &strHostName);
	virtual bool closeServer();

	virtual bool createTable();


};



class ICoreDataBase
{
	public:
	virtual bool openServer(const std::string & strUserName,const std::string & passwd,const std::string &strHostName)=0;
	
	virtual void closeServer()=0;

	virtual bool openDataBase(const std::string & strDbName)=0;

	virtual int addRegion(const stRegion &)=0;

	virtual int addDrill(const stDrill &)=0;

	virtual int addCore(const stCore &)=0;

	virtual QList<stRegion> getRegions()=0;
	virtual QList<stDrill> getDrills(int regionId)=0;
	virtual QList<stCore> getCores(int drillId)=0;

	virtual bool insertData(const std::string &strSqlPath)=0;

	/*virtual QAbstractItemModel * getRegionTableModel()=0;

	virtual QAbstractItemModel * getDrillTableModel()=0;

	virtual QAbstractItemModel * getCoreTableModel()=0;*/
	
	virtual std::string getDbName()=0;
private:


};

#endif

