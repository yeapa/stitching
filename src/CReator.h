
#ifndef CREATOR_H
#define CREATOR_H

#include <string>
#include <sstream>
#include <utility>
#include <map>
#include "CEventObserver.h"

using namespace std;

//本类是个反应器，就是管理用户的事件和观察者，其中基类不带事件分离器
class CReator
{
public:
	//在派生类CMultiIOReator中EventNotify中对ZERO是不处理的，而是循环回去MultiIO的。MUTIIOERROR指的是系统函数调用返回出错
	enum MultiioEvent { ZERO=0,ACCEPT=1, READ=2,WRITE=3,EXCEPTION=4,TIMEOUT=5,MUTIIOERROR=6};
	bool RegisterObserver(unsigned int iEvent, CEventObserver *pObserver);
	void RemoveObserver(unsigned int iEvent);
	virtual int EventNotify(void *pPara);
	static CReator * Instance();
	char *GetError(void );

protected:
	CReator();
	virtual CReator::MultiioEvent MultiIO();

protected:
	static CReator *m_pReator;
	map<unsigned int,CEventObserver *> m_mapEvent;
	string m_strError;
};

#endif
