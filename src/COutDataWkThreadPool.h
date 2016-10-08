
#ifndef COUTDATAWKTHREADPOOL_H
#define COUTDATAWKTHREADPOOL_H

#include "CThreadPool.h"
#include "COutDataWkThread.h"
// 本类是个线程池类。线程的调度有操作系统实现即线程共同阻塞在一个公共的CCond上，由于在Wake之前不知道哪个线程将被唤醒，所以无法将参数
//传入线程对象。鉴于此，通过一个池和线程共享的队列m_QueTEvData来传递数据。本线程池动态静态都可以，不过对于本类线程池推荐用静态的。因
//为动态时需要管理一个链表，这就失去了用操作系统调度的优势因为既然管了这个表，我还不如用CInerDataWkThread直接激活线程.

//未做的工作: 其实m_QueTEvData数据队列应该做成一个线程安全的圆形内存池，每段记录的前四个字节为一个整型数用来表示本记录的长度，这样就摆
//脱了TEvData的限制，也摆脱了内存浪费和有时100字节不足的问题
class COutDataWkThreadPool:public CThreadPool
{
public:
	COutDataWkThreadPool(CReator *pReator, unsigned int iStartNum=5);
	bool Init(void);
	void DispatchEvent(void * pBuf);

protected:
	CMutex *m_ptTDataQueMutex; //and the same as the member of COutDataWkThread
	queue<Message> m_QueTEvData;
	CReator *m_pReator;
	bool m_bIsThreadAtrtr;
	string m_strError;
};

#endif
