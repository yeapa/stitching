
#include "CReator.h"
#include <vector>
#include <stdimage.hxx>

CReator * CReator::m_pReator=NULL;

CReator::CReator()
{ m_strError=""; }

bool CReator::RegisterObserver(unsigned int iEvent, CEventObserver *pObserver)
{
	map<unsigned int,CEventObserver *>::iterator iterMapTmp;
	iterMapTmp = m_mapEvent.find(iEvent);
	if( iterMapTmp!=m_mapEvent.end() )
	{
		stringstream strErrorFormat;
		strErrorFormat<<"error[you have already register the CEventObserver of iEvent= "<<iEvent<<" ]";
		m_strError = strErrorFormat.str();
		return false;
	}

	bool bRlt = ( (m_mapEvent.insert(map<unsigned int,CEventObserver *>::value_type(iEvent,pObserver))) ).second;
	if( !bRlt )
	{ m_strError = "error[fail in CReator::RegisterObserver()]"; }
	return bRlt;
}

void CReator::RemoveObserver(unsigned int iEvent)
{ m_mapEvent.erase(iEvent); }

CReator::MultiioEvent CReator::MultiIO()
{

}

int CReator::EventNotify(void *pPara)
{
	CEventObserver *Observer=NULL;
	vector<vigra::BRGBImage*> tPara=*(vector<vigra::BRGBImage*>*)pPara;
//	Observer = m_mapEvent[tPara.m_msgType];
	Observer = m_mapEvent[1];
	if( NULL== Observer )
	{ m_strError = "error[the Observer is NULL in from m_mapEvent CReator::EventNotify]";  return -1;}
	else
	{ return (Observer->EventProcess(&tPara)); }

}

CReator * CReator::Instance()
{
	if( NULL==m_pReator )
	{
		m_pReator = new CReator();
//		if( NULL==m_pReator )  client program cann't get the error info because the object is not created
//		{ m_strError = "error[fail in new CReator()]"; }
		return m_pReator;
	}
	else
	{ return m_pReator; }
}

char *CReator::GetError(void )
{ return const_cast<char *>( m_strError.c_str() ); }
