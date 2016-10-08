
#include "CLocalLog.h"
#include <cstring>

CLog *CLocalLog::m_bFirstThis=NULL;
CLocalLog::CLocalLog(const char * pFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog):CLog( iLogLevel, bIsWriteHexLog)
{
	m_fpLog = NULL;

	if( strlen(pFileName)==0 )
	{ m_strBaseFileName="Default"; }
	else { m_strBaseFileName = pFileName; }
	m_strFileName = m_strBaseFileName + ".log";

	if( iMaxLogSize>10000000 || iMaxLogSize<=100000 )
	{ m_iMaxLogBytes=10000000; }
	else { m_iMaxLogBytes=iMaxLogSize; }

	if( iLogFileNum<0 || iLogFileNum>80)
	{ m_iLogFileNum=80; }
	else { m_iLogFileNum = iLogFileNum; }

	m_iCurLine=0;
	m_bIsScrowLog=bIsScrowLog;
}

CLocalLog::CLocalLog(const string sFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog):CLog( iLogLevel, bIsWriteHexLog)
{
	m_fpLog = NULL;

	if( sFileName.size()==0 )
	{ m_strBaseFileName="Default"; }
	else { m_strBaseFileName = sFileName; }
	m_strFileName = m_strBaseFileName + ".log";

	if( iMaxLogSize>10000000 || iMaxLogSize<=100000 )
	{ m_iMaxLogBytes=10000000; }
	else { m_iMaxLogBytes=iMaxLogSize; }

	if( iLogFileNum<0 || iLogFileNum>80)
	{ m_iLogFileNum=80; }
	else { m_iLogFileNum = iLogFileNum; }

	m_iCurLine=0;
	m_bIsScrowLog=bIsScrowLog;
}

CLocalLog::~CLocalLog()
{
	if( NULL!=m_fpLog)
	{ fclose(m_fpLog); }
}

int CLocalLog::Open()
{
	if( m_strFileName.size()<string(".log").size() )
	{ m_bCanWriteStr = false;  m_bCanWriteHex = false;  return -1;}
	m_fpLog = fopen(m_strFileName.c_str(), "a");
	if( NULL==m_fpLog )
	{ m_strError="fail in open file:" + m_strFileName; m_bCanWriteStr = false;  m_bCanWriteHex = false; return -1; }
	return 0;
}

int CLocalLog::Close()
{
	if( m_fpLog!=NULL)
	{
		if( fclose(m_fpLog)!=0 )
		{ m_strError="fail in close file:" + m_strFileName; return -1; }
	}
	return 0;
}

int CLocalLog::ChangeLogFile(char * pFileName)        // ������־�ļ���,��ĳ������������־�ļ�ʱ��
{
	Close();
	m_strBaseFileName = pFileName;
	m_strFileName=m_strBaseFileName + ".log";
	if(Open()<0)
	{ m_bCanWriteStr = false; m_bCanWriteHex = false; return -1; }
	return 0;
}

int CLocalLog::ChangeLogFile(const string & sFileName)
{
	Close();
	m_strBaseFileName = sFileName;
	m_strFileName=m_strBaseFileName + ".log";
	if(Open()<0)
	{ m_bCanWriteStr = false; m_bCanWriteHex = false; return -1; }
	return 0;
}

bool CLocalLog::IsNeedShiftFile()
{
	struct stat tStat;

	if( stat(m_strFileName.c_str(), &tStat)<0 )
	{
		m_strError="stat() incurr an error=[";
		m_strError = m_strError +strerror(errno) + "]";
		m_bCanWriteStr = false;
		m_bCanWriteHex = false;
		return false;
	}
	else
	{
		if( tStat.st_size < m_iMaxLogBytes)
		{ return false; }
		else
		{
			if( tStat.st_size> 99000000 ) //99M ��ʵ���������ļ�������10M˵����־���������쳣
			{ m_bCanWriteStr = false; m_bCanWriteHex = false; }
			return true;
		}

	}
}

