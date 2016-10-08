// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#include "CConfig.h"

CConfig::~CConfig()
{
}


char * CConfig::GetError(void)
{
	char *p = const_cast<char *>(m_pError.c_str());
	return p;
}

int CConfig::RenameCofigFile(const string & sNewFile)
{
	m_pFileName = sNewFile;
	return 0;
}

int CConfig::RenameCofigFile(char * pNewFile)
{
	m_pFileName = pNewFile;
	return 0;
}
