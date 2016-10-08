
#include "CEventObserver.h"

CEventObserver::CEventObserver(unsigned int iEvent)
{ m_iEvent = iEvent; }

CEventObserver::~CEventObserver()
{}

int CEventObserver::GetEventHandle(void)
{ return m_iEvent; }


int CEventObserver::EventProcess(char *pInPara, char *pOutPara)
{
	return 0;
}

char * CEventObserver::GetError()
{ return const_cast<char *>(m_strError.c_str()); }
