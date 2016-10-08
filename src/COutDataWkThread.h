
#ifndef COUTDATAWKTHREAD_H
#define COUTDATAWKTHREAD_H
// 本类在构造函数中会抛出异常 ，请注意处理。本类重载了new和delete以实现内存池的管理，避免了
//创建对象过频引起的内存碎片的问题

#include "CMutex.h"
#include <queue>
#include <list>
#include <algorithm>
#include <unistd.h>
#include <stdimage.hxx>
//#include "CException.h"
#include "CAnonymSem.h"
#include "Message.h"
#include "CThread.h"
#include "CReator.h"

using namespace std;

class COutDataWkThread: public CThread
{
public:
	COutDataWkThread(CReator *pReator,queue<vector<vigra::BRGBImage*>> *pQueTEvData);
	~COutDataWkThread();       //override the virtual

	int ThreadFunc(void);     //override the virtual
	static void Wake(void);
	static void SetMaxMemNum(int iMaxNum)
	{ m_iMaxMemNum = iMaxNum; }
protected:
	void Wait(void);

protected:
	static CAnonymSem m_tWakeSem;  // 与Wake()对应所以本变量申明静态的
	// 下面这个指针指向的锁也被线程池COutDataWkThreadPool使用所以由单件类模式赋值
	// 否则仅静态就可以满足本类的所有对象之用
	static CMutex *m_ptTDataQueMutex ;
	queue<vector<vigra::BRGBImage*>> *m_pQueTEvData;
	CReator *m_ptReactor;
	static bool m_bIsStatic;
	static COutDataWkThread *m_pIdleMemFront;
	COutDataWkThread *m_pNext;
	static int m_iMaxMemNum;
};

#endif
