
#ifndef CANONYMSEM_H
#define CANONYMSEM_H
// �����ڹ��캯���л��׳��쳣
#include <string.h>
#include <error.h>
#include <semaphore.h>
#include <errno.h>
#include "CException.h"

class CAnonymSem
{
public:
	CAnonymSem();
	~CAnonymSem();
	static CAnonymSem *GetFirstSingleton(void);
	int Signal();
	int GetSemValue();
	int Wait();
	char * GetError();

protected:
	string m_strError;
	static CAnonymSem *m_pFirst;
	sem_t m_tSem;
};

#endif
