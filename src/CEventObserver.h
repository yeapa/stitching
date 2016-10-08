
#ifndef CEVENTOBSERVER_H
#define CEVENTOBSERVER_H

#include <string.h>
#include <unistd.h>
#include <stdimage.hxx>
#include "Message.h"

// #define OBSERVER_DEBUG
#ifdef OBSERVER_DEBUG
#include <iostream>
#endif
using namespace std;
class CEventObserver
{
public:
	CEventObserver(unsigned int iEvent);
	virtual ~CEventObserver();
	int GetEventHandle(void);
	//�������û��Ĵ����ӿ�,ʹ�õ���ģ�巽��ģʽ,����ֻ��ʵ���Լ���ParsePara()��ConCreteProcess
	virtual int EventProcess(vector<vigra::BRGBImage*> *pInPara, char *pOutPara=NULL);
	char *GetError();
protected:
	unsigned int m_iEvent;
	string m_strError;
};

#endif
