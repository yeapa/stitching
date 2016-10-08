
#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H

#include "CThread.h"

class CThreadPool
{
public:
	CThreadPool(unsigned int iStartNum=15);
	char *GetError();
	virtual bool Init(void);
	virtual bool Init(pthread_attr_t tThreadAttr);
	virtual int Monitor(void);
	virtual void DispatchEvent(void * pBuf);

protected:
	int m_iMaxPermitNum, m_iStartNum;
	string m_strError;
	bool m_bIsStatic;
};

#endif
