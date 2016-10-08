
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "CEventObserver.h"
#include "COutDataWkThreadPool.h"
#include "CReator.h"

// #include "CLog.h"
#include "CLocalThreadLog.h"
#include "CSimpleConfig.h"
#include "CMsgQueue.h"
#include "CImageTrans.h"

class CWkObserver: public CEventObserver
{
public:
	CWkObserver(unsigned int iEvent): CEventObserver(iEvent) {} ;
	~CWkObserver() {};
	int EventProcess(char *pInPara, char *pOutPara=NULL)
	{

//		string picName= "./hello.jpg";
//		exportImage(vigra::srcImageRange(*pInPara), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
		cout<<"threadid="<<pthread_self();
//		printf(" is dealing with \"%s\"\n",pInPara );
		cout << endl;
		return 0;
	}
};


using namespace std;
int main(void)
{
	//-------------------------------------------------------
	// CLog *pLog=new CLocalThreadLog("../log/testThreadLog");
	// pLog->Open();
	// pLog->WriteErrorLog("error log hello ");
	// //----------------------------------------------------------------
	// CConfig *pConfig = CSimpleConfig::GetFirstSingleton("../config/testconfig");
    // pConfig->ParseFile();
	// string a;
	// pConfig->GetParaValue("a", a);
	// cout << "string a = "+a;
	//-----------------------------------------------------------------


    int width = 640;
    int height = 480;
    CMsgQueue * msgQueue=new CMsgQueue(1124);
    CImageTrans* imageTrans=new CImageTrans(width,height,"./image/");
    queue<vigra::BRGBImage*> queue1;
//    vector<vigra::BRGBImage*> vector2;
//    vector<vigra::BRGBImage*> vector3;
//    vector<vigra::BRGBImage*> vector4;
//    vector<vigra::BRGBImage*> vector5;
//    vector<vigra::BRGBImage*> vector6;
    vigra::BRGBImage ** images=NULL;


	int i=1;
	CReator *pReator = CReator::Instance();

	CEventObserver *pObserver = new CWkObserver(i);
	if( !(pReator->RegisterObserver(pObserver->GetEventHandle(), pObserver)) )
	{ cout<<pReator->GetError()<<endl; }


	CThreadPool *pThreadPool = new COutDataWkThreadPool(pReator);
	if( !pThreadPool->Init() )
		{ cout<<"fail in create COutDataWkThreadPool"<<endl; return -1;}

	while(1)
	{
		try
		{
			sleep(2);
			Message tTest;
			// tTest.msg_type=1;
			// snprintf(tTest.pPara,10, "hello %d para from queue",i);
			msgQueue->receiveMsg(&tTest,0);
            cout<<tTest.m_length<<endl;
            imageTrans->transform((const unsigned char *) tTest.pPara);
            queue1.push(imageTrans->getBRGBImage());
            imageTrans->exportAImage();
//            *images=new vigra::BRGBImage[6];
//            while(!queue1.empty()){
//                images[0]=queue1.front();
//            }
//			pThreadPool->DispatchEvent( (void *)imageTrans->getBRGBImage() );

			pThreadPool->DispatchEvent( (void *)&tTest );
			i++;
		}
		catch(CException &ex)
		{ cout<<"======"<<ex.GetError()<<endl;}
	}
	return 0;
}
