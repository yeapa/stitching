// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#include "CSimpleConfig.h"
#include <iostream>

CConfig *CSimpleConfig::m_pThisFirst=NULL;
int CSimpleConfig::GetLinePara(const string strLine, string & strField, string & strValue)
{
	if( strLine.empty() )
	{ return -1; }
	strField="";
	strValue="";

	string sLine=strLine;
	string::size_type i=0;
	while( sLine[i] != 0x00 )
	{
		//if( (sLine.at(i)!=' ')&&(sLine.at(i)!='\t') )
		if( (sLine.at(i)>0x21)&&(sLine.at(i)<0x7e) )
		{ break; }
		if( i==(sLine.size()-1) ) { return -1; }
		i++;
	}
	if(sLine.at(i)=='#' || (sLine.at(i)=='/'&&sLine.at(i+1)=='/') )
	{ return -1; }

	while( sLine.at(i) != 0x00 )
	{
		if( (sLine.at(i)==' ')||(sLine.at(i)=='\t')||(sLine.at(i)=='\n') )
		{ break; }
		strField += sLine.at(i);
		i++;
	}

	while( sLine[i]!=0x00 )
	{
		if( (sLine.at(i)!=' ')&&(sLine.at(i)!='\t')&&(sLine.at(i)!='\n') )
		{  break; }
		i++;
	}
	string::size_type iLen=sLine.size();
	while( (sLine[iLen]<0x21)||(sLine[iLen]>0x7E) )
	{ iLen--; }
	if( (iLen-i)<0 ) { return -1;}

	string sTmpStr( sLine, i,(iLen-i)+1 );
	strValue=sTmpStr;

	return 0;
}

int CSimpleConfig::GetConfigLineNum() const
{
	return  mapFieldValue.size();
}

int CSimpleConfig::ParseFile(void)
{
	ifstream inConfigFile(m_pFileName.c_str());
	if( !inConfigFile )
	{ m_pError = "fail in open config file=" + m_pFileName + " for read";
	 inConfigFile.close();
	 return -1; }
	string strLine, strField, strValue;
	while( getline(inConfigFile, strLine, '\n') )
	{
		if(GetLinePara(strLine, strField, strValue) == 0)
		{ mapFieldValue.insert( make_pair(strField,strValue) ); }
	}
	return 0;
}

int CSimpleConfig::GetParaValue(const string sParaField, string & sParaValue)
{
	sParaValue = mapFieldValue[sParaField];
	return 0;
}

int CSimpleConfig::GetParaValue(const char * pParaField, string & sParaValue)
{
	sParaValue = mapFieldValue[pParaField];
	return 0;
}

int CSimpleConfig::GetParaValue(const string sParaField, int & iParaValue)
{
	char *p=const_cast<char *>(mapFieldValue[sParaField].c_str());
	iParaValue = atoi(p);
	return 0;
}

int CSimpleConfig::GetParaValue(const char * pParaField, int & iParaValue)
{
	char *p=const_cast<char *>(mapFieldValue[pParaField].c_str());
	iParaValue = atoi(p);
	return 0;
}

int CSimpleConfig::GetParaValue(const string sParaField, double & dbParaValue)
{
	char *p=const_cast<char *>(mapFieldValue[sParaField].c_str());
	dbParaValue = atof(p);
	return 0;
}

int CSimpleConfig::GetParaValue(const char * pParaField, double & dbParaValue)
{
	char *p=const_cast<char *>(mapFieldValue[pParaField].c_str());
	dbParaValue = atof(p);
	return 0;
}

CConfig *CSimpleConfig::GetFirstSingleton(const string & sFile)
{
	if( 0==sFile.size() )
	{ return NULL; }
	if( NULL==m_pThisFirst )
	{
		m_pThisFirst = new CSimpleConfig(sFile);
		return m_pThisFirst;
	}
	else { return m_pThisFirst; }
}

CConfig *CSimpleConfig::GetFirstSingleton(const char *pFile)
{
	if( NULL==pFile )
	{ return NULL; }
	if( NULL==m_pThisFirst )
	{
		m_pThisFirst = new CSimpleConfig(pFile);
		return m_pThisFirst;
	}
	else { return m_pThisFirst; }
}