int CLocalLog::ShiftFiles()
{
	stringstream FormatStr;
	FormatStr<<(m_iLogFileNum-1)<<flush;
	string TmpFileName = m_strBaseFileName + FormatStr.str() + ".log";
	if(access( TmpFileName.c_str(), F_OK )==0)
	{
		if( remove(TmpFileName.c_str())<0 )     // remove the last file
		{
			m_strError="remove() file=";
			m_strError = m_strError + TmpFileName + "incurr an error=[" +strerror(errno) + "]";
			m_bCanWriteStr = false;
			m_bCanWriteHex = false;
			return -1;
		}
	}

	string TmpNewFileName;
	for( int i=m_iLogFileNum-2; i>=0; i-- )
	{
		if(i!=0)
		{
			FormatStr.str("");
			FormatStr<<i<<flush;
			TmpFileName = m_strBaseFileName + FormatStr.str() + ".log";
			FormatStr.str("");
			FormatStr<<(i+1)<<flush;
			TmpNewFileName = m_strBaseFileName + FormatStr.str() + ".log";
		}
		else
		{
			TmpFileName = m_strFileName;
			FormatStr.str("");
			FormatStr<<(i+1)<<flush;
			TmpNewFileName = m_strBaseFileName + FormatStr.str() + ".log";
		}
		if(access(TmpFileName.c_str(),F_OK) == 0)
		{
			if( rename(TmpFileName.c_str(), TmpNewFileName.c_str())<0 )
			{
				m_strError="rename file:";
				m_strError = m_strError + TmpFileName + "incurr an error=[" +strerror(errno) + "]";
				m_bCanWriteStr = false;
				m_bCanWriteHex = false;
				return -1;
			}
		}
	}
	return 0;
}

int CLocalLog::WriteHex(char *buf, int iBufLen,int iCutLen)
{
	if( !m_bCanWriteHex )
	{ return 0; }

	if(m_bIsScrowLog)
	{
		m_iCurLine++;
		if(m_iCurLine>=m_iTestLogBytesPerLine)
		{
			if( IsNeedShiftFile() )
			{
				Close();
				ShiftFiles();
				Open();
			}
			m_iCurLine = 0;
		}
	}
	if( NULL==m_fpLog)
	{
		if( Open()<0 )
		{ return -1;  }
	}

 	int i=0;
 	int iRet=0;
 	string strCurrentTime;
 	if( m_bCanWritePrex )
	{
		GetCurrentTime(strCurrentTime);
		iRet=fprintf( m_fpLog,"[%s] ",strCurrentTime.c_str() );
		if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
 	}

	while(i<iBufLen)
	{
 		iRet=fprintf(m_fpLog,"%#02x ",buf[i]);
	 	if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
		i++;
		if( (i%iCutLen)==0 )
		{ fprintf( m_fpLog,"\n"); }
	}
	fprintf( m_fpLog,"\n");
	fflush(m_fpLog);
	return 0;
}

int CLocalLog::WriteErrorLog(const char *pFmt, ...)
{
	if( false == m_bCanWriteStr )
	{ return 0; }
	if( LOG_ERROR<m_iLogLevel )
	{ return 0; }

	if(m_bIsScrowLog)
	{
		m_iCurLine++;
		if(m_iCurLine>=m_iTestLogBytesPerLine)
		{
			if( IsNeedShiftFile() )
			{
				Close();
				ShiftFiles();
				Open();
			}
			m_iCurLine = 0;
		}
	}
	if( NULL==m_fpLog)
	{ if( Open()<0 ) return -1;  }

	int iRet;
	string strCurrentTime;
 	if( m_bCanWritePrex )
	{
		GetCurrentTime(strCurrentTime);
		iRet=fprintf( m_fpLog,"[%s] ERROR ",strCurrentTime.c_str() );
		if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
 	}

	va_list ap;
	va_start(ap,pFmt);
	iRet=vfprintf(m_fpLog,pFmt,ap);
	va_end(ap);
	if( iRet<0 )
	{
		m_strError="vfprintf() to file=";
		m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
		return -1;
	}
	fflush(m_fpLog);

	return 0;
}

