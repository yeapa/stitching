
#include "COutDataWkThread.h"
#include <stdio.h>

CMutex *COutDataWkThread::m_ptTDataQueMutex  = CMutex::GetFistSingleton();
CAnonymSem COutDataWkThread::m_tWakeSem;
bool COutDataWkThread::m_bIsStatic=true; //这个值最好在相关静态函数里设置
int COutDataWkThread::m_iMaxMemNum=1000; //这个值最好在相关静态函数里设置
COutDataWkThread * COutDataWkThread::m_pIdleMemFront=NULL;
COutDataWkThread::COutDataWkThread(CReator *pReator,queue<Message> *pQueTEvData):CThread()
{
	m_ptReactor =NULL;
	m_pQueTEvData = pQueTEvData;
	if( NULL==m_pQueTEvData )
	{ throw CException("error[para queue<TEvData> *pQueTEvData is NULL in COutDataWkThread::COutDataWkThread()]");}
	m_ptReactor = pReator;
	if( NULL==m_ptReactor )
	{ throw CException("error[fail in CReator::Instance() ]"); }
}

COutDataWkThread::~COutDataWkThread()
{

}

int COutDataWkThread::ThreadFunc(void)
{
	Message tTmmPara;
	if( false==m_bIsStatic )
	{
		if( !SetAynCancel() )
		{ return -1; }
	}
	while(1)
	{
#ifdef OBSERVER_DEBUG
		cout<<"before wait COutDataWkThread thread id="<<GetCurrThreadId()<<endl;
#endif
		m_bIsIdle = true;
		Wait();
		m_bIsIdle = false;
//		m_pThreadSate->DecSem();
#ifdef OBSERVER_DEBUG
		cout<<"after wait COutDataWkThread thread "<<m_tThreadId<<endl;
#endif
		m_ptTDataQueMutex->Lock();
		if( NULL!=m_pQueTEvData )
		{
			tTmmPara =m_pQueTEvData->front();
			m_pQueTEvData->pop();
		}
		m_ptTDataQueMutex->UnLock();

		if( NULL==m_pQueTEvData )
		{ m_strError = "error[COutDataWkThread::m_pQueTEvData is NULL]"; continue; }
		if(m_ptReactor->EventNotify(&tTmmPara)==-1)
		{
			fprintf(stderr, "no msg_type in the CReator::m_mapEvent\n");
		}

	}
	return 0;
}

void COutDataWkThread::Wake(void)
{ m_tWakeSem.Signal(); }

void COutDataWkThread::Wait(void)
{
	m_tWakeSem.Wait();
}
