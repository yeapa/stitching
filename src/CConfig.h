// ԭ������Ծǿ
// ���ţ�Ԥ�в�

#ifndef CCONFIG_H
#define CCONFIG_H
#include <string>
using namespace std;
class CConfig
{
public:
	virtual ~CConfig();
	char * GetError(void);
	int RenameCofigFile(const string & sNewFile);
	int RenameCofigFile(char * pNewFile);
	virtual int ParseFile(void) =0;
	virtual int GetConfigLineNum(void) const=0 ;
	virtual int GetParaValue(const string sParaField, string & sParaValue)=0;
	virtual int GetParaValue(const char * pParaField, string & sParaValue)=0;
	virtual int GetParaValue(const string sParaField, int & iParaValue)=0;
	virtual int GetParaValue(const char * pParaField, int & iParaValue)=0;
	virtual int GetParaValue(const string sParaField, double & dbParaValue)=0;
	virtual int GetParaValue(const char * pParaField, double & dbParaValue)=0;

protected:
	CConfig(const string & sFileName): m_pFileName(sFileName) {}
	CConfig(const char * pFileName): m_pFileName(pFileName) {}
	string m_pFileName;
	string m_pError;
};

#endif
