// ԭ������Ծǿ
// ���ţ�Ԥ�в�
// ����һ�Դ�������������κ�ʹ���߱��븽�����ߵ�������

#ifndef CEXEPTION_H
#define CEXEPTION_H

#include <iostream>
#include <string>

using namespace std;

class CException
{
public:
	virtual ~CException();
	CException(string sError);
	CException(char *pError);
	char * GetError(void );
	virtual void ProcessExtion();

protected:
	string m_strError;
};

#endif
