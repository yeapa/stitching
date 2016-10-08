//ԭ��:��Ծǿ
//��˾:��Ѷ
//����:Ԥ�в�
//����ֻ�ṩһ���ӿڣ��ڱ�����������������־����Զ����־��

#ifndef CLOG_H
#define CLOG_H

#include <string>
#include <errno.h>

using namespace std;
class CLog
{
public:
	virtual ~CLog();
	void IsSetWriteHexLog(bool bWrite) ;
	void IsWriteLogPrex(bool bWrite=true);
	void SetLogLevel(int iLogLevel) ;
	void SetThisTimeID(unsigned long ulID) ;
	virtual char * GetError(void);
	virtual int Open()=0;
	virtual int Close()=0;
	virtual int WriteHex(char *buf, int iBufLen,int iCutLen=50)=0 ;
	virtual int WriteErrorLog(const char *pFmt, ...)=0 ;
	virtual int WriteNoticeLog(const char *pFmt, ...)=0 ;
	virtual int WriteLog(const char *pFmt, ...)=0 ;
	virtual int WriteDebugLog(const char *pFmt, ...)=0 ;

public:
	static const int LOG_ERROR=4;
	static const int LOG_NOTICE=3;
	static const int LOG_NORMAL=2;
	static const int LOG_DEBUG=1;
protected:
	CLog(int iLogLevel=1, bool bIsWriteHexLog=true);
	void GetCurrentTime(string & sTime);
protected:
	string m_strError;
	int m_iLogLevel;
	unsigned long m_ulID;
	bool m_bCanWriteHex, m_bCanWriteStr, m_bCanWritePrex;

};

#endif
