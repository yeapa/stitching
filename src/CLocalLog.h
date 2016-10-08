//ԭ��:��Ծǿ
//��˾:��Ѷ
//����:Ԥ�в�
//����:������־��

#ifndef CLOCALLOG_H
#define CLOCALLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include "CLog.h"

using namespace std;
class CLocalLog : public CLog
{
public:
	CLocalLog(const char * pFileName, int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
	CLocalLog(const string sFileName, int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
	virtual ~CLocalLog();
	virtual int Open();
	virtual int Close();
	virtual int WriteHex(char *buf, int iBufLen,int iCutLen=50);
	virtual int WriteErrorLog(const char *pFmt, ...);
	virtual int WriteNoticeLog(const char *pFmt, ...);
	virtual int WriteLog(const char *pFmt, ...);
	virtual int WriteDebugLog(const char *pFmt, ...);

	virtual int ChangeLogFile(char * pFileName);        // ������־�ļ���,��ĳ������������־�ļ�ʱ��
	virtual int ChangeLogFile(const string & sFileName);
	static CLog *GetFirstSingleton(const string sFileName="", int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
	static CLog *GetFirstSingleton(const char * pFileName=NULL, int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
protected:
	bool IsNeedShiftFile();
	virtual int ShiftFiles();
protected:
	FILE *m_fpLog;
	string m_strBaseFileName,m_strFileName;
	int m_iMaxLogBytes, m_iLogFileNum, m_iCurLine;
	static const int m_iTestLogBytesPerLine = 32;
	bool m_bIsScrowLog;
	static CLog *m_bFirstThis;
};

#endif
