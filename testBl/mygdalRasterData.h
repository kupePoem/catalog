#ifndef MYGDALRASTERDATA_H
#define MYGDALRASTERDATA_H
#include "irasterdata.h"
class GDALDataset;
#include <QMap>
class CMygdalCoreRasterData:public ICoreRasterData
{
public:
	CMygdalCoreRasterData(void);
	~CMygdalCoreRasterData(void);
	virtual void readData(int band,int xstart,int ystart,int xLength,int yLength,int dataType,void *data);

	virtual void readPixel(int x,int y,QList<double> &vecData);
	virtual int getW();
	virtual int getH();
	virtual int getBandCount();
	virtual int getDataType(int bandIndex);
	
	virtual int getCoreId();

	virtual void computeStatistics(int bandIndex,double *dMin,double *dMax,double *dMean,double *dStd);

private:

	template <class T>
	void readPixelPriv(int x,int y,QList<double> &vecData);

	void setDataSet(GDALDataset * pDataset);

	void setCoreId(int coreId);
private:
	GDALDataset *m_pDataSet;
	int m_coreId;

public:

	static ICoreRasterData* createDataSet(const std::string & strFileName,int coreId);

};

//template <class T>
//void readPixelPriv(int x,int y,QList<double> &vecData)
//{
//	int nBandCount=getBandCount();
//
//	if(nBandCount<=0)
//		return ;
//
//
//	T sVal;
//
//	for(int i=0;i<nBandCount;++i)
//	{
//		m_pDataSet->GetRasterBand(i+1)->RasterIO(GF_Read,x,y,1,1,(void*)&sVal,1,1,(GDALDataType)dataType,0,0);
//		vecData.push_back(sVal);
//	}
//
//}

class CMygdalDrillRasterData:public IDrillRasterData
{
public:
	CMygdalDrillRasterData(void);
	~CMygdalDrillRasterData(void);



	virtual ICoreRasterData* getCoreRasterData(int coreid );
	virtual int getDrillId();
	void addCoreRasterData(ICoreRasterData*);
	virtual int getW();
	virtual int getH();
	virtual QList<int> getCoreIdLst();
private:
	void setDrillId(int drillId);
private:
	int m_drillId;
	QMap<int,ICoreRasterData*> m_mapCoreRasterData;
	

public:
	static IDrillRasterData* createDataSet(int drillId);
};
#endif
