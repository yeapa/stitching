
#include "CLog.h"
#include <stdio.h>
#include <cstring>

CLog::CLog(int iLogLevel, bool bIsWriteHexLog)
{
	m_iLogLevel = iLogLevel;
	m_bCanWriteHex = bIsWriteHexLog;
	m_bCanWriteStr = true;
	m_bCanWritePrex = true;
	m_ulID=0;
}
CLog::~CLog()
{ }

void CLog::IsSetWriteHexLog(bool bWrite)
{ m_bCanWriteHex = bWrite; }

void CLog::IsWriteLogPrex(bool bWrite)
{ m_bCanWritePrex = bWrite;printf("m_bCanWritePrex=%d\n",m_bCanWritePrex ); }

void CLog::SetLogLevel(int iLogLevel)
{ m_iLogLevel = iLogLevel; }

void CLog::SetThisTimeID(unsigned long ulID)
{ m_ulID = ulID; }

void CLog::GetCurrentTime(string & sTime)
{
	long tminsec;
	struct tm *tn;

	tminsec=time((time_t *)0);
	tn=localtime((time_t *)&tminsec);
	char strDate[25];
	memset(strDate,0x00,sizeof(strDate));
	snprintf(strDate, sizeof(strDate), "%04d-%02d-%02d %02d:%02d:%02d",tn->tm_year+1900, tn->tm_mon+1, tn->tm_mday, tn->tm_hour, tn->tm_min, tn->tm_sec);
	sTime = strDate;
}

char * CLog::GetError(void)
{ return const_cast<char *>( m_strError.c_str() ); }
