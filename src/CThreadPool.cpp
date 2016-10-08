
#include "CThreadPool.h"

CThreadPool::CThreadPool(unsigned int  iStartNum)
{
	m_bIsStatic=true;
	if( 0==iStartNum )
	{ m_iStartNum = 1; }
	else if( iStartNum>100000 )
	{ m_iStartNum=100000; }
	else { m_iStartNum=iStartNum;}

}

bool CThreadPool::Init(void)
{
	CThread *pThread=NULL;
	for( int i=0; i<m_iStartNum; i++)
	{
		pThread = new CThread();
		if( NULL==pThread )
		{ m_strError = "CThreadPool::Init() incur an error[fail in new CThread()]"; return false;}
		if( !pThread->Create() )
		{ m_strError = pThread->GetError(); return false; }
	}
	return true;
}

char * CThreadPool::GetError()
{ return const_cast<char *>(m_strError.c_str()); }

bool CThreadPool::Init(pthread_attr_t tThreadAttr)
{
	CThread *pThread=NULL;
	for( int i=0; i<m_iStartNum; i++)
	{
		pThread = new CThread(tThreadAttr);
		if( NULL==pThread )
		{ m_strError = "CThreadPool::Init() incur an error[fail in new CThread()]"; return false;}
		if( !pThread->Create() )
		{ m_strError = pThread->GetError(); return false; }
	}
	return true;
}

int CThreadPool::Monitor(void)
{
	return 0;
}

void CThreadPool::DispatchEvent(void * pBuf)
{

}
