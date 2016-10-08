
#include "COutDataWkThreadPool.h"

COutDataWkThreadPool::COutDataWkThreadPool(CReator *pReator,unsigned int iStartNum):CThreadPool(iStartNum)
{
	m_ptTDataQueMutex = CMutex::GetFistSingleton();
	m_pReator = pReator;
}

bool COutDataWkThreadPool::Init(void)
{
	CThread *pThread=NULL;
	for( int i=0; i<m_iStartNum; i++)
	{
		usleep(20);
		try {
			pThread = new COutDataWkThread(m_pReator, &m_QueTEvData);
		}
		catch( CException &ex)
		{ cout<<ex.GetError()<<endl; continue;}
		if( NULL==pThread )
		{ m_strError = "COutDataWkThreadPool::Init() incur an error[fail in new CThread()]"; return false;}
		if( !pThread->Create() )
		{ m_strError = pThread->GetError(); return false; }
	}
	m_bIsThreadAtrtr = false;
	return true;
}


// 将参数数据pBuf传入队列中，当被阻塞的事件数目小于最大允许线程/4 时Wake()，否则丢掉本次事件，因为此时系统太忙了
void COutDataWkThreadPool::DispatchEvent(void * pBuf)
{
	if( NULL!= pBuf )
	{
		Message tEvData;
		memcpy((char *)&tEvData, pBuf, sizeof(tEvData));
		m_ptTDataQueMutex->Lock();
		m_QueTEvData.push(tEvData);
		m_ptTDataQueMutex->UnLock();

		if( true==m_bIsStatic )
		{
//			pSem->IncSem();
			COutDataWkThread::Wake();
		}
	}
}
