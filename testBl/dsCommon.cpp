#include "dsCommon.h"

void copyStdStringToChar(char *p,const std::string & str,int ccount )
{
	int ns=str.size();

	int ncp=std::min(ns,ccount);

	memset(p,0,ccount);

	for(int i=0;i<ncp;i++)
		p[i]=str.at(i);

}