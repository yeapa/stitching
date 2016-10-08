
#include "CThread.h"
#include <cstring>

CThread::CThread()
{
	m_ptAttr=NULL;
	m_tThreadId= pthread_t(-1);
	m_bIsIdle = false;
}

CThread::CThread(pthread_attr_t tThreadAttr)
{
	m_tAttr = tThreadAttr;
	m_ptAttr = const_cast<pthread_attr_t *>(&m_tAttr);
	m_tThreadId= pthread_t(-1);
	m_bIsIdle = false;
}

bool CThread::Create(void)
{
	if( pthread_create(&m_tThreadId, m_ptAttr, StaticThreadFunc, this)!=0 )
	{
		m_strError = "CThread::ThreadCreate() incur ";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	return true;
}

CThread::~CThread()
{ }

bool CThread::Detach(void)
{
	if( pthread_detach(pthread_self())!=0 )
	{
		m_strError = "CThread::ThreadDetach() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	else { return true; }
}

bool CThread::Detach(pthread_t tThreadId)
{
	if( pthread_detach(tThreadId)!=0 )
	{
		m_strError = "CThread::ThreadDetach() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	else { return true; }
}

pthread_t CThread::GetCurrThreadId(void)
{ return (pthread_self());}

pthread_t CThread::GetThisObjThreadId(void)
{ return m_tThreadId; }

int CThread::ThreadFunc(void)
{
#ifdef CTHREAD_DEBUG
	cout<<"in CThread::ThreadFunc() thread id="<<GetCurrThreadId()<<endl;
#endif
	return 0;
}

void *CThread::StaticThreadFunc(void * pThis)
{
	CThread* pMyThis=(CThread*)pThis;
	if( pMyThis->Detach()<0 )
	{ cerr<<"detach error"<<endl; return NULL;}
#ifdef CTHREAD_DEBUG
	cout<<"thread id="<<pthread_self()<<endl;
#endif

	pMyThis->ThreadFunc();
}

 // ���ñ��������߳�������IDΪtThreadId���߳�
bool CThread::JoinCurrThread(pthread_t tThreadId, void ** ppThreadRet)
{
	if( pthread_join(tThreadId,ppThreadRet)!=0 )
	{
		m_strError = "function CThread::ThreadJoin() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	else { return true; }
}
void CThread::ExitCurrThread(void *pRetVal)
{ pthread_exit(pRetVal); }

bool CThread::SetAynCancel()
{
	if( pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL)!=0 )
	{
		m_strError = "function CThread::SetAynCancel() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	else { return true; }
}

bool CThread::CancelThisObjThread()
{
	int iRet=pthread_cancel(m_tThreadId);
	if( iRet!=0 )
	{
		m_strError = "function pthread_cancel() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	return true;
}

bool CThread::CancelThreadById(pthread_t tId)
{
	int iRet=pthread_cancel(tId);
	if( iRet!=0 )
	{
		m_strError = "function pthread_cancel() incur";
		m_strError =  m_strError +"an error[" + strerror(errno) + "]";
		return false;
	}
	return true;

}

void CThread::SetThisObjIdle()
{
	m_bIsIdle = true;
}
void CThread::SetThisObjBusy()
{
	m_bIsIdle = false;
}

char * CThread::GetError(void)
{ return const_cast<char *>(m_strError.c_str()); }