int CLocalLog::WriteNoticeLog(const char *pFmt, ...)
{
	if( false == m_bCanWriteStr )
	{ return 0; }
	printf("iLogLevel=%d\n",m_iLogLevel);
	if( LOG_NOTICE<m_iLogLevel )
	{ return 0; }

	if(m_bIsScrowLog)
	{
		m_iCurLine++;
		if(m_iCurLine>=m_iTestLogBytesPerLine)
		{
			if( IsNeedShiftFile() )
			{
				Close();
				ShiftFiles();
				Open();
			}
			m_iCurLine = 0;
		}
	}
	if( NULL==m_fpLog)
	{ if( Open()<0 ) return -1;  }

	int iRet;
	string strCurrentTime;
 	if( m_bCanWritePrex )
	{
		GetCurrentTime(strCurrentTime);
		iRet=fprintf( m_fpLog,"[%s] NOTICE ",strCurrentTime.c_str() );
		if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
 	}
	va_list ap;
	va_start(ap,pFmt);
	iRet=vfprintf(m_fpLog,pFmt,ap);
	va_end(ap);
	if( iRet<0 )
	{
		m_strError="vfprintf() to file=";
		m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
		return -1;
	}
	fflush(m_fpLog);

	return 0;
}

int CLocalLog::WriteLog(const char *pFmt, ...)
{
	if( false == m_bCanWriteStr )
	{ return 0; }
	if( LOG_NORMAL<m_iLogLevel )
	{ return 0; }

	if(m_bIsScrowLog)
	{
		m_iCurLine++;
		if(m_iCurLine>=m_iTestLogBytesPerLine)
		{
			if( IsNeedShiftFile() )
			{
				Close();
				ShiftFiles();
				Open();
			}
			m_iCurLine = 0;
		}
	}
	if( NULL==m_fpLog)
	{ if( Open()<0 ) return -1;  }

	int iRet;
	string strCurrentTime;
 	if( m_bCanWritePrex )
	{
		GetCurrentTime(strCurrentTime);
		iRet=fprintf( m_fpLog,"[%s] ",strCurrentTime.c_str() );
		if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
 	}

	va_list ap;
	va_start(ap,pFmt);
	iRet=vfprintf(m_fpLog,pFmt,ap);
	va_end(ap);
	if( iRet<0 )
	{
		m_strError="vfprintf() to file=";
		m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
		return -1;
	}
	fflush(m_fpLog);

	return 0;
}

int CLocalLog::WriteDebugLog(const char *pFmt, ...)
{
	if( false == m_bCanWriteStr )
	{ return 0; }
	if( LOG_DEBUG<m_iLogLevel )
	{ return 0; }

	if(m_bIsScrowLog)
	{
		m_iCurLine++;
		if(m_iCurLine>=m_iTestLogBytesPerLine)
		{
			if( IsNeedShiftFile() )
			{
				Close();
				ShiftFiles();
				Open();
			}
			m_iCurLine = 0;
		}
	}
	if( NULL==m_fpLog)
	{ if( Open()<0 ) return -1;  }

	int iRet;
	string strCurrentTime;
 	if( m_bCanWritePrex )
	{
		GetCurrentTime(strCurrentTime);
		iRet=fprintf( m_fpLog,"[%s] DEBUG ",strCurrentTime.c_str() );
		if( iRet<0 )
		{
			m_strError="fprintf() to file=";
			m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
			return -1;
		}
 	}

	va_list ap;
	va_start(ap,pFmt);
	iRet=vfprintf(m_fpLog,pFmt,ap);
	va_end(ap);
	if( iRet<0 )
	{
		m_strError="vfprintf() to file=";
		m_strError = m_strError + m_strFileName + "the error=[" + strerror(errno) + "]";
		return -1;
	}
	fflush(m_fpLog);

	return 0;
}

CLog *CLocalLog::GetFirstSingleton(const string sFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog)
{
	if( 0==sFileName.size() )
	{ return NULL; }
	if( NULL==m_bFirstThis )
	{
		m_bFirstThis = new CLocalLog(sFileName, iMaxLogSize, iLogFileNum, iLogLevel, bIsWriteHexLog, bIsScrowLog);
		return m_bFirstThis;
	}
	else { return m_bFirstThis; }
}

CLog *CLocalLog::GetFirstSingleton(const char * pFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog)
{
	if( NULL== pFileName )
	{ return NULL; }
	if( NULL==m_bFirstThis )
	{
		m_bFirstThis = new CLocalLog(pFileName, iMaxLogSize, iLogFileNum, iLogLevel, bIsWriteHexLog, bIsScrowLog);
		return m_bFirstThis;
	}
	else { return m_bFirstThis; }
}
