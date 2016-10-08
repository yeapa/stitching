// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#ifndef CMUTEX_H
#define CMUTEX_H
// �����ڹ��캯���л��׳��쳣
#include <errno.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include "CException.h"

using namespace std;

class CMutex
{
public:
	CMutex(void);
	virtual ~CMutex(void);
	static CMutex *GetFistSingleton();
	static CMutex *GetSecSingleton();
	virtual int Lock(void);
	virtual int TryLock(void);
	virtual int UnLock(void);
	virtual pthread_mutex_t * GetMutexPtr();
	virtual char * GetError(void);
public:
	pthread_mutex_t m_Mutex;
protected:
	static CMutex *m_pFirstSingleton;
	static CMutex *m_pSecSingleton;
	string m_strError;
};

#endif
