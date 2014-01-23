#include "mygdalRasterData.h"
#include "gdal_priv.h"
CMygdalCoreRasterData::CMygdalCoreRasterData()
{
	m_pDataSet=NULL;

	m_coreId=0;
}

CMygdalCoreRasterData::~CMygdalCoreRasterData()
{

}

 void CMygdalCoreRasterData::readData(int band,int xstart,int ystart,int xLength,int yLength,int dataType,void *data)
 {
	 m_pDataSet->GetRasterBand(band)->RasterIO(GF_Read,xstart,ystart,xLength,yLength,data,xLength,yLength,(GDALDataType)dataType,0,0);
 }
 	



  void CMygdalCoreRasterData::readPixel(int x,int y,QList<double> &vecData)
  {
	 // int nBandCount=getBandCount();

	 // if(nBandCount<=0)
		//  return ;
	 //
	 // int dataType=getDataType(1);
	 // unsigned short int sVal;

	 // for(int i=0;i<nBandCount;++i)
	 //{
		// m_pDataSet->GetRasterBand(i+1)->RasterIO(GF_Read,x,y,1,1,(void*)&sVal,1,1,(GDALDataType)dataType,0,0);
		// vecData.push_back(sVal);
	 // }

	  int nBandCount=getBandCount();
	  if(nBandCount<=0)
		  return ;
	  int dataType=getDataType(1);

	  switch(dataType)
	  {
	  case GDT_Byte:
		  readPixelPriv<unsigned char>(x,y,vecData);
		  break;
	  case GDT_UInt16:
		  readPixelPriv<unsigned short int>(x,y,vecData);
		   break;
	  case GDT_Int16:
		  readPixelPriv< short int>(x,y,vecData);
		  break;
	  case GDT_UInt32:
		  readPixelPriv<unsigned  int>(x,y,vecData);
		  break;
	  case GDT_Int32:
		   readPixelPriv<int>(x,y,vecData);
		  break;
	  case GDT_Float32:
		   readPixelPriv<float>(x,y,vecData);
		  break;
	  case GDT_Float64:
		   readPixelPriv<double>(x,y,vecData);
		  break;

	  }






  }

  template <class T>
  void CMygdalCoreRasterData::readPixelPriv(int x,int y,QList<double> &vecData)
  {

	  int nBandCount=getBandCount();
	  if(nBandCount<=0)
		  return ;
	  int dataType=getDataType(1);

	  T sVal;

	  for(int i=0;i<nBandCount;++i)
	  {
		  m_pDataSet->GetRasterBand(i+1)->RasterIO(GF_Read,x,y,1,1,(void*)&sVal,1,1,(GDALDataType)dataType,0,0);
		  vecData.push_back(sVal);
	  }

	
  }
int CMygdalCoreRasterData::getW()
{

	return m_pDataSet->GetRasterXSize();
	
 }
int CMygdalCoreRasterData::getH()
{


	return m_pDataSet->GetRasterYSize();
}
int CMygdalCoreRasterData::getBandCount()
{
	return m_pDataSet->GetRasterCount();
}
int CMygdalCoreRasterData::getDataType(int bandIndex)
{

	return m_pDataSet->GetRasterBand(bandIndex)->GetRasterDataType();
}

 int CMygdalCoreRasterData::getCoreId()
 {
	 return m_coreId;
 }
 void CMygdalCoreRasterData::setDataSet(GDALDataset * pDataset)
 {
	 m_pDataSet=pDataset;
 }
 void CMygdalCoreRasterData::computeStatistics(int bandInex,double *dMin,double *dMax,double *dMean,double *dStd)
 {
	 m_pDataSet->GetRasterBand(bandInex)->ComputeStatistics(false,dMin,dMax,dMean,dStd,NULL,NULL);
 }
 void CMygdalCoreRasterData::setCoreId(int coreId)
 {
	 m_coreId=coreId;
 }
 ICoreRasterData* CMygdalCoreRasterData::createDataSet(const std::string & strFileName,int coreId)
 {


	 GDALAllRegister();
	 GDALDataset *   hDataset;
	 hDataset = ( GDALDataset * )GDALOpen( strFileName.c_str(),GA_ReadOnly);

	 if(hDataset==NULL)
		 return NULL;

		 ICoreRasterData *pData=new CMygdalCoreRasterData();

		((CMygdalCoreRasterData*)pData)->setDataSet(hDataset);

		((CMygdalCoreRasterData*)pData)->setCoreId(coreId);


		return pData;

   return NULL;
 }



 CMygdalDrillRasterData::CMygdalDrillRasterData()
 {

 }

 CMygdalDrillRasterData::~CMygdalDrillRasterData()
 {

 }

 ICoreRasterData * CMygdalDrillRasterData::getCoreRasterData(int coreid)
 {
	 return m_mapCoreRasterData.value(coreid);
 }
void CMygdalDrillRasterData::addCoreRasterData( ICoreRasterData * p)
{
	m_mapCoreRasterData.insert(p->getCoreId(),p);
}

int CMygdalDrillRasterData::getDrillId()
{
	return m_drillId;
}
void CMygdalDrillRasterData::setDrillId(int drillId)
{
	m_drillId=drillId;
}
IDrillRasterData* CMygdalDrillRasterData::createDataSet(int drillId)
{
	CMygdalDrillRasterData *pdata=new CMygdalDrillRasterData();

	pdata->setDrillId(drillId);

	return pdata;
}

 int CMygdalDrillRasterData::getW()
{
	QList<int> keyLst=m_mapCoreRasterData.keys();
	if(keyLst.size()!=0)
	{
		return m_mapCoreRasterData.value(keyLst[0])->getW();
	}

	return 0;
}
 int CMygdalDrillRasterData::getH()
 {
	 QList<int> keyLst=m_mapCoreRasterData.keys();

	 int ncount=keyLst.size();
	 int nh=0;

	 for(int i=0;i<ncount;i++)
	 {
		 nh=nh+m_mapCoreRasterData.value(keyLst[i])->getH();
	 }

	 return nh;
 }

 QList<int> CMygdalDrillRasterData::getCoreIdLst()
 {
	 return m_mapCoreRasterData.keys();
 }