#ifndef IRASTERDATA_H
#define IRASTERDATA_H
#include <QList>


class ICoreRasterData
{
public:
	virtual void readData(int band,int xstart,int ystart,int xLength,int yLength,int dataType,void *data)=0;
	virtual void readPixel(int x,int y,QList<double> &vecData)=0;

	virtual int getW()=0;
	virtual int getH()=0;
	virtual int getBandCount()=0;
    virtual int getDataType(int)=0;

	virtual void computeStatistics(int bandIndex,double *dMin,double *dMax,double *dMean,double *dStd)=0;

	virtual int getCoreId()=0;


public:

	
};


class IDrillRasterData
{
public:
	virtual ICoreRasterData* getCoreRasterData(int coreid )=0;
	virtual int getDrillId()=0;
	virtual void addCoreRasterData(ICoreRasterData*)=0;
	virtual QList<int> getCoreIdLst()=0;
	virtual int getW()=0;
	virtual int getH()=0;

	//virtual QList<int> getCoreIdLst()=0;
};
#endif