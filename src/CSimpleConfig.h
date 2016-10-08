// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#ifndef CSIMPLECONFIG_H
#define CSIMPLECONFIG_H

#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <stdlib.h>
#include <math.h>
#include "CConfig.h"
using namespace std;
class CSimpleConfig: public CConfig
{
public:
	CSimpleConfig(const string & sFile):CConfig(sFile) { }
	CSimpleConfig(const char *pFile):CConfig(pFile)  { }
	~CSimpleConfig() { }

	int GetLinePara(const string strLine, string & strField, string & strValue);
	virtual int GetConfigLineNum() const ;
        virtual int ParseFile(void);
        virtual int GetParaValue(const string sParaField, string & sParaValue);
        virtual int GetParaValue(const char * pParaField, string & sParaValue);
        virtual int GetParaValue(const string sParaField, int & iParaValue);
        virtual int GetParaValue(const char * pParaField, int & iParaValue);
        virtual int GetParaValue(const string sParaField, double & dbParaValue);
        virtual int GetParaValue(const char * pParaField, double & dbParaValue);
        static CConfig *GetFirstSingleton(const string & sFile="");
        static CConfig *GetFirstSingleton(const char *pFile=NULL);
protected:
	map<string,string>  mapFieldValue;
	static CConfig *m_pThisFirst;
};

#endif
