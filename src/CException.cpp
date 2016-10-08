
#include "CException.h"

CException::CException(char * pError)
{	m_strError = pError; }

CException::~CException()
{}

CException::CException(string sError)
{ m_strError = sError;  }

char * CException::GetError(void)
{ return const_cast<char *>(m_strError.c_str()); }

void CException::ProcessExtion()
{
}
