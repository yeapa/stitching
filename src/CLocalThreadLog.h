//ԭ��:��Ծǿ
//��˾:��Ѷ
//����:Ԥ�в�
//����:�����߳���־��

#ifndef CLOCALTHREAD_H
#define CLOCALTHREAD_H

#include "CLocalLog.h"
#include "CMutex.h"

using namespace std;
class CLocalThreadLog : public CLocalLog
{
public:
	CLocalThreadLog(const char * pFileName, int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
	CLocalThreadLog(const string sFileName, int iMaxLogSize=8000000, int iLogFileNum=8, int iLogLevel=1, bool bIsWriteHexLog=true, bool bIsScrowLog=true);
	virtual ~CLocalThreadLog();
	virtual int Open();
	virtual int Close();
	virtual int WriteHex(char *buf, int iBufLen,int iCutLen=50);
	virtual int WriteErrorLog(const char *pFmt, ...);
	virtual int WriteNoticeLog(const char *pFmt, ...);
	virtual int WriteLog(const char *pFmt, ...);
	virtual int WriteDebugLog(const char *pFmt, ...);

	virtual int ChangeLogFile(char * pFileName);        // ������־�ļ���,��ĳ������������־�ļ�ʱ��
	virtual int ChangeLogFile(const string & sFileName);
protected:
	// bool IsNeedShiftFile();
	// virtual int ShiftFiles();
protected:
	CMutex m_tMutex;
};

#endif
