
#include "CAnonymSem.h"

CAnonymSem *CAnonymSem::m_pFirst=NULL;
CAnonymSem::CAnonymSem()
{
	if( sem_init(&m_tSem,0,0)<0 )
	{
		m_strError="fail in function CAnonymSem::CAnonymSem()";
		m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		throw CException(m_strError);
	}
}

CAnonymSem::~CAnonymSem()
{
	sem_destroy(&m_tSem);
}

CAnonymSem *CAnonymSem::GetFirstSingleton(void)
{
	if( NULL==m_pFirst )
	{
		m_pFirst=new CAnonymSem();
		return m_pFirst;
	}
	else {return m_pFirst; }
}

int CAnonymSem::Signal()
{
	if( sem_post(&m_tSem)<0 )
	{
		m_strError="fail in function CAnonymSem::Signal()";
		m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		return -1;
	}
	return 0;
}

int CAnonymSem::GetSemValue()
{
	int iVal;
	sem_getvalue(&m_tSem,&iVal);
	return iVal;
}

int CAnonymSem::Wait()
{
	sem_wait(&m_tSem);
	return 0;
}

char * CAnonymSem::GetError()
{
	return const_cast<char *>(m_strError.c_str());
}
