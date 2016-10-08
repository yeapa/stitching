// 原著：吕跃强
// 部门：预研部
// 这是一款开源的软件，但是任何使用者必须附上作者的申明。

#ifndef CTHREAD_H
#define CTHREAD_H

#include <errno.h>
#include <string>
#include <pthread.h>
#include <iostream>

#ifdef CTHREAD_DEBUG
	#include <unistd.h>
#endif

using namespace std;
class CThread
{
public:
	CThread();
	CThread(pthread_attr_t tThreadAttr);  // 按参数中属性创建线程
	virtual ~CThread();

	bool Create(void);
	bool Detach(void);  // 调用本函数的线程脱离主线程
	bool Detach(pthread_t tThreadId); // 使ID为tThreadId的线程脱离主线程
	pthread_t GetCurrThreadId(void);  // 调用本函数的线程ID
	pthread_t GetThisObjThreadId(void);  // 本对象创建的线程ID
	virtual int ThreadFunc(void);
	static void *StaticThreadFunc(void * pThis);
	virtual bool JoinCurrThread(pthread_t tThreadId, void ** ppThreadRet);  // 调用本函数的线程阻塞于ID为tThreadId的线程
	virtual void ExitCurrThread(void *pRetVal);  //退出调用本函数的线程
	bool SetAynCancel();
	bool CancelThisObjThread();
	bool CancelThreadById(pthread_t tId);
	void SetThisObjIdle();
	void SetThisObjBusy();
	virtual char * GetError(void); // 取出最近一次的错误信息
protected:
	string m_strError;
	pthread_attr_t * m_ptAttr; // point to m_tAttr
	pthread_t m_tThreadId; // the thread ID of the thread created by the object
	pthread_attr_t m_tAttr; // create thread by atributes: m_tAttr
	bool m_bIsIdle;
};

#endif
