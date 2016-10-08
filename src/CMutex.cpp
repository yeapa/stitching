// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#include "CMutex.h"

CMutex *CMutex::m_pFirstSingleton=NULL;
CMutex *CMutex::m_pSecSingleton=NULL;
CMutex::CMutex(void)
{
	if(pthread_mutex_init(&m_Mutex,NULL)!=0)
	{
		m_strError="fail in function CMutex::CMutex(void)";
		m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		throw CException(m_strError);
	}
}

CMutex::~CMutex(void)
{
	TryLock();
	UnLock();
	if(pthread_mutex_destroy(&m_Mutex)!=0)
	{
		m_strError="fail in function CMutex::~CMutex(void)";
		m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		throw CException(m_strError);
	}
}

CMutex *CMutex::GetFistSingleton()
{
	if(NULL==m_pFirstSingleton)
	{
		m_pFirstSingleton = new CMutex();
		return m_pFirstSingleton;
	}
		return m_pFirstSingleton;
}

CMutex *CMutex::GetSecSingleton()
{
	if(NULL==m_pSecSingleton)
	{
		m_pSecSingleton = new CMutex();
		return m_pSecSingleton;
	}
		return m_pSecSingleton;
}

int CMutex::Lock(void)
{
	if( pthread_mutex_lock(&m_Mutex) != 0 )
	{
                m_strError="fail in function CMutex::Lock(void)";
                m_strError =  m_strError +"the error is {" + strerror(errno) + "}";
		return -1;
	}
	else { return 0; }
}

int CMutex::UnLock(void)
{
	if( pthread_mutex_unlock(&m_Mutex) != 0 )
	{
                m_strError="fail in function CMutex::UnLock(void)";
                m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		return -1;
	}
	else { return 0; }
}

int CMutex::TryLock(void)
{
	if( pthread_mutex_trylock(&m_Mutex) != 0 )
	{
                m_strError="fail in function CMutex::UnLock(void)";
                m_strError = m_strError + "the error is {" + strerror(errno) + "}";
		return -1;
	}
	else { return 0; }

}

pthread_mutex_t * CMutex::GetMutexPtr()
{
	return &m_Mutex;
}

char * CMutex::GetError(void)
{
	return const_cast<char *>(m_strError.c_str());
}
