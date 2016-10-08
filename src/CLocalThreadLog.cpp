
#include "CLocalThreadLog.h"

CLocalThreadLog::CLocalThreadLog(const char * pFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog)
:CLocalLog(pFileName, iMaxLogSize, iLogFileNum, iLogLevel, bIsWriteHexLog, bIsScrowLog)
{}

CLocalThreadLog::CLocalThreadLog(const string sFileName, int iMaxLogSize, int iLogFileNum, int iLogLevel, bool bIsWriteHexLog, bool bIsScrowLog)
:CLocalLog(sFileName, iMaxLogSize, iLogFileNum, iLogLevel, bIsWriteHexLog, bIsScrowLog)
{}

CLocalThreadLog::~CLocalThreadLog()
{ }

int CLocalThreadLog::Open()
{
	int iRet=0;
	m_tMutex.Lock();
	iRet = CLocalLog::Open();
	m_tMutex.UnLock();
	return iRet;
}

int CLocalThreadLog::Close()
{
	int iRet=0;
	m_tMutex.Lock();
	iRet = CLocalLog::Close();
	m_tMutex.UnLock();
	return iRet;
}

int CLocalThreadLog::WriteHex(char *buf, int iBufLen,int iCutLen)
{
	int iRet=0;
	m_tMutex.Lock();
	iRet = CLocalLog::WriteHex(buf,iBufLen, iCutLen);
	m_tMutex.UnLock();
	return iRet;
}

int CLocalThreadLog::WriteErrorLog(const char *pFmt, ...)
{
	m_tMutex.Lock();

	if( false == m_bCanWriteStr )
	{ m_tMutex.UnLock(); return 0;}
	if( LOG_ERROR<m_iLogLevel )
	{m_tMutex.UnLock(); return 0;}

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
		{ m_tMutex.UnLock(); return -1; }
	}

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
			m_tMutex.UnLock();
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
		m_tMutex.UnLock();
		return -1;
	}
	fflush(m_fpLog);

	m_tMutex.UnLock();
	return 0;
}

int CLocalThreadLog::WriteNoticeLog(const char *pFmt, ...)
{
	m_tMutex.Lock();

	if( false == m_bCanWriteStr )
	{ m_tMutex.UnLock(); return 0;}
	if( LOG_NOTICE<m_iLogLevel )
	{m_tMutex.UnLock(); return 0;}

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
		{ m_tMutex.UnLock(); return -1; }
	}

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
			m_tMutex.UnLock();
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
		m_tMutex.UnLock();
		return -1;
	}
	fflush(m_fpLog);

	m_tMutex.UnLock();
	return 0;
}

int CLocalThreadLog::WriteLog(const char *pFmt, ...)
{
	m_tMutex.Lock();

	if( false == m_bCanWriteStr )
	{ m_tMutex.UnLock(); return 0;}
	if( LOG_NORMAL<m_iLogLevel )
	{m_tMutex.UnLock(); return 0;}

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
		{ m_tMutex.UnLock(); return -1; }
	}

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
			m_tMutex.UnLock();
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
		m_tMutex.UnLock();
		return -1;
	}
	fflush(m_fpLog);

	m_tMutex.UnLock();
	return 0;
}

int CLocalThreadLog::WriteDebugLog(const char *pFmt, ...)
{
	m_tMutex.Lock();

	if( false == m_bCanWriteStr )
	{ m_tMutex.UnLock(); return 0;}
	if( LOG_DEBUG<m_iLogLevel )
	{m_tMutex.UnLock(); return 0;}

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
		{ m_tMutex.UnLock(); return -1; }
	}

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
			m_tMutex.UnLock();
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
		m_tMutex.UnLock();
		return -1;
	}
	fflush(m_fpLog);

	m_tMutex.UnLock();
	return 0;
}

int CLocalThreadLog::ChangeLogFile(char * pFileName)
{
	int iRet=0;
	m_tMutex.Lock();
	iRet = CLocalLog::ChangeLogFile( pFileName);
	m_tMutex.UnLock();
	return iRet;
}
int CLocalThreadLog::ChangeLogFile(const string & sFileName)
{
	int iRet=0;
	m_tMutex.Lock();
	iRet = CLocalLog::ChangeLogFile( sFileName);
	m_tMutex.UnLock();
	return iRet;
}
