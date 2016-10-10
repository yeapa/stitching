
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
	int EventProcess(vector<vigra::BRGBImage*> *pInPara, char *pOutPara=NULL)
	{

//		string picName= "./hello.jpg";
//		exportImage(vigra::srcImageRange(*pInPara), vigra::ImageExportInfo(picName.c_str()).setCompression("80"));
		cout<<"threadid="<<pthread_self()<<"  vectorSize: "<<pInPara->size()<<endl;

        CImageTrans imageTrans(640,480);
        imageTrans.exportAImage(pInPara->front(),"./");
//		printf(" is dealing with \"%s\"\n",pInPara );
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
			sleep(1);
			Message tTest;
            vector<vigra::BRGBImage*> images;
			// tTest.msg_type=1;
			// snprintf(tTest.pPara,10, "hello %d para from queue",i);

            msgQueue->receiveMsg(&tTest,1);
            cout<<tTest.m_msgType<<endl;
            cout<<tTest.m_length<<endl;
            imageTrans->transform((const unsigned char *) tTest.pPara);
            imageTrans->exportAImage();

            images.push_back(imageTrans->getBRGBImage());

//			pThreadPool->DispatchEvent( (void *)imageTrans->getBRGBImage() );

//			pThreadPool->DispatchEvent( (void *)&tTest );
            pThreadPool->DispatchEvent( (void *)&images);
			i++;
		}
		catch(CException &ex)
		{ cout<<"======"<<ex.GetError()<<endl;}
	}
	return 0;
}
